#include <iostream>
#include <string>

#include "ShapeHandler.h"
#include "ErrorCode.h"

using namespace std;

int main() {
    
    cout << "Shape handler 1.0 :" << endl;
    
    ShapeHandler shapeHandler;
    int code;
    
    
    string cmd;
	getline(cin,cmd);
    
    while(cmd.compare("EXIT"))
    {
    	code = shapeHandler.userExecute(cmd);
    	
    	switch (code) 
    	{
    		case 0 :
    			break;		
    		case UNKNOWN_COMMAND :
    			cout << "#unkown command" << endl;
    			break;			
    		case INVALID_PARAMETERS :
    			cout << "#invalid parameters" << endl;
    			break;  			
    		case NAME_ALREADY_USED :
    			cout << "#name already used" << endl;
    			break;			
    		case NAME_NOT_USED :
    			cout << "#name not used" << endl;
    			break;		
    		case POLYGON_IS_NOT_CONVEX :
    			cout << "#polygon defined is not convex" << endl;
    			break;			
    		case POLYGON_LESS_THAN_3 :
    			cout << "#polygon defined contains less than 3 corners" << endl;
    			break;
    		case UNKNOWN_FILE_ERROR :
    			cout << "#unkown file error" << endl;
    			break;			
    		case FILE_DOES_NOT_EXIST :
    			cout << "#file does not exist" << endl;
    			break;
			case NOTHING_TO_DO:
				cout << "#nothing to be done" << endl;
				break;
    		default :		
    			cout << "#unknown error" << endl;
    			break;
    	} 
    	
    	getline(cin,cmd);
    }
    return 0;
}
