#include <sstream>
#include "Rectangle.h"

Rectangle::Rectangle(std::string RectName, Point firstCorner, Point secondCorner): Polygon(RectName)
{
    points.reserve(4); // set the reserved size of the vector to 4
    points.push_back(firstCorner);
    points.push_back(Point(firstCorner.getX(),secondCorner.getY()));
    points.push_back(secondCorner);
    points.push_back(Point(secondCorner.getX(),firstCorner.getY()));

    //set min and max coordinate
    if(firstCorner.getX() < secondCorner.getX())
    {
        xMin = firstCorner.getX();
        xMax = secondCorner.getX();
    }
    else
    {
        xMax = firstCorner.getX();
        xMin = secondCorner.getX();
    }

    if(firstCorner.getY() < secondCorner.getY())
    {
        yMin = firstCorner.getY();
        yMax = secondCorner.getY();
    }
    else
    {
        yMax = firstCorner.getY();
        yMin = secondCorner.getY();
    }
}

bool Rectangle::contain(Point point) const
{
    if( point.getX()<=xMax && point.getX()>=xMin && point.getY()<=yMax && point.getY()>=yMin)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Rectangle::describe() const
{
    std::stringstream ret;
    ret << "R " << name << " " << points.at(0).getX() << " " << points.at(0).getY();
    ret << points.at(2).getX() << " " << points.at(2).getY() << std::endl;
    return ret.str();
}