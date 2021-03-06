#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "../../include/environment/ballcatching/toroidalstate.h"
#include "../../include/environment/ballcatching/ballcatchingworld.h"
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
    std::string filename = "logs-p";

    int size = 15;
    int ball_direction = 0;
    double reward = 10;
    double punishment = -1;
    int start_ball_x = -1;
    int start_ball_y = -1;
    int start_agent_x = -1;
    int start_agent_y = -1;
    ballcatching::BallCatchingWorld* world2p = new ballcatching::BallCatchingWorld(size,ball_direction,reward,punishment,start_ball_x,start_ball_y,start_agent_x,start_agent_y);
    std::unique_ptr<ballcatching::BallCatchingWorld> world2(world2p);

    size = 10;
    int initialX = 0;
    int initialY = 0;
    int terminalX = 9;
    int terminalY = 9;
    reward = 10;
    simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld("hugeHalls.gwmap",reward);
    std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

    double gamma = 0.9;
    double epsilon = 0.1;
    double planning_limit = 250;
    double priority_threshold = 0.01;
    prioritizedsweeping::PrioritizedSweepingAgent agent1(std::move(world1), gamma, epsilon, planning_limit, priority_threshold,filename);

    // agent1.SetLogModel(true);
    // agent1.SetLogQtable(true);
    // agent1.SetLogExperience(true);
    // agent1.SetLogHistory(true);
    agent1.Train(50);
    std::cout << "--- Epsilon 0 ---" << '\n';
    // agent1.SetEpsilon(0);
    // agent1.Train(5);
    agent1.SetLogModel(true);
    agent1.SetLogQtable(true);
    agent1.InitiateLogsFiles();
    agent1.LogModel(0,0);
    agent1.LogQtable(0,0,0);

    std::cout << "End of the program" << '\n';
    return 0;
}
