import React, { useState } from "react";
import { Button, Grid, makeStyles, TextField } from "@material-ui/core";

const useStyles = makeStyles((theme) => ({
  container: {
    display: 'flex',
    alignItems: 'center',
    marginBottom: theme.spacing(2),
  },
  textField: {
    marginRight: theme.spacing(2),
  },
  button: {
    backgroundColor: '#4caf50',
    color: '#ffffff',
    '&:hover': {
      backgroundColor: '#45a049',
    },
  },
}));

const InputBox = React.memo(({label,placeholder,onChange})=>{
    const classes = useStyles();
    return (
        <Grid item xs={12} sm={6}>
            <TextField
            label={label}
            variant="outlined"
            size="small"
            onChange={onChange}
            placeholder={placeholder}
            fullWidth
            className={classes.textField}
            />
        </Grid>
    )
});

export default function InputFields({ props }) {
  const classes = useStyles();
  const [tracingData, setTracingData] = useState({});

  function submitData(){
    
  }
  return (
    <Grid container spacing={2} className={classes.container}>
        {console.log(tracingData)}
      {props.map((item) => (
        <InputBox
            key={item.label}
            label={item.label}
            placeholder={item.placeholder}
            onChange={(e)=>{
                setTracingData((prevData)=>({
                    ...prevData,[item.label]:e.target.value
                }))
            }}
        />
      ))}
      <Grid item xs={12}>
        <Button
          variant="contained"
          className={classes.button}
          onClick={submitData}
        >
          Save
        </Button>
      </Grid>
    </Grid>
  );
}
