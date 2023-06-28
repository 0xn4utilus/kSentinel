const authServer = import.meta.env.VITE_AUTH_API_URL;
const kscoreServer = import.meta.env.VITE_KSCORE_API_URL;

// auth service endpoints
export const registerRoute = authServer + "/api/auth/register";
export const loginRoute = authServer+"/api/auth/login";
export const tokenValidationRoute = authServer+"/api/auth/validate";

// kscore service endpoints
export const eventCreationRoute = kscoreServer + "/api/kscore/events";
