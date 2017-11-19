/*
    @file gridstate,h
    @author Bilal Dinc
    @date 1.0 23/10/2017
    @brief
*/
#ifndef _TOROIDALSTATE_H_INCLUDED
#define _TOROIDALSTATE_H_INCLUDED

#include <list>
#include "../../../include/rlinterface/state.h"

namespace ballcatching{

  class ToroidalState : public rlinterface::State {

    public:
      ToroidalState(int x, int y, bool terminal);
      ToroidalState(int x, int y, bool terminal, std::list<int> actions);
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
