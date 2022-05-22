#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

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