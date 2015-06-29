#include "Robot.h"


Robot::Robot()
{
    map = new WorldMap();
    searchProblem = new SearchPath(this, map);
    searchAlgorithm = new BreadthFirstSearch(searchProblem);
}

Robot::~Robot()
{
    delete searchProblem;
    delete map;
}

void Robot::GetInformations(QString rot, QString tran, QString &&frame)
{
    Vec2d oldPosition = robotState.GetPosition();
    robotState.UpdateState(rot[0], tran[0]); // update robot state
    Vec2d position = robotState.GetPosition();
    updateWorldMap(frame); // update robot world model
    ((SearchPath*)searchProblem)->EarseDots(oldPosition, position, false);
    map->PrintWorldMap();

}

ActionsList Robot::MakeDecisions()
{
    return searchAlgorithm->Search();
}

RobotState &Robot::GetRobotState()
{
    return robotState;
}

void Robot::updateWorldMap(QString& frame)
{
    map->UpdateWorldMap(frame, robotState);
}





