import React, { useEffect, useState,useRef } from 'react'
import styles from './DetailedPost.module.css'
import {Link, useSearchParams,useParams } from 'react-router-dom'
import {ArrowUp,ArrowDown,Pencil} from 'phosphor-react'
import Comment from '../comment/Comment'
import useGetPostDetails from '../../hooks/useGetPostDetails'
import getParsedTime from '../../../time'
import axios from 'axios'
import url from '../../../url'

function DetailedPost({type,postID}) {

    const [param,setParams] = useSearchParams()
    const login=param.get("login")
    const state = useGetPostDetails({postID:postID,type:type})
    const [time,setTime] = useState('')
    const [tagList,setTagList] = useState([])
    const [profileimage,setprofileimage] = useState('/man.png')
    const [editTime,setEditTime] = useState('')
    const [commentList,setCommentList] = useState([])
    const [commentLength,setCommentLength] = useState(0)
    const [more,setMore] = useState("more")
    const [allComments,setAllComments] = useState([])
    const urlparams = useParams()
    const [link,setLink] = useState('')
    const [voteCast,setVoteCast] = useState('false');
    const [voteCount,setVoteCount] =useState(0)


    useEffect(()=>{
        setVoteCount(state.score)
    },[state])

    useEffect(()=>{
        axios.get(`${url.axios_url}/vote/${param.get('uid').split('@')[1]}/${postID}`).then((res)=>{
            console.log(res)
            if(res.data[0])
                {
                    if(res.data[0].vote_type_id==2)
                        setVoteCast('upvote')
                    else
                        setVoteCast('downvote')
                }
            console.log(voteCast)
        })
    },[])

    useEffect(()=>{
        console.log(voteCast)
    },[voteCast])
    const upvote = async ()=>{
        const token = document.cookie
        // console.log(token)
        if(voteCast!='false'){
            //reset
            console.log("here")
            let data = {
                post_id: postID,
                user_id: param.get('uid').split('@')[1],
                vote_type_id: 2,
                token: token
            }
            let res = await axios.delete(`${url.axios_url}/vote/${param.get('uid').split('@')[1]}/${postID}`,{data:{token:token,vote_type_id:2}})
            console.log(res)
            let res2 = await axios.post(`${url.axios_url}/vote`,data)
            console.log(res2)
            setVoteCount((old)=>{
                if(voteCast=='upvote')
                    return old
                else
                    return old +2
            })
            setVoteCast((old)=>{
                if(old!='upvote')
                    return 'upvote'
                else 
                    return old
            })
        }
        else{
            setVoteCast('upvote')
            console.log(voteCast)
            let data = {
                post_id: postID,
                user_id: param.get('uid').split('@')[1],
                vote_type_id: 2,
                token: token
            }
            let res = await axios.post(`${url.axios_url}/vote`,data)
            console.log(res)
            setVoteCount((old)=>{
                old+1
            })

        }
    }

    const downvote = async ()=>{
        const token = document.cookie
        // console.log(token)
        if(voteCast!='false'){
            //reset
            console.log("here")
            let data = {
                post_id: postID,
                user_id: param.get('uid').split('@')[1],
                vote_type_id: 3,
                token: token
            }
            let res = await axios.delete(`${url.axios_url}/vote/${param.get('uid').split('@')[1]}/${postID}`,{data:{token:token,vote_type_id:3}})
            console.log(res)
            let res2 = await axios.post(`${url.axios_url}/vote`,data)
            console.log(res2)
            setVoteCount((old)=>{
                if(voteCast=='upvote')
                    return old
                else
                    return old -2
            })
            setVoteCast((old)=>{
                if(old!='downvote')
                    return 'upvote'
                else 
                    return old
            })
        }
        else{
            console.log("downvote")
            setVoteCast('downvote')
            // console.log(voteCast)
            let data = {
                post_id: postID,
                user_id: param.get('uid').split('@')[1],
                vote_type_id: 3,
                token: token
            }
            let res = await axios.post(`${url.axios_url}/vote`,data)
            console.log(res)
            setVoteCount((old)=>{
                old-1
            })

        }
    }


    const getComments = async ()=>{
        let res = await axios.get(`${url.axios_url}/comment/parent/${postID}/creation_date/asc`)
    
        if(res.data.length>5)
            setCommentLength(5)
        else 
            setCommentLength(res.data.length)
        setCommentList(res.data.slice(0,commentLength))
        setAllComments(res.data)

    }


    useEffect(()=>{
        // console.log(state)
        // console.log(postID)
        getParsedTime(state,setTime)
        if(type=='question')
        {
            axios.get(`${url.axios_url}/user/${state.owner_user_id}`).then((res)=>{
            if(res.data.profile_image_url) setprofileimage(res.data.profile_image_url)})
        }
        else{
            axios.get(`${url.axios_url}/user/${state.display_id}`).then((res)=>{
                if(res.data.profile_image_url) setprofileimage(res.data.profile_image_url)
            }) 
        }
        if(type=='question')
            getParsedTime({creation_date:state.last_edit_date},setEditTime)
        if(type=="question"&&state.tags)
        {
          let taglist = state.tags.split('>')
          let taglength = state.tags.split('>').length-1;
        taglist = taglist.slice(0,taglength)
        setTagList(taglist.map(tag=>tag.replace('<','')))
        }
        getComments()
        if(type=='question')
            setLink(`/user/${param.get('uid')}/questions/${postID}/edit`)
        else
            setLink(`/user/${param.get('uid')}/answers/${postID}/edit`)   
    },[state])
    const handleMore = ()=>{
        if(more=='more')
        {
            setMore('less')
            setCommentLength(allComments.length)
            setCommentList(allComments)
        }
        else
           { 
            setMore('more')
            if(allComments.length>5){
                setCommentLength(5)
            }
            else
            {
                setCommentLength(allComments.length)
            }
            setCommentList(allComments.slice(0,commentLength))
        }
        
    }

    const [comment,setComment] =useState('')
    const commentRef = useRef(null)

    const handleComment =async()=>{
        // console.log(comment)
        let token = document.cookie
        const data = {
            text: comment,
            post_id: postID,
            user_id: param.get('uid').split('@')[1],
            user_display_name: param.get('uid').split('@')[0],
            token: token
        }

        let res = await axios.post(`${url.axios_url}/comment`,data)
        console.log(res)
    }
  return (
    <div className={styles.postcontainer}>
            <div>
                <div>
                {type=="question" && <h2>{state.title}</h2>}
{                type=="question"&& <div className={styles.header}><span className={styles.headertext} style={{paddingLeft:"1%"}}><span style={{color:"#919090",paddingRight:"0.7%"}}>Added</span> {time}</span><span className={styles.headertext}><span style={{color:"#919090",paddingRight:"0.7%"}}>Modified</span>{editTime}</span></div>
}                <hr />
                <div className={styles.questionbody}>
                    <div className={styles.left}>
                    <div className={styles.count}>
        <ArrowUp size={35} onClick={upvote} color="#2a00fa" weight='bold' style={{marginLeft: "33.5%",cursor:"pointer"}} />
          <div className={styles.votes}>
              {voteCount}
          </div>
          <ArrowDown size={35} onClick={downvote} color="#fa0000" weight='bold' style={{marginLeft: "33.5%",cursor:"pointer"}} />
          {login=="true" &&param.get('uid')==postID && <Link to={link}>
          <Pencil size={35} color="#b5a4a3" weight='light' style={{marginLeft: "33.5%",cursor:"pointer",marginTop:"10%"}}/>
          </Link>}

        </div>
                    </div>
                <div className={styles.right} style={{minWidth:"90%"}}>                
                    <div style={{width:"100%"}} dangerouslySetInnerHTML={{__html:state.body}} className={styles.quesbody}></div>
                    <div>
                        {type=="question" && <div style={{marginBottom:"2%",marginTop:"2%"}}>
                        
                        {tagList.map(tag=>{
                            return <span key={tag} className={styles.tagitem}>{tag}</span>
                        })}
                        </div>}
                    </div>
                    <div className={styles.footer}>
                        <div className={styles.piccontainer} style={{display:"flex"}}>
                            <img src={profileimage}alt="" className={styles.pic}/>
                            
                        </div>
                        <div style={{marginLeft:"5%",fontSize:"17px", color:"#919090s",minWidth:"25%"}}>
                            {type=="question"?"Asked by":"Answered by"}: <span style={{color:"black",marginLeft:"5%"}}>{type=="question"?state.owner_display_name:state.display_name}</span>
                        </div>
                        <div style={{marginLeft:"5%",fontSize:"17px", color:"#919090s",minWidth:"25%"}}>
                            On: <span style={{color:"black",marginLeft:"5%"}}>{time}</span>
                        </div>
                    </div>
                    <hr />

                    <div className={styles.commentcontainer}>
                        {
                            <div>
                        {
                            commentList.map((comment)=>{
                                // console.log(comment)
                                return <Comment key={comment.id} id={comment.id}/>
                            })
                        }
                        </div>}
                        <div style={{textAlign:"center",cursor:"pointer"}} onClick={handleMore}>
                            Show {more}
                        </div>
                        
                        
                        <div><textarea ref={commentRef} onChange={()=>{setComment(commentRef.current.value)}} name="Add comment" id="" cols="30" rows="2" style={{borderStyle:"none",width:"100%"}} placeholder={"Add a comment..."}></textarea> <button className="btn-primary btn" onClick={handleComment}>Comment</button> </div>
                    </div>
                </div>
            </div>
        </div>
        </div>
        <hr />
        </div>
  )
}

export default DetailedPost
