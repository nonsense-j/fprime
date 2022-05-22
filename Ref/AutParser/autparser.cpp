#include "autparser.hpp"

/*
===========================================================================
Apsent Methods
===========================================================================
*/

bool startsWith(std::string s, std::string sub) {
  return s.find(sub) == 0 ? true : false;
}

bool endsWith(std::string s, std::string sub) {
  if (s.empty() && !sub.empty())
    return false;
  else
    return s.rfind(sub) == (s.length() - sub.length()) ? true : false;
}

int bits_n(int x) { return (x != 0) ? ceil(log(x) / log(2)) : 1; }

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(),
                             [](unsigned char ch) { return !isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(find_if(s.rbegin(), s.rend(),
                  [](unsigned char ch) { return !isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

// split a string by del
std::vector<std::string> tokenize(std::string s, std::string del = ", ") {
  std::vector<std::string> strList;
  int start = 0;
  int end = s.find(del);
  while (end != -1) {
    strList.push_back(s.substr(start, end - start));
    start = end + del.size();
    end = s.find(del, start);
  }
  strList.push_back(s.substr(start, end - start));
  return strList;
}

/*
===========================================================================
State class
===========================================================================
*/

void State::printInfo(void) {
  std::cout << "*state_id: " << state_id << "  goal_id: " << goal_id
            << "\ttrue propositions: {";
  // enabled propositions cout
  for (auto i_se = propositions.begin(); i_se != propositions.end(); i_se++) {
    if ((*i_se).second)
      if ((i_se + 1) != propositions.end())
        std::cout << (*i_se).first << ", ";
      else
        std::cout << (*i_se).first;
  }
  std::cout << "}" << std::endl << "\t--> successors: ";
  // successors cout
  for (auto i_su = successors.begin(); i_su != successors.end(); i_su++) {
    if ((i_su + 1) != successors.end())
      std::cout << (*i_su) << " ";
    else
      std::cout << (*i_su);
  }
  std::cout << std::endl;
}

/*
===========================================================================
Strategy class
===========================================================================
*/

Strategy::Strategy(std::string specFileName) {
  std::ifstream specfile;
  std::string autFileName;

  States.clear();
  Sensors.clear();
  Actions.clear();
  Customs.clear();
  Regions_encoded.clear();
  RegionMapping.clear();
  deRegionMapping.clear();
  regionFileName.clear();
  curSensorMap.clear();

  loadFromSpec(specFileName);
  checkSpec();

  if (enable_decompose)
    regionFileName = projectName + "_decomposed.regions";
  loadFromRegion(regionFileName);

  // all propositions init
  // connect Sensors, Actions, Customs to form AllPropsitions
  AllPropsitions.insert(AllPropsitions.begin(), Sensors.begin(), Sensors.end());
  AllPropsitions.insert(AllPropsitions.end(), Customs.begin(), Customs.end());
  AllPropsitions.insert(AllPropsitions.end(), Actions.begin(), Actions.end());
  for (int i = 0; i < regionBitNum; i++)
    AllPropsitions.push_back("bit" + std::to_string(i));

  allPropNum = AllPropsitions.size();

  autFileName = projectName + ".aut";
  loadFromAut(autFileName);

  // init execution
  setCurState(0);
}

void Strategy::loadFromSpec(std::string specFileName) {

  std::ifstream specfile;
  specfile.open(specFileName, std::ios::in);
  if (!specfile.good()) {
    std::cout << "[Terminate] SpecFile: (" << specFileName << ") Not Found." << std::endl;
    exit(0);
  }

  std::string data;
  std::smatch sm;
  std::vector<std::string> tmp;
  std::regex pattern("(.*?),\\s+(\\d)");

  projectName = specFileName.substr(0, specFileName.rfind(".spec"));
  while (getline(specfile, data)) {
    if (startsWith(data, "Actions:")) {
      getline(specfile, data);
      while (data.length() != 0) {
        regex_match(data, sm, pattern);
        if (sm[2] == "1")
          Actions.push_back(sm.str(1));
        getline(specfile, data);
      }
    } else if (startsWith(data, "use_region_bit_encoding:")) {
      if (endsWith(data, "False"))
        region_bit_encoding = false;
      getline(specfile, data);
    } else if (startsWith(data, "decompose:")) {
      if (endsWith(data, "False"))
        enable_decompose = false;
      getline(specfile, data);
    } else if (startsWith(data, "Customs:")) {
      getline(specfile, data);
      while (data.length() != 0) {
        Customs.push_back(data);
        getline(specfile, data);
      }
    } else if (startsWith(data, "RegionFile:")) {
      getline(specfile, data);
      if (data.length() != 0)
        regionFileName = data;
    } else if (startsWith(data, "Sensors:")) {
      getline(specfile, data);
      while (data.length() != 0) {
        regex_match(data, sm, pattern);
        if (sm[2] == "1")
          Sensors.push_back(sm.str(1));
        getline(specfile, data);
      }
    } else if (startsWith(data, "RegionMapping:")) {
      getline(specfile, data);
      while (data.length() != 0) {
        std::regex_match(data, sm, std::regex("(.*?)\\s=\\s(.*?)"));
        if (sm[2].length() != 0) {
          // num = stoi((sm.str(2)).substr(1));
          tmp = tokenize(sm.str(2));
          RegionMapping.insert(std::make_pair(sm.str(1), tmp));
          for (auto j = tmp.begin(); j != tmp.end(); j++)
            deRegionMapping.insert(std::make_pair(*j, sm.str(1)));
        }
        getline(specfile, data);
      }
    }
  }
  sensorNum = Sensors.size();
  // close spec file
  specfile.close();
}

void Strategy::loadFromRegion(std::string regionFileName) {
  std::ifstream regfile;
  std::string data;
  std::smatch sm;
  bool regionSymbol = false;

  regfile.open(regionFileName, std::ios::in);
  if (!regfile.good()) {
    std::cout << "[Terminate] RegionFile: (" << regionFileName
              << ") Not Found."<< std::endl;
    exit(0);
  }
  while (getline(regfile, data)) {
    if (startsWith(data, "Regions:"))
      regionSymbol = true;
    else if (regionSymbol && endsWith(data, "{")) {
      getline(regfile, data);
      if (startsWith(data, "Transitions:"))
        regionSymbol = false;
      else {
        std::regex_match(data, sm, std::regex("^.*?\"name\": \"(.*?)\".*?$"));
        Regions_encoded.push_back(sm.str(1));
      }
    }
  }
  regionNum = Regions_encoded.size();
  regionBitNum = bits_n(regionNum);
}

void Strategy::loadFromAut(std::string autFileName) {
  // start reading file
  std::ifstream autfile;
  std::string data, tmp;

  std::regex data_pattern("^State (\\d+) with rank (\\d+) -> <(.*?)>$");
  std::regex split_pattern("^(.*?):(\\d)$");
  std::regex suc_pattern("^\\s+With successors : (.*?)$");
  std::smatch sm, sm_split, sm_suc;

  int state_id, goal_id;
  std::vector<std::string> strList; // split xxx, xxx, xxx into a std::vector
  std::vector<std::pair<std::string, int>> propositions;
  std::vector<int> successors;

  autfile.open(autFileName, std::ios::in);
  if (!autfile.good()) {
    std::cout << "[Terminate] AutFile: (" << autFileName << ") Not Found." << std::endl;
    exit(0);
  }
  while (getline(autfile, data)) {
    if (startsWith(data, "State")) {
      // clear propositions and successors
      propositions.clear();
      successors.clear();

      // based on first line : data
      regex_match(data, sm, data_pattern);
      state_id = stoi(sm.str(1));
      goal_id = stoi(sm.str(2));
      strList = tokenize(sm.str(3));
      for (auto i = strList.begin(); i != strList.end(); i++) {
        regex_match(*i, sm_split, split_pattern);
        propositions.push_back(
            std::make_pair(sm_split.str(1), stoi(sm_split.str(2))));
      }
      strList.clear();

      // based on second line: tmp --> successor
      getline(autfile, tmp);
      regex_match(tmp, sm_suc, suc_pattern);
      strList = tokenize(sm_suc.str(1));
      for (auto i = strList.begin(); i != strList.end(); i++)
        successors.push_back(stoi(*i));
      // add new state to strategy
      addNewState(state_id, goal_id, propositions, successors);
    }
  }
  // close file
  autfile.close();
}

void Strategy::addNewState(
    int state_id, int goal_id,
    std::vector<std::pair<std::string, int>> propositions,
    std::vector<int> successors) {
  State newState;
  newState.state_id = state_id;
  newState.goal_id = goal_id;
  newState.propositions = propositions;
  newState.successors = successors;

  States.push_back(newState);
};

void Strategy::checkSensorMap(std::unordered_map<std::string, int> sensorMap) {
  for (auto i = sensorMap.begin(); i != sensorMap.end(); i++) {
    if (find(Sensors.begin(), Sensors.end(), (*i).first) == Sensors.end()) {
      std::cout << "[Terminate] Unvalid Proposition Name : " << (*i).first;
      exit(0);
    }
  }
};

int Strategy::getNextStateID(
    std::unordered_map<std::string, int> nextSensorMap) {
  State curState = States[curStateID];
  std::vector<std::pair<std::string, int>> suc_prop;
  std::vector<int> successors = curState.successors;
  int match; // matched proposition number

  for (int suc : successors) {
    suc_prop = States[suc].propositions;
    match = 0;
    for (int m = 0; m < sensorNum; m++) {
      if (nextSensorMap[suc_prop[m].first] != suc_prop[m].second)
        break;
      else
        match++;
    }
    if (match == sensorNum)
      return suc;
  }
  return -1;
};

std::string Strategy::getRegionNameByStateID(int state_id) {
  int region_index = 0;
  State cur_state = States[state_id];

  for (int i = 0; i < regionBitNum; i++) {
    region_index += cur_state.propositions[allPropNum - regionBitNum + i].second
                    << (regionBitNum - i - 1);
  }
  return Regions_encoded[region_index];
}

void Strategy::setCurState(int next_state_id) {
  std::pair<std::string, int> env_pair;

  if (next_state_id != -1 && next_state_id < States.size()) {
    //  change of curStateID
    curStateID = next_state_id;
    for (int i = 0; i < sensorNum; i++) {
      env_pair = States[next_state_id].propositions[i];
      curSensorMap[env_pair.first] = env_pair.second;
    }
  } else {
    std::cout << "[Wait] No Successor State to Select, Wait for Env Change";
  }
}

std::vector<std::string> Strategy::runSingleTransition(
    std::unordered_map<std::string, int> nextSensorMap) {
  /*
      return the sys propositions (Actions, Customs, Region) to reach the
      transition
  */
  //  change of nextStateID
  nextStateID = getNextStateID(nextSensorMap);
  int p_index = sensorNum, cur_index = 0, next_index = 0;
  std::vector<std::pair<std::string, int>> cur_props =
      States[curStateID].propositions;
  std::vector<std::pair<std::string, int>> next_props =
      States[nextStateID].propositions;
  std::vector<std::string> sysProps;

  int actions_end = sensorNum + Actions.size();
  for (; p_index < actions_end; p_index++)
    if (cur_props[p_index].second != next_props[p_index].second) {
      if (next_props[p_index].second)
        sysProps.push_back(next_props[p_index].first);
      else
        sysProps.push_back("!" + next_props[p_index].first);
    }
  p_index += Customs.size();
  for (; p_index < allPropNum; p_index++){
    cur_index += cur_props[p_index].second << (allPropNum - p_index -1);
    next_index += next_props[p_index].second << (allPropNum - p_index -1);
  }
  if (cur_index != next_index)
    sysProps.push_back(getRegionNameByStateID(nextStateID));
  else
    sysProps.push_back("!" + getRegionNameByStateID(nextStateID));

  return sysProps;
};

void Strategy::refreshCurState(void) {
  /*
      state will only be refreshed when the actions have finished
  */
  setCurState(nextStateID);
}

std::pair<std::string, std::string> Strategy::getCurRegionNamePair() {
  int region_index = 0;
  std::string tmp;
  State curState = States[curStateID];

  for (int i = 0; i < regionBitNum; i++) {
    region_index += curState.propositions[allPropNum - regionBitNum + i].second
                    << (regionBitNum - i - 1);
  }
  tmp = Regions_encoded[region_index];
  return std::make_pair(tmp, deRegionMapping[tmp]);
};

void Strategy::printPropositions(void) {
  std::cout << std::endl
            << "=================|Propositions|=================" << std::endl;
  std::cout << "#Sensors:\t";
  if (!Sensors.empty())
    printStringVector(Sensors);
  else
    std::cout << "[Not Defined]" << std::endl;
  std::cout << "#Actions:\t";
  if (!Actions.empty())
    printStringVector(Actions);
  else
    std::cout << "[Not Defined]" << std::endl;
  std::cout << "#Customs:\t";
  if (!Customs.empty())
    printStringVector(Customs);
  else
    std::cout << "[Not Defined]" << std::endl;
  std::cout << "#Regions_encoded:\t";
  if (!Regions_encoded.empty()) {
    printStringVector(Regions_encoded);
    if (enable_decompose) {
      std::cout << "#Regions_name:\t";
      if (!deRegionMapping.empty()) {
        for (auto i = Regions_encoded.begin(); i != Regions_encoded.end();
             i++) {
          auto cur_i = deRegionMapping.find(*i);
          if (cur_i != deRegionMapping.end())
            if (i + 1 != Regions_encoded.end())
              std::cout << (*cur_i).second << " | ";
            else
              std::cout << (*cur_i).second;
        }
        std::cout << std::endl;
      } else
        std::cout << "[Not Defined]" << std::endl;
    }
  } else
    std::cout << "[Not Defined]" << std::endl;
  std::cout << "#All_propsitions:  ";
  if (!AllPropsitions.empty())
    printStringVector(AllPropsitions);
  else
    std::cout << "[Not Defined]" << std::endl;
  std::cout << "=================[Propositions]=================" << std::endl;
}

void Strategy::printRegionMapping(void) {
  std::cout << std::endl
            << "=================|RegionMapping|=================" << std::endl;
  for (auto i = RegionMapping.begin(); i != RegionMapping.end(); i++) {
    std::cout << (*i).first << "\t---\t";
    printStringVector((*i).second);
  }
  std::cout << "=================[RegionMapping]=================" << std::endl;
}

void Strategy::printStatesInfo(void) {
  std::vector<std::pair<std::string, int>> props_cur;
  std::cout << std::endl
            << "=================|States Status|=================" << std::endl;
  std::cout << "#States:" << std::endl;
  for (auto i = States.begin(); i != States.end(); i++)
    (*i).printInfo();
  std::cout << "=================[States Status]=================" << std::endl;
}

void Strategy::printCurStateInfo() {
  States[curStateID].printInfo();
  std::cout << "\t--> region name: \t" << getCurRegionNamePair().first << " ("
            << getCurRegionNamePair().second << ")" << std::endl;
}

void Strategy::checkSpec(int check_id) {
  // 0 -- RegionMapping and regionFileName;
  if (check_id == 0) {
    if (RegionMapping.empty()) {
      std::cout << "[Terminate] No Region Selected in SpecFile.";
      exit(0);
    } else if (regionFileName.length() == 0) {
      std::cout << "[Terminate] No Region File Specified in SpecFile.";
      exit(0);
    }
  }
}