/*
    @file response,h
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief wraps responses after an action is taken
*/

#ifndef _RL_RESPONSE_H_INCLUDED
#define _RL_RESPONSE_H_INCLUDED

#include "state.h"
#include <memory>

namespace rlinterface{

  class Response {

    public:
      Response(std::unique_ptr<State> state, double reward);
      std::unique_ptr<State> GetState();
      double GetReward();

    private:
      std::unique_ptr<State> state;
      double reward;
  };

}

#endif
