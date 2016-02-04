#include <sstream>
#include "Polygon.h"

Polygon::Polygon(const std::string & polyName,const std::vector<Point> & polyPoints) : Shape(polyName), points(polyPoints)
{

}

bool Polygon::contain(const Point & point) const
{
    bool overBounded=false, underBounded=false;
    Point firstSegmentPoint(0,0);
    Point secondSegmentPoint = points.at(points.size()-1);

    for(unsigned i=0 ; i<points.size() ; i++)
    {
        firstSegmentPoint = secondSegmentPoint;
        secondSegmentPoint = points.at(i);

        if( point.getX()==firstSegmentPoint.getX() && firstSegmentPoint.getX()==secondSegmentPoint.getX())
        {
            if( isBetween(point.getY(),firstSegmentPoint.getY(),secondSegmentPoint.getY()))
            {
                return true; //over and under bounded at the same time;
            }
            else
            {
                return  false; // the polygon is convex so the point can't be contained on the polygon
                               // (may add false result in case of aligned points)
            }
        }
        else if( isBetween(point.getX(),firstSegmentPoint.getX(),secondSegmentPoint.getX()) )
        {
            if( point.getY()==firstSegmentPoint.getY() && firstSegmentPoint.getY()==secondSegmentPoint.getY())
            {//if the line is as y=const then if the point have the same y it's on the polygon
                return true;
            }
            else if( point.getY()<=firstSegmentPoint.getY() && point.getY()<=secondSegmentPoint.getY() )
            {//if the both extremity of the segment are over the point
                overBounded = true;
            }
            else if(point.getY()>=firstSegmentPoint.getY() && point.getY()>=secondSegmentPoint.getY())
            {//if the both extremity of the segment are under the point
                underBounded = true;
            }
            else
            {//if the point is between the two some work is needed
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
            }
            // check if we have found the solution
            if(underBounded && overBounded)
            {
                return true; //we found a segment over the point and an other under, the point must be contained on the polygon (as it's a convex one)
            }
        }
    }
    return false;
}

void Polygon::move(const Point & vector)
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

Shape* Polygon::clone() const
{
    return new Polygon(*this);
}
