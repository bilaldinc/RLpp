/*
    @file action,cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief customize action types and adding them additional information
*/

/*
  This class wrapes action types. adding additional information each instences
  (value etc.)
  Smaller then operator is overloaded for ordering actions.

*/

#include "../../../include/agent/rl-cd-s/action.h"

namespace rlcds{

  Action::Action(int type) : type(type){

  }

  Action::Action(int type, double value) : type(type), value(value){

  }

  int Action::GetType() const{
    return type;
  }

  double Action::GetValue() const{
    return value;
  }

  void Action::SetValue(double value){
    this->value = value;
  }

  bool Action::operator == (const Action& action){
    return action.GetType() == this->GetType();
  }

  bool Action::operator < (const Action& action){
    if (value < action.GetValue()){
      return true;
    }
    else{
      return false;
    }
  }

}
