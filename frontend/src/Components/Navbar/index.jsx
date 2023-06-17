import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import {
  AppBar,
  Toolbar,
  Typography,
  Button,
  IconButton,
  Drawer,
  List,
  ListItem,
  ListItemText,
  useMediaQuery,
  useTheme,
  Avatar,
} from '@material-ui/core';
import { Dashboard, Settings, Build, Menu } from '@material-ui/icons';
import { navbarTemplate } from '../Themes';

const Navbar = () => {
  const classes = navbarTemplate();
  const theme = useTheme();
  const isSmallScreen = useMediaQuery(theme.breakpoints.down('sm'));
  const [mobileMenuOpen, setMobileMenuOpen] = useState(false);

  const handleMobileMenuToggle = () => {
    setMobileMenuOpen(!mobileMenuOpen);
  };

  const renderDesktopButtons = () => {
    if (isSmallScreen) {
      return null;
    }

    return (
      <div className={classes.linkContainer}>
        <Button color="inherit" component={Link} to="/dashboard" className={classes.navbarButton}>
          <Dashboard style={{ marginRight: 5 }} />
          Dashboard
        </Button>
        <Button color="inherit" component={Link} to="/configuration" className={classes.navbarButton}>
          <Build style={{ marginRight: 5 }} />
          Configuration
        </Button>
        <Button color="inherit" component={Link} to="/settings" className={classes.navbarButton}>
          <Settings style={{ marginRight: 5 }} />
          Settings
        </Button>
      </div>
    );
  };

  const renderMobileMenu = () => (
    <Drawer anchor="right" open={mobileMenuOpen} onClose={handleMobileMenuToggle}>
      <List className={classes.list}>
        <ListItem button component={Link} to="/dashboard" onClick={handleMobileMenuToggle}>
          <ListItemText primary="Dashboard" />
        </ListItem>
        <ListItem button component={Link} to="/configuration" onClick={handleMobileMenuToggle}>
          <ListItemText primary="Configuration" />
        </ListItem>
        <ListItem button component={Link} to="/settings" onClick={handleMobileMenuToggle}>
          <ListItemText primary="Settings" />
        </ListItem>
      </List>
    </Drawer>
  );

  return (
    <AppBar position="sticky">
      <Toolbar className={classes.toolbar}>
        <Typography variant="h6">
          <div>
          <Avatar src='kslogo1.png'/>
          kSentinel
          </div>
        </Typography>
        {isSmallScreen ? (
          <>
            <IconButton
              color="inherit"
              edge="end"
              onClick={handleMobileMenuToggle}
              className={classes.mobileMenuButton}
            >
              <Menu />
            </IconButton>
            {renderMobileMenu()}
          </>
        ) : (
          renderDesktopButtons()
        )}
      </Toolbar>
    </AppBar>
  );
};

export default Navbar;
