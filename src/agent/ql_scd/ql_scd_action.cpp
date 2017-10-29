/*
	scd
*/

#include "../../../include/agent/ql_scd/ql_scd_action.h"

namespace ql_scd {

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
