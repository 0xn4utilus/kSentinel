import React from 'react';
import {
  Button,
  Card,
  CardContent,
  Grid,
  makeStyles,
  TextField,
  Typography,
} from '@material-ui/core';
import InputFields from './inputFields';

const useStyles = makeStyles((theme) => ({
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
}));

const Tracing = () => {
  const classes = useStyles();

  return (
    <Card className={classes.card}>
      <CardContent>
        <Typography variant="h5" className={classes.title}>
          Tracing
        </Typography>
        <InputFields
          props={[
            { placeholder: 'sys_enter_execve', label: 'sys_enter*' },
            { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' },
            { placeholder: 'prepare_kernel_cred', label: 'kfunction_exit' },
            { placeholder: 'puts', label: 'ufunction_entry' },
            { placeholder: 'puts', label: 'ufunction_exit' },
          ]}
        />
      </CardContent>
    </Card>
  );
};

const Blocking = () => {
  const classes = useStyles();

  return (
    <Card className={classes.card}>
      <CardContent>
        <Typography variant="h5" className={classes.title}>
          Blocking
        </Typography>
        <InputFields
          props={[
            { placeholder: 'sys_enter_execve', label: 'sys_enter*' },
            { placeholder: 'prepare_kernel_cred', label: 'kfunction_entry' },
            { placeholder: 'prepare_kernel_cred', label: 'kfunction_exit' },
            { placeholder: 'puts', label: 'ufunction_entry' },
            { placeholder: 'puts', label: 'ufunction_exit' },
          ]}
        />
      </CardContent>
    </Card>
  );
};

const Info = () => {
  const classes = useStyles();

  return (
    <Card className={classes.card}>
      <CardContent>
        <Typography variant="h5" className={classes.title}>
          Info
        </Typography>
        <Grid container spacing={2}>
          <Grid item xs={12}>
            <Button
              variant="contained"
              className={classes.button}
              fullWidth
            >
              Status
            </Button>
          </Grid>
          <Grid item xs={12}>
            <Button
              variant="contained"
              className={classes.button}
              fullWidth
            >
              KS Config
            </Button>
          </Grid>
        </Grid>
      </CardContent>
    </Card>
  );
};

const Page = () => {
  const classes = useStyles();

  return (
    <div className={classes.pageContainer}>
      <Tracing />
      <Blocking />
      <Info />
    </div>
  );
};

export default Page;
