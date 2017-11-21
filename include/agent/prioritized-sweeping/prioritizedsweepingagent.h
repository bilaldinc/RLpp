/*
    @file qlaerningagent.h
    @author Bilal Dinc
    @date 1.0 24/09/2017
    @brief implementation of qlearning algirithm
*/

#ifndef _PS_AGENT_INCLUDED
#define _PS_AGENT_INCLUDED

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include <limits>
#include <cmath>
#include <queue>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../../include/rlinterface/environment.h"
#include "../../../include/rlinterface/state.h"
#include "../../../include/rlinterface/response.h"
#include "../../../include/agent/prioritized-sweeping/state.h"
#include "../../../include/agent/prioritized-sweeping/action.h"
#include "../../../include/agent/prioritized-sweeping/model.h"

namespace prioritizedsweeping{

    struct PriorityQueueItem {
        std::list<State>::iterator state;
        std::list<Action>::iterator action;
        StateAction *state_action;
        double priority;
        PriorityQueueItem(std::list<State>::iterator state, std::list<Action>::iterator action, StateAction *state_action, double priority);
        bool operator < (PriorityQueueItem const& rhs) const;
    };
    typedef struct PriorityQueueItem PriorityQueueItem;

    class PrioritizedSweepingAgent {

    private:
        //environment object
        std::unique_ptr<rlinterface::Environment> environment;

        //parameters
        double gamma;
        double epsilon;
        double planning_limit;
        double priority_threshold;

        //qtable
        std::list<State> qtable;

        //model
        Model model;

        //priority queue
        std::priority_queue<PriorityQueueItem> priority_queue;

        //random number generator and distribution
        std::random_device rd;
        std::default_random_engine generator = std::default_random_engine(rd());
        std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0.0,1.0);

        //log parameters
        bool log_model;
        bool log_qtable;
        bool log_experience;
        bool log_history;
        std::string log_name;
        std::ofstream historyfile;
        std::ofstream expfile;
        int total_episode_count;
        bool log_directory_created;

        // internal functions
        int EpsilonGreedyPolicy(std::list<State>::iterator agentstate);
        std::list<State>::iterator AddNewStateToQTable(rlinterface::State* state);


    public:
        PrioritizedSweepingAgent(std::unique_ptr<rlinterface::Environment> environment, double gamma, double epsilon, double planning_limit, double priority_threshold, std::string log_name);
        void Train(int numberofepisode);
        void SetAlpha(double alpha);
        void SetEpsilon(double epsilon);
        void SetEnvironment(std::unique_ptr<rlinterface::Environment> environment);
        std::list<State>& GetQTable();

        // logging funtions
        void LogModel(int episode, int step);
        void LogQtable(int episode, int step, int plan);
        void LogExperience(int episode, int step, ExperienceTuple &tuple);
        void LogHistory(int episode, int step);
        void SetLogModel(bool x);
        void SetLogQtable(bool x);
        void SetLogExperience(bool x);
        void SetLogHistory(bool x);
        void InitiateLogsFiles();
        void CloseLogsFiles();

  };

}

#endif
