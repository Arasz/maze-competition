#include "WorldMap.h"

WorldMap::WorldMap()
{
    actualPositionOnMap = {mapCenter, mapCenter};
    for(int i = 0; i< mapSize; i++)
    {
        for( int q = 0; q< mapSize; q++)
        {
           map[i][q]='?';
           mapCopy[i][q]='?';
        }
    }
}


void WorldMap::UpdateWorldMap(QString frame,  RobotState actualState)
{
    switch( actualState.GetOrientation() )
    {
    case Orientation::Up:
    {
        actualPositionOnMap.second = actualState.GetPosition().second+mapCenter;

        int framePosition = 0;

        for(  int i =actualPositionOnMap.second; i>actualPositionOnMap.second-viewAreaHeight; i-- ) // Width of frame, y map
        {
            for( int q =actualPositionOnMap.first-3; q<=actualPositionOnMap.first+3; q++) // Height of frame, x map
            {
                if((map[i][q] == '?') && (frame[framePosition]!='?')) // Check if there is no data in given map position
                {
                    map[i][q] = frame[framePosition].toLatin1();
                }
                framePosition++;
            }
        }
        std::cout<<std::endl<<"Orientation: "<< actualState.GetOrientation() << " x: "<< actualPositionOnMap.first<<" y: "<<actualPositionOnMap.second<<std::endl;
        break;
    }
    case Orientation::Down:
    {
        actualPositionOnMap.second = actualState.GetPosition().second+mapCenter;

        int framePosition = 0;

        for(int i =actualPositionOnMap.second; i<actualPositionOnMap.second+viewAreaHeight; i++) // Width of frame, y map
        {
            for( int q =actualPositionOnMap.first+3; q>=actualPositionOnMap.first-3; q--) // Height of frame, x map
            {
                if((map[i][q] == '?') && (frame[framePosition]!='?')) // Check if there is no data in given map position
                {
                    map[i][q] = frame[framePosition].toLatin1();
                }
                framePosition++;
            }
        }
        std::cout<<std::endl<<"Orientation: "<< actualState.GetOrientation() << " x: "<< actualPositionOnMap.first<<" y: "<<actualPositionOnMap.second<<std::endl;
        break;
    }
    case Orientation::Left:
    {
        actualPositionOnMap.first = actualState.GetPosition().first+mapCenter;

        int framePosition = 0;

        for( int q =actualPositionOnMap.first; q>actualPositionOnMap.first-viewAreaHeight; q--) // Height of frame, x map
        {
            for( int i =actualPositionOnMap.second+3; i>=actualPositionOnMap.second-3; i--) // Width of frame, y map
            {
                if((map[i][q] == '?') && (frame[framePosition]!='?')) // Check if there is no data in given map position
                {
                    map[i][q] = frame[framePosition].toLatin1();
                }
                framePosition++;
            }
        }
        std::cout<<std::endl<<"Orientation: "<< actualState.GetOrientation() << " x: "<< actualPositionOnMap.first<<" y: "<<actualPositionOnMap.second<<std::endl;
        break;
    }
    case Orientation::Right:
    {
        actualPositionOnMap.first = actualState.GetPosition().first+mapCenter;

        int framePosition = 0;

        for( int q =actualPositionOnMap.first; q<actualPositionOnMap.first+viewAreaHeight; q++) // Height of frame, x map
        {
            for( int i =actualPositionOnMap.second-3; i<=actualPositionOnMap.second+3; i++) // Width of frame, y map
            {
                if((map[i][q] == '?') && (frame[framePosition]!='?')) // Check if there is no data in given map position
                {
                    map[i][q] = frame[framePosition].toLatin1();
                }
                framePosition++;
            }
        }
        std::cout<<std::endl<<"Orientation: "<< actualState.GetOrientation() << " x: "<< actualPositionOnMap.first<<" y: "<<actualPositionOnMap.second<<std::endl;

        break;
    }
    case Orientation::Unknown:
        return;
    }
}

void WorldMap::PrintWorldMap()
{
    std::cout<<"World Map"<<std::endl;
    for(int i = 0; i< mapSize; i++)
    {
        for( int q = 0; q< mapSize; q++)
        {
            if(q == actualPositionOnMap.first && i == actualPositionOnMap.second)
                std::cout<<'R'<<"|";
            else
                std::cout<<map[i][q]<<"|";
        }
        std::cout<<std::endl;
    }
}

char WorldMap::CheckPosition(int x, int y) const
{
    return map[y+mapCenter][x+mapCenter];
}

void WorldMap::SetSymbolAtPosition(QChar sym, int x, int y)
{
    map[y+mapCenter][x+mapCenter] = sym.toLatin1();
}
int WorldMap::GetMapSize()
{
    return mapSize;
}
int WorldMap::getMapCenter() const
{
    return mapCenter;
}

void WorldMap::MakeMapCopy()
{
    for(int i = 0; i<this->mapSize; i++)
    {
        for(int j = 0; j<this->mapSize; j++)
        {
            mapCopy[i][j]=map[i][j];
        }
    }
}

void WorldMap::ReloadMapFromCopy()
{
    for(int i = 0; i<this->mapSize; i++)
    {
        for(int j = 0; j<this->mapSize; j++)
        {
            map[i][j]=mapCopy[i][j];
        }
    }
}



