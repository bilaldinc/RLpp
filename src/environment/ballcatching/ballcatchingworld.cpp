/*
    @file gridwold,cpp
    @author Bilal Dinc
    @date 1.0 23/10/2017
    @brief
*/

/*
    Toroidal gridworld environment with a ball that moves along specified direction each time step
    If agent cathes the ball it gets specified reward, otherwise it gets punishment
    Indexed as (0 1 ... size-1)
    X axis increases to right
    Y axis increases to down
    action 0 is right
    action 1 is left
    action 2 is up
    action 3 is down
    action 4 is do nothing

    If terminal state is reached next state is returned as terminal state but
    environment is reseted to initial state.

    If start state of agent specified as (-1,-1) every episode agent start at random state
    If start state of ball specified as (-1,-1) every episode ball start at random state

    States are  position of the ball relative to the catcher.
*/

/*
    Tested
    TO-DO
    throw expection or terminate program in case of invalid action type
*/

#include "../../../include/environment/ballcatching/ballcatchingworld.h"

namespace ballcatching{

  BallCatchingWorld::BallCatchingWorld(int size, int ball_direction, double reward, double punishment,int start_ball_x, int start_ball_y,int start_agent_x, int start_agent_y):
  size(size), reward(reward), ball_direction(ball_direction), punishment(punishment),
  start_ball_x(start_ball_x), start_ball_y(start_ball_y), start_agent_x(start_agent_x), start_agent_y(start_agent_y){
    StartEpisode();
  }

  rlinterface::State* BallCatchingWorld::ObserveState(){
    //callee must handle deallocating the memory
    int relative_x = Mod(current_ball_x - current_agent_x,size);
    int relative_y = Mod(current_ball_y - current_agent_y,size);
    return  new ToroidalState(relative_x,relative_y,false);
  }

  rlinterface::Response* BallCatchingWorld::TakeAnAction(int type){
    //callee must handle allocated memory
    int next_agent_x = current_agent_x;
    int next_agent_y = current_agent_y;

    //decide next state according the action type
    if (type == 0){
      next_agent_x = Mod(current_agent_x + 1,size);
      next_agent_y = current_agent_y;
    }
    else if(type == 1) {
      next_agent_x = Mod(current_agent_x - 1,size);
      next_agent_y = current_agent_y;
    }
    else if(type == 2){
      next_agent_x = current_agent_x;
      next_agent_y = Mod(current_agent_y - 1,size);
    }
    else if(type == 3){
      next_agent_x = current_agent_x;
      next_agent_y = Mod(current_agent_y + 1,size);
    }
    else if(type == 4){
      next_agent_x = current_agent_x;
      next_agent_y = current_agent_y;
    }
    else{
      //invalid action type
      std::cout << "invalid action! something is wrong" << '\n';
    }

    int next_ball_x = current_ball_x;
    int next_ball_y = current_ball_y;
    //decide next ball position
    if (ball_direction == 0){
      next_ball_x = Mod(current_ball_x + 1,size);
      next_ball_y = current_ball_y;
    }
    else if(ball_direction == 1) {
      next_ball_x = Mod(current_ball_x - 1,size);
      next_ball_y = current_ball_y;
    }
    else if(ball_direction == 2){
      next_ball_x = current_ball_x;
      next_ball_y = Mod(current_ball_y - 1,size);
    }
    else if(ball_direction == 3){
      next_ball_x = current_ball_x;
      next_ball_y = Mod(current_ball_y + 1,size);
    }
    else{
      //invalid ball position
      std::cout << "invalid ball position! something is wrong" << '\n';
    }


    //check terminal
    bool isterminal = false;
    double next_reward = punishment;
    if((next_agent_x == next_ball_x) && (next_agent_y == next_ball_y)){
      next_reward = reward;
      isterminal = true;

      // random start or normal
      StartEpisode();
    }
    else{
      next_reward = punishment;
      isterminal = false;
      current_ball_x = next_ball_x;
      current_ball_y = next_ball_y;
      current_agent_x = next_agent_x;
      current_agent_y = next_agent_y;
    }
    //Create return values
    int relative_x = Mod(current_ball_x - current_agent_x,size);
    int relative_y = Mod(current_ball_y - current_agent_y,size);
    std::unique_ptr<ToroidalState> toroidal_state(new ToroidalState(relative_x,relative_y,isterminal));
    rlinterface::Response *response = new rlinterface::Response(std::move(toroidal_state),next_reward);

    return response;
  }

