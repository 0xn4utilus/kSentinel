export const simpleJsonPost = async(url,body,responseMode)=>{
    const response = await fetch(url,{
        method:"POST",
        headers:{
            "Content-Type":"application/json"
        },
        body:JSON.stringify(body)
    });
    if(responseMode=="json"){
        return [response.status,await response.json()];
    }
    return [response.status,await response.text()];
}

export const simpleGet = async(url)=>{
    const response = await fetch(url);
    return [response.status,await response.text()];
}