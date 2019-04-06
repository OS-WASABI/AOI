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

import Modal from 'react-bootstrap/Modal';
import Row from 'react-bootstrap/Row';
import Container from 'react-bootstrap/Container';
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

class Confirm extends Component {

  render() {
    return (
      <div id='Confirmation'>
        <Modal {...this.props} centered>
          <Modal.Header closeButton>
            <Modal.Title>{this.props.alert.info.event}</Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Row>
              <Col sm={4}>Status</Col>
              <Col>{this.props.alert.status}</Col>
            </Row>
            <Row>
              <Col sm={4}>Message Type </Col>
              <Col>{this.props.alert.msgType}</Col>
            </Row>
            <Row>
              <Col sm={4}>Scope</Col>
              <Col>{this.props.alert.scope}</Col>
            </Row>
            <hr/>
            <Row>
              <Col sm={4}>Urgency</Col>
              <Col>{this.props.alert.info.urgency}</Col>
            </Row>
            <Row>
              <Col sm={4}>Certainty</Col>
              <Col>{this.props.alert.info.certainty}</Col>
            </Row>
            <Row>
              <Col sm={4}>Category</Col>
              <Col>{this.props.alert.info.category.map(cat => cat + ", ")}</Col>
            </Row>
            <Row>
              <Col sm={4}>Severity</Col>
              <Col>{this.props.alert.info.severity}</Col>
            </Row>
            <hr/>
            <Row>
              <Col sm={4}>Area</Col>
              <Col>{this.props.alert.info.area.areaDesc}</Col>
            </Row>
            <Row>
              <Col sm={4}/>
              <Col>{this.props.alert.info.area.polygon.map(pair => pair + ", ")} </Col>
            </Row>
          </Modal.Body>
          <Modal.Footer>
            <Button variant={'light'} onClick={this.props.onHide}>Edit</Button>
            <Button variant={'info'} onClick={this.props.onHide}>Send</Button>
          </Modal.Footer>
        </Modal>
      </div>
    );
  }
}

function mapDispatchToProps(dispatch) {
  return bindActionCreators({
    sendAlert,
  }, dispatch)
}

export default connect(null, mapDispatchToProps)(Confirm);