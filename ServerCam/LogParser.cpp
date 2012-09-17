//
//  LogParser.cpp
//  ServerCam
//
//  Created by Dustin Dettmer on 9/16/12.
//  Copyright (c) 2012 Dusty Technologies. All rights reserved.
//

#include "LogParser.h"
#include "utmp_local.h"
#include <string.h>
#include <assert.h>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

static string nameOfType(int type)
{
    if(type == LogParserTypeSshLogin)
        return "ssh_login";
    
    if(type == LogParserTypeLogin)
        return "login";
    
    if(type == LogParserTypeLogout)
        return "logout";
    
    return "unknown";
}


template <typename Type>
string toString(const Type &type) {
    
    ostringstream strm;
    
    strm << type;
    
    return strm.str();
}

bool LogParser::parseOne(istream &in)
{
    streampos pos = in.tellg();
    
    if(in.seekg(sizeof(struct utmp), ios_base::cur).fail()) {
        
        in.clear(ios_base::failbit);
        
        assert(pos == in.tellg());
        
        return false;
    }
    
    struct utmp utmp;
    
    // Todo: check failure.
    in.read((char*)&utmp, sizeof(utmp));
    
    logParserType = (LogParserType)utmp.ut_type;
    
    data["process_id"] = toString(utmp.ut_pid);
    data["terminal_name"].assign(utmp.ut_line, strnlen(utmp.ut_line, sizeof(utmp.ut_line)));
    data["user_name"].assign(utmp.ut_user, strnlen(utmp.ut_user, sizeof(utmp.ut_user)));
    data["time_stamp"] = toString(utmp.ut_tv.tv_sec);
    
    data["login_ip_address"].assign(utmp.ut_host, strnlen(utmp.ut_host, sizeof(utmp.ut_host)));
    
    if(data["user_name"] == "ddustin") {
        
        cout << "Whats up with ddustin.\n";
    }
    
    return true;
}
