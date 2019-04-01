/// Send Live Alert form.
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
    this.state = {
      coordinatePairs: [
        '',
        '',
        '',
        ''
      ]
    };

    this.getPairs = this.getPairs.bind(this);
    this.addPair = this.addPair.bind(this);
    this.removePair = this.removePair.bind(this);
    this.editPair = this.editPair.bind(this);
  }


  getPairs() {
    return this.state.coordinatePairs.map((pair, i) => {
    if (i > 3) {
      return (
        <Col key={i}>
          <InputGroup>
            <Form.Control
              placeholder={(i+1)}
              value={this.state.coordinatePairs[i]}
              onChange={(event) => this.editPair(event.target.value, i)}/>
            <InputGroup.Append>
              <Button
                onClick={()=>this.removePair(i)}
                variant={'secondary'}>
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
            value={this.state.coordinatePairs[i]}
            onChange={(event) => this.editPair(event.target.value, i)}/>
        </Col>
      )
    }
  })}

  addPair() {
    let newPairs = [...this.state.coordinatePairs];
    newPairs.push('');
    this.setState(prevState => ({
      ...prevState,
      coordinatePairs: [...newPairs]
    }))
  }

  editPair(val, i) {
    let newPairs = [...this.state.coordinatePairs];
    newPairs[i] = val;
    this.setState(prevState => ({
      ...prevState,
      coordinatePairs: [...newPairs]
    }))
  }

  removePair(i) {
    let newPairs = [...this.state.coordinatePairs];
    newPairs.splice(i, 1);
    this.setState(prevState => ({
      ...prevState,
      coordinatePairs: [...newPairs]
    }))
  }

  render() {
    return (
      <div id='Polygon'>
        <Form.Row>
          {this.getPairs()}
          <Button
            onClick={()=>this.addPair()}
            variant={"light"}>
            +
          </Button>
        </Form.Row>
      </div>
    );
  }
}


export default Polygon;