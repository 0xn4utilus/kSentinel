import Footer from "../Footer"
import Navbar from "../Navbar"

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
        <div style={styles.content}>
            {children}
        </div>
        <Footer />
    </div>
}