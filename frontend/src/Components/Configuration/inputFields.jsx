import React from "react";
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

export default function InputFields({ props }) {
    const classes = useStyles();

    function InputBox(props) {
        console.log(props)
        return <Grid item xs={12} sm={6}>
            <TextField
                label={props.label}
                variant="outlined"
                size="small"
                placeholder={props.placeholder}
                fullWidth
                className={classes.textField}
            />
        </Grid>
    }
    return (
        <Grid container spacing={2} className={classes.container}>
            {props.map(item => <InputBox key={Math.random()} {...item}/>)}
            <Grid item xs={12}>
                <Button
                    variant="contained"
                    className={classes.button}
                >
                    Save
                </Button>
            </Grid>
        </Grid>
    );
}
