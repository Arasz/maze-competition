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
    falseGoalCounter = 0;
}

bool SearchPath::isGoalState(const SearchState& state)
{
    Vec2d position = state.getPosition();
    if(position == findGoalPosition() || ((state.getDotsAmount() == 0)))
        return true;
    else
        return false;
}

SearchState SearchPath::getNewState(Action action, const SearchState &state)
{
    OrientationConverter converter;
    Vec2d orientationVec = converter.GetOrientationVector(state.getOrientation());
    Vec2d position = state.getPosition();


    if(actionTranslationMap[action] == 0)
    {
        auto updateOrientation = state.getUpdatedOrientation(actionRotationMap[action]);
        SearchState newState(position,updateOrientation , countDots(), state.getActions());
        return newState;
    }
    else
    {
        Vec2d newPosition = {position.first+orientationVec.first*actionTranslationMap[action]
                             ,position.second+orientationVec.second*actionTranslationMap[action]};
        QChar fieldType = map->CheckPosition(newPosition.first, newPosition.second);
        if(fieldType== '.' || fieldType=='E' || fieldType=='S')
        {
            int dotsNumber = EarseDots(position,newPosition, true);
            SearchState newState(newPosition,state.getOrientation(),
                                       dotsNumber, state.getActions());
            return newState;
        }
    }
}

StatesList SearchPath::GetSuccessors(const SearchState &state)
{
    ActionsList list = {"RotateLeft", "RotateRight", "Wait", "Rush", "FastForward", "Forward"};
    StatesList successors;
    SearchState newState;

    for(auto action: list)
    {
        if(isMovePossible(action,state))
        {
            newState = getNewState(action,state);
            newState.addAction(action);
            successors.push_back(newState);
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
    QChar c = ' ';
    int size = map->getMapCenter();
    for(int i = -size; i< size; i++)
        for(int j = -size; j< size; j++)
        {
            c = map->CheckPosition(i,j);
            //std::cout<<c.toLatin1()<<" ";
            if(c ==  '.')
                dotsCounter++;
        }
    return dotsCounter;
}

Vec2d SearchPath::findGoalPosition()
{
    Vec2d position = {9999,9999}; // Impossible position, if returned there is no goal state on the map
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

// TODO -> move logic to separate function
bool SearchPath::isMovePossible(Action action, const SearchState &state)
{
    OrientationConverter converter;
    Vec2d orientationVec = converter.GetOrientationVector(state.getOrientation());
    Vec2d position = state.getPosition();


    if(actionTranslationMap[action] == 0)
        return true;
    else
    {
        Vec2d newPosition = {position.first+orientationVec.first*actionTranslationMap[action]
                             ,position.second+orientationVec.second*actionTranslationMap[action]};
        QChar fieldType = map->CheckPosition(newPosition.first, newPosition.second);
        if(fieldType== '.' || fieldType=='E' || fieldType=='S')
        {
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

    int xSign = 0;
    if( xDiffrence != 0)
        xSign = (xDiffrence)/std::abs(xDiffrence);

    int ySign = 0;
    if( yDiffrence != 0)
        ySign = (yDiffrence)/std::abs(yDiffrence);


    int x = oldPosition.first;
    int y = oldPosition.second;

    while(x != newPosition.first || x == newPosition.first)
    {
        while(y != newPosition.second || y == newPosition.second)
        {  
            map->SetSymbolAtPosition(' ',x,y);
            if(y != newPosition.second)
                y += ySign;
            else
                break;
        }
        if(x != newPosition.first)
            x += xSign;
        else
            break;
    }
    //map->PrintWorldMap();
    int dotsNumber = countDots();

    if(local)
        map->ReloadMapFromCopy();
    return dotsNumber;
}
