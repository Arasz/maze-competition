#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(SearchProblem* problem)
{
    this->problem = problem;
    this->fringe.push(problem->GetStartState());
}

BreadthFirstSearch::BreadthFirstSearch(SearchProblem* problem, int searchDepth):
    BreadthFirstSearch(problem)
{
    this->searchDepth = searchDepth;
}

void BreadthFirstSearch::ChangeSearchDepth(int newDepth)
{
    searchDepth = newDepth;
}

ActionsList BreadthFirstSearch::Search()
{
    depthCounter=0;
    while(depthCounter<=searchDepth)
    {
        depthCounter++;
        if( fringe.empty()) // If there is no next state return empty action list
            return actionsList;
        node = fringe.front();
        fringe.pop();// Take first state from fringe
        if (problem->isGoalState(node)) // Check if this goal state
            return node.getActions(); // Return action list to goal
        if((closed.find(node) == closed.end())) // If this state isn't in the closed set
        {
            closed.insert(node); // Add him to the closed set
            auto successors = problem->GetSuccessors(node); // Get successors states
            for(auto& successor: successors)
            {
                fringe.push(successor); // Add new states to the fringe
            }
        }
        actionsList = node.getActions();
    }
    return actionsList;
}

