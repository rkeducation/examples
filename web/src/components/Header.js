import React from 'react';

function Header({ setCurrentPage, currentPage }) {
  return (
    <header className="header">
      <div className="logo">OpenSaaS</div>
      <nav>
        <ul>
          <li
            className={currentPage === 'home' ? 'active' : ''}
            onClick={() => setCurrentPage('home')}
          >
            Home
          </li>
          <li
            className={currentPage === 'solutions' ? 'active' : ''}
            onClick={() => setCurrentPage('solutions')}
          >
            Solutions
          </li>
          <li
            className={currentPage === 'pricing' ? 'active' : ''}
            onClick={() => setCurrentPage('pricing')}
          >
            Pricing
          </li>
        </ul>
      </nav>
    </header>
  );
}

export default Header;
