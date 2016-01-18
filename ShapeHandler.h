#ifndef TP_CPP3_SHAPEHANDLER_H
#define TP_CPP3_SHAPEHANDLER_H

#include <string>
#include "Point.h"
#include "Shape.h"
#include "Intersection.h"
#include "Union.h"
#include "Polygon.h"
#include "Segment.h"
#include "Rectangle.h"

class ShapeHandler {

public:
    ShapeHandler();

    int addRect(const std::string & name,const Point & firstCorner,const Point & secondCorner);
    int addSegment(const std::string & name,const Point & firstPoint,const Point & secondPoint);
    int addConvexPolygon(const std::string & name,const std::vector<Point> & polygonCorners);
    int addUnion(const std::string & name,const std::vector<std::string> & shapesToUnion);
    int addIntersection(const std::string & name,const std::vector<std::string> & shapesToIntersect);
};


#endif //TP_CPP3_SHAPEHANDLER_H
