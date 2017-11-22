/*
    @file action,cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief customize action types and adding them additional information
*/

#ifndef _CD_ACTION_H_INCLUDED
#define _CD_ACTION_H_INCLUDED

namespace rlcd{

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
