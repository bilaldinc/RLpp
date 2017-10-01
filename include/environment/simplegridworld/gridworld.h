/*
    @file gridwold.h
    @author Bilal Dinc
    @date 1.0 25/09/2017
    @brief
*/
#ifndef _GRIDWORLD_H_INCLUDED
#define _GRIDWORLD_H_INCLUDED

#include <list>
#include <iostream>
#include "gridstate.h"
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"

namespace simplegridworld{

  class GridWorld : public rlinterface::Environment {

    public:
      GridWorld(int size, int initialX, int initialY, int terminalX, int terminalY, double reward);
      rlinterface::State* ObserveState();
      rlinterface::Response* TakeAnAction(int type);

    private:
      int currentX, currentY;
      int initialX, initialY;
      int terminalX, terminalY;
      int size;
      double reward;
  };

}

#endif
