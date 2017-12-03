/*
    @file state.cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief customize rlinterface::State objects
*/

#ifndef _CDS_STATE_INCLUDED
#define _CDS_STATE_INCLUDED

#include "../../../include/agent/rl-cd-s/action.h"
#include "../../../include/rlinterface/state.h"
#include <algorithm>
#include <list>
#include <memory>
#include <limits>
#include <iostream>
#include <random>

namespace rlcds{

  class State {

    public:
      State(std::unique_ptr<rlinterface::State> state);
      State(const State& src);
      State& operator = (State& rhs);
      void UpdateActionList(rlinterface::State *state);
      double GetMaxActionValue();
      int GetMaxActionType();
      int GetMaxActionTypeRandom();
      std::list<Action>::iterator GetAction(int type);
      std::list<Action>& GetActionList();
      rlinterface::State* GetPureState() const;
      bool operator == (const State& s);


    private:
      std::list<Action> actions;
      std::unique_ptr<rlinterface::State> state;

      //random number generator and distribution
      static std::random_device rd;
      static std::default_random_engine generator;
      static std::uniform_real_distribution<double> distribution;

  };

}

#endif
