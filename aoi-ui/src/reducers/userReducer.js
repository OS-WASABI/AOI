import { CREATE_USER, GET_USER, UPDATE_USER } from "../actions/types";

const initialState = {
  username: '',
  userID: -1,
  name: {
    first: '',
    last: ''
  }
}

export default (state = initialState, action) => {
  switch(action.type) {
    default:
      return state;
  }
}