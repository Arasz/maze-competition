#include "SearchPath.h"

SearchPath::SearchPath(Robot* robot, WorldMap *map)
{
    this->robot = robot;
    this->map = map;
}

SearchPath::~SearchPath()
{

}


SearchState SearchPath::GetStartState()
{
    return SearchState(robot->GetRobotState().GetPosition(), robot->GetRobotState().GetOrientation(), countDots(),{});
}

bool SearchPath::isGoalState(const SearchState& state)
{
    Vec2d position = state.getPosition();
    if(position == findGoalPosition() || (countDots() == 0))
        return true;
    else
        return false;
}

StatesList SearchPath::GetSuccessors(const SearchState &state)
{
    ActionsList list = {"RotateLeft", "RotateRight", "Wait", "Rush", "FastForward", "Forward"};
    StatesList successors;
    SearchState* newState;
    for(auto action: list)
    {
        if(isMovePossible(action,state,newState))
        {
            newState->addAction(action);
            successors.push_back(*newState);
        }
    }
    return successors;
}

double SearchPath::GetCostOfActions(ActionsList actions)
{
    return static_cast<double>(actions.size());
}

int SearchPath::countDots()
{
    int dotsCounter = 0;
    int size = map->getMapCenter();
    for(int i = -size; i< size; i++)
        for(int j = -size; j< size; j++)
        {
            QChar c = map->CheckPosition(i,j);
            //std::cout<<c.toLatin1()<<" ";
            if(c ==  '.')
                dotsCounter++;
        }
    return dotsCounter;
}

Vec2d SearchPath::findGoalPosition()
{
    Vec2d position = {0,0};
    int size = map->GetMapSize();
    for(int i = -size; i< size; i++)
        for(int j = -size; j< size; j++)
        {
            if(map->CheckPosition(i,j) == 'E')
            {
                position={i,j};
                return position;
            }
        }
    return position;
}

bool SearchPath::isMovePossible(Action action, const SearchState &state, SearchState* newState)
{
    OrientationConverter converter;
    Vec2d orientationVec = converter.GetOrientationVector(state.getOrientation());
    Vec2d position = state.getPosition();

    if(actionTranslationMap[action] == 0)
    {
        auto updateOrientation = state.getUpdatedOrientation(actionRotationMap[action]);
        newState = new SearchState(position,updateOrientation ,
                                   countDots(), state.getActions());
        return true;
    }
    else
    {
        Vec2d newPosition = {position.first+orientationVec.first*actionTranslationMap[action]
                             ,position.second+orientationVec.second*actionTranslationMap[action]};
        QChar fieldType = map->CheckPosition(newPosition.first, newPosition.second);
        if(fieldType== '.' || fieldType=='E' || fieldType=='S')
        {
            int dotsNumber = EarseDots(position,newPosition, true);
            newState = new SearchState(newPosition,state.getOrientation(),
                                       dotsNumber, state.getActions());
            return true;
        }
        else
            return false;
    }
}

int SearchPath::EarseDots(Vec2d& oldPosition,Vec2d& newPosition,bool local)
{
    if(local)
        map->MakeMapCopy();

    int xDiffrence = newPosition.first-oldPosition.first;
    int yDiffrence = newPosition.second-oldPosition.second;

    for(int i = 1; i<= xDiffrence; i++)
    {
        for(int j = 1; j<= yDiffrence; j++)
        {
            map->SetSymbolAtPosition(' ',i,j);
        }
    }
    int dotsNumber = countDots();

    if(local)
        map->ReloadMapFromCopy();
    return dotsNumber;
}
