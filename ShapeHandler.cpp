
#include <fstream>
#include <iostream>
#include <sstream>
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
            //undoCommandStack.push(undo);
            undoCommandStack.top().append(undo);
        }
        else
        {
            //redoCommandStack.push(undo);
            redoCommandStack.top().append(undo);
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
/*
 * Algorithme 
 * Pour chacun des sommets du polygone, on teste si il se trouve bien
 * a l'exterieur du polygone forme par tous les autres points du polygone
 * etudie
 * on utilise la methode contain() de Polygon sur le point
 * Pour un polygone concave, cette methode peut indiquer que le point est
 * a l'interieur alors qu'il est a l'exterieur, mais jamais l'inverse, et
 * cette methode est eprouvee pour un polygone convexe, donc ne trouvera
 * jamais pour un polygone convexe un sommet a l'interieur du polygone
 * nouvellement forme 
 * Donc si un des sommets est a l'interieur du polygone reforme sans ce 
 * sommet, le polygone est concave et indquier comme incorrect
 */
{
 /* TODO test */
    Shape * polygon = new Polygon(name, polygonCorners);
    Polygon trunc;
    std::vector<Point> truncCorners(polygonCorners);
    int size = polygonCorners.size();
    for(int i = 0, i < size, i++)
    {
    	trunc.erase(trunc.begin()+i);
    	if(trunc.contain(polygonCorners[i]))
        	return POLYGON_IS_NOT_CONVEX;
        trunc.insert(trunc.begin()+i, polygonCorners[i]);
    }
    
    return addShape(polygon,saveInUndoList);
}

int ShapeHandler::addIntersection(const std::string &name, const std::vector<std::string> &shapesToIntersect,
                                  bool saveInUndoList)
{
    std::vector<Shape*> shapeList;
    shapeList.reserve(shapesToIntersect.size());
    for(const std::string &shapeName:shapesToIntersect)
    {
        std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
        if(element!=nameShapeMap.end())
        {
            shapeList.push_back(element->second->clone());
        }
        else
        {
            return NAME_NOT_USED;
        }
    }
    Intersection * intersection = new Intersection(name,shapeList);
    return addShape(intersection,saveInUndoList);
}

int ShapeHandler::addUnion(const std::string &name, const std::vector<std::string> &shapesToUnion,
                           bool saveInUndoList)
{
    std::vector<Shape*> shapeList;
    shapeList.reserve(shapesToUnion.size());
    for(const std::string &shapeName:shapesToUnion)
    {
        std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
        if(element!=nameShapeMap.end())
        {
            shapeList.push_back(element->second->clone());
        }
        else
        {
            return NAME_NOT_USED;
        }
    }
    Union * anUnion = new Union(name,shapeList);
    return addShape(anUnion,saveInUndoList);
}

int ShapeHandler::removeShape(const std::string &shapeName, bool saveInUndoList)
{
    std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
    if(element != nameShapeMap.end())
    {
        if(saveInUndoList)
        {//add the undo command to list:
            undoCommandStack.top().append(element->second->describe());
            //undoCommandStack.push(element->second->describe());
        }
        else
        {//add the undo command to redo list:
            redoCommandStack.top().append(element->second->describe());
            //redoCommandStack.push(element->second->describe());
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
		file << deleteList();
		file.close();
		return 0;
	}
		return UNKNOWN_FILE_ERROR;
}

int ShapeHandler::loadFile(const std::string & fileName)
{
    std::ifstream file(fileName, std::ios::in);

	if(file)
	{
        std::string ret = "";
        std::string line;
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
        {//if every things go right remove command from undo list
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
        {//if every things go right remove command from redo list
            redoCommandStack.pop();
        }
    }
}

int ShapeHandler::execute(const std::string &command, bool saveInUndoList)
{
    std::stringstream commandStream;
    commandStream.str(command);
    std::string line;
    std::stringstream lineStream;
    std::string commandId;
    //read command line by line
    while(std::getline(commandStream,line))
    {
        lineStream.str(line);
        lineStream >> commandId;
        if(commandId.compare("S")==0)
        {
            std::string name;
            int x1,x2,y1,y2;
            lineStream >> name >> x1 >> y1 >> x2 >> y2;
            addSegment(name,Point(x1,y1),Point(x2,y2));
        }
        else if(commandId.compare("R")==0)
        {
            std::string name;
            int x1,x2,y1,y2;
            lineStream >> name >> x1 >> y1 >> x2 >> y2;
            addRect(name,Point(x1,y1),Point(x2,y2));
        }
        else if(commandId.compare("PC")==0)
        {
            std::string name;
            std::vector<Point> points;
            int c[2];
            for(int i = 0; lineStream ; i=1-i) {
                lineStream >> c[i];
                if(i==1)
                {
                    points.push_back(Point(c[0],c[1]));
                }
            }
        }
        else if(commandId.compare("OR")==0)
        {

        }
        else if(commandId.compare("OI")==0)
        {

        }
        else if(commandId.compare("HIT")==0)
        {

        }
        else if(commandId.compare("DELETE")==0)
        {

        }
        else if(commandId.compare("MOVE")==0)
        {

        }
        else if(commandId.compare("LIST")==0)
        {

        }
        else if(commandId.compare("UNDO")==0)
        {

        }
        else if(commandId.compare("REDO")==0)
        {

        }
        else if(commandId.compare("LOAD")==0)
        {

        }
        else if(commandId.compare("SAVE")==0)
        {

        }
        else if(commandId.compare("CLEAR")==0)
        {

        }
        else if(commandId.compare("EXIT")==0)
        {

        }
        else
        {

        }
    }
}

std::string ShapeHandler::list()
{
	std::stringstream ret;

	for(std::pair<std::string, Shape *> s:nameShapeMap)
	{
		ret << s.second->describe();
	}
	
	return ret.str();
}

std::string ShapeHandler::deleteList()
{
	std::stringstream ret;
	ret << std::endl << "|" << std::endl << "DELETE ";

	for(std::pair<std::string, Shape *> s:nameShapeMap)
	{
		ret << s.first << " ";
	}

	return ret.str();
}
