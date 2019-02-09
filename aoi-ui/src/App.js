/// The root of the GUI.
/**
 * This class represents the highest-level component of the GUI.
 * It wraps the components of the application in a Provider component
 * so they can connect to the centralized store if needed.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file App.js
 * @date January 2018
 * @authors Ross Arcemont, Vaniya Agrawal
 */
import React, { Component } from 'react';
import './css/App.css';
import HeaderContent from './components/header-content/header-content';
import Sidebar from './components/sidebar/sidebar';
import MainContent from './components/main-content/main-content'

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
