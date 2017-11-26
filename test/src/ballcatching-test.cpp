#include <iostream>
#include <vector>
#include <memory>

#include "../../include/environment/ballcatching/ballcatchingworld.h"
#include "../../include/environment/ballcatching/toroidalstate.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

#include "../../include/agent/qlearning/action.h"
#include "../../include/agent/qlearning/state.h"
#include "../../include/agent/qlearning/qlearningagent.h"

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"

using namespace std;


int main() {

  // ballcatching::BallCatchingWorld w1(15,0,10,-1,9,9);
  //
  // std::cout << "helllo???" << '\n';
  // int action = 0;
  // rlinterface::Response *response;
  //
  // unique_ptr<rlinterface::State> state;
  // ballcatching::ToroidalState *s2;
  //
  // while (action != 9){
  //   cin >> action;
  //
  //   response = w1.TakeAnAction(action);
  //
  //   state = std::move(response->GetState());
  //   s2 = (ballcatching::ToroidalState*)state.get();
  //
  //   std::cout << "agent " << s2->GetX() << "  " << s2->GetY() << " : " << response->GetReward() << '\n';
  //   std::cout << "ball  " << w1.GetBallX() << "  " << w1.GetBallY() << '\n';
  // }


  // ballcatching::BallCatchingWorld* world1p = new ballcatching::BallCatchingWorld(15,0,10,-1,9,9,-1,-1);
  // std::unique_ptr<ballcatching::BallCatchingWorld> world1(world1p);
  // qlearning::QLearningAgent agent1(std::move(world1), 0.1, 1, 0.1);
  // agent1.Train(40000);
  // agent1.SetEpsilon(0);
  // agent1.Train(50);

  // simplegridworld::GridWorld* world2p = new simplegridworld::GridWorld(10,9,9,0,0,1);
  // std::unique_ptr<simplegridworld::GridWorld> world2(world2p);
  //
  // simplegridworld::GridWorld* world3p = new simplegridworld::GridWorld(10,5,5,7,1,1);
  // std::unique_ptr<simplegridworld::GridWorld> world3(world3p);

  ballcatching::BallCatchingWorld* world1p = new ballcatching::BallCatchingWorld(15,0,10,-1,-1,-1,-1,-1);
  std::unique_ptr<ballcatching::BallCatchingWorld> world1(world1p);

  ballcatching::BallCatchingWorld* world2p = new ballcatching::BallCatchingWorld(15,1,10,-1,6,6,0,0);
  std::unique_ptr<ballcatching::BallCatchingWorld> world2(world2p);



  qlearning::QLearningAgent agent2(std::move(world1), 0.1, 0.95, 0.1);
  agent2.TrainRandom(10000);
  agent2.SetEpsilon(0);
  agent2.TrainRandom(10);

  // int i;
  // std::cin >> i;
  //  agent2.SetEpsilon(0.1);
  //
  // agent2.SetEnvironment(std::move(world2));
  // agent2.TrainRandom(5000);
  // agent2.SetEpsilon(0);
  // agent2.TrainRandom(10);



  std::cout << "end of the program" << '\n';

}
