/*
    @file environment,h
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief Environment interface
*/

#ifndef _RL_ENVIRONMENT_H_INCLUDED
#define _RL_ENVIRONMENT_H_INCLUDED

#include "response.h"
#include "state.h"

namespace rlinterface{

  class Environment {

    public:
      virtual State* ObserveState() = 0;
      virtual Response* TakeAnAction(int type) = 0;
      virtual ~Environment();

  };

}

#endif
