/// Polygon widget.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file polygon.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Form from 'react-bootstrap/Form';
import InputGroup from 'react-bootstrap/InputGroup';
import Button from 'react-bootstrap/Button';
import Col from 'react-bootstrap/Col';


class Polygon extends Component {
  constructor(props) {
    super(props);
    this.getPairs = this.getPairs.bind(this);
  }

  getPairs() {
    return this.props.pairs.map((pair, i) => {
    if (i > 3) {
      return (
        <Col key={i}>
          <InputGroup>
            <Form.Control
              placeholder={"Coordinate Pair " + (i+1)}
              value={this.props.pairs[i]}
              onChange={(event) => this.props.editPair(event.target.value, i)}/>
            <InputGroup.Append>
              <Button
                size={'sm'}
                onClick={()=>this.props.removePair(i)}
                variant={'light'}>
                X
              </Button>
            </InputGroup.Append>
          </InputGroup>
        </Col>
      )
    }
    else {
      return (
        <Col key={i}>
          <Form.Control
            placeholder={"Coordinate Pair " + (i+1)}
            value={this.props.pairs[i]}
            onChange={(event) => this.props.editPair(event.target.value, i)}/>
        </Col>
      )
    }
  })}

  render() {
    return (
      <Form.Group controlId={'polygon'}>
        <Form.Row>
          <Form.Label
            column
            style={{"color": "#6c757d"}}
            sm={2}>Area Polygon</Form.Label>
          <Col>
            <Form.Row>
              {this.getPairs()}
              <Button
                onClick={()=>this.props.addPair()}
                variant={"light"}>
                +
              </Button>
            </Form.Row>
          </Col>
        </Form.Row>
        </Form.Group>
    );
  }
}


export default Polygon;