ls *.hpp-template |awk -F "ComponentImpl" '{print "mv "$0" "$1".hpp"}'|bash
ls *.cpp-template |awk -F "ComponentImpl" '{print "mv "$0" "$1".cpp"}'|bash