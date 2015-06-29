#include "SearchState.h"

SearchState::SearchState(Vec2d position, Orientation orientation, int dotsAmount, ActionsList actions)
    :position(position),orientation(orientation),dotsAmount(dotsAmount),actions(actions)
{
}

SearchState::SearchState()
{

}
Vec2d SearchState::getPosition() const
{
    return position;
}

void SearchState::setPosition(const Vec2d &value)
{
    position = value;
}
int SearchState::getDotsAmount() const
{
    return dotsAmount;
}

void SearchState::setDotsAmount(int value)
{
    dotsAmount = value;
}
Orientation SearchState::getOrientation() const
{
    return orientation;
}

void SearchState::setOrientation(const Orientation &value)
{
    orientation = value;
}

Orientation SearchState::getUpdatedOrientation(QChar rotation) const
{
    Orientation orientation = this->orientation;
    switch((int)rotation.toLatin1())
    {
    case (int)'0':
        break;
    case (int)'L':
        orientation = static_cast<Orientation>(  (uint(orientation-1))%4 );
        break;
    case (int)'R':
        orientation = static_cast<Orientation>(  (uint(orientation+1))%4 );
        break;
    }
    return orientation;
}

void SearchState::addAction(Action action)
{
    actions.push_back(action);
}
ActionsList SearchState::getActions() const
{
    return actions;
}

bool SearchState::operator<(const SearchState &state) const
{
    return this->dotsAmount < state.dotsAmount;
}





