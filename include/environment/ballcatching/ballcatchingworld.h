/*
    @file gridwold.h
    @author Bilal Dinc
    @date 1.0 23/10/2017
    @brief
*/
#ifndef _BALLCATCHINGWORLD_H_INCLUDED
#define _BALLCATCHINGWORLD_H_INCLUDED

#include <list>
#include <vector>
#include <iostream>
#include <random>
#include "toroidalstate.h"
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"

namespace ballcatching{

  class BallCatchingWorld : public rlinterface::Environment {

    public:
      BallCatchingWorld(int size, int ball_direction, double reward, double punishment, int start_ball_x, int start_ball_y,int start_agent_x, int start_agent_y);
      rlinterface::State* ObserveState();
      rlinterface::Response* TakeAnAction(int type);
      void SetBallDirection(int ball_direction);
      int GetBallX();
      int GetBallY();
      std::list<rlinterface::State*> CreateAllPossibleStates();

    private:
      int size;
      int ball_direction;
      double reward;
      double punishment;
      int current_ball_x;
      int current_ball_y;
      int current_agent_x;
      int current_agent_y;
      int start_ball_x;
      int start_ball_y;
      int start_agent_x;
      int start_agent_y;
      int Mod(int a, int b);
      void StartEpisode();
      //random number generator and distribution
      static std::random_device rd;
      static std::default_random_engine generator;
      static std::uniform_real_distribution<double> distribution;
  };

}

#endif
