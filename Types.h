#ifndef TYPES
#define TYPES

#include<QString>
#include<vector>
#include<map>

typedef std::pair<int,int> Vec2d;
typedef std::vector<QString> ActionsList;
typedef QString Action;


enum Orientation
{
    Unknown = -1,
    Left = 0,
    Up =  1,
    Right = 2,
    Down = 3,
};

class OrientationConverter
{
private:
    std::map<Orientation,Vec2d> orientationMap = {{Up,{0,-1}},{Down,{0,1}},{Left,{-1,0}},{Right,{1,0}},{Unknown,{-9,-9}}};

public:

    Vec2d GetOrientationVector(Orientation orientation)
    {
        return orientationMap[orientation];
    }
};


#endif // TYPES

