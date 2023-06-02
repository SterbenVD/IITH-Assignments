import React, { useState, useEffect, useReducer } from "react";
import axios from "axios";
import url from "../../url";

function useGetPostDetails({ postID, type }) {
  const [data, setData] = useState({
    title: "",
    body: "",
    score: "",
    creation_date: "",
    owner_display_name: "",
    owner_user_id: "",
    tags: "",
    anscount: "",
  });
  const reducer = (state, action) => {
    switch (action.type) {
      case "home":
        return {
          title: action.payload.title,
          body: action.payload.body,
          score: action.payload.score,
          creation_date: action.payload.creation_date,
          owner_display_name: action.payload.owner_display_name,
          owner_user_id: action.payload.owner_user_id,
          tags: action.payload.tags,
          anscount: action.payload.anscount,
        };
      case "question":
        return {
          title: action.payload.title,
          body: action.payload.body,
          score: action.payload.score,
          creation_date: action.payload.creation_date,
          owner_display_name: action.payload.owner_display_name,
          owner_user_id: action.payload.owner_user_id,
          tags: action.payload.tags,
          anscount: action.payload.anscount,
          last_edit_date: action.payload.last_edit_date,
        };

      case "answer":
        return {
          title: action.payload.title,
          display_id: action.payload.display_id,
          display_name: action.payload.display_name,
          body: action.payload.body,
          score: action.payload.score,
          creation_date: action.payload.creation_date,
          owner_display_name: action.payload.owner_display_name,
          owner_user_id: action.payload.owner_user_id,
          tags: action.payload.tags,
          anscount: action.payload.anscount,
          parent_id: action.payload.parent_id,
        };
      case "comment":
        return {
          title: action.payload.title,
          body: action.payload.body,
          creation_date: action.payload.creation_date,
          owner_display_name: action.payload.owner_display_name,
          owner_user_id: action.payload.owner_user_id,
          text: action.payload.text,
          parent_id: action.payload.parent_id,
        };
    }
  };

  const [state, dispatch] = useReducer(reducer, {
    title: "",
    body: "",
    score: "",
    creation_date: "",
    owner_display_name: "",
    owner_user_id: "",
    tags: "",
    anscount: "",
  });

  useEffect(() => {
    // console.log(state);
  }, [state]);

  const datagen = async () => {
    if (type != "comment") {
      let res = await axios.get(`${url.axios_url}/post/${postID}`);
      // console.log(res);
      if (type == "question" || type == "home") {
        axios
          .get(`${url.axios_url}/user/${res.data.owner_user_id}`)
          .then((res2) => {
            // console.log(res2);
            dispatch({
              type: type,
              payload: {
                title: res.data.title,
                body: res.data.body,
                score: res.data.score,
                creation_date: res.data.creation_date,
                owner_display_name: res2.data.display_name,
                owner_user_id: res.data.owner_user_id,
                tags: res.data.tags,
                anscount: 10,
                last_edit_date: res.data.last_edit_date
                  ? res.data.last_edit_date
                  : res.data.creation_date,
              },
            });
          });
      } else if (type == "answer") {
        // console.log(`${url.axios_url}/post/${res.data.parent_id}`);
        // console.log(res);
        let user = await axios.get(
          `${url.axios_url}/user/${res.data.owner_user_id}`
        );
        // console.log(user);
        let res2 = await axios.get(
          `${url.axios_url}/post/${res.data.parent_id}`
        );
        // console.log(res2);
        let res3 = await axios.get(
          `${url.axios_url}/user/${res2.data.owner_user_id}`
        );
        dispatch({
          type: type,
          payload: {
            display_name: user.data.display_name,
            display_id: res.data.owner_user_id,
            title: res2.data.title,
            body: res.data.body,
            score: res.data.score,
            creation_date: res.data.creation_date,
            owner_user_id: res3.data.owner_user_id,
            owner_display_name: res3.data.display_name,
            tags: res.data.tags,
            anscount: 10,
            parent_id: res.data.parent_id,
          },
        });
      }
    } else {
      let res = await axios.get(`${url.axios_url}/comment/${postID}`);
      // console.log(res);
      let post = await axios.get(`${url.axios_url}/post/${res.data.post_id}`);
      if (post.data.parent_id) {
        post = await axios.get(`${url.axios_url}/post/${post.data.parent_id}`);
      }
      // console.log(post);
      let user = await axios.get(`${url.axios_url}/user/${res.data.user_id}`);
      // console.log(user);
      dispatch({
        type: type,
        payload: {
          title: post.data.title,
          body: post.data.body,
          text: res.data.text,
          creation_date: res.data.creation_date,
          owner_user_id: res.data.user_id,
          owner_display_name: user.data.display_name,
          parent_id: post.data.id,
        },
      });
    }
  };

  useEffect(() => {
    datagen();
  }, []);
  return state;
}

export default useGetPostDetails;
