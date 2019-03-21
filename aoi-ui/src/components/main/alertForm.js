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
import InputGroup from 'react-bootstrap/InputGroup';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import Button from 'react-bootstrap/Button';
import DropdownButton from 'react-bootstrap/DropdownButton';
import Dropdown from 'react-bootstrap/Dropdown';
import Nav from 'react-bootstrap/Nav';
import Col from 'react-bootstrap/Col';

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
  ],
  scopes: [
    'Public',
    'Restricted',
    'Private'
  ],
  types: [
    'Alert',
    'Update',
    'Cancel',
    'Ack',
    'Error'
  ],
  statuses: [
    'Actual',
    'Exercise',
    'System',
    'Test',
    'Draft'
  ]
}

class AlertForm extends Component {
  constructor(props) {
    super(props);
    this.state = {
      categories: [],
      severity: 'Severity',
      urgency: 'Urgency',
      certainty: 'Certainty',
      scope: 'Scope',
      type:'Type',
      status:'Status',

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

  getStatuses() {
    return options.statuses.map(status => (
      <Dropdown.Item
        onClick={()=>this.selection('status', status)}>
        {status}
      </Dropdown.Item>
    ))
  }

  getTypes() {
    return options.types.map(type => (
      <Dropdown.Item
        onClick={()=>this.selection('type', type)}>
        {type}
      </Dropdown.Item>
    ))
  }

  getScopes() {
    return options.scopes.map(scope => (
      <Dropdown.Item
        onClick={()=>this.selection('scope', scope)}>
        {scope}
      </Dropdown.Item>
    ))
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
          variant={'secondary'}
          style={{'marginLeft':10}}>
          {category}
        </Button>
        <Button
          variant={'secondary'}
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
          <h1>Send Alert</h1>
          <Form>
            <Form.Row>
              <Form.Group>
                <DropdownButton title={this.state.status} variant={'light'}>
                  {this.getStatuses()}
                </DropdownButton>
              </Form.Group>
              <Form.Group style={{'marginLeft':10}}>
                <DropdownButton title={this.state.type} variant={'light'}>
                  {this.getTypes()}
                </DropdownButton>
              </Form.Group>
            </Form.Row>
            <Form.Group controlId={'event'}>
              <Form.Row>
              <Form.Label column sm={2}>Event Title</Form.Label>
              <Col>
                <InputGroup>
                  <Form.Control placeholder={'Event Title'} type={'text'}/>
                  <DropdownButton
                    as={InputGroup.Append}
                    variant={'light'}
                    title={this.state.urgency}>
                    {this.getUrgencies()}
                  </DropdownButton>
                  <DropdownButton
                    as={InputGroup.Append}
                    variant={'light'}
                    title={this.state.certainty}>
                    {this.getCertainties()}
                  </DropdownButton>
                  <DropdownButton
                    as={InputGroup.Append}
                    variant={'light'}
                    title={this.state.scope}>
                    {this.getScopes()}
                  </DropdownButton>
                </InputGroup>
              </Col>
              </Form.Row>
            </Form.Group>
            <Form.Group controlId={'severity'}>
              <Form.Row>
              <Form.Label column sm={2}>Severity</Form.Label>
              <ButtonGroup>
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
                  variant={'outline-info'}
                  onClick={()=>this.selection('severity','Moderate')}
                  active={this.state.severity==='Moderate'}>
                  Moderate
                </Button>
                <Button
                  variant={'outline-primary'}
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
              </Form.Row>
            </Form.Group>
            <Form.Group controlId={'category'}>
              <Form.Row>
              <Form.Label column sm={2}>Category</Form.Label>
                <DropdownButton
                  variant={'light'}
                  title={'Choose'}>
                {this.getCategories()}
              </DropdownButton>
              {this.showCategories()}
              </Form.Row>
            </Form.Group>
            <Form.Group controlId={'area'}>
              <Form.Row>
                <Form.Label column sm={2}>Area</Form.Label>
                <Col>
                  <Form.Control placeholder={'Description'} type={'text'}/>
                </Col>
              </Form.Row>
            </Form.Group>
          </Form>
        </Container>
      </div>
    );
  }

};

export default AlertForm;