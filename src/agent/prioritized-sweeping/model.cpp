/*
    @file qlaerningagent.h
    @author Bilal Dinc
    @date 1.0 18/11/2017
    @brief

    Notes. Line 71.
    Decide new comming states error
    For now it is assummed to be (new value - 0). It could be changed with 0
*/

#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include <limits>
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"
#include "../../../include/agent/prioritized-sweeping/model.h"

namespace prioritizedsweeping{

    UpdateError Model::UpdateModel(ExperienceTuple exp){
        UpdateError error;

        //find the specified state
        std::unique_ptr<rlinterface::State> t1(exp.state->clone());
        StateM search_object0(std::move(t1));
        std::list<StateM>::iterator it = find(state_list.begin(), state_list.end(),search_object0);
        if(it == state_list.end()){
            // it is not in the model
            state_list.push_back(search_object0);
            it--;
        }
        // it is in the model, then find the related action
        StateAction search_object1(exp.action);
        std::list<StateAction>::iterator it2 = find(it->action_list.begin(), it->action_list.end(),search_object1);
        if(it2 == it->action_list.end()){
            // action is not in the model
            search_object1.state_m = &(*it);
            search_object1.action = exp.action;
            search_object1.state_action_counter = 0;
            search_object1.reward_estimate = 0;
            it->action_list.push_back(search_object1);
            it2--;
        }
        // increase counter, calculate error, update reward estimate
        it2->state_action_counter ++;
        error.reward_error = (exp.reward - it2->reward_estimate) / it2->state_action_counter;
        it2->reward_estimate += error.reward_error;
        //find next state
        bool founded = false;
        std::unique_ptr<rlinterface::State> t2(exp.next_state->clone());
        NextState search_object2(std::move(t2));
        for(std::list<NextState>::iterator it3 = it2->next_state_list.begin(); it3 != it2->next_state_list.end(); ++it3){
            if(*it3 == search_object2){
                founded = true;
                it3->state_action_nextstate_counter ++;
                it3->reward_estimate += (exp.reward - it3->reward_estimate) / it3->state_action_nextstate_counter;
                // calculate propbability error, update, add error to error list
                double probability_error = 1 - it3->probability ;
                it3->probability += probability_error / it2->state_action_counter;
                error.transition_errors.push_back(probability_error);
            }
            else{
                // calculate propbability error, update, add error to the error list
                double probability_error = 0 - it3->probability;
                it3->probability += probability_error / it2->state_action_counter;
                error.transition_errors.push_back(probability_error);
            }
        }
        if(founded == false){
            // next_state is not in the model
            search_object2.reward_estimate = exp.reward;
            search_object2.state_action_nextstate_counter = 1;
            search_object2.probability = 1.0 / it2->state_action_counter;
            it2->next_state_list.push_back(search_object2);
            error.transition_errors.push_back(0 - (1.0 / it2->state_action_counter));
        }

        return error;
	}

    double Model::GetRewardEstimate(rlinterface::State *state,int action, rlinterface::State *next_state){
        // O(|S| + |A| + |S|)
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            if(*it0->state == *state){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    if(it1->action == action){
                        for(std::list<NextState>::iterator it2 = it1->next_state_list.begin(); it2 != it1->next_state_list.end(); ++it2){
                            if(*it2->state == *next_state){
                                return it2->reward_estimate;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
        std::cout << "error while finding given reward estimate" << '\n';
        exit(1);
        return 0;
	}

    double Model::GetRewardEstimate(rlinterface::State *state,int action){
        // O(|S| + |A|)
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            if(*it0->state == *state){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    if(it1->action == action){
                        return it1->reward_estimate;
                    }
                }
                break;
            }
        }
        std::cout << "error while finding given reward estimate" << '\n';
        exit(1);
        return 0;
	}

    double Model::GetTrasitionEstimate(rlinterface::State *state,int action, rlinterface::State *next_state){
        // O(|S| + |A| + |S|)
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            if(*it0->state == *state){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    if(it1->action == action){
                        for(std::list<NextState>::iterator it2 = it1->next_state_list.begin(); it2 != it1->next_state_list.end(); ++it2){
                            if(*it2->state == *next_state){
                                return it2->probability;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
        std::cout << "error while finding given transition estimate" << '\n';
        exit(1);
        return 0;
	}

    std::list<NextState> Model::GetTrasitionEstimates(rlinterface::State *state, int action){
        // O(|S| + |A|)
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            if(*it0->state == *state){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    if(it1->action == action){
                        return it1->next_state_list;
                    }
                }
                break;
            }
        }
        std::cout << "error while finding given transition estimates" << '\n';
        exit(1);
        std::list<NextState> null;
        return null;
	}

    StateAction *Model::GetStateAction(rlinterface::State *state, int action){
        // O(|S| + |A|)
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            if(*(it0->state) == *state){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    if(it1->action == action){
                        return &(*it1);
                    }
                }
                break;
            }
        }
        std::cout << "error while finding given StateAction struct" << '\n';
        exit(1);
        return NULL;
    }

    std::list<StateAction*> Model::GetStatesLeadsToS(rlinterface::State *state){
        // O(|S| * |A| * |S|)
        std::list<StateAction*> resulting_list;
        for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
            for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                for(std::list<NextState>::iterator it2 = it1->next_state_list.begin(); it2 != it1->next_state_list.end(); ++it2){
                    if(*it2->state == *state){
                        resulting_list.push_back(&(*it1));
                    }
                }

            }
        }
        return resulting_list;
    }

    std::list<StateM>&  Model::GetStateList(){
        return Model::state_list;
    }

    // initializers , copy constructers, operator overloads

    ExperienceTuple::ExperienceTuple(rlinterface::State *state, int action, rlinterface::State *next_state, double reward):
    state(state),action(action),next_state(next_state),reward(reward){

    }

    UpdateError::UpdateError():reward_error(0){

    }

    NextState::NextState(std::unique_ptr<rlinterface::State> state):state(std::move(state)),
    probability(0),reward_estimate(0),state_action_nextstate_counter(0){

    }

    NextState::NextState(NextState const& src){
        state = std::unique_ptr<rlinterface::State>(src.state->clone());
        state_action_nextstate_counter = src.state_action_nextstate_counter;
        reward_estimate = src.reward_estimate;
        probability = src.probability;
    }

    NextState& NextState::operator = (NextState const& rhs){
        state = std::unique_ptr<rlinterface::State>(rhs.state->clone());
        state_action_nextstate_counter = rhs.state_action_nextstate_counter;
        reward_estimate = rhs.reward_estimate;
        probability = rhs.probability;
        return *(this);
    }

    bool NextState::operator == (const NextState& s){
        return *(this->state) == *(s.state);
    }

    StateAction::StateAction(int action):action(action),state_action_counter(0),reward_estimate(0){

    }

    bool StateAction::operator == (const StateAction& s){
        return this->action == s.action;
    }

    StateM::StateM(std::unique_ptr<rlinterface::State> state):state(std::move(state)){

    }

    StateM::StateM(StateM const& src){
        state = std::unique_ptr<rlinterface::State>(src.state->clone());
        action_list = src.action_list;
    }

    StateM& StateM::operator = (StateM const& rhs){
        state = std::unique_ptr<rlinterface::State>(rhs.state->clone());
        action_list = rhs.action_list;
        return *this;
    }

    bool StateM::operator == (const StateM& s){
        return *(this->state) == *(s.state);
    }


}
