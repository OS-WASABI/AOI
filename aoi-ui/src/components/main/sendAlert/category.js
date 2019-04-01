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
import Col from "react-bootstrap/Col";
import Form from "react-bootstrap/Form";

class Category extends Component {
  getCategories() {
    return this.props.categories.map(category => (
      <Dropdown.Item
        key={category}
        disabled={this.props.category.includes(category)}
        onClick={() => this.props.pushInfoSelection(category)}>
        {category}
      </Dropdown.Item>
    ))
  }

  showCategories() {
    return this.props.category.map((category, i) => (
      <ButtonGroup key={i}>
        <Button
          variant={'secondary'}
          style={{'marginLeft': 10, 'marginBottom': 10}}>
          {category}
        </Button>
        <Button
          variant={'secondary'}
          style={{'marginBottom': 10}}
          onClick={() => this.props.popInfoSelection(category)}>
          X
        </Button>
      </ButtonGroup>
    ))
  }

  render() {
    return (
      <Form.Group controlId={'category'}>
        <Form.Row>
          <Form.Label column sm={2}>Category</Form.Label>
          <Col sm={2}>
            <DropdownButton
              variant={'light'}
              title={'Choose'}>
              {this.getCategories()}
            </DropdownButton>
          </Col>
          <Col>
            {this.showCategories()}
          </Col>
      </Form.Row>
      </Form.Group>
    )
  }
}

export default Category;