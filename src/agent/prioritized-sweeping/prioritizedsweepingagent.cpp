/*
    @file qlaerningagent.cpp
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief implementation of qlearning algirithm

    model probabilitylele dogru calisiyormu test et. DONE
    yapiyi degistir agent icin base class yaz
    context detection ekle
    terminal state 1 tane (yap kesin yap) DONE
    episodelog  DONE
    conditional log DONE

*/

#include "../../../include/agent/prioritized-sweeping/prioritizedsweepingagent.h"


namespace prioritizedsweeping{

    PrioritizedSweepingAgent::PrioritizedSweepingAgent(std::unique_ptr<rlinterface::Environment> environment, double gamma, double epsilon, double planning_limit, double priority_threshold, std::string log_name):
    environment(std::move(environment)), gamma(gamma), epsilon(epsilon), planning_limit(planning_limit),
    priority_threshold(priority_threshold), log_model(false), log_qtable(false),log_experience(false), log_history(false), log_directory_created(false), total_episode_count(0), log_name(log_name){

    }

    void PrioritizedSweepingAgent::Train(int numberofepisode){
        InitiateLogsFiles();
        int episodecounter = 0;
        // for each episode
        while (episodecounter < numberofepisode){
            // initial state & response
            std::unique_ptr<rlinterface::State> currentenvironmentstate(environment->ObserveState());
            std::list<State>::iterator currentagentstate = AddNewStateToQTable(currentenvironmentstate.get());
            // counter for stepsize of each episode
            int stepsizecounter = 0;
            // for every step of the episode
            while (!currentenvironmentstate->IsTerminal()){
                // decide next action
                int nextaction = EpsilonGreedyPolicy(currentagentstate);
                // execute nextaction, update current environment state known by agent, add new state to qtable
                std::unique_ptr<rlinterface::Response> response(environment->TakeAnAction(nextaction));
                currentenvironmentstate = response->GetState();
                std::list<State>::iterator nextagentstate = AddNewStateToQTable(currentenvironmentstate.get());
                // update model
                ExperienceTuple experience_tuple(currentagentstate->GetPureState(),nextaction,nextagentstate->GetPureState(),response->GetReward());
                model.UpdateModel(experience_tuple,true);
                LogModel((episodecounter+total_episode_count),stepsizecounter);
                LogExperience((episodecounter+total_episode_count),stepsizecounter,experience_tuple);
                // calculate the error
                StateAction *state_action = model.GetStateAction(currentagentstate->GetPureState(),nextaction);
                double sum = 0;
                for(std::list<NextState>::iterator it = state_action->next_state_list.begin(); it != state_action->next_state_list.end(); ++it){
                    std::list<State>::iterator it2 = find(qtable.begin(), qtable.end(),State(std::unique_ptr<rlinterface::State>(it->state->clone())));
                    sum += it->probability * it2->GetMaxActionValue();
                }
                std::list<Action>::iterator currentq = currentagentstate->GetAction(nextaction);
                double error = std::abs(currentq->GetValue() - (state_action->reward_estimate + (gamma * sum)));
                // insert to priority queue
                priority_queue.push(PriorityQueueItem(currentagentstate,currentq,state_action,error));
                // do planning
                int planning_counter = 0;
                while (!priority_queue.empty() && (planning_counter < planning_limit)){
                    // pop top element
                    PriorityQueueItem priority_queue_item = priority_queue.top();
                    priority_queue.pop();
                    // calculate new q value,update qtable
                    sum = 0;
                    for(std::list<NextState>::iterator it = priority_queue_item.state_action->next_state_list.begin(); it != priority_queue_item.state_action->next_state_list.end(); ++it){
                        std::list<State>::iterator it2 = find(qtable.begin(), qtable.end(),State(std::unique_ptr<rlinterface::State>(it->state->clone())));
                        sum += it->probability * it2->GetMaxActionValue();
                    }
                    priority_queue_item.action->SetValue(priority_queue_item.state_action->reward_estimate + (gamma * sum));
                    LogQtable((episodecounter+total_episode_count),stepsizecounter,planning_counter);
                    // for all states action pairs that leads to this state
                    std::list<StateAction*> leading_states = model.GetStatesLeadsToS((priority_queue_item.state)->GetPureState());
                    for(std::list<StateAction*>::iterator it = leading_states.begin(); it != leading_states.end(); ++it){
                        // calculate the error
                        sum = 0;
                        for(std::list<NextState>::iterator it2 = (*it)->next_state_list.begin(); it2 != (*it)->next_state_list.end(); ++it2){
                            std::list<State>::iterator it3 = find(qtable.begin(), qtable.end(),State(std::unique_ptr<rlinterface::State>(it2->state->clone())));
                            sum += it2->probability * it3->GetMaxActionValue();
                        }
                        std::list<State>::iterator current_s = find(qtable.begin(), qtable.end(),State(std::unique_ptr<rlinterface::State>((*it)->state_m->state->clone())));
                        currentq = current_s->GetAction((*it)->action);
                        error = std::abs(currentq->GetValue() - ((*it)->reward_estimate + (gamma * sum)));
                        // insert to priority queue
                        if(error > priority_threshold){
                            priority_queue.push(PriorityQueueItem(current_s,currentq,*it,error));
                        }
                    }
                    planning_counter++;
                }
                // update agent current state
                currentagentstate = nextagentstate;
                priority_queue = std::priority_queue<PriorityQueueItem>();
                stepsizecounter++;
            }
            std::cout << "episode : " <<(episodecounter + total_episode_count) << "  stepsize : " << stepsizecounter <<'\n';
            LogHistory((episodecounter+total_episode_count),stepsizecounter);
            episodecounter++;
        }
        total_episode_count += numberofepisode;
        CloseLogsFiles();
    }

