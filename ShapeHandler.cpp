
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
        bool lineBreak = false;
        while(getline(file,line))
        {
            if(lineBreak)
                ret.append("\n");
            else
                lineBreak=true;
            ret.append(line);
        }
        execute(ret, true);
		/*getline(file,line);
		while(!line.compare("|"))
		{
			ret.append(line);
			getline(file,line);
		}
		getline(file, line);
		undoCommandStack.push(line);
		execute(ret, true);
		undoCommandStack.pop();*/
	}
	return FILE_DOES_NOT_EXIST;
}

int ShapeHandler::undo()
{
    if(undoCommandStack.size()>0)
    {
        int returnCode;
        std::string command = undoCommandStack.top();
        redoCommandStack.push("");
        if( (returnCode=execute(command,false))==0 )
        {//if every things go right remove command from undo list
            //if the command has no undo command then generate a basic one
            if(command.find("|")==std::string::npos)
            {
                std::string redoCommand = "\n|\n";
                redoCommand.append(command);
                redoCommandStack.top().append(redoCommand);
            }
            undoCommandStack.pop();
        }
        return returnCode;
    }
    return 0;
}

int ShapeHandler::redo()
{
    if(redoCommandStack.size()>0)
    {
        int returnCode;
        std::string command = redoCommandStack.top();
        if( (returnCode=execute(command,true))==0 )
        {//if every things go right remove command from redo list
            redoCommandStack.pop();
        }
        return returnCode;
    }
    return 0;
}

int ShapeHandler::clear()
{
    int returnCode;
    for(const std::pair<std::string,Shape*> & element:nameShapeMap)
    {
        returnCode = removeShape(element.second->getName(),true);
        if(returnCode!=0)
        {
            return returnCode;
        }
    }
    return 0;
}

int ShapeHandler::hitShape(const std::string &shapeName, const Point &point)
{
    std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
    if(element != nameShapeMap.end())
    {
        if(element->second->contain(point))
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
        return 0;
    }
    else
    {
        return NAME_NOT_USED;
    }
}

