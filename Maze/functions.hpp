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
    int currentPosition;
    int linenum;
    int intnum;
    int North, West, South, East;
    stack<int> intersectionX, intersectionY, positionX, positionY, tempX, tempY;
    int lineWidth;
    int lineHeight;
    int lineLength;
    int playerRadius;
public:
    functions();
    void move();
    void import();
    void printVector();
    void drawMaze();
    void linePosition();
    void wallChecker(int, int);
};

#endif /* functions_hpp */
