/*
    @file response,cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief wraps responses after an action is taken
*/

/*
    Response object carries comminication information between agent and
    environment. It owns State object.
*/

#include "../../include/rlinterface/response.h"

namespace rlinterface{

  Response::Response(std::unique_ptr<State> state, double reward) :
  state(move(state)), reward(reward) {

  }

  std::unique_ptr<State> Response::GetState(){
    //this method transfers ownership it should not be used twice.
    return std::move(state);
  }

  double Response::GetReward(){
    return reward;
  }

}
