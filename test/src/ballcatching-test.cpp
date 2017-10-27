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


  ballcatching::BallCatchingWorld* world1p = new ballcatching::BallCatchingWorld(15,0,10,-1,9,9,1,1);
  std::unique_ptr<ballcatching::BallCatchingWorld> world1(world1p);
  qlearning::QLearningAgent agent1(std::move(world1), 0.1, 1, 0.1);
  //agent1.Train(40000);

  simplegridworld::GridWorld* world2p = new simplegridworld::GridWorld(10,0,0,9,9,1);
  std::unique_ptr<simplegridworld::GridWorld> world2(world2p);
  qlearning::QLearningAgent agent2(std::move(world2), 0.1, 0.99, 0.1);
  agent1.Train(3000);

  std::cout << "end of the program" << '\n';

}
