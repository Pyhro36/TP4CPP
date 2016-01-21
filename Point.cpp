#include "Point.h"

Point::Point(int xCoordinate, int yCoordinate): x(xCoordinate), y(yCoordinate)
{

}

Point::Point(const Point& point): x(point.getX()), y(point.getY())
{

}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

Point Point::operator+(const Point & otherPoint) const
{
    Point ret(x+otherPoint.x,y+otherPoint.y);
    return ret;
}

Point & Point::operator+=(const Point & otherPoint)
{
    x += otherPoint.x;
    y += otherPoint.y;
    return *this;
}

Point Point::operator-(const Point & otherPoint) const
{
    Point ret(x-otherPoint.x,y-otherPoint.y);
    return ret;
}

Point & Point::operator-=(const Point & otherPoint)
{
    x -= otherPoint.x;
    y -= otherPoint.y;
    return *this;
}
