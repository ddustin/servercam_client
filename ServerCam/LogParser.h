//
//  LogParser.h
//  ServerCam
//
//  Created by Dustin Dettmer on 9/16/12.
//  Copyright (c) 2012 Dusty Technologies. All rights reserved.
//

#ifndef ServerCam_LogParser_h
#define ServerCam_LogParser_h

#include <iostream>
#include <map>

enum LogParserType {
    LogParserTypeLogin = 6,
    LogParserTypeSshLogin = 7,
    LogParserTypeLogout = 8,
};

class LogParser {
public:
    
    LogParserType logParserType;
    
    /// Takes an input stream and parses out a single log value.
    /// If the stream is not large enough, false is returned
    /// and the parsing action is undone.
    bool parseOne(std::istream &data);
    
    /// A simple map holding all the parsed data, in a json ready format.
    typedef std::map<std::string, std::string> Data;
    Data data;
};

#endif
