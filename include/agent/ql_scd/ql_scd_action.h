/*
	scd
*/

#ifndef _ACTION_H_INCLUDED
#define _ACTION_H_INCLUDED

namespace ql_scd {

	class Action {

	public:
		Action(int type, double value);
		Action(int type);

		int GetType() const;
		double GetValue() const;
		void SetValue(double value);
		bool operator == (const Action& action);
		bool operator < (const Action& action);

	private:
		int type;
		double value;
	};

}

#endif
