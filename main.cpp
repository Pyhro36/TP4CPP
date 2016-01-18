#include <iostream>
#include <string>

#include "ShapeHandler.h"

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
    		case 10 :		
    			cout << "#unkown command" << endl;
    			break;			
    		case 100 :		
    			cout << "#invalid parameters" << endl;
    			break;  			
    		case 101 :   		
    			cout << "#name already used" << endl;
    			break;			
    		case 102 :   		
    			cout << "#name not used" << endl;
    			break;		
    		case 110 :		
    			cout << "#polygon defined is not convex" << endl;
    			break;			
    		case 120 :  		
    			cout << "#unkown file error" << endl;
    			break;			
    		case 121 :   		
    			cout << "#file does not exist" << endl;
    			break;			
    		default :		
    			cout << "#unknown error" << endl;
    			break;
    	} 
    	
    	getline(cin,cmd);
    }
    return 0;
}
