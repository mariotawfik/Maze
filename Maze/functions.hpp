//
//  functions.hpp
//  Maze
//
//  Created by Mary Tamry on 27.04.22.
//

#ifndef functions_hpp
#define functions_hpp
using namespace std;

#include <stdio.h>
#include <vector>

class functions {
private:
    int** coordinates;
    int linenum;
    int intnum;
public:
    functions();
    void import();
    void printVector();
};

#endif /* functions_hpp */
