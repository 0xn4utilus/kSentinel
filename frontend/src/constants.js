const authServer = import.meta.env.VITE_AUTH_API_URL;
export const registerRoute = authServer + "/api/auth/register";
export const loginRoute = authServer+"/api/auth/login";
export const tokenValidationRoute = authServer+"/api/auth/validate"