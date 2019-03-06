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
import {
  BrowserRouter as Router,
  Route,
  Switch
} from 'react-router-dom';
import Header from './components/header/header';
import Home from './components/main/home';
import Alerts from './components/main/alerts';

class App extends Component {
  render() {
    return (
        <div className="App">
          <Router>
            <div>
              <Header/>
              <Switch>
                <Route exact path={'/'} component={Home}/>
                <Route path={'/alerts'} component={Alerts}/>
              </Switch>
            </div>

          </Router>
        </div>
    );
  }
}

export default App;
