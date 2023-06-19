import React from 'react';
import { makeStyles } from '@material-ui/core/styles';


const loginTemplate = makeStyles((theme) => ({
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
        fontSize:60,
    },
    input: {
        margin: theme.spacing(1),
    },
    submitButton: {
        margin: theme.spacing(2, 0),
    },
}));

const configTemplate = makeStyles((theme) => ({
    pageContainer: {
      backgroundColor: '#FDF6E3',
      minHeight: '100vh',
      display: 'flex',
      flexDirection: 'column',
      alignItems: 'center',
      justifyContent: 'center',
    },
    card: {
      marginBottom: theme.spacing(3),
      padding: theme.spacing(2),
      backgroundColor: '#F3F7F9',
      boxShadow: '0px 3px 6px rgba(0, 0, 0, 0.16)',
      borderRadius: 8,
    },
    title: {
      marginBottom: theme.spacing(2),
      color: '#333333',
      fontWeight: 'bold',
    },
    button: {
      marginRight: theme.spacing(2),
      backgroundColor: 'green',
      color: '#FFFFFF',
      '&:hover': {
        backgroundColor: '#C51162',
      },
    },
    inputField: {
      marginBottom: theme.spacing(2),
    },
    inputContainer: {
      display: 'flex',
      alignItems: 'center',
    },
}))

const footerTemplate = makeStyles((theme) => ({
    footer: {
      backgroundColor: theme.palette.primary.main,
      padding: theme.spacing(2),
      textAlign: 'center',
      color: theme.palette.primary.contrastText,
      marginTop: 'auto',
    },
}));

const navbarTemplate = makeStyles((theme) => ({
    toolbar: {
      display: 'flex',
      justifyContent: 'space-between',
      backgroundColor: '#3f51b5', // Replace with your desired background color
    },
    navbarButton: {
      marginLeft: theme.spacing(2),
    },
    mobileMenuButton: {
      marginRight: theme.spacing(2),
    },
    list: {
      width: 250,
    },
    linkContainer: {
      display: 'flex',
      alignItems: 'center',
    },
}));

export {
    loginTemplate,
    configTemplate,
    footerTemplate,
    navbarTemplate
}