/*
scd
*/

#ifndef _Q_STATE_INCLUDED
#define _Q_STATE_INCLUDED

#include "../../../include/agent/ql_scd/ql_scd_action.h"
#include "../../../include/rlinterface/state.h"
#include <algorithm>
#include <list>
#include <memory>
#include <limits>
#include <iostream>
#include <random>

namespace ql_scd {

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
		std::list<Action>& GetActionList(int type);
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
