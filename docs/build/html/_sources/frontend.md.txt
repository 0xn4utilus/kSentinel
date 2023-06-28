## Frontend

<hr>
kSentinel utilizes the power of React, Redux, and Vite to create a seamless and efficient web application that acts as a control panel for multiple `kSentinel` binaries running on servers, containers, etc.. React serves as the foundation for building dynamic user interfaces, providing a component-based approach that enhances code reusability and modularity. Redux acts as a centralized state management tool, allowing us to manage complex application states with ease and facilitate seamless data flow between components. Vite, our build tool, enables rapid development and hot module replacement, ensuring faster reload times and an optimal developer experience. By combining these cutting-edge technologies, we are able to deliver a high-performance and responsive web application that enhances user interactions and overall efficiency.

<hr>

### Development Mode
- Clone the repository if you haven't already done so : `git clone https://github.com/InfoSecIITR/kSentinel`

- Change the current directory to `kSentinel/frontend`

- Install the dependencies if you haven't already done so: `yarn install`

- Create a .env file in the frontend directory using the following format.
```
VITE_AUTH_API_URL = http://127.0.0.1:8080 
VITE_KSCORE_API_URL = http://127.0.0.1:9000
```
- `VITE_AUTH_API_URL` : Should be the base url of `auth` service.
- `VITE_KSCORE_API_URL` : Should be the base url of `kscore` service.

- Now you're all set. Run the development server: `vite dev`

### Files and Directories

- `frontend/src/Components` : Stores different React components. Each subdirectory in this directory should contain an `index.jsx` file that returns the component. For example:
```js
// frontend/src/Components/sample/index.jsx

export default function TestComponent(){
    return something;
}
```

- `frontend/assets` : Contains assets such as images, icons, etc.

- `frontend/helpers` : Contains commonly used functions or items across multiple components.

- `frontend/slices` : Contains Redux slices for state management.

- `frontend/store` : Redux store

- `frontend/constants.js` : Commonly used constants should be defined here. For example:
```
const authServer = import.meta.env.VITE_AUTH_API_URL;
const kscoreServer = import.meta.env.VITE_KSCORE_API_URL;

// auth service endpoints
export const registerRoute = authServer + "/api/auth/register";
export const loginRoute = authServer+"/api/auth/login";
export const tokenValidationRoute = authServer+"/api/auth/validate";

// kscore service endpoints
export const eventCreationRoute = kscoreServer + "/api/kscore/events";

```

### Routes
- `/dashboard` : kSentinel Dashboard
- `/configuration` : Configuration options for the kSentinel binary
- `/settings` : Settings for kSentinel frontend
- `/login` : Login route
- `/register` : Signup route

