//
//  functions.cpp
//  Maze
//
//  Created by Mary Tamry on 27.04.22.
//
#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <math.h>
#include <queue>
using namespace std;
using namespace sf;
#define North 2
#define West 1
#define South 8
#define East 4

functions::functions(){
    linenum = 0;
    intnum = 0;
    coordinates = new int*[linenum];
    for(int i = 0; i < 0; i++){
        coordinates[i] = new int[intnum];
    }
}

void functions::import(){
    string line;
    ifstream file("/Users/marytamry/Downloads/maze3.txt");
    if(file.is_open()){
        cout << "file is open" << endl;
        while (file.eof() != true){
            if(linenum == 0){
                file >> intnum;
                file >> linenum;
                coordinates = new int*[linenum+2];
                for(int i = 0; i < 2; i++){
                    coordinates[i] = new int[3];
                }
                for(int i = 2; i < linenum+2; i++){
                    coordinates[i] = new int[intnum];
                }
            }
            int tempInt = 0;
            for(int i = 0; i < 2; i++){
                for(int k = 0; k < 3; k++){
                    file >> tempInt;
                    coordinates[i][k] = tempInt;
                }
            }
            for(int o = 2; o < linenum+2; o++){
                for(int j = 0; j < intnum; j++){
                    file >> tempInt;
                    coordinates[o][j] = tempInt;
                }
            }
        }
    }else{
        cout << "File is not open" << endl;
    }
}

