/*
    @file gridstate,cpp
    @author Bilal Dinc
    @date 1.0 23/10/2017
    @brief
*/

#include "../../../include/environment/ballcatching/toroidalstate.h"

namespace ballcatching{

  ToroidalState::ToroidalState(int x, int y, bool terminal) : x(x), y(y), terminal(terminal){
    //For simplicity all states has all actions
    actions.push_back(0);
    actions.push_back(1);
    actions.push_back(2);
    actions.push_back(3);
    actions.push_back(4);

  }
  ToroidalState::ToroidalState(int x, int y, bool terminal, std::list<int> actions) :
  x(x), y(y), terminal(terminal), actions(actions){

  }

  std::list<int> ToroidalState::GetAvailableActions(){
    return actions;
  }

  bool ToroidalState::operator == (const State& s){
    ToroidalState& s2 = ((ToroidalState&)s);

    bool eq = (s2.GetX() == this->GetX()) && (s2.GetY() == this->GetY());
    bool t1 = s2.IsTerminal();
    bool t2 = this->IsTerminal();
    return (t1 && t2) || (eq && !t1 && !t2);
  }

  bool ToroidalState::IsTerminal(){
    return terminal;
  }

  rlinterface::State* ToroidalState::clone(){
    return new ToroidalState(x,y,terminal,actions);
  }

  int ToroidalState::GetX() const{
    return this->x;
  }

  int ToroidalState::GetY() const{
    return this->y;
  }

  std::string ToroidalState::ToString(){
      if(terminal){
          return "(term)";
      }
      else{
          return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
      }
  }

}
