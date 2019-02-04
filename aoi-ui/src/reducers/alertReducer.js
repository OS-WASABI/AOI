import {
  GET_ALERTS,
  SEND_ALERT,
  UPDATE_ALERT,
  CANCEL_ALERT } from "../actions/types";

const initialState = {
  activeAlerts: {},
}

export default (state = initialState, action) => {
  switch(action.type) {
    case GET_ALERTS:
      return {
        ...state
      };
    case SEND_ALERT:
      return {
        ...state,
      }
    case UPDATE_ALERT:
      return {
        ...state,
      };
    case CANCEL_ALERT:
      return {
        ...state,
      };
    default:
      return state;
  }
}