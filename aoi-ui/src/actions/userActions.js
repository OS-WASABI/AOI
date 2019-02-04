import {
  GET_USERS,
  CREATE_USER,
  UPDATE_USER,
  REMOVE_USER } from "./types";

export const getUser = (query) => dispatch => {
    fetch('https://jsonplaceholder.typicode.com/users/' + query)
      .then(res => res.json())
      .then(user => dispatch({
        type: GET_USERS,
        payload: user
      }));
}

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

export const updateUser = (userData) => dispatch => {
  fetch('https://jsonplaceholder.typicode.com/users', {
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