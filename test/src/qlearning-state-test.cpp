#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "../../include/environment/simplegridworld/gridworld.h"
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/agent/qlearning/action.h"
#include "../../include/agent/qlearning/state.h"
#include "../../include/rlinterface/environment.h"
#include "../../include/rlinterface/state.h"
#include "../../include/rlinterface/response.h"

using namespace std;

int Test(qlearning::State state){
  std::cout << "inside test function" << '\n';
}


int main() {
  simplegridworld::GridState* g1 = new simplegridworld::GridState(15,45,false);
  simplegridworld::GridState* g2 = new simplegridworld::GridState(49,18,false);
  simplegridworld::GridState* g3 = new simplegridworld::GridState(15,45,false);

  std::unique_ptr<rlinterface::State> s1(g1);
  std::unique_ptr<rlinterface::State> s2(g2);
  std::unique_ptr<rlinterface::State> s3(g3);

  std::cout << (*s1 == *s2) << '\n';
  std::cout << (*s1 == *s3) << '\n';

  qlearning::State ss1(std::move(s1));
  qlearning::State ss2(std::move(s2));
  qlearning::State ss3(std::move(s3));

  qlearning::State ss4 = ss2;

  std::cout << (ss4 == ss2) << '\n';
  std::cout << (ss4 == ss1) << '\n';

  Test(ss1);

  auto action = ss1.GetAction(3);
  std::cout << (action->GetValue()) << '\n';
  action->SetValue(60);
  auto action2 = ss1.GetAction(3);
  std::cout << (action2->GetValue()) << '\n';
  action2 = ss1.GetAction(1);
  action2->SetValue(80);
  std::cout << (ss1.GetMaxActionValue()) << '\n';
  std::cout << (ss1.GetMaxActionType()) << '\n';


  std::list<qlearning::Action> actions;
  actions.push_back(qlearning::Action(0,3.0));
  actions.push_back(qlearning::Action(1,3.0));
  actions.push_back(qlearning::Action(5,3.0));
  std::list<qlearning::Action>::iterator it = find(actions.begin(),actions.end(),qlearning::Action(1,0));
  std::cout << (it->GetValue()) << '\n';
  it->SetValue(25);
  it = find(actions.begin(),actions.end(),qlearning::Action(1,0));
  std::cout << (it->GetValue()) << '\n';

  std::list<int> actions2;
  actions2.push_back(1);
  actions2.push_back(3);
  actions2.push_back(2);
  actions2.push_back(6);


  simplegridworld::GridState* g7 = new simplegridworld::GridState(435,4456,false,actions2);
  std::unique_ptr<rlinterface::State> s7(g7);

  ss1.UpdateActionList(s7.get());
  std::cout << " - " << '\n';

  std::list<int> actions3 = (ss1.GetPureState())->GetAvailableActions();
  for(auto i: actions3){
    std::cout << i << '\n';
  }

  // std::cout << " - " << '\n';
  // std::list<qlearning::Action> actions4 = ss1.GetActionList();
  // for(auto i: actions4){
  //   std::cout << (i.GetType()) << '\n';
  // }

  return 0;

}
