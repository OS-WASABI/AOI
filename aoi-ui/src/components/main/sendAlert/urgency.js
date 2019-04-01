/// Severity widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file severity.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Button from 'react-bootstrap/Button';
import ButtonGroup from "react-bootstrap/ButtonGroup";
import Dropdown from "react-bootstrap/Dropdown";
import InputGroup from "react-bootstrap/InputGroup";
import DropdownButton from "react-bootstrap/DropdownButton";

class Certainty extends Component {
  getUrgencies() {
    return this.props.urgencies.map(urgency => (
      <Dropdown.Item
        key={urgency}
        onClick={()=>this.props.addInfo('urgency', urgency)}>
        {urgency}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <DropdownButton
        as={InputGroup.Append}
        variant={'light'}
        title={this.props.urgency}>
        {this.getUrgencies()}
      </DropdownButton>
    );
  }
}


export default Certainty;