/// Defines actions the involve user data.
/**
 * Defines the actions that can occur to manage
 * or manipulate user data.
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file    userActions.js
 * @date    February 2019
 * @authors Vaniya Agrawal
 */
import {
  GET_USERS,
  CREATE_USER,
  UPDATE_USER,
  REMOVE_USER } from "./types";

/// Get user data.
/**
 * Gets user data from the server. If all user data is being requested,
 * the query must be null. Otherwise, the query must include the key
 * and value to search on. For instance:
 *    { userID: 0 },
 *    { name: 'Vaniya' }
 * @param query The search parameter in the form {key: value}
 * @returns {Function}  Dispatches an action.
 */
export const getUser = (query) => dispatch => {
    // TODO (Vaniya): Build message body or query string based on query.
    fetch('https://jsonplaceholder.typicode.com/users/' + query)
      .then(res => res.json())
      .then(user => dispatch({
        type: GET_USERS,
        payload: user
      }));
}

/// Post user data.
/**
 * Posts user data to the server. The user data is contained in the body
 * of the request and contains all necessary information.
 * @param user  Contains a first_name, last_name, username, email. Optionally,
 *              has a phone, address, country, state_region, and zip.
 * @returns {Function}  Dispatches an action.
 */
export const createUser = (user) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/users', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(user)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: CREATE_USER,
      payload: res
    }));
}

/// Put user data.
/**
 * Puts user data to the server.
 * @param userData  Contains the data to be modified in the form {key: value, key2: value2, ...}
 * @param userID    The ID of the user to be modified.
 * @returns {Function}  Dispatches an action.
 */
export const updateUser = (userData, userID) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/users/' + userID, {
    method: 'PUT',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(userData)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: UPDATE_USER,
      payload: res
    }))
};

///Remove user data.
/**
 * Removes a data from the server.
 * @param userID  The id of the user to remove.
 * @returns {Function}  Dispatches an action.
 */
export const removeUser = (userID) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/users', {
    method: 'POST',
    headers: {
      'content-type': 'application/json'
    },
    body: JSON.stringify(userID)
  })
    .then(res => res.json())
    .then(res => dispatch({
      type: REMOVE_USER,
      payload: res
    }));
}