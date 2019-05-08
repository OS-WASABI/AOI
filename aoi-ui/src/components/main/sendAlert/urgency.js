/// Urgency widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file urgency.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Dropdown from "react-bootstrap/Dropdown";
import DropdownButton from "react-bootstrap/DropdownButton";
import Form from "react-bootstrap/Form";

class Certainty extends Component {
  getUrgencies() {
    return this.props.urgencies.map(urgency => (
      <Dropdown.Item
        key={urgency}
        onClick={()=>this.props.addInfo(urgency)}>
        {urgency}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <Form.Group controlId={'urgency'} style={{'marginLeft':5}}>
        <DropdownButton
          variant={'light'}
          title={this.props.urgency}>
          {this.getUrgencies()}
        </DropdownButton>
      </Form.Group>
    );
  }
}


export default Certainty;