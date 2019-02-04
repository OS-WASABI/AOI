import {
  GET_ALERTS,
  SEND_ALERT,
  UPDATE_ALERT,
  CANCEL_ALERT } from "./types";

export const getAlerts = (query) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts')
    .then(res => res.json())
    .then(alerts => dispatch({
      type: GET_ALERTS,
      payload: alerts
    }));
};

export const sendAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(alert)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: SEND_ALERT,
      payload: res
    }));
};

export const updateAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(userData)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: UPDATE_ALERT,
      payload: res
    }))
};

export const cancelAlert = (alert) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(alert)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: CANCEL_ALERT,
      payload: res
    }))
};
