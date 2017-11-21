#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/agent/prioritized-sweeping/state.h"
#include "../../include/agent/prioritized-sweeping/action.h"
#include "../../include/agent/prioritized-sweeping/model.h"
#include "../../include/agent/prioritized-sweeping/prioritizedsweepingagent.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int main() {
    std::cout << "hello world!" << '\n';

    std::string filename = "logs";

    int size = 5;
    int initialX = 0;
    int initialY = 0;
    int terminalX = 4;
    int terminalY = 4;
    double reward = 1;
    simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld(size,initialX,initialY,terminalX,terminalY,reward);
    std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

    double gamma = 0.95;
    double epsilon = 0.1;
    double planning_limit = 10;
    double priority_threshold = 0.00000001;
    prioritizedsweeping::PrioritizedSweepingAgent agent1(std::move(world1), gamma, epsilon, planning_limit, priority_threshold,filename);

    agent1.SetLogModel(true);
    agent1.SetLogQtable(true);
    agent1.SetLogExperience(true);
    agent1.SetLogHistory(true);
    agent1.Train(10);
    agent1.Train(10);

    std::cout << "End of the program" << '\n';
    return 0;
}
