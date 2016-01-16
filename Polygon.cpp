#include <sstream>
#include "Polygon.h"

Polygon::Polygon(std::string polyName, std::vector<Point> polyPoints) : Shape(polyName), points(polyPoints)
{

}

bool Polygon::contain(Point point) const
{
    bool overBounded=false, underBounded=false;
    Point firstSegmentPoint = points.at(points.size()-1);
    Point secondSegmentPoint = points.at(0);
    for(int i=0 ; i<points.size() ; i++)
    {
        if( point.getX()==firstSegmentPoint.getX() && firstSegmentPoint.getX()==secondSegmentPoint.getX())
        {
            if( isBetween(point.getY(),firstSegmentPoint.getY(),secondSegmentPoint.getY()))
            {
                return true; //over and under bounded at the same time;
            }
            else
            {
                return  false; // the polygon is convex so the point can't be contained on the polygon
            }
        }
        else if( isBetween(point.getX(),firstSegmentPoint.getX(),secondSegmentPoint.getX()) )
        {
            double deltaY = firstSegmentPoint.getY()-secondSegmentPoint.getY();
            double deltaX = firstSegmentPoint.getX()-secondSegmentPoint.getX();

            double yOnCurrantSegment = (point.getX()-firstSegmentPoint.getX())*deltaY/deltaX + firstSegmentPoint.getY();

            if(yOnCurrantSegment > point.getY())
            {
                overBounded = true;
            }
            else if(yOnCurrantSegment < point.getY())
            {
                underBounded = true;
            }
            else // if yOnCurrantSegment == point.getY()
            {
                return true; //the point is on the segment so is contained on the polygon
            }
            // check if we have found the solution
            if(underBounded && overBounded)
            {
                return true; //we found a segment over the point and an other under, the point must be contained on the polygon (as it's a convex one)
            }
        }
        firstSegmentPoint = secondSegmentPoint;
        secondSegmentPoint = points.at(i);
    }
    return false;
}

void Polygon::move(Point vector)
{
    for(Point & point:points)
    {
        point+=vector;
    }
}

bool Polygon::isBetween(int x, int firstBound, int secondBound) const
{
    return ( firstBound>=x && secondBound<=x ) ||
           ( firstBound<=x && secondBound>=x );
}

std::string Polygon::describe() const
{
    std::stringstream ret;
    ret << "PC " << name;
    for(const Point & p:points)
    {
        ret << " " << p.getX() << " " << p.getY();
    }
    ret << std::endl;
    return ret.str();
}