import Footer from "../Footer"
import Navbar from "../Navbar"
import AuthChecker from "../Authchecker";

const styles = {
    container: {
        display: 'flex',
        flexDirection: 'column',
        minHeight: '100vh',
    },
    content: {
        flex: 1,
    },
};

export default function Layout({ children }) {
    return <div style={styles.container}>
        <Navbar/>
        <AuthChecker/>
        <div style={styles.content}>
            {children}
        </div>
        <Footer />
    </div>
}