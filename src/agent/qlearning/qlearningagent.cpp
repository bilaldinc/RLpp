/*
    @file qlaerningagent.cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief implementation of qlearning algirithm
*/

#include "../../../include/agent/qlearning/qlearningagent.h"


namespace qlearning{

  QLearningAgent::QLearningAgent(std::unique_ptr<rlinterface::Environment> environment, double alpha, double gamma, double epsilon):
  environment(std::move(environment)), alpha(alpha), gamma(gamma), epsilon(epsilon){

  }

  void QLearningAgent::Train(int numberofepisode){
    int episodecounter = 1;
    //for each episode
    while (episodecounter < numberofepisode){
      //initial state & response
      std::unique_ptr<rlinterface::State> currentenvironmentstate(environment->ObserveState());
      std::list<State>::iterator currentagentstate = AddNewStateToQTable(currentenvironmentstate.get());
      //counter for stepsize of each episode
      int stepsizecounter = 0;
      //for every step of the episode
      while (!currentenvironmentstate->IsTerminal()){
        //decide next action
        int nextaction = EpsilonGreedyPolicy(currentagentstate);
        //execute nextaction, update current environment state known by agent, add new state to qtable
        std::unique_ptr<rlinterface::Response> response(environment->TakeAnAction(nextaction));
        currentenvironmentstate = response->GetState();
        std::list<State>::iterator nextagentstate = AddNewStateToQTable(currentenvironmentstate.get());
        //calculate and do the update
        std::list<Action>::iterator currentq = currentagentstate->GetAction(nextaction);
        double error = alpha*(response->GetReward() + gamma*(nextagentstate->GetMaxActionValue()) - currentq->GetValue());
        currentq->SetValue(currentq->GetValue() + error);
        // update agent current state
        currentagentstate = nextagentstate;
        stepsizecounter++;
      }
      episodecounter++;
      std::cout << "episode : " <<episodecounter << "  stepsize : " << stepsizecounter <<'\n';
    }
  }

  int QLearningAgent::EpsilonGreedyPolicy(std::list<State>::iterator agentstate){
    // O(actions)
    if(distribution(generator) > epsilon){
      //select max valued action
      return agentstate->GetMaxActionType();

    }
    else{
      //select randomly among all actions
      std::list<int> actions = agentstate->GetPureState()->GetAvailableActions();
      int count = (int)(distribution(generator) * actions.size());
      std::list<int>::iterator it = actions.begin();
      std::advance(it,count);
      return *it;
    }
  }

  std::list<State>::iterator QLearningAgent::AddNewStateToQTable(rlinterface::State* state){
    // Searches State in qtable and adds if it not exist O(states)
    // If it exist update its action list O(actions^2)
    // O(states+actions^2)
    // Returns iterator points that state in table.
    std::unique_ptr<rlinterface::State> t1(state->clone());
    State searchobject(std::move(t1));
    std::list<State>::iterator it = find(qtable.begin(), qtable.end(),searchobject);
    if(it == qtable.end()){
      qtable.push_back(searchobject);
      return --it;
    }
    else{
      it->UpdateActionList(state);
      return it;
    }
  }

  std::list<State>& QLearningAgent::GetQTable(){
    return qtable;
  }

  void QLearningAgent::SetAlpha(double alpha){
    this->alpha = alpha;
  }

  void QLearningAgent::SetEpsilon(double epsilon){
    this->epsilon = epsilon;
  }

}
