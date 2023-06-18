import React, { useState } from 'react';
import { TextField , Button, Typography, Link } from '@material-ui/core';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import { loginTemplate } from '../Themes';
import CheckCircleOutlinedIcon from '@mui/icons-material/CheckCircleOutlined';
import ErrorOutlineOutlinedIcon from '@mui/icons-material/ErrorOutlineOutlined';

const ForgotPassword = () =>{
    const classes = loginTemplate();
    const [userData,setUserData] = useState({"data":""});
    const [isDataSent, setDataSent] = useState(false);
    const [isDataValid, setValidity] = useState(true);

    function queryData(){
        // setDataSent(true);
        // setValidity(false);
    }


    return(
        <div className={classes.container}>
            {
                !isDataSent && (
                    <div className={classes.formContainer}>
                        {
                            isDataValid &&(
                                <LockOutlinedIcon className={classes.avatar} style={{fontSize:60}}/>
                            )}
                        {
                            !isDataValid && (
                                <div className="flex flex-col items-center">
                                    <ErrorOutlineOutlinedIcon className={classes.avatar} style={{fontSize:60}}/>
                                    <Typography component="h1" variant="h4">
                                        User Not found
                                    </Typography>
                                </div>
                            )
                        }
                        <Typography component="h1" variant="h5">
                        Enter Username or Email
                        </Typography>
                        <TextField
                            className={classes.input}
                            label="Username / Email"
                            name="username"
                            onChange={(e)=>{
                                setUserData({data:e.target.value});
                            }}
                            variant="outlined"
                            fullWidth
                            />
                        <Button
                        className={classes.submitButton}
                        variant="contained"
                        color="primary"
                        fullWidth
                        disabled = {userData.data.length < 1}
                        onClick={queryData}
                        >
                        Submit
                        </Button>
                    </div>
            )}
            {
                isDataSent && (
                    <div className={classes.formContainer}>
                        <CheckCircleOutlinedIcon className={classes.avatar} style={{fontSize:60}}/>
                        <Typography component="h1" variant="h4">
                            Password Reset Sucessful.
                        </Typography>
                        <Typography component="h3" variant="h5">
                            Please check email to find the reset link.
                        </Typography>
                    </div>
            )}
        </div>
    )
}

export default ForgotPassword