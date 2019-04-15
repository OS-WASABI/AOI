/// Reduces actions dispatched for the user store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * user data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file configReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
// import {  /// action types.
//    } from "../actions/types";


const initialState = {  /// Defaults to the guest user.
  currUser: {
    0: {
      username: 'guest',
      name: 'Guest',
    },
  },
  alertEndpoint: '/v1/cadg/api/alerts'
}

/// Main reducer for user actions.
/**
 * Uses a switch statement to modify the config store. Switch statement is used
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
    default:
      return state;
  }
}