export const simpleJsonPost = async(url,body)=>{
    const response = await fetch(url,{
        method:"POST",
        headers:{
            "Content-Type":"application/json"
        },
        body:JSON.stringify(body)
    });
    return [response.status,await response.json()];
}

export const simpleGet = async(url)=>{
    const response = await fetch(url);
    return [response.status,await response.text()];
}