#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/agent/qlearning-scd/action.h"
#include "../../include/agent/qlearning-scd/state.h"
#include "../../include/agent/qlearning-scd/qlearningagent.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int Test(qlearning::State state){
	std::cout << "inside test function" << '\n';
}


int main() {

	simplegridworld::GridWorld* world1p = new simplegridworld::GridWorld(10,0,0,9,9,0.1);
	std::unique_ptr<simplegridworld::GridWorld> world1(world1p);

	simplegridworld::GridWorld* world2p = new simplegridworld::GridWorld(10,0,0,0,9,0.1);
	std::unique_ptr<simplegridworld::GridWorld> world2(world2p);

	qlearning::QLearningAgent agent1(std::move(world1), 0.1, 0.99, 0.3);
	agent1.socketConnection(20000);
	agent1.Train(10000);
	agent1.SetEnvironment(std::move(world2));
	agent1.SetEpsilon(0.3);
	agent1.Train(10000);
	agent1.TerminateLearning();

	// std::list<qlearning::State>& qtable = agent1.GetQTable();

	// int observervedstatecounter = 0;
	// for(std::list<qlearning::State>::iterator it = qtable.begin(); it != qtable.end(); it++){
	//   int x = ((simplegridworld::GridState*)it->GetPureState())->GetX();
	//   int y = ((simplegridworld::GridState*)it->GetPureState())->GetY();
	//   double value = it->GetMaxActionValue();
	//   std::cout << "(" << x << "," << y << ") --> " << value << endl;
	//   observervedstatecounter++;
	// }

	// std::cout << "#of observerved states : " << observervedstatecounter <<'\n';
	// std::cout << "End of the program" << '\n';
}