    int PrioritizedSweepingAgent::EpsilonGreedyPolicy(std::list<State>::iterator agentstate){
        // O(actions^2)
        // Selects greedy action with the probability = 1-e + (1-e / #ofactions)
        // If some greedy actions are equal, selects randomly among them
        if(distribution(generator) > epsilon){
            //select max valued action
            return agentstate->GetMaxActionTypeRandom();

        }
        else{
            //select randomly among all actions
            std::list<int> actions = agentstate->GetPureState()->GetAvailableActions();
            int count = (int)(distribution(generator) * actions.size());
            std::list<int>::iterator it = actions.begin();
            std::advance(it,count);
            return *it;
        }
    }

    std::list<State>::iterator PrioritizedSweepingAgent::AddNewStateToQTable(rlinterface::State* state){
        // Searches State in qtable and adds if it not exist O(states)
        // If it exist update its action list O(actions^2)
        // O(states+actions^2)
        // Returns iterator points that state in table.
        std::unique_ptr<rlinterface::State> t1(state->clone());
        State searchobject(std::move(t1));
        std::list<State>::iterator it = find(qtable.begin(), qtable.end(),searchobject);
        if(it == qtable.end()){
            qtable.push_back(searchobject);
            return --it;
        }
        else{
            it->UpdateActionList(state);
            return it;
        }
    }

    PriorityQueueItem::PriorityQueueItem(std::list<State>::iterator state, std::list<Action>::iterator action, StateAction *state_action, double priority):
    state(state), action(action),state_action(state_action), priority(priority){

    }
    bool PriorityQueueItem::operator < (PriorityQueueItem const& rhs) const{
      if (priority < rhs.priority){
        return true;
      }
      else{
        return false;
      }
    }

    std::list<State>& PrioritizedSweepingAgent::GetQTable(){
        return qtable;
    }

    void PrioritizedSweepingAgent::SetEpsilon(double epsilon){
        this->epsilon = epsilon;
    }
    void PrioritizedSweepingAgent::SetEnvironment(std::unique_ptr<rlinterface::Environment> environment) {
        this->environment = std::move(environment);
    }