  void BallCatchingWorld::SetBallDirection(int ball_direction){
    this->ball_direction = ball_direction;
  }

  int BallCatchingWorld::Mod(int a, int b){
     int ret = a % b;
     if(ret < 0){
        ret += b;
     }
     return ret;
  }

  int BallCatchingWorld::GetBallX(){
    return current_ball_x;
  }

  int BallCatchingWorld::GetBallY(){
    return current_ball_y;
  }

  void BallCatchingWorld::StartEpisode(){
      std::vector<int> temp_list_x;
      std::vector<int> temp_list_y;
      if(start_agent_y == -1 && start_agent_x == -1){
          if(start_ball_y == -1 && start_ball_x == -1){
              int current_agent_x = (int)(distribution(generator) * size);
              int current_agent_y = (int)(distribution(generator) * size);
              for (size_t i = 0; i < size; i++) {
                  if(current_agent_x != i){
                      temp_list_x.push_back(i);
                  }
                  if(current_agent_y != i){
                      temp_list_y.push_back(i);
                  }
              }
              int random_start_ball_x = (int)(distribution(generator) * (size-1));
              int random_start_ball_y = (int)(distribution(generator) * (size-1));
              current_ball_x = temp_list_x.at(random_start_ball_x);
              current_ball_y = temp_list_y.at(random_start_ball_y);

          }
          else{
              current_ball_x = start_ball_x;
              current_ball_y = start_ball_y;
              for (size_t i = 0; i < size; i++) {
                  if(start_ball_x != i){
                     temp_list_x.push_back(i);
                  }
                  if(start_ball_y != i){
                      temp_list_y.push_back(i);
                  }
              }
              int random_start_agent_x = (int)(distribution(generator) * (size-1));
              int random_start_agent_y = (int)(distribution(generator) * (size-1));
              current_agent_x = temp_list_x.at(random_start_agent_x);
              current_agent_y = temp_list_y.at(random_start_agent_y);
              }
      }
      else{
          if(start_ball_y == -1 && start_ball_x == -1){
              current_agent_x = start_agent_x;
              current_agent_y = start_agent_y;
              for (size_t i = 0; i < size; i++) {
                  if(start_agent_x != i){
                      temp_list_x.push_back(i);
                  }
                  if(start_agent_y != i){
                      temp_list_y.push_back(i);
                  }
              }
              int random_start_ball_x = (int)(distribution(generator) * (size-1));
              int random_start_ball_y = (int)(distribution(generator) * (size-1));
              current_ball_x = temp_list_x.at(random_start_ball_x);
              current_ball_y = temp_list_y.at(random_start_ball_y);
          }
          else{
              current_agent_x = start_agent_x;
              current_agent_y = start_agent_y;
              current_ball_x = start_ball_x;
              current_ball_y = start_ball_y;
          }
      }
  }

  std::list<rlinterface::State*> BallCatchingWorld::CreateAllPossibleStates(){
      std::list<rlinterface::State*> list;
      for (size_t i = 0; i < size; i++) {
          for (size_t j = 0; j < size; j++) {
              if(i == 0 && j == 0){
                  list.push_back(new ToroidalState(i,j,true));
              }
              else{
                  list.push_back(new ToroidalState(i,j,false));
              }

          }
      }
      return list;
  }

  //initialize random number generator and distribution
  std::random_device BallCatchingWorld::rd;
  std::default_random_engine BallCatchingWorld::generator(rd());
  std::uniform_real_distribution<double> BallCatchingWorld::distribution(0.0,1.0);

}
