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
import Form from "react-bootstrap/Form";
import DropdownButton from "react-bootstrap/DropdownButton";

class Status extends Component {
  getStatuses() {
    return this.props.statuses.map(status => (
      <Dropdown.Item
        key={status}
        onClick={()=>this.props.addAlert(status)}>
        {status}
      </Dropdown.Item>
    ))
  }

  render() {
    return (
      <Form.Group controlId={'status'}>
        <DropdownButton title={this.props.status} variant={'light'}>
          {this.getStatuses()}
        </DropdownButton>
      </Form.Group>
    );
  }
}


export default Status;