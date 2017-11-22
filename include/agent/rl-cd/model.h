/*
    @file qlaerningagent.h
    @author Bilal Dinc
    @date 1.0 18/11/2017
    @brief
*/

#ifndef _CD_MODEL_INCLUDED
#define _CD_MODEL_INCLUDED

#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include <limits>
#include <math.h>
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"
#include "../../../include/agent/rl-cd/state.h"
#include "../../../include/agent/rl-cd/action.h"

namespace rlcd{

    struct ExperienceTuple {
        rlinterface::State *state;
        int action;
        rlinterface::State *next_state;
        double reward;
        ExperienceTuple(rlinterface::State *state, int action, rlinterface::State *next_state, double reward);
    };
    typedef struct ExperienceTuple ExperienceTuple;

    struct UpdateError {
        std::list<double> transition_errors;
        double reward_error;
        double cm;
        UpdateError();
    };
    typedef struct UpdateError UpdateError;

    struct NextState {
        std::unique_ptr<rlinterface::State> state;
        int state_action_nextstate_counter;
        double reward_estimate;
        double probability;
        NextState(std::unique_ptr<rlinterface::State> state);
        NextState(NextState const& src);
        NextState& operator = (NextState const& rhs);
        bool operator == (const NextState& s);
    };
    typedef struct NextState NextState;

    struct StateAction {
        struct StateM *state_m;
        int action;
        std::list<NextState> next_state_list;
        int state_action_counter;
        double reward_estimate;
        StateAction(int action);
        bool operator == (const StateAction& s);
    };
    typedef struct StateAction StateAction;

    struct StateM {
        std::unique_ptr<rlinterface::State> state;
        std::list<StateAction> action_list;
        StateM(std::unique_ptr<rlinterface::State> state);
        StateM(StateM const& src);
        StateM& operator = (StateM const& rhs);
        bool operator == (const StateM& s);
    };
    typedef struct StateM StateM;

  class Model {
    private:
        std::list<StateM> state_list;
        std::list<State> qtable;
        int M;
        int Nsa(int state_action_counter);
        double Csa(int state_action_counter);
        double E;
        double p;
        double omega;
        int id;


    public:
        Model(int M, double p, double omega,int id);
        UpdateError UpdateModel(ExperienceTuple exp,bool update);
        double GetRewardEstimate(rlinterface::State *state, int action, rlinterface::State *next_state);
        double GetRewardEstimate(rlinterface::State *state, int action);
        double GetTrasitionEstimate(rlinterface::State *state,int action, rlinterface::State *next_state);
        std::list<NextState> GetTrasitionEstimates(rlinterface::State *state, int action);
        StateAction *GetStateAction(rlinterface::State *state, int action);
        std::list<StateAction*> GetStatesLeadsToS(rlinterface::State *state);
        std::list<StateM>& GetStateList();
        double UpdateModelQuality(ExperienceTuple exp,double Rmax ,double Rmin);
        std::list<State>& GetQTable();
        double GetE() const;
        int GetId();
        bool operator < (const Model& model);
  };

}

#endif
