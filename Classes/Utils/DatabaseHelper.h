

#ifndef __DatabaseHelper__
#define __DatabaseHelper__

#include <iostream>
#include <string>
//#include "CCFileUtils.h"

using namespace std;

class DatabaseHelper {
private:
    static DatabaseHelper *_sharedDatabaseHelper;
    string fileName(string pDatabaseName);
protected:
    int copyfile(string pSource, string pDest);
public:
    static DatabaseHelper *getInstance();
    bool createDatabase(string pDatabaseName);
    string databasePath(string pDatabaseName);
};

#endif /* defined(__GIRLS_Framework_part__DatabaseHelper__) */
