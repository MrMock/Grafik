#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

using namespace std;

class request
{

public:
    request(string employee_ID);
    void draw();
    void add_request();

private:
    string ID;
    void recognition();
    void load();

};

#endif // REQUEST_H
