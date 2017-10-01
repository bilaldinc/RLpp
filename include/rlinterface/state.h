/*
    @file state,h
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief State interface
*/

#ifndef _RL_STATE_H_INCLUDED
#define _RL_STATE_H_INCLUDED

#include <list>

namespace rlinterface{

  class State {

    public:
        virtual std::list<int> GetAvailableActions() = 0;
        virtual bool IsTerminal() = 0;
        virtual bool operator == (const State& s) = 0;
        virtual State* clone() = 0;
        virtual ~State();

  };

}

#endif
