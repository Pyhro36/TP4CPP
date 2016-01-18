#ifndef TP_CPP3_SHAPEHANDLER_H
#define TP_CPP3_SHAPEHANDLER_H

#include <string>
#include <map>
#include <stack>

#include "Point.h"
#include "Shape.h"
#include "Intersection.h"
#include "Union.h"
#include "Polygon.h"
#include "Segment.h"
#include "Rectangle.h"

class ShapeHandler {
private:
    std::map<std::string,Shape*> nameShapeMap; //map of pointer to Shape ordered by shape name
    std::stack<std::string> undoCommandStack; //LIFO list of command, one command per undo (one command can have more than one line)
    std::stack<std::string> redoCommandStack; //LIFO list of command, one command per redo (one command can have more than one line)

public:
    ShapeHandler();
    virtual ~ShapeHandler();

    void execute(const std::string & command);

private:
    int addRect(const std::string & name,const Point & firstCorner,const Point & secondCorner);
    int addSegment(const std::string & name,const Point & firstPoint,const Point & secondPoint);
    int addConvexPolygon(const std::string & name,const std::vector<Point> & polygonCorners);
    int addUnion(const std::string & name,const std::vector<std::string> & shapesToUnion);
    int addIntersection(const std::string & name,const std::vector<std::string> & shapesToIntersect);
    void addShape(Shape * shapeToAdd);

    int removeShape(const std::string & shapeName);

    int clear();
    int undo();
    int redo();
};


#endif //TP_CPP3_SHAPEHANDLER_H
