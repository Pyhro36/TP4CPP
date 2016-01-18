
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "ShapeHandler.h"
#include "ErrorCode.h"

ShapeHandler::ShapeHandler()
{

}

ShapeHandler::~ShapeHandler()
{
    for(std::map<std::string,Shape*>::iterator shapeAndName=nameShapeMap.begin() ; shapeAndName!=nameShapeMap.end() ; shapeAndName++ )
    {
        delete shapeAndName->second;
        nameShapeMap.erase(shapeAndName);
    }
}

int ShapeHandler::addShape(Shape *shapeToAdd, bool saveInUndoList)
{
    if(nameShapeMap.count(shapeToAdd->getName()) == 0)
    {
        //prepare undo command:
        std::string undo = "DELETE ";
        undo.append(shapeToAdd->getName());
        //put undo command on stack:
        if(saveInUndoList)
        {
            undoCommandStack.push(undo);
        }
        else
        {
            redoCommandStack.push(undo);
        }

        nameShapeMap.insert(std::pair<std::string,Shape*>(shapeToAdd->getName(),shapeToAdd));
        return 0;
    }
    else
    {
        return NAME_ALREADY_USED;
    }
}

int ShapeHandler::addSegment(const std::string &name, const Point &firstPoint, const Point &secondPoint, bool saveInUndoList)
{
    Shape * segment = new Segment(name,firstPoint,secondPoint);
    return addShape(segment,saveInUndoList);
}

int ShapeHandler::addRect(const std::string &name, const Point &firstCorner, const Point &secondCorner, bool saveInUndoList)
{
    Shape * rect = new Rectangle(name,firstCorner,secondCorner);
    return addShape(rect,saveInUndoList);
}

int ShapeHandler::addConvexPolygon(const std::string &name, const std::vector<Point> &polygonCorners, bool saveInUndoList)
{
    Shape * polygon = new Polygon(name, polygonCorners);
    //TODO: check if the polygon is convex
    /*if( poligon is not convex )
    {
        return POLYGON_IS_NOT_CONVEX;
    }*/
    return addShape(polygon,saveInUndoList);
}

int ShapeHandler::addIntersection(const std::string &name, const std::vector<std::string> &shapesToIntersect,
                                  bool saveInUndoList)
{
    std::vector<Shape*> shapeList;
    shapeList.reserve(shapesToIntersect.size());
    for(const std::string & name:shapesToIntersect)
    {

    }
}

int ShapeHandler::removeShape(const std::string &shapeName, bool saveInUndoList)
{
    std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
    if(element != nameShapeMap.end())
    {
        if(saveInUndoList)
        {//add the undo command to list:
            undoCommandStack.push(element->second->describe());
        }
        else
        {//add the undo command to redo list:
            redoCommandStack.push(element->second->describe());
        }
        delete element->second; //delete object
        nameShapeMap.erase(element); //delete object from map
        return 0;
    }
    else
    {
        return NAME_NOT_USED;
    }
}

int ShapeHandler::saveFile(const std::string & fileName)
{
	std::ofstream file(fileName, std::ios::out | std::ios::trunc);

	if(file)
	{
		file << list();
		file.close();
		return 0;
	}
		return UNKNOWN_FILE_ERROR;
}

int ShapeHandler::loadFile(const std::string & fileName)
{
	ifstream file(fileName, ios::in);
	
	if(file)
	{
		string ret = "";
		string line;
		getline(file,line);
		while(!line.compare("|"))
		{
			ret.append(line);
			getline(file,line);
		}
		getline(file, line);
		undoCommandStack.push(line);
		execute(ret, true);
		undoCommandStack.pop();
	}
	return FILE_DOES_NOT_EXIST;
}

int ShapeHandler::undo()
{
    if(undoCommandStack.size()>0)
    {
        std::string command = undoCommandStack.top();
        if( execute(command,false)==0 )
        {
            //if every things go right remove command from undo list
            undoCommandStack.pop();
        }
    }
}

int ShapeHandler::redo()
{
    if(redoCommandStack.size()>0)
    {
        std::string command = redoCommandStack.top();
        if( execute(command,true)==0 )
        {
            //if every things go right remove command from undo list
            redoCommandStack.pop();
        }
    }
}

std::stringstream ShapeHandler::list()
{
	std::stringstream ret;
	
	for(std::pair<std::string, Shape *> s:nameShapeMap)
	{s
		ret << s.second->describe();
	}
	
	ret << std::endl << "|" << std::endl << "DELETE ";
	
	for(std::pair<std::string, Shape *> s:nameShapeMap)
	{ 
		ret << s.first << " ";
	}
	
	return ret;
}
