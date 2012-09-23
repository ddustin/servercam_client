//
//  Json.h
//  ServerCam
//
//  Created by Dustin Dettmer on 9/22/12.
//  Copyright (c) 2012 Dusty Technologies. All rights reserved.
//

#ifndef ServerCam_Json_h
#define ServerCam_Json_h

#include <string>
#include <sstream>

class Json {
public:
    
    /// Escapes str and adds double quotes around str, returning the result.
    static std::string escapeString(std::string str)
    {
        using namespace std;
        
        for(string::iterator itr = str.begin(); itr != str.end(); ) {
            
            if(*itr == '"')
                itr = str.erase(itr);
            else
                ++itr;
        }
        
        str.insert(str.begin(), '"');
        str.push_back('"');
        
        return str;
    }
    
    template <typename ListType>
    static std::string toJson(const ListType &list)
    {
        using namespace std;
        
        typedef typename ListType::const_iterator IteratorType;
        
        ostringstream stream;
        
        stream << "{";
        
        for(IteratorType itr = list.begin(); itr != list.end(); ++itr) {
            
            stream << escapeString(itr->first) << ":" << escapeString(itr->second);
            
            if(++IteratorType(itr) != list.end())
                stream << ",";
        }
        
        stream << "}";
        
        return stream.str();
    }
};

#endif
