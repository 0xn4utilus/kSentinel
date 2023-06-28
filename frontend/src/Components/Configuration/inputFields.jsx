import React, { createContext, useContext, useState } from "react";
import { Button, Grid, makeStyles, MenuItem, Select, TextField } from "@material-ui/core";
import { simpleJsonPost } from "../../helpers/httphelpers";
import { eventCreationRoute } from "../../constants";

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
    backgroundColor: '#ff4081',
    color: '#ffffff',
    '&:hover': {
      backgroundColor: '#f50057',
    },
    borderRadius: theme.spacing(1), // Added border radius to match the box
    padding: theme.spacing(1, 4), // Adjusted padding for better button proportions
    textTransform: 'none', // Prevent text transformation
    fontWeight: 'bold', // Added font weight for emphasis
    boxShadow: 'none', // Removed box shadow
  },
  boxContainer: {
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
    padding: theme.spacing(2),
    border: "1px solid #f06292",
    borderRadius: theme.spacing(1),
    backgroundColor: '#fce4ec',
  },
}));

const InputBox = React.memo(({ label, placeholder, type, handleChange }) => {
  const classes = useStyles();
  return (
    <Grid item xs={12} sm={6}>
      <div className={classes.boxContainer}>
        <TextField
          label={label}
          placeholder={placeholder}
          className={classes.textField}
          variant="outlined"
          onChange={(e) => handleChange(e, label)}
        />
        <TextField
          label="message"
          placeholder={`Custom error message`}
          className={classes.textField}
          variant="outlined"
          onChange={(e) => handleChange(e, label + "-message")}
        />
      </div>
    </Grid>
  );
});

export default function InputFields({ props }) {
  const classes = useStyles();
  const [data, setData] = useState({});

  function handleChange(e, label) {
    setData((prevData) => ({
      ...prevData,
      [label]: e.target.value,
    }));
  }

  async function submitData(deviceId) {
    const type = props[0].type;
    const events = Object.keys(data).filter(key=>!key.includes("message"));
    const finalData = [];
    let messageKey;
    for(let event of events){
      messageKey = event+"-message";
      finalData.push({"type":event,"name":data[event],"message":data[messageKey]==undefined?"":data[messageKey],"mode":type});
    }
    const route = eventCreationRoute+"/"+deviceId;
    const [status,resp] = await simpleJsonPost(route,finalData,"text");
    if(status!=200){
      console.log("Failed to post events");
    }
    else{
      console.log(resp);
    }
  }

  return (
    <Grid container spacing={2} className={classes.container}>
      {props.map((item) => (
        <InputBox key={item.label} label={item.label} placeholder={item.placeholder} type={item.type} handleChange={handleChange} />
      ))}
      <Grid item xs={12}>
        <Button
          variant="contained"
          className={classes.button}
          onClick={()=>submitData("root_8933919957")}
        >
          Save
        </Button>
      </Grid>
    </Grid>
  );
}
