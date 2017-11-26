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
#include "../../include/agent/rl-cd/state.h"
#include "../../include/agent/rl-cd/action.h"
#include "../../include/agent/rl-cd/model.h"
#include "../../include/agent/rl-cd/rlcdagent.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int main() {
    std::cout << "hello world!" << '\n';
    std::string filename = "logs";

    int size = 10;
    int initialX = 9;
    int initialY = 9;
    int terminalX = 0;
    int terminalY = 0;
    double reward = 1;
    simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld(size,initialX,initialY,terminalX,terminalY,reward);
    std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

    size = 10;
    initialX = 0;
    initialY = 0;
    terminalX = 9;
    terminalY = 9;
    reward = 1;
    world1p = new simplegridworld::GridWorld(size,initialX,initialY,terminalX,terminalY,reward);
    std::unique_ptr<simplegridworld::GridWorld> world2(world1p);


    size = 15;
    int ball_direction = 0;
    reward = 10;
    double punishment = -1;
    int start_ball_x = -1;
    int start_ball_y = -1;
    int start_agent_x = -1;
    int start_agent_y = -1;
    ballcatching::BallCatchingWorld* world2p = new ballcatching::BallCatchingWorld(size,0,reward,punishment,start_ball_x,start_ball_y,start_agent_x,start_agent_y);
    std::unique_ptr<ballcatching::BallCatchingWorld> ballcatchingR(world2p);

    world2p = new ballcatching::BallCatchingWorld(size,2,reward,punishment,start_ball_x,start_ball_y,start_agent_x,start_agent_y);
    std::unique_ptr<ballcatching::BallCatchingWorld> ballcatchingU(world2p);


    double gamma = 0.95;
    double epsilon = 1;
    double planning_limit = 10;
    double priority_threshold = 0.00000001;
    int M = std::numeric_limits<int>::max();
    double Emin = -0.1;
    double p = 0.5;
    double omega = 0;
    double Rmax = 1;
    double Rmin = 0;
    rlcd::RLCDAgent agent1(std::move(ballcatchingR), gamma, epsilon, planning_limit, priority_threshold,filename,M,Emin,p,omega,Rmax,Rmin);
    agent1.Train(1000);
    agent1.SetLogModel(true);
    // agent1.SetLogQtable(true);
    // agent1.SetLogExperience(true);
    // agent1.SetLogErrors(true);
    agent1.SetLogHistory(true);
    agent1.Train(2);
    // agent1.SetEnvironment(std::move(ballcatchingU));
    //  std::cout << "---Environment is changed---" << '\n';
    // agent1.Train(200);
    // std::cout << "--- Epsilon 0 ---" << '\n';
    // agent1.SetEpsilon(0);
    // agent1.Train(5);
    // agent1.SetLogModel(true);
    // agent1.SetLogQtable(true);
    // agent1.InitiateLogsFiles();
    // agent1.LogModel(0,0);
    // agent1.LogQtable(0,0,0);

    std::cout << "End of the program" << '\n';
    return 0;
}
