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
    for (int i = 0; i < size; i++){
            std::vector<char> row;
            for (int j = 0; j < size; j++){
                int state_type = (j == 0) * 8 + (i == 0) * 4 + (j == size - 1) * 2 + (i == size-1) * 1;
                row.push_back(intToHex(state_type));
                std::cout<<state_type<<" ";
            }
            map_matrix.push_back(row);
            std::cout<<std::endl;

    }
  }
  GridWorld::GridWorld(const std::string mapName):
  mapName(mapName){
    std::cout<<mapName<<std::endl;
    std::ifstream infile("../maps/"+mapName);
    std::string line;
    int i = 0;
    while (std::getline(infile, line))
    {
        std::istringstream ss(line);
        if(i == 0){
          ss>>initialX;
          ss>>initialY;
          std::cout<<"initialX: " << initialX << std::endl;
          std::cout<<"initialY: " << initialY << std::endl;
        }
        else if(i == 1){
          ss>>terminalX;
          ss>>terminalY;
          std::cout<<"terminalX: " << terminalX<< std::endl;
          std::cout<<"terminalY: " << terminalY<< std::endl;
        }
        else if(i > 2){
          std::vector<char> row;
          char c;
          while(ss>>c)
          {
              row.push_back(c);
          }
          map_matrix.push_back(row);
        }  
        i++;
    }
    size = map_matrix.size();
  }

  rlinterface::State* GridWorld::ObserveState(){
    //callee must handle deallocating the memory
    return  new GridState(currentX,currentY,false);
  }

  rlinterface::Response* GridWorld::TakeAnAction(int type){
    //callee must handle allocated memory
    int nextX = currentX;
    int nextY = currentY;
    // std::cout<<"\nmap: "<<map_matrix[currentX][currentY]<<std::endl;
    // std::cout<<"type: "<<type<<std::endl;
    // std::cout<<"cx: "<<currentX<<", cy: "<<currentY<<std::endl;
    

    //decide next state according the action type
    if (type == 0){
      if('2' != map_matrix[currentY][currentX] &&  '3' != map_matrix[currentY][currentX] &&  '6' != map_matrix[currentY][currentX] &&  '7' != map_matrix[currentY][currentX] &&  'A' != map_matrix[currentY][currentX] &&  'B' != map_matrix[currentY][currentX] &&  'E' != map_matrix[currentY][currentX] &&  'F' != map_matrix[currentY][currentX]){
        nextX = currentX + 1;
        nextY = currentY;
      }
    }
    else if(type == 1) {
      if('8' != map_matrix[currentY][currentX] &&  '9' != map_matrix[currentY][currentX] &&  'A' != map_matrix[currentY][currentX] &&  'B' != map_matrix[currentY][currentX] &&  'C' != map_matrix[currentY][currentX] &&  'D' != map_matrix[currentY][currentX] &&  'E' != map_matrix[currentY][currentX] &&  'F' != map_matrix[currentY][currentX]){
        nextX = currentX - 1;
        nextY = currentY;
      }

    }
    else if(type == 2){
      if('4' != map_matrix[currentY][currentX] &&  '5' != map_matrix[currentY][currentX] &&  '6' != map_matrix[currentY][currentX] &&  '7' != map_matrix[currentY][currentX] &&  'C' != map_matrix[currentY][currentX] &&  'D' != map_matrix[currentY][currentX] &&  'E' != map_matrix[currentY][currentX] &&  'F' != map_matrix[currentY][currentX]){
        nextX = currentX;
        nextY = currentY - 1;
      }

    }
    else if(type == 3){
      if('1' != map_matrix[currentY][currentX] &&  '3' != map_matrix[currentY][currentX] &&  '5' != map_matrix[currentY][currentX] &&  '7' != map_matrix[currentY][currentX] &&  '9' != map_matrix[currentY][currentX] &&  'B' != map_matrix[currentY][currentX] &&  'D' != map_matrix[currentY][currentX] &&  'F' != map_matrix[currentY][currentX]){
        nextX = currentX;
        nextY = currentY + 1;
      }

    }
    else{
      //invalid action type
      std::cout << "invalid action! something is wrong" << '\n';
    }

    // std::cout<<"nx: "<<nextX<<", ny: "<<nextY<<std::endl;
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
  char GridWorld::intToHex(int i){
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    return hex[i];
     }

}
