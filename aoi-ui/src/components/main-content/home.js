import React from "react";

const Home = () => {
  return (
    <div className="Home">
    <header className="Home">
      <h1>Welcome!</h1>
      <h2>Please sign in:</h2><br/>
      Username: <input/><br/>
      Password: <input type="password"/><br/>
      <button formAction="POST">Login</button>
    </header>
  </div>);
};

export default Home;