#include "ReflexAgent.h"

ReflexAgent::ReflexAgent()
{
    map = new WorldMap();
}

ReflexAgent::~ReflexAgent()
{
    delete map;
}

void ReflexAgent::UpdatePossibleActions(RobotState &state)
{
    Vec2d position = state.GetPosition();
    ActionsList list = {"RotateLeft", "RotateRight", "Wait"};
    int i =0;
    switch (state.GetOrientation())
    {
    case Orientation::Right:
        while(i<3)
        {
            i++;
            if(map->CheckPosition(position.first+i,position.second) != '.' )
                break;
        }
        switch (i)
        {
        case 3:
            list.push_back("Rush");
        case 2:
            list.push_back("FastForward");
        case 1:
            list.push_back("Forward");
        }
        break;
    case Orientation::Up:
        while(i<3)
        {
            i++;
            QChar fieldType = map->CheckPosition(position.first,position.second-1);
            if(fieldType!= '.' && fieldType!='E'&&fieldType!='S')
                break;
        }
        switch (i)
        {
        case 3:
            list.push_back("Rush");
        case 2:
            list.push_back("FastForward");
        case 1:
            list.push_back("Forward");
        }
        break;
    case Orientation::Left:
        while(i<3)
        {
            i++;
            if(map->CheckPosition(position.first-i,position.second) != '.' )
                break;
        }
        switch (i)
        {
        case 3:
            list.push_back("Rush");
        case 2:
            list.push_back("FastForward");
        case 1:
            list.push_back("Forward");
        }
        break;
    case Orientation::Down:
        while(i<3)
        {
            i++;
            if(map->CheckPosition(position.first+i,position.second+1) != '.' )
                break;
        }
        switch (i)
        {
        case 3:
            list.push_back("Rush");
        case 2:
            list.push_back("FastForward");
        case 1:
            list.push_back("Forward");
        }
        break;
    default:
        break;
    }
    state.UpdatePossibleActions(list);
}

Action ReflexAgent::FindBestAction(RobotState& state)
{
    // Wersja początkowa uproszczona
    double w[] = {1, 0.5, 1, 1};

    int xState = state.GetPosition().first;
    int yState = state.GetPosition().second;
    int xSuccessor = state.GetPosition().first;
    int ySuccessor = state.GetPosition().second;

    std::map<double,Action,std::greater<double>> actions;
    for(const Action& action : state.GetPossibleActions())
    {
        RobotState successor = GetSuccesorState(state, action);
       if(lastAction!=action) // Jeśli stanu nie znaleziono
       {

           ]\\\\\\
       }
    }
    std::cout<<std::endl;
    for(auto& act : actions)
    {
        std::cout<<act.first<<" "<<act.second.toStdString()<<" ";
    }
    return ((actions.begin())->second); // Return key value
}

RobotState ReflexAgent::GetSuccesorState(RobotState &state, Action action)
{
    RobotState succesor = state;
    succesor.UpdateState(actionRotation[action],actionTranslation[action]);
    return succesor;
}

Action ReflexAgent::MakeDecision(RobotState &state, QString Frame)
{
    map->UpdateWorldMap(Frame, state);
    map->PrintWorldMap();
    UpdatePossibleActions(state);
    return FindBestAction(state);
}

