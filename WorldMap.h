#ifndef WORLDMAP_H
#define WORLDMAP_H

#define MAP_SIZE 21

#include <QString>
#include <RobotState.h>
#include <iostream>
#include "Types.h"

typedef char MapArray[MAP_SIZE][MAP_SIZE]; //> Map array type definition for better readability of code

class WorldMap
{
public:
    WorldMap();

    ///
    /// \brief updates world map
    ///
    void UpdateWorldMap(QString frame,  RobotState actualState);

    ///
    /// \brief PrintWorldMap
    ///
    void PrintWorldMap();

    char CheckPosition(int x, int y) const;

    void SetSymbolAtPosition(QChar sym, int x, int y);

    static int GetMapSize();

    int getMapCenter() const;

    void MakeMapCopy();
    void ReloadMapFromCopy();

private:
    const int mapCenter = ((MAP_SIZE-1)/2)+1; //> Map center
    const int viewAreaHeight = 4;
    const int viewAreaWidth = 7;
    Vec2d actualPositionOnMap;
    static const int mapSize = MAP_SIZE; //> Size of rectangular map
    char map[mapSize][mapSize]; //> World map
    MapArray mapCopy;
};

#endif // WORLDMAP_H
