import React from 'react';
import { Typography, Link } from '@material-ui/core';
import { footerTemplate } from '../Themes';

const Footer = () => {
  const classes = footerTemplate();

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
