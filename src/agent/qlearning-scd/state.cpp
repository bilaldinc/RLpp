/*
    @file state,cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief customize rlinterface::State objects
*/

/*
    This class wrapes pure state object that comes from environment object. Possenion
    of pure state objects should move to this object via std::move() during the
    constraction.
    Creates Action objects list with available actions list in pure state object.
    Two State objects are equal iff their pure state objects are equal.
*/

/*
    TO-DO
    This class is not tested yet
*/


#include "../../../include/agent/qlearning/state.h"
#include <iostream>

namespace qlearning{

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
    std::list<Action>::iterator it = std::max_element(actions.begin(), actions.end());
    return it->GetType();
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