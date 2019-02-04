import {
  GET_USERS,
  CREATE_USER,
  UPDATE_USER,
  REMOVE_USER } from "../actions/types";

const initialState = {
  currUser: 0,
  allUsers: {
    0: {
      username: 'guest',
      name: 'Guest',
    }
  }
}

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