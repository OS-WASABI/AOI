import React, { Component } from 'react';
import { Provider } from 'react-redux';
import './css/App.css';
import HeaderContent from './components/header-content/header-content';
import Sidebar from './components/sidebar/sidebar';
import MainContent from './components/main-content/main-content'
import store from './store';

class App extends Component {
  render() {
    return (
      <Provider store={store}>
        <div className="App">
            <HeaderContent/>
            <Sidebar/>
            <MainContent/>
        </div>
      </Provider>
    );
  }
}

export default App;
