#ifndef ROBOT_H
#define ROBOT_H
#include "RobotState.h"
#include "WorldMap.h"
#include "Types.h"
#include <QTextStream>
#include "SearchPath.h"
#include "BreadthFirstSearch.h"

class Robot
{
public:
    Robot();
    virtual ~Robot();
    void GetInformations(QString rot, QString tran, QString &&frame);
    ActionsList MakeDecisions();
    RobotState &GetRobotState();
private:
    RobotState robotState;
    SearchProblem* searchProblem;
    BreadthFirstSearch* searchAlgorithm;
    WorldMap* map;
    void updateWorldMap(QString &frame);
};

#endif // ROBOT_H
