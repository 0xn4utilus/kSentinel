import React from 'react';
import { Typography, Link, makeStyles } from '@material-ui/core';

const useStyles = makeStyles((theme) => ({
  footer: {
    backgroundColor: theme.palette.primary.main,
    padding: theme.spacing(2),
    textAlign: 'center',
    color: theme.palette.primary.contrastText,
    marginTop: 'auto',
  },
}));

const Footer = () => {
  const classes = useStyles();

  return (
    <footer className={classes.footer}>
      <Typography variant="body1">
        Made with{' '}
        <span role="img" aria-label="heart">
          ❤️
        </span>{' '}
        by{' '}
        <Link
          href="https://infoseciitr.in"
          color="inherit"
          target="_blank"
          rel="noopener"
        >
          InfoSecIITR
        </Link>
      </Typography>
    </footer>
  );
};

export default Footer;
