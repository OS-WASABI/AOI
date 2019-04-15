/// Defines actions the involve alert data.
/**
 * Defines the actions that can occur to manage alert data.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alertActions.js
 * @date    February 2019
 * @authors Vaniya Agrawal
 */
import {
  GET_ALERTS,
  SENDING_ALERT,
  SENT_ALERT,
  RECEIVE_ERROR } from "./types";

/// Get alert data.
/**
 * Gets alert data from the server. If all alert data is being requested,
 * the query must be null. Otherwise, the query must include the key
 * and value to search on. For instance:
 *    { alertID: 0 },
 *    { severity: 'URGENT' }
 * @param query The search parameter in the form {key: value}
 * @returns {Function}  Dispatches an action.
 */
export const getAlerts = (query) => (dispatch, getState) => {
  fetch(window.location.origin + getState().config.alertEndpoint + query)
    .then(res => res.json())
    .then(alerts => dispatch({
      type: GET_ALERTS,
      payload: alerts
    }));
};

const sendingAlert = () => {
  return {
    type: SENDING_ALERT
  }
}

const receiveError = (err) => {
  return {
    type: RECEIVE_ERROR,
    payload: err
  }
}

/// Post alert data.
/**
 * Posts alert data to the server. The alert data is contained in the body
 * of the request and contains all necessary information.
 * @param alert Contains all necessary items defined by the CAP standard.
 * @returns {Function}  Dispatches an action.
 */
export const sendAlert = (alert) => (dispatch, getState) => {
  alert.sender = "dummy-sender";
  alert.sent = new Date();

  dispatch(sendingAlert());

  fetch(window.location.origin + getState().config.alertEndpoint, {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(alert)
  })
    .then(res => {
      if (res.status !== 201) {
        dispatch(receiveError('Error ' + res.status + ": Unable to complete request."))
      }
      else return res.json();
    })
    .then(res => dispatch({
      type: SENT_ALERT,
      payload: res
    }))
    .catch(err => dispatch(receiveError("Unexpected error. Unable to fulfill request.")));
};

