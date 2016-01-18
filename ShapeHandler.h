#ifndef TP_CPP3_SHAPEHANDLER_H
#define TP_CPP3_SHAPEHANDLER_H

#include <string>
#include <map>
#include <stack>
#include <sstream>

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

    int execute(const std::string & command, bool saveInUndoList = true);

private:
    int addRect(const std::string & name,const Point & firstCorner,const Point & secondCorner, bool saveInUndoList = true);
    int addSegment(const std::string & name,const Point & firstPoint,const Point & secondPoint, bool saveInUndoList = true);
    int addConvexPolygon(const std::string & name,const std::vector<Point> & polygonCorners, bool saveInUndoList = true);
    int addUnion(const std::string & name,const std::vector<std::string> & shapesToUnion, bool saveInUndoList = true);
    int addIntersection(const std::string & name,const std::vector<std::string> & shapesToIntersect, bool saveInUndoList = true);

    int addShape(Shape * shapeToAdd, bool saveInUndoList = true);
    int removeShape(const std::string & shapeName, bool saveInUndoList = true);

    int saveFile(const std::string & fileName);
    int loadFile(const std::string & fileName, bool saveUndoList = true);

    int clear();
    int undo();
    int redo();
    
    std::stringstream list();

};


#endif //TP_CPP3_SHAPEHANDLER_H
