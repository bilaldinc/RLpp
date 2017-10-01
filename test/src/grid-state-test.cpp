#include <iostream>
#include <vector>
#include <memory>
#include "../../include/environment/simplegridworld/gridstate.h"
#include "../../include/rlinterface/state.h"


int main() {
  simplegridworld::GridState gridstate1(15,26,false);
  simplegridworld::GridState* gridstate2 = new simplegridworld::GridState(15,26,true);
  rlinterface::State* gridstate3 = new simplegridworld::GridState(48,26,true);
  rlinterface::State* gridstate4 = gridstate3->clone();

  std::cout << (*gridstate3 == *gridstate4) << '\n';
  std::cout << (*gridstate3 == *gridstate2) << '\n';
  std::cout << (gridstate1 == *gridstate2) << '\n';

  std::cout << ((simplegridworld::GridState*)(gridstate3))->GetX() << '\n';

  std::cout << "end of the program" << '\n';

  return 0;

}
