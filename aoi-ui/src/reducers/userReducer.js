/// Reduces actions dispatched for the user store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * user data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file userReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// User action types.
  GET_USERS,
  CREATE_USER,
  UPDATE_USER,
  REMOVE_USER } from "../actions/types";


const initialState = {  /// Defaults to the guest user.
  currUser: 0,
  allUsers: {
    0: {
      username: 'guest',
      name: 'Guest',
    },
    1: {
      username: 'vsagrawal',
      name: 'Vaniya'
    }
  }
}

/// Main reducer for user actions.
/**
 * Uses a switch statement to modify the user store. Switch statement is used
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
    case GET_USERS:
      return {
        ...state
      };
    case CREATE_USER:
      return {
        ...state,
      }
    case UPDATE_USER:
      return {
        ...state,
      };
    case REMOVE_USER:
      return {
        ...state,
      };
    default:
      return state;
  }
}