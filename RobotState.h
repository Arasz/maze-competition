#ifndef STATE_H
#define STATE_H
#include "Types.h"
#include<iostream>
#include <map>




///
/// \brief The RobotState class
/// Contains full information about robot in the world
class RobotState
{

public:
    RobotState();
    RobotState(QChar rotation, QChar tran);

    Orientation GetOrientation() const;

    Vec2d GetPosition() const;

    int GetTranslation() const;

    Vec2d GetOrientationVector() const;

    void UpdateState(QChar rotation, QChar translation);



    bool operator== (const RobotState& state2) const;

private:
    Orientation orientation;
    int translation;
    Vec2d position;
    Vec2d orientationVector;

    void setOrientationVector(Orientation orientation);
    void updateOrientation(QChar rotation);
    void updateTranslation(QChar translation);
    void updatePosition();
};


#endif // STATE_H
