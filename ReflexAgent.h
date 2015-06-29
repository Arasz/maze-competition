#ifndef REFLEXAGENT_H
#define REFLEXAGENT_H
#include "WorldMap.h"
#include "RobotState.h"
#include <map>
#include <unordered_set>


class ReflexAgent
{
private:
    WorldMap* map;
    std::map<QChar,int> fieldPoints = {{'.',7},{'O',1},{'?',3},{'S',1},{'E',10},{'#',-1}};
    std::map<Action,int> moveVisionArea = {{"Wait", 28},{"RotateLeft", 16},{"RotateRight", 16},{"Forward", 16},{"FastForward", 8},{"Rush", 4}};
    std::map<Action,QChar> actionTranslation = {{"Wait", '0'},{"RotateLeft", '0'},{"RotateRight", '0'},{"Forward", '1'},{"FastForward", '2'},{"Rush", '3'}};
    std::map<Action,QChar> actionRotation = {{"Wait", '0'},{"RotateLeft", 'L'},{"RotateRight", 'R'},{"Forward", '0'},{"FastForward", 0},{"Rush", '0'}};
    std::map<Action,int> actionPoints = {{"Wait", 0},{"RotateLeft", 9},{"RotateRight", 11},{"Forward", 10},{"FastForward", 7},{"Rush", 4}};
    Action lastAction = "";

public:
    ReflexAgent();
    ~ReflexAgent();
    void UpdatePossibleActions(RobotState& state);
    Action FindBestAction(RobotState &state);
    RobotState GetSuccesorState(RobotState &state, Action action);
    Action MakeDecision(RobotState& state, QString Frame);

};



#endif // REFLEXAGENT_H
