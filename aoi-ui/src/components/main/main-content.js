import React from 'react';
import {Route} from "react-router-dom";
import '../../css/main-content.css';
import Home from './home';
import Test from './test';

const mainContent = () => {
    return (
      <div className="App">
        <Route path="/" component={Home}/>
        <Route path="/test" component={Test}/>
      </div>
    );
};

export default mainContent;