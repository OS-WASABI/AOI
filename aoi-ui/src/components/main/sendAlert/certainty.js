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
import DropdownButton from "react-bootstrap/DropdownButton";
import InputGroup from "react-bootstrap/InputGroup";

class Certainty extends Component {
  getCertainties() {
    return this.props.certainties.map(certainty => (
      <Dropdown.Item
        key={certainty}
        onClick={()=>this.props.addInfo(certainty)}>
        {certainty}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <DropdownButton
        as={InputGroup.Append}
        variant={'light'}
        title={this.props.certainty}>
        {this.getCertainties()}
      </DropdownButton>
    );
  }
}


export default Certainty;