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

    Every episode agent and ball start at random states.
*/

/*
    Tested
    TO-DO
    throw expection or terminate program in case of invalid action type
*/

#include "../../../include/environment/ballcatching/ballcatchingworld.h"

namespace ballcatching{

  BallCatchingWorld::BallCatchingWorld(int size, int ball_direction, double reward, double punishment):
  size(size), reward(reward), ball_direction(ball_direction), punishment(punishment){
    // random start
    int random_start_ball_x = (int)(distribution(generator) * size);
    int random_start_ball_y = (int)(distribution(generator) * size);
    std::vector<int> x_without_ball;
    std::vector<int> y_without_ball;
    for (size_t i = 0; i < size; i++) {
      if(random_start_ball_x != i){
        x_without_ball.push_back(i);
      }
      if(random_start_ball_y != i){
        y_without_ball.push_back(i);
      }
    }
    int random_start_agent_x = (int)(distribution(generator) * size-1);
    int random_start_agent_y = (int)(distribution(generator) * size-1);
    random_start_agent_x = x_without_ball.at(random_start_agent_x);
    random_start_agent_y = y_without_ball.at(random_start_agent_y);

    current_ball_x = random_start_ball_x;
    current_ball_y = random_start_ball_y;
    current_agent_x = random_start_agent_x;
    current_agent_y = random_start_agent_y;
  }

  rlinterface::State* BallCatchingWorld::ObserveState(){
    //callee must handle deallocating the memory
    return  new ToroidalState(current_agent_x,current_agent_y,false);
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
      next_ball_x = BallCatchingWorld::Mod(current_ball_x + 1,size);
      next_ball_y = current_ball_y;
    }
    else if(ball_direction == 1) {
      next_ball_x = BallCatchingWorld::Mod(current_ball_x - 1,size);
      next_ball_y = current_ball_y;
    }
    else if(ball_direction == 2){
      next_ball_x = current_ball_x;
      next_ball_y = BallCatchingWorld::Mod(current_ball_y - 1,size);
    }
    else if(ball_direction == 3){
      next_ball_x = current_ball_x;
      next_ball_y = BallCatchingWorld::Mod(current_ball_y + 1,size);
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

      // random start
      int random_start_ball_x = (int)(distribution(generator) * size);
      int random_start_ball_y = (int)(distribution(generator) * size);
      std::vector<int> x_without_ball;
      std::vector<int> y_without_ball;
      for (size_t i = 0; i < size; i++) {
        if(random_start_ball_x != i){
          x_without_ball.push_back(i);
        }
        if(random_start_ball_y != i){
          y_without_ball.push_back(i);
        }
      }
      int random_start_agent_x = (int)(distribution(generator) * size-1);
      int random_start_agent_y = (int)(distribution(generator) * size-1);
      random_start_agent_x = x_without_ball.at(random_start_agent_x);
      random_start_agent_y = y_without_ball.at(random_start_agent_y);

      current_ball_x = random_start_ball_x;
      current_ball_y = random_start_ball_y;
      current_agent_x = random_start_agent_x;
      current_agent_y = random_start_agent_y;
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
    std::unique_ptr<ToroidalState> toroidal_state(new ToroidalState(next_agent_x,next_agent_y,isterminal));
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

  //initialize random number generator and distribution
  std::random_device BallCatchingWorld::rd;
  std::default_random_engine BallCatchingWorld::generator(rd());
  std::uniform_real_distribution<double> BallCatchingWorld::distribution(0.0,1.0);

}
