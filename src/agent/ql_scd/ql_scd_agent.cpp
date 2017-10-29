/*
	scd
*/

#include "../../../include/agent/ql_scd/ql_scd_agent.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <strings.h>

namespace ql_scd {

	QL_SCD_Agent::QL_SCD_Agent(std::unique_ptr<rlinterface::Environment> environment, double alpha, double gamma, double epsilon):
	environment(std::move(environment)), alpha(alpha), gamma(gamma), epsilon(epsilon){

	}

	int listenFd, numberOfTokens;
	bool loop = false;
	struct sockaddr_in svrAdd;
	struct hostent *server;

	void QL_SCD_Agent::socketConnection (int portNo) {
		listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (listenFd < 0) {
			std::cerr << "Cannot open socket" << std::endl;
			return;
		}
		server = gethostbyname("localhost");
		if (server == NULL) {
			std::cerr << "Host does not exist" << std::endl;
			return;
		}
		bzero((char *) &svrAdd, sizeof(svrAdd));
		svrAdd.sin_family = AF_INET;
		bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
		svrAdd.sin_port = htons(portNo);
		int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
		if (checker < 0) {
			std::cerr << "Cannot connect!" << std::endl;
			return;
		}
		else {
			std::cout << "Connection successful." << std::endl;
		}
	}

	void QL_SCD_Agent::Train(int numberofepisode){
		int episodecounter = 1;
		int total_step_size_counter = 1;
		char token;
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
				token = nextaction + '0';
				write(listenFd, &token, sizeof(token));
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
			DecreaseEpsilon(0.995);
			episodecounter++;
			total_step_size_counter += stepsizecounter;
			std::cout << "episode : " <<episodecounter << "  stepsize : " << stepsizecounter <<'\n';
		}
		std::cout << "total steps: " << total_step_size_counter << std::endl;
		// token = 'x';
		// write(listenFd, &token, 1);
	}

	void QL_SCD_Agent::TrainRandom(int numberofepisode){
		// Uses EpsilonGreedyPolicyRandom function. See function implementation
		int episodecounter = 1;
		int total_step_size_counter = 1;
		char token;
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
				token = nextaction + '0';
				write(listenFd, &token, sizeof(token));
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
			DecreaseEpsilon(0.995);
			episodecounter++;
			total_step_size_counter += stepsizecounter;
		}
		std::cout << "total steps: " << total_step_size_counter << std::endl;
	}

	void QL_SCD_Agent::TrainV2(int numberofepisode){
		// Uses EpsilonGreedyPolicyV2 function. See function implementation
		int episodecounter = 1;
		int total_step_size_counter = 1;
		char token;
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
				token = nextaction + '0';
				write(listenFd, &token, sizeof(token));
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
			DecreaseEpsilon(0.995);
			episodecounter++;
			total_step_size_counter += stepsizecounter;
		}
		std::cout << "total steps: " << total_step_size_counter << std::endl;
	}

	void QL_SCD_Agent::TerminateLearning () {
		char token;
		token = 'x';
		write(listenFd, &token, 1);
	}

	int QL_SCD_Agent::EpsilonGreedyPolicy(std::list<State>::iterator agentstate){
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

	int QL_SCD_Agent::EpsilonGreedyPolicyRandom(std::list<State>::iterator agentstate){
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

	int QL_SCD_Agent::EpsilonGreedyPolicyV2(std::list<State>::iterator agentstate){
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

	std::list<State>::iterator QL_SCD_Agent::AddNewStateToQTable(rlinterface::State* state){
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

	std::list<State>& QL_SCD_Agent::GetQTable(){
		return qtable;
	}

	void QL_SCD_Agent::SetAlpha(double alpha){
		this->alpha = alpha;
	}

	void QL_SCD_Agent::SetEpsilon(double epsilon){
		this->epsilon = epsilon;
	}

	void QL_SCD_Agent::DecreaseEpsilon (double factor) {
		if (this->epsilon > 0) {
			this->epsilon *= factor;
		}
	}

	void QL_SCD_Agent::SetEnvironment (std::unique_ptr<rlinterface::Environment> new_environment) {
		this->environment = std::move(new_environment);
	}

}
