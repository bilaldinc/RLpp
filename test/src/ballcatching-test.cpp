#include <iostream>
#include <vector>
#include <memory>

#include "../../include/environment/ballcatching/ballcatchingworld.h"
#include "../../include/environment/ballcatching/toroidalstate.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;


int main() {

  ballcatching::BallCatchingWorld w1(15,0,10,-1);

  std::cout << "helllo???" << '\n';

  int action = 0;
  rlinterface::Response *response;


  unique_ptr<rlinterface::State> state;
  ballcatching::ToroidalState *s2;

  while (action != 9){
    cin >> action;

    response = w1.TakeAnAction(action);

    state = std::move(response->GetState());
    s2 = (ballcatching::ToroidalState*)state.get();

    std::cout << "agent " << s2->GetX() << "  " << s2->GetY() << " : " << response->GetReward() << '\n';
    std::cout << "ball  " << w1.GetBallX() << "  " << w1.GetBallY() << '\n';
  }

}
