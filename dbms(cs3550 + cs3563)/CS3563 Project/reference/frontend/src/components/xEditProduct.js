/* eslint-disable react-hooks/exhaustive-deps */
import { useState, useEffect } from 'react'
import axios from "axios";
import { useNavigate, useParams } from 'react-router-dom';
const EditProduct = () => {
   const [title, setTitle] = useState('');
   const [price, setPrice] = useState('');
   const history = useNavigate();
   const { id } = useParams();
   const updateProduct = async (e) => {
       e.preventDefault();
       await axios.patch(`http://192.168.51.xx:5000/products/${id}`, {
           title: title,
           price: price
       });
       history.push("/");
   }
   useEffect(() => {
       getProductById();
   }, []);
   const getProductById = async () => {
       const response = await axios.get(`http://192.168.51.xx:5000/products/${id}`);
       setTitle(response.data.title);
       setPrice(response.data.price);
   }
   return (
       <div>
           <form onSubmit={updateProduct}>
               <div className="field">
                   <label className="label">Title</label>
                   <input
                       className="input"
                       type="text"
                       placeholder="Title"
                       value={title}
                       onChange={(e) => setTitle(e.target.value)}
                   />
               </div>
               <div className="field">
                   <label className="label">Price</label>
                   <input
                       className="input"
                       type="text"
                       placeholder="Price"
                       value={price}
                       onChange={(e) => setPrice(e.target.value)}
                   />
               </div>
               <div className="field">
                   <button className="button is-primary">Update</button>
               </div>
           </form>
       </div>
   )
}
export default EditProduct
