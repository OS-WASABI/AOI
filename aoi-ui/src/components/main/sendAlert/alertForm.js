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
import Alert from 'react-bootstrap/Alert';

import Confirmation from './confirm';
import Polygon from './polygon';
import Severity from './severity';
import Status from './status';
import Type from './type';
import Scope from './scope';
import Certainty from "./certainty";
import Urgency from "./urgency";
import Category from "./category";
import Area from "./area";
import Expires from "./expires";

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
        status: "Status ",
        msgType: "Message Type",
        scope: "Scope ",
        expires: '',
        info: {
          category: [],
          event: "",
          urgency: "Urgency ",
          severity: "Severity ",
          certainty: "Certainty ",
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
      },
      confirming: false,
      error: {
        msg: "",
        show: false
      }
    };
    this.addInfo = this.addInfo.bind(this);
    this.addAlert = this.addAlert.bind(this);
    this.pushInfoSelection = this.pushInfoSelection.bind(this);
    this.popInfoSelection = this.popInfoSelection.bind(this);

    this.addPolygonPair = this.addPolygonPair.bind(this);
    this.editPolygonPair = this.editPolygonPair.bind(this);
    this.removePolygonPair = this.removePolygonPair.bind(this);

    this.validateAlert = this.validateAlert.bind(this);

  }

  validateAlert(object, error) {
    Object.keys(object).forEach(alertOption => {
      let val = object[alertOption];

      if (typeof val === "string") {
        if ( val === null || val.length === 0 || val.includes(" ")) {
          error.push(alertOption);
        }
      }

      else if (val instanceof Array) {
        if (val.length === 0) {
          error.push(alertOption);

        }
        for (let i=0; i<val.length; i++){
          let item = val[i];
          if (item === null || item.length === 0) {
            error.push(alertOption);
            break;
          }
        }
      }

      else {
        error = this.validateAlert(val, error);
      }
    })
    return error;
  }

  handleValidate() {
    let error = this.validateAlert(this.state.alert, []);
    if (error.length !== 0) {
      let errorStr = ["Oops! Please fix missing fields: "];
      error.forEach(opt => errorStr.push(opt + ", "));
      this.setState({error: { msg: errorStr, show: true}});
    }
    else {
      this.setState({confirming: true});
      this.setState({error: { msg: "", show: false}});

    }
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
    console.log("Changing " + name);
    console.log(value);
    this.setState(prevState => ({
      ...prevState,
      alert: {
        ...prevState.alert,
        [name]: value
      },
    }))
  }

  addInfo(name, value) {
    if (name === "areaDesc") {
      this.setState(prevState => ({
        ...prevState,
        alert: {
          ...prevState["alert"],
          info: {
            ...prevState.alert.info,
            area: {
              ...prevState.alert.info.area,
              [name]: value
            }
          }
        },
      }))
    }
    else {
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
    let confirmationClose = () => this.setState({confirming: false});

    return (
      <div id='Alerts'>
        <br/><br/><br/>
        <Container>
          <Confirmation
            alert={this.state.alert}
            show={this.state.confirming}
            onHide={confirmationClose}/>
          <br/>
          <h1>Send Alert</h1>
          <Alert
            variant={"danger"}
            dismissible
            onClose={()=> this.setState({error: {msg:'', show: false}})}
            show={this.state.error.show}>
            {this.state.error.msg}
          </Alert>
          <hr/>
          <Form>
              <Form.Row>
                <Form.Label
                  column
                  sm={2}>Alert Options</Form.Label>
                <Status
                  status={this.state.alert.status}
                  statuses={options.statuses}
                  addAlert={alert=>this.addAlert('status', alert)}/>
                <Type
                  type={this.state.alert.msgType}
                  types={options.types}
                  addAlert={alert=>this.addAlert('msgType', alert)}/>
                <Scope
                  scope={this.state.alert.scope}
                  scopes={options.scopes}
                  addAlert={alert=>this.addAlert('scope', alert)}/>
              </Form.Row>
            <Form.Group>
              <Form.Row>
                <Form.Label
                  column
                  sm={2}>
                  Expires
                </Form.Label>
                <Expires
                  addAlert={date=>this.addAlert('expires', date)}/>
              </Form.Row>
            </Form.Group>
            <hr/>
            <Form.Group>
              <Form.Row>
                <Form.Label
                  column
                  sm={2}>Event</Form.Label>
                <Col>
                  <InputGroup>
                    <Form.Control
                      placeholder={'Event Title'}
                      onChange={event => this.addInfo('event', event.target.value)}
                      type={'text'}/>
                  </InputGroup>
                </Col>
              </Form.Row>
            </Form.Group>
            <Form.Row>
              <Form.Label
                column
                className={'grey'}
                sm={2}>Info Options</Form.Label>
              <Urgency
                urgency={this.state.alert.info.urgency}
                urgencies={options.urgencies}
                addInfo={val=>this.addInfo("urgency",val)}/>
              <Certainty
                certainty={this.state.alert.info.certainty}
                certainties={options.certainties}
                addInfo={info=>this.addInfo('certainty',info)}/>
            </Form.Row>
            <Category
              category={this.state.alert.info.category}
              categories={options.categories}
              pushInfoSelection={info=>this.pushInfoSelection('category',info)}
              popInfoSelection={info=>this.popInfoSelection('category',info)}/>
            <Severity
              severity={this.state.alert.info.severity}
              addInfo={info=>this.addInfo('severity', info)}/>
            <Area
              addInfo={val => this.addInfo("areaDesc", val)}>
              <Polygon
                pairs={this.state.alert.info.area.polygon}
                addPair={()=>this.addPolygonPair()}
                editPair={(val, i)=>this.editPolygonPair(val, i)}
                removePair={(i)=>this.removePolygonPair(i)}/>
            </Area>
            <hr/>
            <Form.Row>
              <Col sm={2}/>
              <Col>
              <Button
                variant={'dark'}
                onClick={()=> this.handleValidate()}>
                Send Alert
              </Button>
              </Col>
            </Form.Row>
          </Form>
          <br/><br/>
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