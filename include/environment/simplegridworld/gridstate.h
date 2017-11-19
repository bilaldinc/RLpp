/*
    @file gridstate,h
    @author Bilal Dinc
    @date 1.0 25/09/2017
    @brief simple gridworld environment
*/
#ifndef _GRIDSTATE_H_INCLUDED
#define _GRIDSTATE_H_INCLUDED

#include <list>
#include "../../../include/rlinterface/state.h"

namespace simplegridworld{

  class GridState : public rlinterface::State {

    public:
      GridState(int x, int y, bool terminal);
      GridState(int x, int y, bool terminal, std::list<int> actions);
      std::list<int> GetAvailableActions();
      bool operator == (const State& s);
      bool IsTerminal();
      rlinterface::State* clone();
      int GetX() const;
      int GetY() const;
      std::string ToString();

    private:
      int x, y;
      bool terminal;
      std::list<int> actions;
  };

}

#endif
