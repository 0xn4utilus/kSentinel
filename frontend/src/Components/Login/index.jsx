import React from 'react';
import { TextField, Box, Button, Typography } from '@material-ui/core';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import { makeStyles } from '@material-ui/core/styles';

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

const LoginPage = () => {
  const classes = useStyles();

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
        />
        <Button
          className={classes.submitButton}
          variant="contained"
          color="primary"
          fullWidth
        >
          Submit
        </Button>
      </div>
    </div>
  );
};

export default LoginPage;
