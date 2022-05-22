#include "autparser.hpp"


void printStrategyInfo(){
  Strategy StrategyImp("ResCap.spec");

  StrategyImp.printPropositions();
  StrategyImp.printRegionMapping();
  StrategyImp.printStatesInfo();
}

void printTransit() {
  Strategy StrategyImp("../../ResCapMission/Config/ResCap.spec");
  StrategyImp.printCurStateInfo();

  std::unordered_map<std::string, int> envMap = StrategyImp.curSensorMap;
  //  search acts required for the first transition
  std::cout << std::endl << "Single Transition Requires Actions: ";
  printStringVector(StrategyImp.runSingleTransition(envMap));
  //  refresh state after the acts are executed
  StrategyImp.refreshCurState();
  //  print current state information
  StrategyImp.printCurStateInfo();

  //  the change of environment
  envMap["enemy"] = 1;
  //  search acts required for the change of environment
  std::cout << std::endl << "Single Transition Requires Actions: ";
  printStringVector(StrategyImp.runSingleTransition(envMap));
  //  refresh state after the acts are executed
  StrategyImp.refreshCurState();
  //  print current state information
  StrategyImp.printCurStateInfo();

  //  search acts required for the change of environment
  std::cout << std::endl << "Single Transition Requires Actions: ";
  printStringVector(StrategyImp.runSingleTransition(envMap));
  //  refresh state after the acts are executed
  StrategyImp.refreshCurState();
  //  print current state information
  StrategyImp.printCurStateInfo();

  //  the change of environment
  envMap["enemy"] = 0;
  //  search acts required for the change of environment
  std::cout << std::endl << "Single Transition Requires Actions: ";
  printStringVector(StrategyImp.runSingleTransition(envMap));
  //  refresh state after the acts are executed
  StrategyImp.refreshCurState();
  //  print current state information
  StrategyImp.printCurStateInfo();

  //  search acts required for the change of environment
  std::cout << std::endl << "Single Transition Requires Actions: ";
  printStringVector(StrategyImp.runSingleTransition(envMap));
  //  refresh state after the acts are executed
  StrategyImp.refreshCurState();
  //  print current state information
  StrategyImp.printCurStateInfo();
}

int main() { printTransit(); }