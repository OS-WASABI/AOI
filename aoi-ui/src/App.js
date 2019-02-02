import React, { Component } from 'react';
import logo from './img/logo.svg';
import './css/App.css';
import HeaderContent from './header-content/header-content';
import Sidebar from './sidebar/sidebar';
import MainContent from './main-content/main-content'

class App extends Component {
  render() {
    return (
      <div className="App">
          <HeaderContent/>
          <Sidebar/>
          <MainContent/>
      </div>
    );
  }
}

export default App;
