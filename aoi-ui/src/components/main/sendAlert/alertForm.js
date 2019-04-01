/// Send Live Alert form.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertForm.js
 * @date March 2019
 * @authors Vaniya Agrawal
 */
import React, { Component } from 'react';
import { connect } from 'react-redux';
import { bindActionCreators } from 'redux';
import { sendAlert } from "../../../actions/alertActions";
import Form from 'react-bootstrap/Form';
import Container from 'react-bootstrap/Container';
import InputGroup from 'react-bootstrap/InputGroup';
import Button from 'react-bootstrap/Button';
import Col from 'react-bootstrap/Col';

import Polygon from './polygon';
import Severity from './severity';
import Status from './status';
import Type from './type';
import Scope from './scope';
import Certainty from "./certainty";
import Urgency from "./urgency";
import Category from "./category";
import Area from "./area";

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
};

class AlertForm extends Component {
  constructor(props) {
    super(props);
    this.state = {
      alert: {
        sender: "dummy-sender",
        status: "Status",
        msgType: "Message Type",
        scope: "Scope",
        info: {
          category: [],
          event: "",
          urgency: "Urgency",
          severity: "Severity",
          certainty: "Certainty",
          area: {
            areaDesc: "",
            polygon: [
              '',
              '',
              '',
              ''
            ]
          }
        }
      }
    };
    this.addInfo = this.addInfo.bind(this);
    this.addAlert = this.addAlert.bind(this);
    this.pushInfoSelection = this.pushInfoSelection.bind(this);
    this.popInfoSelection = this.popInfoSelection.bind(this);

    this.addPolygonPair = this.addPolygonPair.bind(this);
    this.editPolygonPair = this.editPolygonPair.bind(this);
    this.removePolygonPair = this.removePolygonPair.bind(this);

  }

  popInfoSelection(name, value) {
    let option = [...this.state.alert.info[name]];
    for(let i=0; i<option.length; i++) {
      if(option[i] === value) {
        option.splice(i,1);
      }
    }
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        info: {
          ...prevState.alert.info,
          [name]: [...option]
        }
      }
    }))
  }

  pushInfoSelection(name, value) {
    if(!this.state.alert.info[name].includes(value)) {
      this.setState(prevState => ({
        ...prevState,
        alert: {
          ...prevState.alert,
          info: {
            ...prevState.alert.info,
            [name]: [...prevState.alert.info[name], value]
          }
        }
      }))
    }
  }

  addAlert(name, value) {
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        [name]: value
      },
    }))
  }

  addInfo(name, value) {
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState["alert"],
        info: {
          ...prevState.alert.info,
          [name]: value
        }
      },
    }))
  }



  addPolygonPair() {
    let newPairs = [...this.state.alert.info.area.polygon];
    newPairs.push('');
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        info: {
          ...prevState.alert.info,
          area: {
            ...prevState.alert.info.area,
            polygon: [...newPairs]
          }
        }
      }
    }))
  }

  editPolygonPair(val, i) {
    let newPairs = [...this.state.alert.info.area.polygon];
    newPairs[i] = val;
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        info: {
          ...prevState.alert.info,
          area: {
            ...prevState.alert.info.area,
            polygon: [...newPairs]
          }
        }
      }
    }))
  }

  removePolygonPair(i) {
    let newPairs = [...this.state.alert.info.area.polygon];
    newPairs.splice(i, 1);
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        info: {
          ...prevState.alert.info,
          area: {
            ...prevState.alert.info.area,
            polygon: [...newPairs]
          }
        }
      }
    }))
  }

  render() {
    return (
      <div id='Alerts'>
        <br/><br/><br/>
        <Container>
          <h1>Send Alert</h1>
          <Form>
            <Form.Row>
              <Status
                status={this.state.alert.status}
                statuses={options.statuses}
                addAlert={alert=>this.addAlert('status', alert)}/>
              <Type
                type={this.state.alert.msgType}
                types={options.types}
                addAlert={alert=>this.addAlert('msgType', alert)}/>
            </Form.Row>
            <br/>
            <Form.Group controlId={'event'}>
              <Form.Row>
              <Form.Label column sm={2}>Event Title</Form.Label>
              <Col>
                <InputGroup>
                  <Form.Control placeholder={'Event Title'} type={'text'}/>
                    <Urgency
                      urgency={this.state.alert.info.urgency}
                      urgencies={options.urgencies}
                      addInfo={(name, val)=>this.addInfo(name,val)}/>
                    <Certainty
                      certainty={this.state.alert.info.certainty}
                      certainties={options.certainties}
                      addInfo={info=>this.addInfo('certainty',info)}/>
                    <Scope
                      scope={this.state.alert.scope}
                      scopes={options.scopes}
                      addAlert={alert=>this.addAlert('scope', alert)}/>
                </InputGroup>
              </Col>
              </Form.Row>
            </Form.Group>
            <Severity
              severity={this.state.alert.info.severity}
              addInfo={info=>this.addInfo('severity', info)}/>
            <Category
              category={this.state.alert.info.category}
              categories={options.categories}
              pushInfoSelection={info=>this.pushInfoSelection('category',info)}
              popInfoSelection={info=>this.popInfoSelection('category',info)}/>
            <Area>
              <Polygon
                pairs={this.state.alert.info.area.polygon}
                addPair={()=>this.addPolygonPair()}
                editPair={(val, i)=>this.editPolygonPair(val, i)}
                removePair={(i)=>this.removePolygonPair(i)}/>
            </Area>
            <Button variant={'dark'} onClick={()=>this.props.sendAlert(this.state)}>Send Alert</Button>
          </Form>
        </Container>
      </div>
    );
  }
}

function mapDispatchToProps(dispatch) {
  return bindActionCreators({
    sendAlert,
  }, dispatch)
}

export default connect(null, mapDispatchToProps)(AlertForm);