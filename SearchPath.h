#ifndef FINDALLDOTS_H
#define FINDALLDOTS_H
#include "SearchProblem.h"
#include "SearchState.h"
#include "Robot.h"
#include "Types.h"

class Robot;

class SearchPath : public SearchProblem
{
public:
    SearchPath(Robot* robot, WorldMap* map);
    virtual ~SearchPath();

    // SearchProblem interface
    SearchState GetStartState() override;
    bool isGoalState(const SearchState& state) override;
    StatesList GetSuccessors(const SearchState& state) override;
    double GetCostOfActions(ActionsList actions) override;
    int EarseDots(Vec2d &oldPosition, Vec2d &newPosition, bool local);
protected:
    Robot* robot;
    WorldMap* map;
    std::map<Action,int> actionTranslationMap = {{"RotateLeft",0},{"RotateRight",0}, {"Wait",0}
                                      ,{"Rush",3},{"FastForward",2},{"Forward",1}};
    std::map<Action,QChar> actionRotationMap = {{"RotateLeft",'L'},{"RotateRight",'R'}, {"Wait",'0'}};

    int countDots();
    Vec2d findGoalPosition();
    bool isMovePossible(Action action, const SearchState& state, SearchState* newState);
};

#endif // FINDALLDOTS_H
