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
    playerCircle = new CircleShape;
    rectangle = new RectangleShape;
    window = new RenderWindow;
    linenum = new int;
    intnum = new int;
    reversedX = new stack<int>;
    reversedY = new stack<int>;
    *linenum = 0;
    *intnum = 0;
    coordinates = new int*[*linenum];
    for(int i = 0; i < 0; i++){
        coordinates[i] = new int[*intnum];
    }
    (*playerCircle).setFillColor(Color::Red);
    ballSpeed = new int;
    *ballSpeed = 6;
    mazeName = new string;
    *mazeName = "maze2";
    X = 0;
    Y = 2;
    windowX = 2000;
    windowY = 4000;
    playerDirection = South;
    gaps = new int;
    *gaps = 0;
    lineHeight = new int;
    lineWidth = new int;
}

functions::~functions(){
    delete coordinates; delete currentPosition; delete linenum; delete intnum; delete lineWidth; delete lineHeight; delete ballSpeed;
    delete playerCircle; delete rectangle; delete window; delete gaps; delete mazeName; delete reversedX; delete reversedY;
}
void functions::import(){
    string line;
    ifstream file("/Users/marytamry/Downloads/" +*mazeName+".txt");
    if(file.is_open()){
        cout << "file is open" << endl;
        while (file.eof() != true){
            if(*linenum == 0){
                file >> *intnum;
                file >> *linenum;
                coordinates = new int*[*linenum+2];
                for(int i = 0; i < 2; i++){
                    coordinates[i] = new int[3];
                }
                for(int i = 2; i < *linenum+2; i++){
                    coordinates[i] = new int[*intnum];
                }
            }
            int tempInt = 0;
            for(int i = 0; i < 2; i++){
                for(int k = 0; k < 3; k++){
                    file >> tempInt;
                    coordinates[i][k] = tempInt;
                }
            }
            for(int o = 2; o < *linenum+2; o++){
                for(int j = 0; j < *intnum; j++){
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
    *lineHeight = sqrt((windowX*windowY)/(*linenum**intnum))/2;
    *lineWidth = (*lineHeight)*0.05;
    playerRadius = (*lineHeight/5);
    (*playerCircle).setRadius(playerRadius);
    (*playerCircle).setPointCount(100);
    (*playerCircle).setPosition((((coordinates[0][0])**lineHeight)+((*lineHeight/2)-playerRadius)), ((coordinates[0][1])**lineHeight)+(*lineHeight/2)-playerRadius);
    positionX.push(((coordinates[0][0])**lineHeight)+((*lineHeight/2)-playerRadius));
    positionY.push(((coordinates[0][1])**lineHeight)+(*lineHeight/2)-playerRadius);
    RenderWindow window(VideoMode(windowY, windowX), "SFML window", Style::Default);
    //Begining of moving algorithm
    currentPosition = &coordinates[Y][X];
    while(Y != (coordinates[1][1]+2) || X != coordinates[1][0]){
        //Finds open spaces with no walls
        if((15-*currentPosition) & North){
            (*gaps)++;
        }
        if((15-*currentPosition) & West){
            (*gaps)++;
        }
        if((15-*currentPosition) & East){
            (*gaps)++;
        }
        if((15-*currentPosition) & South){
            (*gaps)++;
        }
        if(playerDirection == South){
            if((15-*currentPosition) & West){
                X--;
                currentPosition = &coordinates[Y][X];
                positionY.push(positionY.top());
                positionX.push(positionX.top()-*lineHeight);
                playerDirection = West;
            }else{
                if((15-*currentPosition) & South){
                    Y++;
                    currentPosition = &coordinates[Y][X];
                    positionY.push(positionY.top()+(*lineHeight));
                    positionX.push(positionX.top());
                    playerDirection = South;
                }else{
                    if((15-*currentPosition) & East){
                        X++;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()+*lineHeight);
                        playerDirection = East;
                    }else{
                        if((15-*currentPosition) & North){
                            Y--;
                            positionY.push(positionY.top()-*lineHeight);
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
                positionX.push(positionX.top()+*lineHeight);
                playerDirection = East;
            }else{
                if((15-*currentPosition) & North){
                        Y--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top()-*lineHeight);
                        positionX.push(positionX.top());
                        playerDirection = North;
                }else{
                    if((15-*currentPosition) & West){
                        X--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-*lineHeight);
                        playerDirection = West;
                    }else{
                        if((15-*currentPosition) & South){
                            Y++;
                            positionY.push(positionY.top()+(*lineHeight));
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
                        positionY.push(positionY.top()-*lineHeight);
                        positionX.push(positionX.top());
                        playerDirection = North;
                }else{
                    if((15-*currentPosition) & West){
                        X--;
                        currentPosition = &coordinates[Y][X];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-*lineHeight);
                        playerDirection = West;
                    }else{
                        if((15-*currentPosition) & South){
                            Y++;
                            currentPosition = &coordinates[Y][X];
                            positionY.push(positionY.top()+(*lineHeight));
                            positionX.push(positionX.top());
                            playerDirection = South;
                        }else{
                            if((15-*currentPosition) & East){
                                X++;
                                positionY.push(positionY.top());
                                positionX.push(positionX.top()+*lineHeight);
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
                        positionY.push(positionY.top()+(*lineHeight));
                        positionX.push(positionX.top());
                        playerDirection = South;
                    }else{
                        if((15-*currentPosition) & East){
                            X++;
                            currentPosition = &coordinates[Y][X];
                            positionY.push(positionY.top());
                            positionX.push(positionX.top()+*lineHeight);
                            playerDirection = East;
                        }else{
                            if((15-*currentPosition) & North){
                                    Y--;
                                    currentPosition = &coordinates[Y][X];
                                    positionY.push(positionY.top()-*lineHeight);
                                    positionX.push(positionX.top());
                                    playerDirection = North;
                            }else{
                                if((15-*currentPosition) & West){
                                    X--;
                                    currentPosition = &coordinates[Y][X];
                                    positionY.push(positionY.top());
                                    positionX.push(positionX.top()-*lineHeight);
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
        *gaps = 0;
}//Moving stops here
    while(!positionY.empty()){
        (*reversedY).push(positionY.top());
        (*reversedX).push(positionX.top());
        positionX.pop();
        positionY.pop();
    }
    
while (window.isOpen() && (*reversedX).empty() != true)
    {
        window.clear(Color::Black);
        window.draw((*playerCircle));
        //Draw lines in the maze
        for(int i = 2; i < *linenum+2; i++){
            for(int j = 0; j < *intnum; j++){
                int tempCoord = coordinates[i][j];
                    if(tempCoord & North){
                        (*rectangle).setSize((Vector2f(*lineHeight, *lineWidth)));
                        (*rectangle).setPosition((j**lineHeight), ((i-2)**lineHeight));
                        window.draw((*rectangle));
                    }
                    if(tempCoord & East){
                        (*rectangle).setSize((Vector2f(*lineWidth, *lineHeight)));
                        (*rectangle).setPosition((j**lineHeight)+*lineHeight-*lineWidth, ((i-2)**lineHeight));
                        window.draw((*rectangle));
                    }
                    if(tempCoord & South){
                        (*rectangle).setSize((Vector2f(*lineHeight, *lineWidth)));
                        (*rectangle).setPosition(j**lineHeight, ((i-2)**lineHeight)+*lineHeight);
                        window.draw((*rectangle));
                    }
                    if(tempCoord & West){
                        (*rectangle).setSize((Vector2f(*lineWidth, *lineHeight)));
                        (*rectangle).setPosition((j**lineHeight), ((i-2)**lineHeight));
                        window.draw((*rectangle));
                    }
                }
            }
        
            (*playerCircle).setPosition((*reversedX).top(), (*reversedY).top());
            (*reversedY).pop();
            (*reversedX).pop();
            window.setFramerateLimit(*ballSpeed);
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
    int answer = 0;
    while(answer != 5){
    cout << "Maze Options: " << endl << "1. Ball Speed" << endl << "2. Ball Color" << endl << "3. Wall Color" << endl << "4. Change Maze" << endl<< "5. Exit" << endl;
    cin >> answer;
    int *colorAns;
    colorAns = new int;
        switch (answer) {
            case 1:
                cout << "Please enter a speed from 1-100 for the ball" << endl;
                cin >> *ballSpeed;
                while((*ballSpeed < 1) || (*ballSpeed > 100)){
                    cout << "Please enter a speed from 1-100 for the ball, speed entered is invalid" << endl;
                    cin >> *ballSpeed;
                }
                break;
            case 2:
                cout << "Please choose from the following colors " << endl;
                cout << "1. Red" << endl << "2. Blue" << endl << "3. Green" << endl << "4. White" << endl;
                cin >> *colorAns;
                switch (*colorAns) {
                    case 1:
                        (*playerCircle).setFillColor(Color::Red);
                        break;
                    case 2:
                        (*playerCircle).setFillColor(Color::Blue);
                        break;
                    case 3:
                        (*playerCircle).setFillColor(Color::Green);
                        break;
                    case 4:
                        (*playerCircle).setFillColor(Color::White);
                        break;
                    default:
                        break;
                }
                delete colorAns;
                break;
            case 3:
                cout << "Please choose from the following colors " << endl;
                cout << "1. Red" << endl << "2. Blue" << endl << "3. Green" << endl << "4. White" << endl;
                cin >> *colorAns;
                switch (*colorAns) {
                    case 1:
                        (*rectangle).setFillColor(Color::Red);
                        break;
                    case 2:
                        (*rectangle).setFillColor(Color::Blue);
                        break;
                    case 3:
                        (*rectangle).setFillColor(Color::Green);
                        break;
                    case 4:
                        (*rectangle).setFillColor(Color::White);
                        break;
                    default:
                        break;
                }
                delete colorAns;
                break;
            case 4:
                cout << "Please enter maze file name" << endl;
                cin >> *mazeName;
                break;
            default:
                break;
        }
    }
}

