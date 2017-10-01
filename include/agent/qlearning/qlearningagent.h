/*
    @file qlaerningagent.h
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief implementation of qlearning algirithm
*/

#ifndef _Q_QLEARNING_AGENT_INCLUDED
#define _Q_QLEARNING_AGENT_INCLUDED

#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"
#include "../../../include/agent/qlearning/state.h"
#include "../../../include/agent/qlearning/action.h"

namespace qlearning{

  class QLearningAgent {

    private:
      //environment object
      std::unique_ptr<rlinterface::Environment> environment;

      //parameters
      double alpha;
      double gamma;
      double epsilon;

      //termination conditions
      double threshold;
      int buffersize;

      //qtable
      std::list<State> qtable;

      //random number generator and distribution
      std::random_device rd;
      std::default_random_engine generator = std::default_random_engine(rd());
      std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0.0,1.0);

    public:
      QLearningAgent(std::unique_ptr<rlinterface::Environment> environment, double alpha, double gamma, double epsilon);
      void Train(int numberofepisode);
      std::list<State>& GetQTable();
      void SetAlpha(double alpha);
      void SetEpsilon(double epsilon);

      int EpsilonGreedyPolicy(std::list<State>::iterator agentstate);
      std::list<State>::iterator AddNewStateToQTable(rlinterface::State* state);

  };

}

#endif
