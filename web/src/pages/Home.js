import React from 'react';
import Hero from '../components/Hero';
import BenefitTile from '../components/BenefitTile';

function Home() {
  const benefits = [
    { icon: '💰', title: 'Save Money', description: 'One-time setup beats monthly subscriptions.' },
    { icon: '🔒', title: 'Stay in Control', description: 'Host on your servers for privacy.' },
    { icon: '⚙️', title: 'No Tech Skills Needed', description: 'Our dashboard simplifies everything.' },
    { icon: '🧠', title: 'AI-Powered (Soon)', description: 'Smart features to boost efficiency.' },
  ];

  return (
    <main>
      <Hero
        headline="Affordable SaaS Alternatives for Your Business"
        subheadline="Deploy open-source tools on your servers with ease—save costs, stay secure, and simplify workflows."
        ctaText="Get Started Free"
        ctaAction={() => alert('Sign up for a pilot! Contact us at [your-email].')}
      />
      <section className="benefits">
        <h2>Why OpenSaaS?</h2>
        <div className="benefits-grid">
          {benefits.map((benefit, index) => (
            <BenefitTile key={index} {...benefit} />
          ))}
        </div>
      </section>
      <section className="showcase">
        <h2>Nextcloud: Your Starting Point</h2>
        <p>Secure, self-hosted file storage—deployed fast, managed simply.</p>
        <button onClick={() => alert('Demo coming soon!')}>Watch Demo</button>
      </section>
    </main>
  );
}

export default Home;
