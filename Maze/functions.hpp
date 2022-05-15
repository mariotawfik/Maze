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
    int *currentPosition, currentOrientation;
    int linenum;
    int intnum;
    stack<int> intersectionX, intersectionY, positionX, positionY, tempX, tempY;
    int lineWidth;
    int lineHeight;
    int lineLength;
    int playerRadius;
public:
    functions();
    void import();
    void printVector();
    void drawMaze();
};

#endif /* functions_hpp */
