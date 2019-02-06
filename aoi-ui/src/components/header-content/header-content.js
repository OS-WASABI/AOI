import React, { Component } from 'react';
import '../../css/header-content.css';
import { connect } from 'react-redux';
import { updateUser } from "../../actions/userActions";

class headerContent extends Component {
    render() {
      return (
        <div className="App">
          <header className="App-header">
            <div className="header-welcome">Welcome <b>{this.props.currUser}</b></div>
            <div>
              <b>OS-WASABI:</b><br/>
              Open Source Warning and Alert Systems A and B Implementation
            </div>
          </header>
        </div>
      );
    }
};


const mapStateToProps = state => ({
  currUser: state.users.allUsers[state.users.currUser].name
})


export default connect(mapStateToProps, { updateUser })(headerContent);