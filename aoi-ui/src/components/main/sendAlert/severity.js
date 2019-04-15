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
import Form from "react-bootstrap/Form";

class Severity extends Component {
  render() {
    return (
      <Form.Group controlId={'severity'}>
        <Form.Row>
          <Form.Label
            column
            style={{"color": "#6c757d"}}
            sm={2}>Severity</Form.Label>
          <ButtonGroup style={{'marginLeft': 5}}>
            <Button
              variant={'outline-danger'}
              onClick={()=>this.props.addInfo('Extreme')}
              active={this.props.severity==='Extreme'}>
              Extreme
            </Button>
            <Button
              variant={'outline-warning'}
              onClick={()=>this.props.addInfo('Severe')}
              active={this.props.severity==='Severe'}>
              Severe
            </Button>
            <Button
              variant={'outline-info'}
              onClick={()=>this.props.addInfo('Moderate')}
              active={this.props.severity==='Moderate'}>
              Moderate
            </Button>
            <Button
              variant={'outline-primary'}
              onClick={()=>this.props.addInfo('Minor')}
              active={this.props.severity==='Minor'}>
              Minor
            </Button>
            <Button
              variant={'outline-secondary'}
              onClick={()=>this.props.addInfo('Unknown')}
              active={this.props.severity==='Unknown'}>
              Unknown
            </Button>
          </ButtonGroup>
        </Form.Row>
      </Form.Group>
    );
  }
}


export default Severity;