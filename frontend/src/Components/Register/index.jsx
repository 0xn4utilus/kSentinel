import React, { useState } from 'react';
import { TextField, Box, Button, Typography, Snackbar } from '@material-ui/core';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import { makeStyles } from '@material-ui/core/styles';
import { registerRoute } from '../../constants';
import Alert from "@mui/material/Alert";
import Stack from "@mui/material/Stack";
import {useNavigate} from "react-router-dom";

const useStyles = makeStyles((theme) => ({
    container: {
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '100vh',
        background: `linear-gradient(to right, ${theme.palette.primary.main}, ${theme.palette.secondary.main})`,
    },
    formContainer: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        padding: theme.spacing(2),
        borderRadius: theme.spacing(1),
        boxShadow: '0px 0px 10px rgba(0, 0, 0, 0.1)',
        backgroundColor: 'rgba(255, 255, 255, 0.8)',
    },
    avatar: {
        margin: theme.spacing(1),
        backgroundColor: theme.palette.primary.main,
    },
    input: {
        margin: theme.spacing(1),
    },
    submitButton: {
        margin: theme.spacing(2, 0),
    },
}));

const Register = () => {
    const navigate = useNavigate();
    const classes = useStyles();
    const [userData, setUserData] = useState({ username: "", password: "", email: "" });
    const [emailError, setEmailError] = useState(false);
    const [submitDisabled, setSubmitDisabled] = useState(true);
    const [alertSeverity, setAlertSeverity] = useState("error");
    const [alertMessage, setAlertMessage] = useState("");
    const [alertSx,setAlertSx] = useState({ "width": "100%","display":"none" });

    async function submitData() {
        setTimeout(()=>{
            setAlertSx({ "width": "100%","display":"none" });
        },5000);
        setAlertSeverity("warning");
        if (userData.username.length === 0) {
            setAlertMessage("Username cannot be empty");
        }
        else if (userData.email.length === 0) {
            setAlertMessage("Email cannot be empty");
        }
        else if (userData.password.length === 0) {
            setAlertMessage("Password cannot be empty");
        }
        const resp = await fetch(registerRoute, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(userData)
        });
        const data = await resp.text();
        if (data == "Registration successful") {
            setAlertSeverity("success");
            setAlertMessage("Registration successful");
            setTimeout(()=>{
                navigate("/login");
            },2000)
        }
        else {
            setAlertSeverity("error");
            setAlertMessage(data);
        }
        setAlertSx({ "width": "100%","display":"inherit" });
    }

    function validateEmail() {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(userData.email)) {
            setEmailError(true);
            setSubmitDisabled(true);
        }
        else {
            setEmailError(false);
            validateData();
        }
    }

    function validateData() {
        if (userData.username.length === 0 || userData.password.length === 0 || userData.email.length === 0) {
            setSubmitDisabled(true);
            return false;
        }
        else {
            setSubmitDisabled(false);
            return true;
        }
    }

    function closeAlert() {
        setAlertSx({ "width": "100%","display":"none" });
    }

    return (
        <div className={classes.container}>
            <div className={classes.formContainer}>
                <LockOutlinedIcon className={classes.avatar} />
                <Typography component="h1" variant="h5">
                    Register
                </Typography>
                <TextField
                    className={classes.input}
                    label="Username"
                    name="username"
                    variant="outlined"
                    onChange={(e) => {
                        setUserData({ username: e.target.value, password: userData.password, email: userData.email });
                        validateData();
                    }}
                    fullWidth
                />
                <TextField
                    className={classes.input}
                    label="Email"
                    name="email"
                    variant="outlined"
                    onChange={(e) => {
                        setUserData({ username: userData.username, email: e.target.value, password: userData.password })
                        validateEmail();
                    }}
                    error={emailError}

                    fullWidth
                />
                <TextField
                    className={classes.input}
                    label="Password"
                    name="password"
                    variant="outlined"
                    onChange={(e) => {
                        setUserData({ username: userData.username, email: userData.email, password: e.target.value })
                        validateData();
                    }}
                    fullWidth
                    type="password"
                />

                <Button
                    className={classes.submitButton}
                    variant="contained"
                    color="primary"
                    fullWidth
                    disabled={submitDisabled}
                    onClick={submitData}
                >
                    Submit
                </Button>
                <Alert sx={alertSx} onClose={closeAlert}  variant='filled' severity={alertSeverity}>{alertMessage}</Alert>

            </div>
        </div>
    );
};

export default Register;
