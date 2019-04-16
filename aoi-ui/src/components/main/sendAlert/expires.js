/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file expires.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */

import React, { Component } from 'react';
import DateTime from 'react-datetime';
import '../../../../node_modules/react-datetime/css/react-datetime.css';

class Expires extends Component {
  constructor(props) {
    super(props);
    this.state = {
      expires: new Date()
    }
  }

  render() {
    return (
      <div style={{'marginLeft': 5}}>
        <DateTime
          defaultValue={this.state.expires}
          timeFormat={'HH:mm'}
          onChange={moment => this.props.addAlert(moment.toDate())}/>
      </div>
    );
  }

}

export default Expires;