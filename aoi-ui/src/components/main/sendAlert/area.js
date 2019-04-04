/// Area widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file area.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Button from 'react-bootstrap/Button';
import ButtonGroup from "react-bootstrap/ButtonGroup";
import Dropdown from "react-bootstrap/Dropdown";
import DropdownButton from "react-bootstrap/DropdownButton";
import Form from "react-bootstrap/Form";
import Col from "react-bootstrap/Col";

class Area extends Component {
  render() {
    return (
      <div id={'area'}>
        <Form.Group controlId={'areaDesc'}>
          <Form.Row>
            <Form.Label column sm={2}>Area</Form.Label>
            <Col>
              <Form.Control placeholder={'Description'} type={'text'}/>
            </Col>
          </Form.Row>
        </Form.Group>
        {this.props.children}
      </div>
    );
  }
}


export default Area;