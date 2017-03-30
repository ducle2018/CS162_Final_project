#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

#include "user.h"
#include "course.h"
#include "score.h"
#include "presence.h"

using namespace std;

class CSV_heper{
public:
    User Get_details(string,string);
    Course Get_details(string,string);
    Presence Get_details(string,pair<string,string>);
    Score Get_details(string,pair<string,string> );
};

