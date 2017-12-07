#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <limits>
#include <algorithm>

#include "../../include/environment/ballcatching/toroidalstate.h"
#include "../../include/environment/ballcatching/ballcatchingworld.h"
#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/agent/rl-scd/state.h"
#include "../../include/agent/rl-scd/action.h"
#include "../../include/agent/rl-scd/model.h"
#include "../../include/agent/rl-scd/rlcdagent.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int main() {

    std::string filename = "logs";

	// int size = 10;
	// int initialX = 9;
	// int initialY = 9;
	// int terminalX = 0;
	// int terminalY = 0;
	// double reward = 1;
	// simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld("hugeHalls.gwmap",reward);
	// std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

	simplegridworld::GridWorld* worldp = new simplegridworld::GridWorld(10, 0, 0, 9, 9, 0.1);
	std::unique_ptr<simplegridworld::GridWorld> world1_1(worldp);

	worldp = new simplegridworld::GridWorld(10, 0, 0, 0, 9, 0.1);
	std::unique_ptr<simplegridworld::GridWorld> world2_1(worldp);
	
	worldp = new simplegridworld::GridWorld(10, 0, 0, 9, 9, 0.1);
	std::unique_ptr<simplegridworld::GridWorld> world1_2(worldp);

	worldp = new simplegridworld::GridWorld(10, 0, 0, 0, 9, 0.1);
	std::unique_ptr<simplegridworld::GridWorld> world2_2(worldp);
	
	
	



	double gamma = 0.9;
    double epsilon = 0.1;
    double planning_limit = 250;
    double priority_threshold = 0.01;
    int M = 2;
    double Emin = -0.1;
    double p = 0.4;
    double omega = 0;
    double Rmax = 10;
    double Rmin = -1;
	rlscd::RLCDAgent agent1(std::move(world1_1), gamma, epsilon, planning_limit, priority_threshold,filename,M,Emin,p,omega,Rmax,Rmin);
	agent1.SetLogExperience(false);
	agent1.SetLogErrors(false);
	agent1.SetLogModel(false);
	agent1.SetLogQtable(false);
	agent1.SetLogHistory(false);

	agent1.socketConnection(20000);

	agent1.Train(200);

	agent1.SetEnvironment(std::move(world2_1));
	agent1.Train(200);

	agent1.SetEnvironment(std::move(world1_2));
	agent1.Train(200);

	agent1.SetEnvironment(std::move(world2_2));
	agent1.Train(200);

	agent1.TerminateLearning();

    std::cout << "End of the program" << '\n';
    return 0;
}
