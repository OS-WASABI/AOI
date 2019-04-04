/// Scope widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file scope.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Button from 'react-bootstrap/Button';
import ButtonGroup from "react-bootstrap/ButtonGroup";
import Dropdown from "react-bootstrap/Dropdown";
import DropdownButton from "react-bootstrap/DropdownButton";
import InputGroup from "react-bootstrap/InputGroup";

class Scope extends Component {
  getScopes() {
    return this.props.scopes.map(scope => (
      <Dropdown.Item
        key={scope}
        onClick={()=>this.props.addAlert(scope)}>
        {scope}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <DropdownButton
        as={InputGroup.Append}
        variant={'light'}
        title={this.props.scope}>
        {this.getScopes()}
      </DropdownButton>
    );
  }
}


export default Scope;