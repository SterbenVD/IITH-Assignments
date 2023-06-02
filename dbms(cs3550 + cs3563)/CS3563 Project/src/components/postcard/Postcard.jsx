import React, { useEffect, useState } from "react";
import useGetUser from "../../hooks/useGetUser";
import styles from "./Postcard.module.css";
import { ChatCenteredText } from "phosphor-react";
import { ArrowUp, ArrowDown, Check, Trash, PencilSimple } from "phosphor-react";
import { Link, useParams, useSearchParams } from "react-router-dom";
import useGetPostDetails from "../../hooks/useGetPostDetails";
import DOMPurify from "dompurify";
import url from "../../../url.js";
import axios from "axios";

function Postcard({ type, accepted, postID}) {
  const state = useGetPostDetails({ postID: postID,type:type });
  const [tags, setTags] = useState([]);
  const [link,setLinks] = useState('')
  const getTags = () => {
    setTags(() => {
      const temp = state.tags
        .trim()
        .replace(/>/gi, ",")
        .replace(/</gi, "")
        .split(",");
      return temp.slice(0, temp.length - 1);
    });
  };

  const [time, setTime] = useState("");
  const getTime = () => {
    let date = new Date(state.creation_date);
    let current = new Date();
    if (
      date.getFullYear() + 1 < current.getFullYear() ||
      (date.getFullYear() + 1 == current.getFullYear() &&
        date.getMonth() < current.getMonth())
    )
      setTime(
        (current.getFullYear() - date.getFullYear()).toString() + "yrs ago"
      );
    else if (date.getMonth() != current.getMonth())
      setTime(
        (current.getMonth() - date.getMonth() + 12).toString() + "months ago"
      );
    else if (date.getDate() != current.getDate())
      setTime((current.getDate() - date.getDate()).toString() + "days ago");
    else if (date.getHours() != current.getHours())
      setTime((current.getHours() - date.getHours()).toString() + "hrs ago");
    else if (date.getMinutes() != current.getMinutes())
      setTime(
        (current.getMinutes() - date.getMinutes()).toString() + "minutes ago"
      );
    else
      setTime(
        (current.getSeconds() - date.getSeconds()).toString() + "seconds ago"
      );
  };

  const [profilePic, setProfilePic] = useState("/man.png");

  const getProfilePic = () => {
    if(state.owner_user_id){
      axios.get(`${url.axios_url}/user/${state.owner_user_id}`).then((res) => {
        // console.log(res);
        if (res.data.profile_image_url) setProfilePic(res.data.profile_image_url);
      });
    }
  };
  const params = useParams();
  const [searchParams,setSearchParams] = useSearchParams()
  const userID = searchParams.get('uid')?searchParams.get('uid'):params.userID
  const login = 

  useEffect(() => {
    console.log(state)
    if(type=='question'||type=='home')
      {
        if(searchParams.get('login')=='true'||params.userID)
          setLinks(`/posts/${postID}?login=true&uid=${userID}`)
        else 
          setLinks(`/posts/${postID}?login=false`)

      }
    else if(type=='answer'||type=='comment'){
      setLinks(`/posts/${state.parent_id}?login=true&uid=${userID}`)
    }
    if(state.tags)
      getTags();
    getTime();
    getProfilePic();
  }, [state]);



  return (
    
    <div className={styles.container}>
      <div className={styles.votecount}>
        <div className={styles.count}>
          <ArrowUp
            size={36}
            color="#2a00fa"
            weight="bold"
            style={{ marginLeft: "32%" }}
          />
          <div className={styles.votes}>{state.score}</div>
          <ArrowDown
            size={36}
            color="#fa0000"
            weight="bold"
            style={{ marginLeft: "32%" }}
          />
        </div>
        {type == "answer" && accepted == "true" && (
          <>
            <Check
              size={36}
              color="#02ac16"
              weight="bold"
              style={{ marginLeft: "30%", marginTop: "32%" }}
            />
          </>
        )}
      </div>
      <div className={styles.right}>
      <Link to={link} style={{textDecoration:"none",color:"black"}}><div className={styles.title}>{state.title}</div></Link>
        <div>
          <div className={styles.text}>
            <div
              className={styles.texttwo}
              dangerouslySetInnerHTML={{
                __html: DOMPurify.sanitize(state.body),
              }}
            ></div>
            <br />
            {tags.map((tag) => {
              return (
                <span className={styles.tagitem} key={tag}>
                  {tag}
                </span>
              );
            })}
          {
            type=="comment" && <>
            <h4 style={{color: "black"}}>Comment:</h4>
            <div>
              {state.text}
            </div>
            </>
          }
            <hr className={styles.footerline} />


          </div>
        </div>

        <div className={styles.footer}>
          <div className={styles.profilepicture}>
            <div className={styles.picture}>
              <div className={styles.dp}>
                <img src={profilePic} alt="" className={styles.itemimage} />
              </div>
            </div>
            <div className={styles.name}>
              Posted By:{" "}
              {state.owner_display_name == null
                ? "[DELETED]"
                : state.owner_display_name}
            </div>
          </div>
          <div className={styles.time}>{time}</div>
          <div className={styles.responses}>
            <ChatCenteredText size={32} color="#812222" />
            <div>{state.anscount}</div>
          </div>
        </div>
      </div>
      {type != "home" && type != "comment" && (
        <div className={styles.options}>
          <div className={styles.optionicon}>
            <Trash
              size={25}
              color="#b80000"
              weight="bold"
              style={{ cursor: "pointer" }}
            />
          </div>
          <div className={styles.optionicon}>
            {
              type=="question"?<Link
              to={`/${params.userID}/questions/${postID}/edit`}
              className={styles.linkstyle}
            >
              <PencilSimple
                size={25}
                color="#2b3b8c"
                weight="bold"
                style={{ cursor: "pointer" }}
              />
            </Link>:<Link
              to={`/${params.userID}/answers/${postID}/edit`}
              className={styles.linkstyle}
            >
              <PencilSimple
                size={25}
                color="#2b3b8c"
                weight="bold"
                style={{ cursor: "pointer" }}
              />
            </Link>
            }
            
          </div>
        </div>
      )}
    </div>
    
  )
}

export default Postcard;
