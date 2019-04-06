import React, { Component } from 'react';
import Navbar from 'react-bootstrap/Navbar';
import { Link } from 'react-router-dom';
import Nav from 'react-bootstrap/Nav';
import NavDropdown from 'react-bootstrap/NavDropdown';
import Dropdown from 'react-bootstrap/Dropdown';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import Button from 'react-bootstrap/Button';
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
        <Navbar fixed={'top'} bg={'dark'} variant={'dark'} expand={'lg'}>
          <Navbar.Brand as={Link} to={'/'}>
            <b>OS-WASABI</b><img src={logo} alt={'logo'} width={42}/> Alert Originator
          </Navbar.Brand>
          <Navbar.Toggle onClick={() => this.toggle()}/>
          <Navbar.Collapse id={'responsive-navbar-nav'}>
            <Nav className={'ml-auto'} navbar>
              <Nav.Link as={Link} to={'/dash'}><b>Dashboard</b></Nav.Link>
              <NavDropdown title={'Send'} alignRight>
                <NavDropdown.Item as={Link} to={'/send/alert'}>Send Alert</NavDropdown.Item>
                <NavDropdown.Item as={Link} to={'/send/poll'}>Send Poll</NavDropdown.Item>
              </NavDropdown>
              <NavDropdown title={'Configure'} alignRight>
                <NavDropdown.Item as={Link} to={'/conf/db'}>Database</NavDropdown.Item>
                <NavDropdown.Item as={Link} to={'/conf/gateway'}>Gateway</NavDropdown.Item>
              </NavDropdown>
              <Nav.Link as={Link} to={'/login'}><b>Login</b></Nav.Link>

              {/*<Dropdown as={ButtonGroup}>*/}
                {/*<Button>Logout</Button>*/}
                {/*<Dropdown.Toggle/>*/}
                {/*<Dropdown.Menu>*/}
                  {/*<Dropdown.Item as={Link} to={'/account'}>Account</Dropdown.Item>*/}
                  {/*<Dropdown.Item as={Link} to={'/settings'}>Settings</Dropdown.Item>*/}
                {/*</Dropdown.Menu>*/}
              {/*</Dropdown>*/}

            </Nav>
          </Navbar.Collapse>
        </Navbar>
      </div>
    );
  }
};
