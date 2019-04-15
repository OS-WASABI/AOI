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
import Button from 'react-bootstrap/Button';
import Col from 'react-bootstrap/Col';
import Container from 'react-bootstrap/Container';

class Confirm extends Component {
  render() {
    return (
      <div id='Confirmation'>
        <Modal alert={this.props.alert}
               show={this.props.show}
               onHide={this.props.onHide} centered>
          <Modal.Header closeButton>
            <Container>
            <Modal.Title >Confirm Alert</Modal.Title>
            </Container>
          </Modal.Header>
          <Modal.Body>
            <Container>
            <Container>
              <h5>Summary</h5>
              <Row>
                <Col sm={4}>Status</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.status}</Col>
              </Row>
              <Row>
                <Col sm={4}>Message Type </Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.msgType}</Col>
              </Row>
              <Row>
                <Col sm={4}>Scope</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.scope}</Col>
              </Row>
            </Container>
            <hr/>
            <Container>
              <h5>Info</h5>
              <Row>
                <Col sm={4}>Event</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.event}</Col>
              </Row>
              <Row>
                <Col sm={4}>Urgency</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.urgency}</Col>
              </Row>
              <Row>
                <Col sm={4}>Certainty</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.certainty}</Col>
              </Row>
              <Row>
                <Col sm={4}>Category</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.category.map(cat => cat + ", ")}</Col>
              </Row>
              <Row>
                <Col sm={4}>Severity</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.severity}</Col>
              </Row>
            </Container>
            <hr/>
            <Container>
              <h5>Area</h5>
              <Row>
                <Col sm={4}>Description</Col>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.area.areaDesc}</Col>
              </Row>
              <Row>
                <Col sm={4}/>
                <Col style={{"color": "#6c757d"}}>{this.props.alert.info.area.polygon.map(pair => pair + ", ")} </Col>
              </Row>
            </Container>
            </Container>
          </Modal.Body>
          <Modal.Footer>
            <Button variant={'light'} onClick={this.props.onHide}>Edit</Button>
            <Button variant={'info'} onClick={()=>this.props.sendAlert(this.props.alert)}>Send</Button>
          </Modal.Footer>
        </Modal>
      </div>
    );
  }
}

function mapStateToProps(props) {

}

function mapDispatchToProps(dispatch) {
  return bindActionCreators({
    sendAlert,
  }, dispatch)
}

export default connect(null, mapDispatchToProps)(Confirm);