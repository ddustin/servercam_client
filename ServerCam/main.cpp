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
#include <curl/curl.h>
#include <cstring>
#include <assert.h>
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
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    ifstream in(filename);
    
    ostringstream ss;
    
    ss << "{\"server_id\":\"1\", \"session_records\":[";
    
    for(int i = 0; in; ) {
        
        LogParser logParser;
        
        logParser.data["server_id"] = "2";
        
        if(!logParser.parseOne(in)) {
            
            cout << "Incomplete entry, aborting.\n";
            break;
        }
        
        if(logParser.logParserType != LogParserTypeSshLogin)
            if(logParser.logParserType != LogParserTypeLogout)
                continue;
        
        if(i++)
            ss << ",";
        
        ss << Json::toJson(logParser.data);
    }
    
    ss << "]}";
    
    cout << ss.str() << endl;
    
    CURL *curl_handle = curl_easy_init();
    CURLcode res = CURLE_OK;
    
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://50.97.174.26:5001/monitor/api/sync");
    
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
    
    struct curl_slist *chunk = NULL;
    
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
    
    res = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, chunk);
    
    assert(res == CURLE_OK);
    
    string str = ss.str().c_str();
    
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, str.c_str());
    
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, str.length());
    
    res = curl_easy_perform(curl_handle);
    
    cout << "Result: " << res << endl;
    
    assert(res == CURLE_OK);
    
    curl_easy_cleanup(curl_handle);
    
    return 0;
}

