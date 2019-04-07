/// Scope widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file scope.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Dropdown from "react-bootstrap/Dropdown";
import DropdownButton from "react-bootstrap/DropdownButton";
import Form from "react-bootstrap/Form";

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
      <Form.Group controlId={'scope'} style={{'marginLeft':10}}>
        <DropdownButton
          variant={'light'}
          title={this.props.scope}>
          {this.getScopes()}
        </DropdownButton>
      </Form.Group>
    );
  }
}


export default Scope;