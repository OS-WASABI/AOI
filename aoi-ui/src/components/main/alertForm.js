/// Send Live Alert form.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertForm.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import Form from 'react-bootstrap/Form';
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import InputGroup from 'react-bootstrap/InputGroup';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import Button from 'react-bootstrap/Button';
import DropdownButton from 'react-bootstrap/DropdownButton';
import Dropdown from 'react-bootstrap/Dropdown';
import Nav from 'react-bootstrap/Nav';

const options = {
  categories: [
    'Geo',
    'Met',
    'Safety',
    'Security',
    'Rescue',
    'Fire',
    'Health',
    'Env',
    'Transport',
    'Infra',
    'CBRNE',
    'Other'
  ],
  urgencies: [
    'Immediate',
    'Expected',
    'Future',
    'Past',
    'Unknown'
  ],
  certainties: [
    'Observed',
    'Likely',
    'Possible',
    'Unlikely',
    'Unknown'
  ]
}

class AlertForm extends Component {
  constructor(props) {
    super(props);
    this.state = {
      categories: [],
      severity: 'Severity',
      urgency: 'Urgency',
      certainty: 'Certainty'
    };
    this.selection = this.selection.bind(this);
    this.pushSelection = this.pushSelection.bind(this);
    this.popSelection = this.popSelection.bind(this);
  }

  popSelection(name, value) {
    console.log(this.state[name]);
    let option = [...this.state[name]];
    for(let i=0; i<option.length; i++) {
      if(option[i] === value) {
        option.splice(i,1);
      }
    }
    this.setState(prevState => ({
      ...prevState,
      [name]: [...option]
    }))
  }

  pushSelection(name, value) {
    if(!this.state[name].includes(value)) {
      this.setState(prevState => ({
        ...prevState,
        [name]: [...prevState[name], value]
      }))
    }
  }

  selection(name, value) {
    this.setState(prevState => ({
      ...prevState,
      [name]: value,
    }))
  }

  getUrgencies() {
    return options.urgencies.map(urgency => (
      <Dropdown.Item
        onClick={()=>this.selection('urgency', urgency)}>
        {urgency}
      </Dropdown.Item>
    ))
  }

  getCertainties() {
    return options.certainties.map(certainty => (
      <Dropdown.Item
        onClick={()=>this.selection('certainty', certainty)}>
        {certainty}
      </Dropdown.Item>
    ))
  }

  getCategories() {
    return options.categories.map(category => (
      <Dropdown.Item
        disabled={this.state.categories.includes(category)}
        onClick={()=>this.pushSelection('categories', category)}>
        {category}
      </Dropdown.Item>
    ))
  }

  showCategories() {
    return this.state.categories.map((category, i) => (
      <ButtonGroup key={i}>
        <Button
          variant={'dark'}
          style={{'marginLeft':10}}>
          {category}
        </Button>
        <Button
          variant={'dark'}
          onClick={()=>this.popSelection('categories', category)}>
          X
        </Button>
      </ButtonGroup>
    ))
  }

  render() {
    return (
      <div id='Alerts'>
        <br/><br/><br/>
        <Container>
          <h1>Send Live Alert</h1>
          <br/>
          <Form>
            <Form.Group controlId={'event'}>
              <Form.Label>Event Title</Form.Label>
              <InputGroup>
                <Form.Control placeholder={'Event Title'} type={'text'}/>
                <DropdownButton as={InputGroup.Append} variant={'outline-secondary'} title={this.state.urgency}>
                  {this.getUrgencies()}
                </DropdownButton>
                <DropdownButton as={InputGroup.Append} variant={'outline-secondary'} title={this.state.certainty}>
                  {this.getCertainties()}
                </DropdownButton>
              </InputGroup>
            </Form.Group>
            <Form.Group>
              <Form.Row>
              <DropdownButton variant={'outline-secondary'} title={'Choose Categories'}>
                {this.getCategories()}
              </DropdownButton>
              {this.showCategories()}
              </Form.Row>
            </Form.Group>
            <Form.Group>
              <Form.Label>Severity</Form.Label>
              <ButtonGroup style={{'marginLeft':20}}>
                <Button
                  variant={'outline-danger'}
                  onClick={()=>this.selection('severity','Extreme')}
                  active={this.state.severity==='Extreme'}>
                  Extreme
                </Button>
                <Button
                  variant={'outline-warning'}
                  onClick={()=>this.selection('severity','Severe')}
                  active={this.state.severity==='Severe'}>
                  Severe
                </Button>
                <Button
                  variant={'outline-primary'}
                  onClick={()=>this.selection('severity','Moderate')}
                  active={this.state.severity==='Moderate'}>
                  Moderate
                </Button>
                <Button
                  variant={'outline-success'}
                  onClick={()=>this.selection('severity','Minor')}
                  active={this.state.severity==='Minor'}>
                  Minor
                </Button>
                <Button
                  variant={'outline-secondary'}
                  onClick={()=>this.selection('severity','Unknown')}
                  active={this.state.severity==='Unknown'}>
                  Unknown
                </Button>
              </ButtonGroup>
            </Form.Group>
            <Form.Group controlId={'area'}>
              <Form.Label>Area</Form.Label>
              <Nav variant={'tabs'}>
                <Nav.Item>
                  <Nav.Link>Polygon</Nav.Link>
                </Nav.Item>
                <Nav.Item>
                  <Nav.Link>Geocode</Nav.Link>
                </Nav.Item>
                <Nav.Item>
                  <Nav.Link>Circle</Nav.Link>
                </Nav.Item>
                <Nav.Item>
                  <Nav.Link>Description</Nav.Link>
                </Nav.Item>
              </Nav>
            </Form.Group>

          </Form>
        </Container>
      </div>
    );
  }

};

export default AlertForm;