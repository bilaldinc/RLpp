/*
	scd
*/

#ifndef _Q_QLEARNING_AGENT_INCLUDED
#define _Q_QLEARNING_AGENT_INCLUDED

#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"
#include "../../../include/agent/ql_scd/ql_scd_state.h"
#include "../../../include/agent/ql_scd/ql_scd_action.h"

namespace ql_scd {

	class QL_SCD_Agent {

	private:
		//environment object
		std::unique_ptr<rlinterface::Environment> environment;

		//parameters
		double alpha;
		double gamma;
		double epsilon;

		//termination conditions
		double threshold;
		int buffersize;

		//qtable
		std::list<State> qtable;

		//random number generator and distribution
		std::random_device rd;
		std::default_random_engine generator = std::default_random_engine(rd());
		std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0.0,1.0);

	public:
		QL_SCD_Agent(std::unique_ptr<rlinterface::Environment> environment, double alpha, double gamma, double epsilon);
		void socketConnection(int portNo);
		void Train(int numberofepisode);
		void TrainRandom(int numberofepisode);
		void TrainV2(int numberofepisode);
		std::list<State>& GetQTable();
		void SetAlpha(double alpha);
		void SetEpsilon(double epsilon);
		void DecreaseEpsilon(double factor);
		void SetEnvironment (std::unique_ptr<rlinterface::Environment> new_environment);
		void TerminateLearning();

		int EpsilonGreedyPolicy(std::list<State>::iterator agentstate);
		int EpsilonGreedyPolicyRandom(std::list<State>::iterator agentstate);
		int EpsilonGreedyPolicyV2(std::list<State>::iterator agentstate);
		std::list<State>::iterator AddNewStateToQTable(rlinterface::State* state);

	};

}

#endif
