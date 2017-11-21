/*
    @file gridstate,cpp
    @author Bilal Dinc
    @date 1.0 25/09/2017
    @brief simple gridworld environment
*/

#include "../../../include/environment/simplegridworld/gridstate.h"

namespace simplegridworld{

  GridState::GridState(int x, int y, bool terminal) : x(x), y(y), terminal(terminal){
    //For simplicity all states has all actions
    actions.push_back(0);
    actions.push_back(1);
    actions.push_back(2);
    actions.push_back(3);

  }
  GridState::GridState(int x, int y, bool terminal, std::list<int> actions) :
  x(x), y(y), terminal(terminal), actions(actions){

  }

  std::list<int> GridState::GetAvailableActions(){
    return actions;
  }

  bool GridState::operator == (const State& s){
    GridState& s2 = ((GridState&)s);

    bool eq = (s2.GetX() == this->GetX()) && (s2.GetY() == this->GetY());
    bool t1 = s2.IsTerminal();
    bool t2 = this->IsTerminal();
    return (t1 && t2) || (eq && !t1 && !t2);
  }

  bool GridState::IsTerminal(){
    return terminal;
  }

  rlinterface::State* GridState::clone(){
    return new GridState(x,y,terminal,actions);
  }

  int GridState::GetX() const{
    return this->x;
  }

  int GridState::GetY() const{
    return this->y;
  }

  std::string GridState::ToString(){
      if(terminal){
          return "(term)";
      }
      else{
          return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
      }
  }

}
