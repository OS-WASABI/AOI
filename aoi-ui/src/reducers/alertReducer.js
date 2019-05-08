/// Reduces actions dispatched for the alert store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * alert data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file alertReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// Alert action types.
  SENT_ALERT,
  SENDING_ALERT,
  RECEIVE_ERROR } from "../actions/types";

const initialState = {  /// Initialized with no active alerts.
  isFetching: false,
  response: {
    success: '',
    error: ''
  }
}

/// Main reducer for alert actions.
/**
 * Uses a switch statement to modify the alert store. Switch statement is used
 * to determine which action has been dispatched and to modify the store accordingly.
 *
 * IMPORTANT!! The store is IMMUTABLE. ALL cases must return a COPY of the store,
 * they must not change the store itself. Utilize a return statement and the spread
 * operator (ex.: ...state) to accomplish this.
 *
 * @param state The current state of the data.
 * @param action  The action that is dispatched. Contains a type and a payload.
 * @returns object  A copy of the store, modified according to the action type and payload.
 */
export default (state = initialState, action) => {
  switch(action.type) {
    case SENDING_ALERT:
      console.log("sending alert...");
      return {
        ...state,
        isFetching: true
      };
    case RECEIVE_ERROR:
      console.log("received an error...");
      return {
        ...state,
        isFetching: false,
        response: {
          error: action.payload,
          success: ''
        }
      }
    case SENT_ALERT:
      console.log("received a response...");
      return {
        ...state,
        isFetching: false,
        response: {
          success: 'Success! Your alert has been sent.',
          error: ''
        }
      }

    default:
      return state;
  }
}