#include "Segment.h"
#include <sstream>

Segment::Segment(const std::string & name,const Point & firstPoint,const Point & secondPoint): Polygon(name)
{
    points.reserve(2); // set the reserved size of the vector to 2
    points.push_back(firstPoint);
    points.push_back(secondPoint);
}

bool Segment::contain(const Point & point) const
{
    if( point.getX()==points.at(0).getX() && points.at(0).getX()==points.at(1).getX())
    {
        if( isBetween(point.getY(),points.at(0).getY(),points.at(1).getY()))
        {
            return true; //the point is on the segment
        }
        else
        {
            return  false; //the point is not on the segment
        }
    }
    else if( isBetween(point.getX(),points.at(0).getX(),points.at(1).getX()) )
    {
        double deltaY = points.at(0).getY()-points.at(1).getY();
        double deltaX = points.at(0).getX()-points.at(1).getX();

        double yOnCurrantSegment = (point.getX()-points.at(0).getX())*deltaY/deltaX + points.at(0).getY();

        if(yOnCurrantSegment == point.getY())
        {
            return true; //the point is on the segment
        }
    }
    return false;
}

bool Segment::isBetween(int x, int firstBound, int secondBound) const
{
    return ( firstBound>=x && secondBound<=x ) ||
           ( firstBound<=x && secondBound>=x );
}

std::string Segment::describe() const
{
    std::stringstream ret;
    ret << "S " << name << " " << points.at(0).getX() << " " << points.at(0).getY();
    ret << points.at(1).getX() << " " << points.at(1).getY() << std::endl;
    return ret.str();
}