import React from 'react';
import './styles.css';
import Header from './components/Header';
import Footer from './components/Footer';
import Home from './pages/Home';
import Solutions from './pages/Solutions';
import Pricing from './pages/Pricing';

function App() {
  const [currentPage, setCurrentPage] = React.useState('home');

  const renderPage = () => {
    switch (currentPage) {
      case 'solutions':
        return <Solutions />;
      case 'pricing':
        return <Pricing />;
      default:
        return <Home />;
    }
  };

  return (
    <div className="app">
      <Header setCurrentPage={setCurrentPage} currentPage={currentPage} />
      {renderPage()}
      <Footer />
    </div>
  );
}

export default App;
