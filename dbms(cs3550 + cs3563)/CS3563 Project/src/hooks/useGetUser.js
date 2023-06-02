import React, { useState, useEffect } from "react";
import axios from "axios";
import url from "../../url";
import { useSearchParams, useParams } from "react-router-dom";

function useGetUser() {
  const params = useParams();
  const [searchParams, setSearchParams] = useSearchParams();
  const [user, setUser] = useState({
    userName: "",
    userProfilePic: "/man.png",
    details: {
      display_name: "",
      upvotes: "",
      downvotes: "",
      quescount: "",
      anscount: "",
      comments: "",
      location: "",
      website: "",
      aboutMe: "",
    },
  });
  useEffect(() => {
    let id = searchParams.get("uid") ? searchParams.get("uid") : params.userID;
    axios.get(`${url.axios_url}/user/${id}`).then((res) => {
      //   console.log(res);
      setUser({
        userName: res.data.display_name,
        userProfilePic: res.data.profile_image_url,
        details: {
          display_name: res.data.display_name,
          upvotes: res.data.up_votes,
          downvotes: res.data.down_votes,
          location: res.data.location,
          website: res.data.website_url,
          aboutMe: res.data.about_me,
        },
      });
    });
  }, []);
  return user;
}

export default useGetUser;
