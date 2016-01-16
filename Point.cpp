#include "Point.h"

Point::Point(int xCoordinate, int yCoordinate): x(xCoordinate), y(yCoordinate)
{

}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

Point Point::operator+(Point otherPoint)
{
    Point ret(x+otherPoint.x,y+otherPoint.y);
}

Point Point::operator+=(Point otherPoint)
{
    x += otherPoint.x;
    y += otherPoint.y;
}

Point Point::operator-(Point otherPoint)
{
    Point ret(x-otherPoint.x,y-otherPoint.y);
}

Point Point::operator-=(Point otherPoint)
{
    x -= otherPoint.x;
    y -= otherPoint.y;
}