void functions::drawMaze(){
    int windowX = 2000;
    int windowY = 4000;
    int ballspeed = 6;
    RenderWindow window(VideoMode(windowY, windowX), "SFML window");
    lineHeight = sqrt((windowX*windowY)/(linenum*intnum))/1.5;
    lineLength = lineHeight;
    lineWidth = lineHeight*0.05;
    playerRadius = (lineHeight/5);
    CircleShape playerCircle(playerRadius, 100);
    playerCircle.setFillColor(Color::Red);
    playerCircle.setPosition((((coordinates[0][0])*lineLength)+((lineLength/2)-playerRadius)), ((coordinates[0][1])*lineHeight)+(lineHeight/2)-playerRadius);
    positionX.push(((coordinates[0][0])*lineLength)+((lineLength/2)-playerRadius));
    positionY.push(((coordinates[0][1])*lineHeight)+(lineHeight/2)-playerRadius);
    
    //Begining of moving algorithm
    stack<int> reversedY, reversedX;
    int gaps = 0, playerDirection = South, X = 0, Y = 2;
    currentPosition = &coordinates[Y][X];
    while(Y != (coordinates[1][1]+2) || X != coordinates[1][0]){
        //Finds open spaces with no walls
        if((15-*currentPosition) & North){
            gaps++;
        }
        if((15-*currentPosition) & West){
            gaps++;
        }
        if((15-*currentPosition) & East){
            gaps++;
        }
        if((15-*currentPosition) & South){
            gaps++;
        }
        if(playerDirection == South){
            if((15-*currentPosition) & West){
                X--;
                currentPosition = &coordinates[Y][X];
                positionY.push(positionY.top());
                positionX.push(positionX.top()-lineLength);
                playerDirection = West;
            }else{
                if((15-*currentPosition) & South){
                    Y++;
                    currentPosition = &coordinates[Y][X];
                    positionY.push(positionY.top()+(lineHeight));
                    positionX.push(positionX.top());
                    playerDirection = South;
                }else{
                    if((15-*currentPosition) & East){
                        X++;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()+lineLength);
                        playerDirection = East;
                    }else{
                        if((15-*currentPosition) & North){
                            Y--;
                            positionY.push(positionY.top()-lineHeight);
                            positionX.push(positionX.top());
                            playerDirection = North;
                            currentPosition = &coordinates[Y][X];
                        }
                    }
                }
            }
        }else{
        if(playerDirection == North){
            if((15-*currentPosition) & East){
                X++;
                currentPosition = &coordinates[Y][X];
                positionY.push(positionY.top());
                positionX.push(positionX.top()+lineLength);
                playerDirection = East;
            }else{
                if((15-*currentPosition) & North){
                        Y--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top()-lineHeight);
                        positionX.push(positionX.top());
                        playerDirection = North;
                }else{
                    if((15-*currentPosition) & West){
                        X--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                        playerDirection = West;
                    }else{
                        if((15-*currentPosition) & South){
                            Y++;
                            positionY.push(positionY.top()+(lineHeight));
                            positionX.push(positionX.top());
                            playerDirection = South;
                            currentPosition = &coordinates[Y][X];
                        }
                    }
                }
            }
        }else{
            if(playerDirection == West){
                if((15-*currentPosition) & North){
                        Y--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top()-lineHeight);
                        positionX.push(positionX.top());
                        playerDirection = North;
                }else{
                    if((15-*currentPosition) & West){
                        X--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                        playerDirection = West;
                    }else{
                        if((15-*currentPosition) & South){
                            Y++;
                            currentPosition = &coordinates[Y][X];
                            positionY.push(positionY.top()+(lineHeight));
                            positionX.push(positionX.top());
                            playerDirection = South;
                        }else{
                            if((15-*currentPosition) & East){
                                X++;
                                positionY.push(positionY.top());
                                positionX.push(positionX.top()+lineLength);
                                playerDirection = East;
                                currentPosition = &coordinates[Y][X];
                            }
                        }
                    }
                }
            }else{
                if(playerDirection == East){
                    if((15-*currentPosition) & South){
                        Y++;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top()+(lineHeight));
                        positionX.push(positionX.top());
                        playerDirection = South;
                    }else{
                        if((15-*currentPosition) & East){
                            X++;
                            currentPosition = &coordinates[Y][X];
                            positionY.push(positionY.top());
                            positionX.push(positionX.top()+lineLength);
                            playerDirection = East;
                        }else{
                            if((15-*currentPosition) & North){
                                    Y--;
                                    currentPosition = &coordinates[Y][X];
                                    positionY.push(positionY.top()-lineHeight);
                                    positionX.push(positionX.top());
                                    playerDirection = North;
                            }else{
                                if((15-*currentPosition) & West){
                                    X--;
                                    currentPosition = &coordinates[Y][X];
                                    positionY.push(positionY.top());
                                    positionX.push(positionX.top()-lineLength);
                                    playerDirection = West;
                                    currentPosition = &coordinates[Y][X];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        gaps = 0;
    }//Moving stops here
    
    while(!positionY.empty()){
        reversedY.push(positionY.top());
        reversedX.push(positionX.top());
        positionX.pop();
        positionY.pop();
    }
while (window.isOpen() && reversedX.empty() != true)
    {
        window.clear(Color(0, 0, 0, 255));
        window.draw(playerCircle);
        //Draw lines in the maze
        for(int i = 2; i < linenum+2; i++){
            for(int j = 0; j < intnum; j++){
                int tempCoord = coordinates[i][j];
                    if(tempCoord & North){
                        RectangleShape rectangle(Vector2f(lineLength, lineWidth));
                        rectangle.setPosition((j*lineLength), ((i-2)*lineHeight));
                        window.draw(rectangle);
                    }
                    if(tempCoord & East){
                        RectangleShape rectangle(Vector2f(lineWidth, lineHeight));
                        rectangle.setPosition((j*lineLength)+lineLength-lineWidth, ((i-2)*lineHeight));
                        window.draw(rectangle);
                    }
                    if(tempCoord & South){
                        RectangleShape rectangle(Vector2f(lineLength, lineWidth));
                        rectangle.setPosition(j*lineLength, ((i-2)*lineHeight)+lineHeight);
                        window.draw(rectangle);
                    }
                    if(tempCoord & West){
                        RectangleShape rectangle(Vector2f(lineWidth, lineHeight));
                        rectangle.setPosition((j*lineLength), ((i-2)*lineHeight));
                        window.draw(rectangle);
                    }
                }
            }
        
            playerCircle.setPosition(reversedX.top(), reversedY.top());
            reversedY.pop();
            reversedX.pop();
            window.setFramerateLimit(ballspeed);
            window.display();
    
    Event event;
    while (window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
    }
    
}
    cout << "Maze Solved" << endl;
}

void functions::options(){

}

