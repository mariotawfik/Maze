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
    int *linenum;
    int *intnum;
    stack<int> positionX, positionY;
    stack<int> *reversedY, *reversedX;
    int *lineWidth;
    int *lineHeight;
    int playerRadius;
    int *ballSpeed;
    int X, Y;
    string *mazeName;
    sf::CircleShape *playerCircle;
    sf::RectangleShape *rectangle;
    sf::RenderWindow *window;
    int windowX, windowY, playerDirection, *gaps;
public:
    functions();
    ~functions();
    void import();
    void drawMaze();
    void options();
};

#endif /* functions_hpp */
