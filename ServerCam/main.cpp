//
//  main.cpp
//  ServerCam
//
//  Created by Dustin Dettmer on 9/16/12.
//  Copyright (c) 2012 Dusty Technologies. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "LogParser.h"
#include "Json.h"
using namespace std;

int main(int argc, const char * argv[])
{
    if(argc > 2) {
        
        cout << argv[0] << " takes one argument: a filename.\n";
        return 0;
    }
    
    const char *filename = argv[1];
    
    if(!filename)
        filename = "/var/log/wtmp";
    
    ifstream in(filename);
    
    while(in) {
        
        LogParser logParser;
        
        logParser.data["server_id"] = "2";
        
        if(!logParser.parseOne(in)) {
            
            cout << "Incomplete entry, aborting.\n";
            break;
        }
        
        if(logParser.logParserType != LogParserTypeSshLogin)
            if(logParser.logParserType != LogParserTypeLogout)
                continue;
        
        cout << Json::toJson(logParser.data) << "\n\n";
    }
    
    return 0;
}

