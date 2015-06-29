#ifndef SEARCHPROBLEM_H
#define SEARCHPROBLEM_H
#include "SearchState.h"
#include <vector>
#include <QString>
#include "Types.h"


class SearchProblem
{
public:
    SearchProblem();
    virtual ~SearchProblem();
    virtual SearchState GetStartState()=0;
    virtual bool isGoalState(const SearchState& state)=0;
    virtual StatesList GetSuccessors(const SearchState& state)=0;
    virtual double GetCostOfActions(ActionsList actions)=0;
};

#endif // SEARCHPROBLEM_H
