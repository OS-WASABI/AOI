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

    this.onChange = this.onChange.bind(this);
  }

  onChange = (moment) => {
    try {
      let date = moment.toDate();
      this.props.addAlert(date);
    } catch {}
  }

  render() {
    return (
      <div style={{'marginLeft': 5}}>
        <DateTime
          defaultValue={this.state.expires}
          timeFormat={'HH:mm'}
          onChange={this.onChange}/>
      </div>
    );
  }

}

export default Expires;