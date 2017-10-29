/*
scd
*/

#include "../../../include/agent/ql_scd/ql_scd_state.h"

namespace ql_scd {

	//initialize random number generator and distribution
	std::random_device State::rd;
	std::default_random_engine State::generator(rd());
	std::uniform_real_distribution<double> State::distribution(0.0,1.0);

	State::State(std::unique_ptr<rlinterface::State> state) : state(std::move(state)){
		std::list<int> intactions = this->state->GetAvailableActions();
		for(auto it: intactions){
			actions.push_back(Action(it,0));
		}
	}

	State::State(const State& src){
		actions = src.actions;
		state = std::unique_ptr<rlinterface::State>(src.state->clone());
	}

	State& State::operator = (State& rhs){
		actions = rhs.actions;
		state = std::unique_ptr<rlinterface::State>(rhs.state->clone());
		return *(this);
	}


	void State::UpdateActionList(rlinterface::State *state){
		// This funtion is implemented without any perfomance conserns.
		// Data structures can be changed some traverses can be reduced.

		// Get new list of action
		std::list<int> newlist = state->GetAvailableActions();
		// Create old list of action
		std::list<int> oldlist = this->state->GetAvailableActions();

		// End of this iterations, newlist will contain actions to be added
		// Old list will contain actions to be deleted from current list
		for(std::list<int>::iterator i = newlist.begin(); i != newlist.end(); ++i) {
			for(std::list<int>::iterator j = oldlist.begin(); j != oldlist.end(); ++j) {
				if(*i == *j){
					j = oldlist.erase(j);
					i = newlist.erase(i);
					i--;
					break;
				}
			}
		}

		// Add the new actions
		for(std::list<int>::iterator i = newlist.begin(); i != newlist.end(); ++i) {
			actions.push_back(Action(*i,0));
		}
		// Remove old actions
		for(std::list<int>::iterator i = oldlist.begin(); i != oldlist.end(); ++i) {
			std::list<Action>::iterator position = std::find(actions.begin(), actions.end(), Action(*i,0));
			if (position != actions.end()){
				actions.erase(position);
			}
		}
		(this->state).reset(state->clone());
	}


	double State::GetMaxActionValue(){
		std::list<Action>::iterator it = std::max_element(actions.begin(), actions.end());
		return it->GetValue();
	}

	int State::GetMaxActionType(){
		// O(actions)
		std::list<Action>::iterator it = std::max_element(actions.begin(), actions.end());
		return it->GetType();
	}

	int State::GetMaxActionTypeRandom(){
		// Random among equally maximum actions but computationally more expensive
		// O(actions)
		// Since clearing the list iterate for deletion of objects it is linear
		// O(actions*2)

		std::list<int> maxlist;
		double max = std::numeric_limits<double>::min();

		for(auto i: actions){
			if(i.GetValue() > max){
				max = i.GetValue();
				maxlist.clear();
				maxlist.push_back(i.GetType());
			}
			else if(i.GetValue() == max){
				maxlist.push_back(i.GetType());
			}
			else{
				// Do nothing
			}
		}
		int count = (int)(distribution(generator) * maxlist.size());
		std::list<int>::iterator it = maxlist.begin();
		std::advance(it,count);
		return *it;
	}

	std::list<Action>::iterator State::GetAction(int type){
		auto it = find(actions.begin(),actions.end(),Action(type));
		return it;
	}

	std::list<Action>& State::GetActionList(int type){
		return actions;
	}


	rlinterface::State* State::GetPureState() const{
		return (this->state).get();
	}

	bool State::operator == (const State& state){
		return *(this->GetPureState()) == *(state.GetPureState());
	}

}
