/// Category widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file category.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Button from 'react-bootstrap/Button';
import ButtonGroup from "react-bootstrap/ButtonGroup";
import Dropdown from "react-bootstrap/Dropdown";
import SplitButton from "react-bootstrap/SplitButton";
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
          variant={'light'}
          style={{'marginLeft': 10, 'marginBottom': 10}}>
          {category}
        </Button>
        <Button
          size={'sm'}
          variant={'light'}
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
          <Form.Label
            column
            style={{"color": "#6c757d"}}
            sm={2}>Category</Form.Label>
          <Col sm={2}>
            <SplitButton
              drop={'right'}
              variant={'light'}
              title={'Choose'}>
              {this.getCategories()}
            </SplitButton>
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