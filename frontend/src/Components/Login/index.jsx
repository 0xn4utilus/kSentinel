import React, { useState } from 'react';
import { TextField , Button, Typography, Link } from '@material-ui/core';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import { loginTemplate } from '../Themes';

const LoginPage = () => {
  const classes = loginTemplate();
  const [userData,setUserData] = useState({"username":"","password":""});

  function submitData(){

  }

  return (
    <div className={classes.container}>
      <div className={classes.formContainer}>
        <LockOutlinedIcon className={classes.avatar} />
        <Typography component="h1" variant="h5">
          Sign in
        </Typography>
        <TextField
          className={classes.input}
          label="Username"
          name="username"
          onChange={(e)=>{
            setUserData({username:e.target.value,password:userData.password});
          }}
          variant="outlined"
          fullWidth
        />
        <TextField
          className={classes.input}
          label="Password"
          name="password"
          variant="outlined"
          fullWidth
          type="password"
          onChange={(e)=>{
            setUserData({username:userData.username,password:e.target.value});
          }}
        />
        <Button
          className={classes.submitButton}
          variant="contained"
          color="primary"
          fullWidth
          disabled={userData.username.length < 1 || userData.password.length < 1}
          onClick={submitData}
        >
          Submit
        </Button>
        <div className='flex flex-col items-center'>
          <Link href="/forgotPassword">
            Forgot Password?
          </Link>
          <Link href="/register">
            Register Now
          </Link>
        </div>
      </div>
    </div>
  );
};

export default LoginPage;
