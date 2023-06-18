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
import { configTemplate } from '../Themes';

const Tracing = () => {
  const classes = configTemplate();

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
  const classes = configTemplate();

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
  const classes = configTemplate();

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
  const classes = configTemplate();

  return (
    <div className={classes.pageContainer}>
      <Tracing />
      <Blocking />
      <Info />
    </div>
  );
};

export default Page;
