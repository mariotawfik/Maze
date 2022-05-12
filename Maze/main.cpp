//
//  main.cpp
//  Maze
//
//  Created by Mary Tamry on 07.04.22.
//
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "functions.hpp"
using namespace sf;

int main()
{
    functions a;
    a.import();
    a.printVector();
    a.drawMaze();
        
    
    return EXIT_SUCCESS;
}
