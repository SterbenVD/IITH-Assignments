import React,{useEffect, useState} from 'react'
import styles from './Comment.module.css'
import useGetPostDetails from '../../hooks/useGetPostDetails'
import getParsedTime from '../../../time'

function Comment({id}) {
  const state = useGetPostDetails({postID:id,type:"comment"})
  const [time,setTime] = useState()

  useEffect(()=>{
    getParsedTime(state,setTime)
  },[state])
  return (
    <div className={styles.container} style={{backgroundColor:"#f7f3f2",paddingTop:"1%",paddingBottom:"1%"}}>
      <div className={styles.left}>
        
      </div>
      <div className={styles.right}>
        <span style={{marginRight:"5%"}}>{state.text}</span><span style={{color:"blue",cursor:"pointer",marginRight:"2%"}}>-{state.owner_display_name}</span> <span style={{color:"#9e9a99"}}>{time}</span>
      </div>
      <hr />
    </div>
  )
}

export default Comment
