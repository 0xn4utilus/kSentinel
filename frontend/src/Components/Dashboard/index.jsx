import React,{useEffect} from "react";
import Layout from "../Layout";
import { simpleGet } from "../../helpers/httphelpers";
import { tokenValidationRoute } from "../../constants";
import {selectUser,selectToken} from "../../slices/userSlice";
import {useDispatch, useSelector} from "react-redux";
import { setUser } from "../../slices/userSlice";
import { useNavigate } from "react-router-dom";

export default function Dashboard(){
    const token = useSelector(selectToken);
    const dispatch = useDispatch();
    const navigate = useNavigate();

    useEffect(()=>{
        const url = tokenValidationRoute+`/${token}`;
        simpleGet(url).then((data)=>{
            if(data[0]!=200){
                dispatch(setUser({
                    username:"",
                    token:""
                }));
                navigate("/") ;
            }
        })
    },[])
    return <Layout>
        
    </Layout>
}