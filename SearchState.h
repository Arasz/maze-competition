#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H
#include "Types.h"


class SearchState
{
public:
    SearchState(Vec2d position, Orientation orientation  , int dotsAmount, ActionsList actions);
    SearchState();

    Vec2d getPosition() const;
    void setPosition(const Vec2d &value);

    int getDotsAmount() const;
    void setDotsAmount(int value);

    Orientation getOrientation() const;
    void setOrientation(const Orientation &value);
    Orientation getUpdatedOrientation(QChar rotation) const;

    void addAction(Action action);
    ActionsList getActions() const;

    bool operator<(const SearchState& state) const;

private:
    Vec2d position;
    Orientation orientation;
    int dotsAmount;
    ActionsList actions;

};
typedef std::vector<SearchState> StatesList;
#endif // SEARCHSTATE_H
