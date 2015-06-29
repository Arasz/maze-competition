#include "RobotState.h"

RobotState::RobotState()
    :orientation(Orientation::Unknown), translation(0), position({0,0})
{}

RobotState::RobotState(QChar rotation, QChar tran)
{
    updateOrientation(rotation);
    updateTranslation(tran);

    std::cout<<std::endl<<"Translation: "<<translation<<std::endl;
    std::cout<<std::endl<<"Last Orientation: "<<orientation<<std::endl;
}


Orientation RobotState::GetOrientation() const
{
    return this->orientation;
}

Vec2d RobotState::GetPosition() const
{
    return this->position;
}

int RobotState::GetTranslation() const
{
    return this->translation;
}

void RobotState::updateOrientation(QChar rotation)
{
    switch((int)rotation.toLatin1())
    {
    case (int)'0':
        break;
    case (int)'X':
        orientation = Orientation::Right;
        setOrientationVector(orientation);
        translation = 0;
        return;
    case (int)'L':
        orientation = static_cast<Orientation>(  (uint(orientation-1))%4 );
        setOrientationVector(orientation);
        break;
    case (int)'R':
        orientation = static_cast<Orientation>(  (uint(orientation+1))%4 );
        setOrientationVector(orientation);
        break;
    }
}

void RobotState::updateTranslation(QChar translation)
{
    if(translation != 'X')
        this->translation = (int)(translation.toLatin1())-48;
}

void RobotState::updatePosition()
{
    this->position.first += orientationVector.first*translation;
    this->position.second += orientationVector.second*translation;
}

void RobotState::UpdateState(QChar rotation, QChar translation)
{
    updateOrientation(rotation);
    updateTranslation(translation);
    updatePosition();
}

Vec2d RobotState::GetOrientationVector() const
{
    return orientationVector;
}


bool RobotState::operator==(const RobotState &state2) const
{
    if(this->position == state2.position && this->orientation == state2.orientation && this->translation == state2.translation)
        return true;
    else
        return false;
}


void RobotState::setOrientationVector(Orientation orientation)
{
    switch (orientation)
    {
    case Orientation::Right:
        orientationVector = {1,0};
        break;
    case Orientation::Up:
        orientationVector = {0,-1};
        break;
    case Orientation::Left:
        orientationVector = {-1,0};
        break;
    case Orientation::Down:
        orientationVector = {0,1};
        break;
    default:
        break;
    }
}


