import React, { useEffect } from "react";
import { simpleGet } from "../../helpers/httphelpers";
import { tokenValidationRoute } from "../../constants";
import {selectUser,selectToken} from "../../slices/userSlice";
import {useDispatch, useSelector} from "react-redux";
import { setUser } from "../../slices/userSlice";
import { useLocation, useNavigate } from "react-router-dom";

export default function AuthChecker(){
    const token = useSelector(selectToken);
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const location = useLocation();

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
            else{
                if(location.pathname=="/"){
                    navigate("/dashboard");
                }
            }
        })
    },[]);
    return <React.Fragment>

    </React.Fragment>
}