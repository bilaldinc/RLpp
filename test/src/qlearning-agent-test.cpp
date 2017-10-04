#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/agent/qlearning/action.h"
#include "../../include/agent/qlearning/state.h"
#include "../../include/agent/qlearning/qlearningagent.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int Test(qlearning::State state){
  std::cout << "inside test function" << '\n';
}


int main() {
  std::cout << "hello world!" << '\n';
  simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld(10,0,0,9,9,0.1);
  std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

  qlearning::QLearningAgent agent1(std::move(world1), 0.1, 0.99, 0.1);

  agent1.TrainV2(3000);

  std::list<qlearning::State>& qtable = agent1.GetQTable();

  int observervedstatecounter = 0;
  for(std::list<qlearning::State>::iterator it = qtable.begin(); it != qtable.end(); it++){
    int x = ((simplegridworld::GridState*)it->GetPureState())->GetX();
    int y = ((simplegridworld::GridState*)it->GetPureState())->GetY();
    double value = it->GetMaxActionValue();
    std::cout << "(" << x << "," << y << ") --> " << value << endl;
    observervedstatecounter++;
  }

  std::cout << "#of observerved states : " << observervedstatecounter <<'\n';
  std::cout << "End of the program" << '\n';
}
