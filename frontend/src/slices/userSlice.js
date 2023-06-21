import {createSlice} from "@reduxjs/toolkit";

export const userSlice = createSlice({
    name:"user",
    initialState:{
        "username":"",
        "token":""
    },
    reducers:{
        setUser:(state,action)=>{
            state.username = action.payload.username
            state.token = action.payload.token
        }
    }
});

export default userSlice.reducer;
export const {setUser} = userSlice.actions;
export const selectUser = (state)=>state.user.username;
export const selectToken = (state)=>state.user.token;