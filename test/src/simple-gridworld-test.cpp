#include <iostream>
#include <vector>
#include <memory>

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;


int main() {

  simplegridworld::GridWorld g1(5,0,0,4,4,1);


  std::cout << "goodby" << '\n';

  int action = 0;
  rlinterface::Response *response;

  unique_ptr<rlinterface::State> state;
  simplegridworld::GridState *s2;

  while (action != 9){
    cin >> action;

    response = g1.TakeAnAction(action);

    state = std::move(response->GetState());
    s2 = (simplegridworld::GridState*)state.get();

    std::cout << s2->GetX() << "  " << s2->GetY() << " : " << response->GetReward() << '\n';
  }

  return 0;

}
