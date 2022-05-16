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
#include <stack>
#include <SFML/Graphics.hpp>

class functions {
private:
    int** coordinates;
    int *currentPosition;
    int linenum;
    int intnum;
    stack<int> positionX, positionY, windowX, windowY, ballSpeed;
    int lineWidth;
    int lineHeight;
    int lineLength;
    int playerRadius;
public:
    functions();
    void import();
    void drawMaze();
    void options();
};

#endif /* functions_hpp */
