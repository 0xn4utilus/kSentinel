import React, { useState } from 'react';
import { TextField, Button, Typography, Link } from '@material-ui/core';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import { loginTemplate } from '../Themes';
import { useDispatch } from 'react-redux';
import { setUser } from '../../slices/userSlice';
import { loginRoute } from '../../constants';
import { simpleJsonPost } from '../../helpers/httphelpers';
import { Alert } from '@mui/material';
import { useNavigate } from 'react-router-dom';

const LoginPage = () => {
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const classes = loginTemplate();
  const [userData, setUserData] = useState({ "username": "", "password": "" });
  const [alertSx, setAlertSx] = useState({ "width": "100%", "display": "none" });
  const [alertSeverity, setAlertSeverity] = useState("error");
  const [alertMessage, setAlertMessage] = useState("");

  function closeAlert() {
    setAlertSx({ "width": "100%", "display": "none" });
  }

  async function submitData() {
    let status, data;
    setAlertSx({ "width": "100%", "display": "inherit" });
    setTimeout(() => {
      setAlertSx({ "width": "100%", "display": "none" });
    }, 5000);

    try {
      [status, data] = await simpleJsonPost(loginRoute, userData)
    }
    catch (err) {
      setAlertSeverity("error");
      setAlertMessage(String(err));
      return;
    }
    if (status != 200) {
      setAlertSeverity("error");
      setAlertMessage(data.Message);
    }
    else {
      setAlertSx({ "width": "100%", "display": "none" });
      let token = data.Token;
      dispatch(setUser({
        username: userData.username,
        token: token
      }));
      navigate("/dashboard");
    }
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
          onChange={(e) => {
            setUserData({ username: e.target.value, password: userData.password });
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
          onChange={(e) => {
            setUserData({ username: userData.username, password: e.target.value });
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
        <Alert sx={alertSx} onClose={closeAlert} variant='filled' severity={alertSeverity}>{alertMessage}</Alert>
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
