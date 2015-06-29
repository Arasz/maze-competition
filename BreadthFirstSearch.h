#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H
#include "SearchProblem.h"
#include "SearchState.h"
#include "Types.h"
#include <set>
#include <queue>



class BreadthFirstSearch
{
private:
    std::set<SearchState> closed;
    std::queue<SearchState> fringe;
    ActionsList actionsList;
    SearchProblem* problem;
    SearchState node;
    int depthCounter = 0;
    int searchDepth = 3;

public:
    BreadthFirstSearch(SearchProblem* problem);
    BreadthFirstSearch(SearchProblem* problem, int searchDepth);
    void ChangeSearchDepth(int newDepth);
    ActionsList Search();

};

#endif // BREADTHFIRSTSEARCH_H
