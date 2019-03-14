import React from 'react';
import Form from 'react-bootstrap/Form';
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';

const AlertForm = () => {
  return (
    <div id='Alerts'>
      <br/><br/><br/>
      <Container>
      <h1>Send Live Alert</h1>
        <br/>
        <Form>
        <Form.Group as={Row} controlId={'event'}>
          <Form.Label column sm={2}>Event Type</Form.Label>
          <Col><Form.Control type={'text'}/></Col>
        </Form.Group>
      </Form>
      </Container>
    </div>
  );
};

export default AlertForm;