int ShapeHandler::moveShape(const std::string &shapeName, const Point &vector, bool saveInUndoList)
{
    std::map<std::string,Shape*>::iterator element = nameShapeMap.find(shapeName);
    if(element != nameShapeMap.end())
    {
        //Undo management:
        std::stringstream undo;
        undo << "MOVE " << shapeName << " " << -vector.getX() << " " << -vector.getY() << std::endl;
        if(saveInUndoList)
        {//add the undo command to list:
            undoCommandStack.top().append(undo.str());
            //undoCommandStack.push(undo.str());
        }
        else
        {//add the undo command to redo list:
            redoCommandStack.top().append(undo.str());
            //redoCommandStack.push(undo.str());
        }
        //Move management
        element->second->move(vector);
        return 0;
    }
    else
    {
        return NAME_NOT_USED;
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
            int returnCode = addSegment(name,Point(x1,y1),Point(x2,y2),saveInUndoList);
            if(returnCode!=0)
            {
                return  returnCode;
            }
        }
        else if(commandId.compare("R")==0)
        {
            std::string name;
            int x1,x2,y1,y2;
            lineStream >> name >> x1 >> y1 >> x2 >> y2;
            int returnCode = addRect(name,Point(x1,y1),Point(x2,y2),saveInUndoList);
            if(returnCode!=0)
            {
                return  returnCode;
            }
        }
        else if(commandId.compare("PC")==0)
        {
            std::string name;
            std::vector<Point> points;
            int c[2];
            lineStream >> name;
            while(!lineStream.eof())
            {
                lineStream >> c[0];
                lineStream >> c[1];
                points.push_back(Point(c[0],c[1]));
            }
            int returnCode = addConvexPolygon(name,points,saveInUndoList);
            if(returnCode!=0)
                return returnCode;
        }
        else if(commandId.compare("OR")==0)
        {
            std::string name;
            std::vector<std::string> names;
            std::string temp;
            lineStream >> name;
            while(!lineStream.eof())
            {
                lineStream >> temp;
                names.push_back(temp);
            }
            int returnCode = addUnion(name,names,saveInUndoList);
            if(returnCode!=0)
                return returnCode;
        }
        else if(commandId.compare("OI")==0)
        {
            std::string name;
            std::vector<std::string> names;
            std::string temp;
            lineStream >> name;
            while(!lineStream.eof())
            {
                lineStream >> temp;
                names.push_back(temp);
            }
            int returnCode = addIntersection(name,names,saveInUndoList);
            if(returnCode!=0)
                return returnCode;
        }
        else if(commandId.compare("HIT")==0)
        {
            std::string name;
            int x,y;
            lineStream >> name >> x >> y;
            int returnCode = hitShape(name,Point(x,y));
            if(returnCode!=0)
            {
                return  returnCode;
            }
        }
        else if(commandId.compare("DELETE")==0)
        {
            std::string temp;
            std::vector<std::string> toDelete;
            int returnCode;
            while(!lineStream.eof())
            {
                lineStream >> temp;
                if(nameShapeMap.find(temp) == nameShapeMap.end())
                {
                    return NAME_NOT_USED;
                }
                toDelete.push_back(temp);
            }
            for(std::string name:toDelete)
            {
                if(0!=(returnCode=removeShape(name,saveInUndoList)))
                {
                    return returnCode;
                }
            }
        }
        else if(commandId.compare("MOVE")==0)
        {
            std::string name;
            int x,y;
            lineStream >> name >> x >> y;
            int returnCode = moveShape(name,Point(x,y),saveInUndoList);
            if(returnCode!=0)
            {
                return  returnCode;
            }
        }
        else if(commandId.compare("LIST")==0)
        {
            std::cout << list() << std::endl;
        }
        else if(commandId.compare("UNDO")==0)
        {
            int returnCode;
            if(0!=(returnCode= undo() ))
            {
                return returnCode;
            }
        }
        else if(commandId.compare("REDO")==0)
        {
            int returnCode;
            if(0!=(returnCode= redo() ))
            {
                return returnCode;
            }
        }
        else if(commandId.compare("LOAD")==0)
        {
            std::string filePath;
            lineStream >> filePath;
            int returnCode;
            if(0!=(returnCode= loadFile(filePath) ))
            {
                return returnCode;
            }
        }
        else if(commandId.compare("SAVE")==0)
        {
            std::string filePath;
            lineStream >> filePath;
            int returnCode;
            if(0!=(returnCode= saveFile(filePath) ))
            {
                return returnCode;
            }
        }
        else if(commandId.compare("CLEAR")==0)
        {
            int returnCode;
            if(0!=(returnCode= clear() ))
            {
                return returnCode;
            }
        }
        else if(commandId.compare("|")==0)
        {//set the undo/redo command to the specified command
            std::string undoCommand("");
            //get the undo command from input
            getline(lineStream,undoCommand);
            std::string undoCommandLine;
            while(std::getline(commandStream,undoCommandLine))
            {
                undoCommand.append("\n");
                undoCommand.append(undoCommandLine);
            }
            //get the redo command
            unsigned long endOfCommand = command.find_first_of('|');
            undoCommand.append("|\n");
            undoCommand.append(command.substr(0,endOfCommand-1));
            //save the command to the appropriate stack:
            if(saveInUndoList)
            {
                undoCommandStack.pop();
                undoCommandStack.push(undoCommand);
            }
            else
            {
                redoCommandStack.pop();
                redoCommandStack.push(undoCommandLine);
            }

        }
        else
        {
            return UNKNOWN_COMMAND;
        }
    }
    return 0;
}

int ShapeHandler::userExecute(const std::string &command)
{
    //if it's a creation command clear redo stack and create a new undo command:
    if(command.substr(0,4).compare("REDO")!=0 && command.substr(0,4).compare("UNDO")!=0 &&
            command.substr(0,4).compare("LIST")!=0 && command.substr(0,3).compare("HIT")!=0 &&
            command.substr(0,4).compare("SAVE")!=0)
    {
        //clear redo stack
        for(unsigned i=0 ; i<redoCommandStack.size() ; i++)
        {
            redoCommandStack.pop();
        }
        //add an empty undo line
        undoCommandStack.push("");
    }

    //execute command:
    int returnCode = execute(command);
    if(returnCode == 0 && command.at(0)!='L' && command.at(0)!='H' ) //L and H not to show 'OK' when HIT or LIST command
    {
        std::cout << "OK" << std::endl;
    }
    return returnCode;
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