    void PrioritizedSweepingAgent::LogModel(int episode, int step){
        if(log_model){
            std::string filename = log_name + "/model/P/model_P_e" + std::to_string(episode) + "_s" + std::to_string(step);
            std::string filename2 = log_name + "/model/R/model_R_e" + std::to_string(episode) + "_s" + std::to_string(step);
            std::ofstream file(filename);
            std::ofstream file2(filename2);
            std::list<StateM> state_list = model.GetStateList();
            for(std::list<StateM>::iterator it0 = state_list.begin(); it0 != state_list.end(); ++it0){
                for(std::list<StateAction>::iterator it1 = it0->action_list.begin(); it1 != it0->action_list.end(); ++it1){
                    file2 << "R [" + it0->state->ToString() + "," + std::to_string(it1->action) + "] = " + std::to_string(it1->reward_estimate) + "\n";
                    for(std::list<NextState>::iterator it2 = it1->next_state_list.begin(); it2 != it1->next_state_list.end(); ++it2){
                        file << "P [" + it0->state->ToString() + "," + std::to_string(it1->action)  + "," + it2->state->ToString() + "] = " + std::to_string(it2->probability) + "\n";
                    }
                }
            }
            file.close();
            file2.close();
        }
    }
    void PrioritizedSweepingAgent::LogQtable(int episode, int step, int plan){
        if(log_qtable){
            std::string filename = log_name + "/qtable/qtable_e" + std::to_string(episode) + "_s" + std::to_string(step) + "_p" + std::to_string(plan);
            std::ofstream file(filename);
                for(std::list<State>::iterator it1 = qtable.begin(); it1 != qtable.end(); ++it1){
                    std::list<Action> actions = it1->GetActionList();
                    for(std::list<Action>::iterator it2 = actions.begin(); it2 != actions.end(); ++it2){
                        file << "Q [" + it1->GetPureState()->ToString() + "," + std::to_string(it2->GetType())  + "] = " + std::to_string(it2->GetValue()) + "\n";
                    }
                }
            file.close();
            }
    }
    void PrioritizedSweepingAgent::LogExperience(int episode, int step, ExperienceTuple &tuple){
        if(log_experience){
          if(step == 0){
              expfile.close();
              std::string filename = log_name + "/exprience/exp_e" + std::to_string(episode);
              expfile.open(filename);
          }
          expfile << std::to_string(step) + " - [" + tuple.state->ToString() + "," + std::to_string(tuple.action) + "," + tuple.next_state->ToString() + "," + std::to_string(tuple.reward) + "]" + "\n";
        }
    }
    void PrioritizedSweepingAgent::LogHistory(int episode, int step){
        if(log_history){
            std::string filename = log_name + "/history" + std::to_string(episode) + "_s" + std::to_string(step);
            historyfile << "episode : " <<episode << "  stepsize : " << step <<'\n';
        }
    }
    void PrioritizedSweepingAgent::InitiateLogsFiles(){
        // platform dependent code
        // creates necessary directories, if exists clears its content.
        if((log_history || log_experience || log_qtable || log_model) && !log_directory_created){
            int result = mkdir(log_name.c_str(),0755);
            if(result == -1){
                // if directory exist then clear its content
                std::string s = log_name + "/";
                // std::string s = "'" + log_name + "/'";
                pid_t childpid = fork();
                if(childpid == 0){
                    // execl("/usr/bin/find","find",s.c_str(),"-type","f","'rm'","'{}'","'\\;'",NULL);
                    execl("/bin/rm","rm","-r",log_name.c_str(),NULL);
                    std::cerr << "Child failed when running execl" << '\n';
                }
                else{
                    wait(NULL);
                    mkdir(log_name.c_str(),0755);
                    std::cout << "log directory is deleted" << '\n';
                }
            }
            log_directory_created = true;
            std::cout << "log directory is created" << '\n';
        }
        if(log_history){
            std::string filename = log_name + "/history";
            historyfile.open(filename,std::ios_base::app);
        }
        if(log_experience){
            std::string s = log_name + "/exprience";
            mkdir(s.c_str(),0755);
        }
        if(log_qtable){
            std::string s = log_name + "/qtable";
            mkdir(s.c_str(),0755);
        }
        if(log_model){
            std::string s = log_name + "/model";
            mkdir(s.c_str(),0755);
            std::string s1 = s + "/P";
            std::string s2 = s + "/R";
            mkdir(s1.c_str(),0755);
            mkdir(s2.c_str(),0755);
        }

    }
    void PrioritizedSweepingAgent::CloseLogsFiles(){
        if(log_history){
            historyfile.close();
        }
        if(log_experience){
            expfile.close();
        }
    }

    void PrioritizedSweepingAgent::SetLogModel(bool x){
        log_model = x;
    }
    void PrioritizedSweepingAgent::SetLogQtable(bool x){
        log_qtable = x;
    }
    void PrioritizedSweepingAgent::SetLogExperience(bool x){
        log_experience = x;
    }
    void PrioritizedSweepingAgent::SetLogHistory(bool x){
        log_history = x;
    }
}
