import {BrowserRouter,Routes,Route} from "react-router-dom";
import Login from "./Components/Login";
import Register from "./Components/Register";
import Configuration from "./Components/Configuration";
import Dashboard from "./Components/Dashboard";
import Settings from "./Components/Settings";
import ForgotPassword from "./Components/ForgotPassword";
import Home from "./Components/Home";

function App() {

  return (
    <>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Home/>}/>
          <Route path="/login" element={<Login/>}/>
          <Route path="/register" element={<Register/>}/>
          <Route path="/forgotPassword" element={<ForgotPassword/>}/>
          <Route path="/configuration" element={<Configuration/>}/>
          <Route path="/dashboard" element={<Dashboard/>}/>
          <Route path="/settings" element={<Settings/>}/>
        </Routes>
      </BrowserRouter>
    </>
  )
}

export default App
