/*
    @file gridwold,cpp
    @author Bilal Dinc
    @date 1.0 25/09/2017
    @brief
*/

/*
    Simplest gridworld environment. To try algorthms in simplest case.
    Terminal state gives specified reward.
    Indexed as (0 1 ... size-1)
    X axis increases to right
    Y axis increases to down
    action 0 is right
    action 1 is left
    action 2 is up
    action 3 is down
    If limits of grid is reached, actions stil available but state is left unchanged

    If terminal state is reached next state is returned as terminal state but
    environment is reseted to initial state.
*/

/*
    Tested
    TO-DO
    throw expection or terminate program in case of invalid action type
*/

#include "../../../include/environment/simplegridworld/gridworld.h"

namespace simplegridworld{

  GridWorld::GridWorld(int size, int initialX, int initialY, int terminalX, int terminalY, double reward):
  size(size), initialX(initialX), initialY(initialY),
  currentX(currentX), currentY(currentY),
  terminalX(terminalX), terminalY(terminalY), reward(reward){
    currentX = initialX;
    currentY = initialY;
  }

  rlinterface::State* GridWorld::ObserveState(){
    //callee must handle deallocating the memory
    return  new GridState(currentX,currentY,false);
  }

  rlinterface::Response* GridWorld::TakeAnAction(int type){
    //callee must handle allocated memory
    int nextX = currentX;
    int nextY = currentY;

    //decide next state according the action type
    if (type == 0){
      nextX = currentX + 1;
      nextY = currentY;
    }
    else if(type == 1) {
      nextX = currentX - 1;
      nextY = currentY;
    }
    else if(type == 2){
      nextX = currentX;
      nextY = currentY - 1;
    }
    else if(type == 3){
      nextX = currentX;
      nextY = currentY + 1;
    }
    else{
      //invalid action type
      std::cout << "invalid action! something is wrong" << '\n';
    }

    //check boundaries
    if(nextX >= size || nextY >= size || nextX < 0 || nextY < 0){
      nextX = currentX;
      nextY = currentY;
    }

    //check terminal
    bool isterminal = false;
    double nextreward = 0;
    if((nextX == terminalX) && (nextY == terminalY)){
      nextreward = reward;
      isterminal = true;
      currentX = initialX;
      currentY = initialY;
    }
    else{
      currentX = nextX;
      currentY = nextY;
    }

    //Create return values
    std::unique_ptr<GridState> gridstate(new GridState(nextX,nextY,isterminal));
    rlinterface::Response *response = new rlinterface::Response(std::move(gridstate),nextreward);


    return response;
  }

}
