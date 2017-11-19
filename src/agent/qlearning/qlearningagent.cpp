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
    // Uses EpsilonGreedyPolicy function. See function implementation
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
      std::cout << "episode : " <<episodecounter << "  stepsize : " << stepsizecounter <<'\n';
      episodecounter++;
    }
  }

  void QLearningAgent::TrainRandom(int numberofepisode){
    // Uses EpsilonGreedyPolicyRandom function. See function implementation
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
        int nextaction = EpsilonGreedyPolicyRandom(currentagentstate);
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
      std::cout << "episode : " <<episodecounter << "  stepsize : " << stepsizecounter <<'\n';
      episodecounter++;
    }
  }

  void QLearningAgent::TrainV2(int numberofepisode){
    // Uses EpsilonGreedyPolicyV2 function. See function implementation
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
        int nextaction = EpsilonGreedyPolicyV2(currentagentstate);
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
      std::cout << "episode : " <<episodecounter << "  stepsize : " << stepsizecounter <<'\n';
      episodecounter++;
    }
  }

  int QLearningAgent::EpsilonGreedyPolicy(std::list<State>::iterator agentstate){
    // O(actions)
    // Selects greedy action with the probability = 1 - e + (1 / #ofactions)
    // If some greedy actions are equal, selects first encountered in list
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

  int QLearningAgent::EpsilonGreedyPolicyRandom(std::list<State>::iterator agentstate){
    // O(actions^2)
    // Selects greedy action with the probability = 1-e + (1-e / #ofactions)
    // If some greedy actions are equal, selects randomly among them
    if(distribution(generator) > epsilon){
      //select max valued action
      return agentstate->GetMaxActionTypeRandom();

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

  int QLearningAgent::EpsilonGreedyPolicyV2(std::list<State>::iterator agentstate){
    // O(actions^2)
    // Selects greedy action with the probability = 1-e
    // If some greedy actions are equal, selects randomly among them
    if(distribution(generator) > epsilon){
      //select max valued action
      return agentstate->GetMaxActionTypeRandom();

    }
    else{
      //select randomly among all nongreedy actions
      std::list<int> actions = agentstate->GetPureState()->GetAvailableActions();
      actions.erase(find(actions.begin(), actions.end(), agentstate->GetMaxActionTypeRandom()));
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

  void QLearningAgent::SetEnvironment(std::unique_ptr<rlinterface::Environment> environment) {
      this->environment = std::move(environment);
  }

}
