import React from 'react';
import Jumbotron from 'react-bootstrap/Jumbotron'
import Button from 'react-bootstrap/Button';

const Home = () => {
  return (
    <div className='full-height'>
      <br/><br/>
      <Jumbotron className={''}>
        <h1 className='display-4'>Alert Originator Interface</h1>
        <p className='lead'>
          Welcome to the AOI Control Panel! This panel is for managing data,
          controlling configurations, and monitoring alert activity.
        </p>
        <hr className='my-2'/>
        <p>
          Use the links above to access data for alerts.
        </p>
        <p className='lead'>
          <Button variant='dark'>Learn more</Button>
        </p>
      </Jumbotron>
    </div>
  );
};

export default Home;