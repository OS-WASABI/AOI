import React, { Component } from 'react';
import Navbar from 'react-bootstrap/Navbar';
import { Link } from 'react-router-dom';
import Nav from 'react-bootstrap/Nav';
import NavDropdown from 'react-bootstrap/NavDropdown';
import logo from '../../images/logo.svg';

export default class Header extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isOpen: false
    };
  }

  toggle() {
    this.setState(prevState => ({
      ...prevState,
      isOpen: !prevState.isOpen
    }))
  }

  render() {
    return (
      <div className="Header">
        <Navbar bg={'dark'} variant={'dark'} fixed={'top'} expand={'lg'}>
          <Navbar.Brand as={Link} to={'/'}>
            <b>OS-WASABI</b><img src={logo} alt={'logo'} width={42}/> Alert Originator
          </Navbar.Brand>
          <Navbar.Toggle onClick={() => this.toggle()}/>
          <Navbar.Collapse id={'responsive-navbar-nav'}>
            <Nav className={'ml-auto'} navbar>
              <NavDropdown title={'Send'} alignRight>
                <NavDropdown.Item as={Link} to={'/send/alert'}>Live Alert</NavDropdown.Item>
                <NavDropdown.Item as={Link} to={'/send/poll'}>Test Poll</NavDropdown.Item>
              </NavDropdown>
              <Nav.Link as={Link} to={'/login'}><b>Login</b></Nav.Link>
            </Nav>
          </Navbar.Collapse>
        </Navbar>
      </div>
    );
  }
};
