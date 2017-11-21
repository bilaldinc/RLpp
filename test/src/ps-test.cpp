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
    std::string filename = "logs";

    int size = 10;
    int ball_direction = 0;
    double reward = 10;
    double punishment = -1;
    int start_ball_x = 5;
    int start_ball_y = 5;
    int start_agent_x = 0;
    int start_agent_y = 0;
    ballcatching::BallCatchingWorld* world2p = new ballcatching::BallCatchingWorld(size,ball_direction,reward,punishment,start_ball_x,start_ball_y,start_agent_x,start_agent_y);
    std::unique_ptr<ballcatching::BallCatchingWorld> world2(world2p);

    size = 5;
    int initialX = 0;
    int initialY = 0;
    int terminalX = 4;
    int terminalY = 4;
    reward = 1;
    simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld(size,initialX,initialY,terminalX,terminalY,reward);
    std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

    double gamma = 0.95;
    double epsilon = 0.1;
    double planning_limit = 30;
    double priority_threshold = 0.00000001;
    prioritizedsweeping::PrioritizedSweepingAgent agent1(std::move(world2), gamma, epsilon, planning_limit, priority_threshold,filename);

    agent1.SetLogModel(false);
    agent1.SetLogQtable(false);
    agent1.SetLogExperience(false);
    agent1.SetLogHistory(true);
    agent1.Train(500);
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
