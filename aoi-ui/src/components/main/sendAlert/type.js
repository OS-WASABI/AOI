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
import Form from "react-bootstrap/Form";

class Type extends Component {
  getTypes() {
    return this.props.types.map(type => (
      <Dropdown.Item
        key={type}
        onClick={()=>this.props.addAlert(type)}>
        {type}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <Form.Group controlId={'type'} style={{'marginLeft':10}}>
        <DropdownButton title={this.props.type} variant={'light'}>
          {this.getTypes()}
        </DropdownButton>
      </Form.Group>
    );
  }
}


export default Type;