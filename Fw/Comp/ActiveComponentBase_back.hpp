/*
 * ActiveComponentBase.hpp
 *
 *  Created on: Aug 14, 2012
 *      Author: tcanham
 */

/*
 * Description:
 */
#ifndef FW_ACTIVE_COMPONENT_BASE_HPP
#define FW_ACTIVE_COMPONENT_BASE_HPP

#include <Fw/Comp/QueuedComponentBase.hpp>
#include <Os/Task.hpp>
#include <FpConfig.hpp>
#include <Fw/Deprecate.hpp>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <unistd.h>

namespace Fw {
    class ActiveComponentBase : public QueuedComponentBase {
        public:
            void start(NATIVE_UINT_TYPE priority = Os::Task::TASK_DEFAULT, NATIVE_UINT_TYPE stackSize = Os::Task::TASK_DEFAULT, NATIVE_UINT_TYPE cpuAffinity = Os::Task::TASK_DEFAULT, NATIVE_UINT_TYPE identifier = Os::Task::TASK_DEFAULT); //!< called by instantiator when task is to be started

            DEPRECATED(void start(NATIVE_INT_TYPE identifier, NATIVE_INT_TYPE priority, NATIVE_INT_TYPE stackSize, NATIVE_INT_TYPE cpuAffinity = -1),
                       "Please switch to start(NATIVE_UINT_TYPE priority, NATIVE_UINT_TYPE stackSize, NATIVE_UINT_TYPE cpuAffinity, NATIVE_UINT_TYPE identifier)"); //!< called by instantiator when task is to be started
            void exit(); //!< exit task in active component
            Os::Task::TaskStatus join(void **value_ptr); //!< provide return value of thread if value_ptr is not NULL

            enum {
                ACTIVE_COMPONENT_EXIT //!< message to exit active component task
            };

        PROTECTED:
            ActiveComponentBase(const char* name); //!< Constructor
            virtual ~ActiveComponentBase(); //!< Destructor
            void init(NATIVE_INT_TYPE instance); //!< initialization code
            virtual void preamble(); //!< A function that will be called before the event loop is entered
            virtual void loop(); //!< The function that will loop dispatching messages
            virtual void finalizer(); //!< A function that will be called after exiting the loop
            Os::Task m_task; //!< task object for active component
#if FW_OBJECT_TO_STRING == 1
            virtual void toString(char* str, NATIVE_INT_TYPE size); //!< create string description of component
#endif
        PRIVATE:
            static void s_baseTask(void*); //!< function provided to task class for new thread.
            static void s_baseBareTask(void*); //!< function provided to task class for new thread.
    };

    /*
    ===========================================================================
    State class
    ===========================================================================
    */

    class State {
        public:
            int state_id;
            int goal_id;
            // group by state_id
            std::vector<std::pair<std::string, int>> propositions;
            std::vector<int> successors;

            void printInfo();
    };

    /*
    ===========================================================================
    Strategy class
    ===========================================================================
    */

    class Strategy {
        public:
            // group by state_id
            std::vector<State> States;

            // all propositions
            std::vector<std::string> AllPropsitions;
            // detailed propositions sorted by aut display
            std::vector<std::string> Sensors; // env propositions
            std::vector<std::string> Actions; // sys propositions
            std::vector<std::string> Customs; // sys propositions
            // <bit0:0, bit1:1, bit2:1> : Regions_encoded[3] = p4 in firefighter
            std::vector<std::string> Regions_encoded; // sys propositions
            // classroom:[p1,p2,p3]
            std::unordered_map<std::string, std::vector<std::string>> RegionMapping;
            // p1: classroom
            std::unordered_map<std::string, std::string> deRegionMapping;

            // project entities
            std::string regionFileName;
            std::string projectName;
            bool region_bit_encoding = true;
            bool enable_decompose = true;
            int regionBitNum = 0;
            int regionNum = 0;
            int sensorNum = 0;
            int allPropNum = 0;

            // transition control
            int curStateID;
            int nextStateID = 0;
            std::unordered_map<std::string, int> curSensorMap; // env propositions

            // member functions
            Strategy(std::string specFileName);

            void loadFromSpec(std::string specFileName);
            void loadFromRegion(std::string regionFileName);
            void loadFromAut(std::string autFileName);

            void addNewState(int state_id, int stage_id,
                            std::vector<std::pair<std::string, int>> propositions,
                            std::vector<int> successors);
            void checkSensorMap(std::unordered_map<std::string, int> sensorMap);
            int getNextStateID(std::unordered_map<std::string, int> nextSensorMap);
            void setCurState(int next_state_id);
            std::string getRegionNameByStateID(int state_id); // decomposed name
            std::vector<std::string>
            runSingleTransition(std::unordered_map<std::string, int> nextSensorMap);
            void refreshCurState();

            std::pair<std::string, std::string> getCurRegionNamePair();

            void printPropositions();
            void printRegionMapping();
            void printCurStateInfo();
            void printStatesInfo();
            void checkSpec(int check_id = 0);
        };

    /*
    ===========================================================================
    inline methods
    ===========================================================================
    */
   static inline void printStringVector(std::vector<std::string> sList) {
    for (auto i = sList.begin(); i != sList.end(); i++)
        if ((i + 1) != sList.end())
        std::cout << *i << " | ";
        else
        std::cout << *i;
    std::cout << std::endl;
    }
}
#endif
