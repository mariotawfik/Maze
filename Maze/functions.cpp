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
    int lineWidth = 5.f;
    int lineHeight = 100.f;
    int lineLength = 100.f;
    int playerRadius = (lineLength/lineHeight)*20;
    currentOrientation = 0;
    stack <int> positionY, tempY;
    stack <int> positionX, tempX;
}

void functions::import(){
    string line;
    ifstream file("/Users/marytamry/Downloads/maze2.txt");
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

/*
void functions::printVector(){
    for(int i = 0; i < 2; i++){
        if(i == 0){
            cout << "Start Coordinates: " << endl;
        }else{
            cout << "End Coordinates: " << endl;
        }
        for(int j = 0; j < 3; j++){
            cout << coordinates[i][j] << endl;
        }
        cout << endl << endl;
    }
    for(int i = 2; i < linenum+2; i++){
        for(int j = 0; j < intnum; j++){
            cout << coordinates[i][j] << endl;
        }
        cout << endl << endl;
    }
}
*/

void functions::drawMaze(){
    
    int windowX = 2000, windowY = 4000;
    RenderWindow window(VideoMode(windowY, windowX), "SFML window");
    window.setFramerateLimit(1);
    int lineHeight = (((linenum*intnum)%(windowX*windowY)));
    int lineLength = lineHeight;
    int lineWidth = lineHeight*0.05;
    int playerRadius = (lineLength/lineHeight)*20;
    CircleShape playerCircle(playerRadius, 100);
    playerCircle.setFillColor(Color::Red);
    playerCircle.setPosition(((coordinates[0][0])*lineLength)+((lineLength/2)-playerRadius), (coordinates[0][1])*lineLength);
    positionX.push(((coordinates[0][0])*lineLength)+((lineLength/2)-playerRadius));
    intersectionX.push(positionX.top());
    positionY.push(((coordinates[0][1])*lineLength));
    intersectionY.push(positionY.top());
    
    while (window.isOpen())
    {
        window.clear(Color(0, 0, 0, 255));
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
        //Begining of moving algorithm
        int gaps = 0, playerDirection = South, X = 0, Y = 2;
        while((positionY.top() != (coordinates[1][0])*lineLength) && (positionX.top() != (coordinates[1][1]*lineHeight))){
            //Finds open spaces with no walls
            currentPosition = &coordinates[Y][X];
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
            cout << "Y: "<< Y << " X: " << X << " position: " << *currentPosition << "   " << gaps << endl;
            //Creates intersection point if 3 or 4 gaps are found;
            if(gaps >= 3){
                intersectionY.push(positionY.top());
                intersectionX.push(positionX.top());
            }
            if(playerDirection == South){
                if((15-*currentPosition) & East){
                    X++;
                    positionY.push(positionY.top());
                    positionX.push(positionX.top()+lineLength);
                    playerDirection = East;
                }else{
                    if((15-*currentPosition) & South){
                        Y++;
                        positionY.push(positionY.top()+(lineHeight));
                        positionX.push(positionX.top());
                        playerDirection = South;
                    }else{
                        if((15-*currentPosition) & West){
                            X--;
                            positionY.push(positionY.top());
                            positionX.push(positionX.top()-lineLength);
                            playerDirection = West;
                        }else{
                            if((15-*currentPosition) & North){
                                    Y--;
                                    positionY.push(positionY.top()-lineHeight);
                                    positionX.push(positionX.top());
                                    playerDirection = North;
                                    coordinates[Y][X] -= South;
                            }
                        }
                    }
                }
            }
            if(playerDirection == North){
                if((15-*currentPosition) & West){
                    X--;
                    positionY.push(positionY.top());
                    positionX.push(positionX.top()-lineLength);
                    playerDirection = West;
                }else{
                    if((15-*currentPosition) & North){
                            Y--;
                            positionY.push(positionY.top()-lineHeight);
                            positionX.push(positionX.top());
                            playerDirection = North;
                    }else{
                        if((15-*currentPosition) & East){
                            X++;
                            positionY.push(positionY.top());
                            positionX.push(positionX.top()+lineLength);
                            playerDirection = East;
                        }else{
                            if((15-*currentPosition) & South){
                                Y++;
                                positionY.push(positionY.top()+(lineHeight));
                                positionX.push(positionX.top());
                                playerDirection = South;
                                coordinates[Y][X] -= North;
                            }
                        }
                    }
                }
            }
            if(playerDirection == West){
                if((15-*currentPosition) & North){
                        Y--;
                        positionY.push(positionY.top()-lineHeight);
                        positionX.push(positionX.top());
                        playerDirection = North;
                }else{
                    if((15-*currentPosition) & West){
                        X--;
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                        playerDirection = West;
                    }else{
                        if((15-*currentPosition) & South){
                            Y++;
                            positionY.push(positionY.top()+(lineHeight));
                            positionX.push(positionX.top());
                            playerDirection = South;
                        }else{
                            if((15-*currentPosition) & East){
                                X++;
                                positionY.push(positionY.top());
                                positionX.push(positionX.top()+lineLength);
                                playerDirection = East;
                                coordinates[Y][X] -= West;
                            }
                        }
                    }
                }
            }
            if(playerDirection == East){
                if((15-*currentPosition) & South){
                    Y++;
                    positionY.push(positionY.top()+(lineHeight));
                    positionX.push(positionX.top());
                    playerDirection = South;
                }else{
                    if((15-*currentPosition) & East){
                        X++;
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()+lineLength);
                        playerDirection = East;
                    }else{
                        if((15-*currentPosition) & North){
                                Y--;
                                positionY.push(positionY.top()-lineHeight);
                                positionX.push(positionX.top());
                                playerDirection = North;
                        }else{
                            if((15-*currentPosition) & West){
                                X--;
                                positionY.push(positionY.top());
                                positionX.push(positionX.top()-lineLength);
                                playerDirection = West;
                                coordinates[Y][X] -= East;
                            }
                        }
                    }
                }
            }
            gaps = 0;
        }//Moving stops here
        
        //Moving Alg starts here
        /*
        int w = 0, l = 2;
        int gaps = 0;
        currentPosition = &coordinates[2][0];
        stack<int> finalStepsY, finalStepsX;
        int *prevPosition;
        prevPosition = new int;
        while((positionY.top() != (coordinates[1][0])*lineLength) && (positionX.top() != (coordinates[1][1]*lineHeight))){
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
            if(gaps >= 3){
                intersectionY.push(positionY.top());
                intersectionX.push(positionX.top());
            }
            
            if(((15-*currentPosition) & East)){
                if(*prevPosition != 14){
                prevPosition = currentPosition;
                cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                w = w+1;
                currentPosition = &coordinates[l][w];
                positionY.push(positionY.top());
                positionX.push(positionX.top()+lineLength);
                }else{
                    while(positionX.top() != intersectionX.top()){
                        prevPosition = currentPosition;
                        w = w-1;
                        currentPosition = &coordinates[l][w];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                        cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                    }
                    currentPosition -= East;
                }
            }else{
                if(((15-*currentPosition) & South)){
                    if(*prevPosition != 13){
                    prevPosition = currentPosition;
                    cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                    l = l+1;
                    currentPosition = &coordinates[l][w];
                    positionY.push(positionY.top()+lineHeight);
                    positionX.push(positionX.top());
                    }else{
                        while(positionY.top() != intersectionY.top()){
                            prevPosition = currentPosition;
                            l = l-1;
                            currentPosition = &coordinates[l][w];
                            positionY.push(positionY.top()-lineHeight);
                            positionX.push(positionX.top());
                            cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                        }
                        currentPosition -= South;
                    }
                }else{
                    if(((15-*currentPosition) & West)){
                        if(*prevPosition != 11){
                        prevPosition = currentPosition;
                        cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                        w = w-1;
                        currentPosition = &coordinates[l][w];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                        }else{
                            while(positionX.top() != intersectionX.top()){
                                prevPosition = currentPosition;
                                w = w+1;
                                currentPosition = &coordinates[l][w];
                                positionY.push(positionY.top());
                                positionX.push(positionX.top()+lineLength);
                                cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                            }
                            currentPosition -= West;
                        }
                    }else{
                        if(((15-*currentPosition) & North)){
                            if(*prevPosition != 7){
                            prevPosition = currentPosition;
                            cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                            l = l-1;
                            currentPosition = &coordinates[l][w];
                            positionY.push(positionY.top()-lineHeight);
                            positionX.push(positionX.top());
                            }else{
                                while(positionY.top() != intersectionY.top()){
                                    prevPosition = currentPosition;
                                    l = l+1;
                                    currentPosition = &coordinates[l][w];
                                    positionY.push(positionY.top()+lineHeight);
                                    positionX.push(positionX.top());
                                    cout << "Y: "<< l << " X: " << w << " position: " << *currentPosition << "   " << gaps << endl;
                                }
                                currentPosition -= North;
                            }
                        }
                    }
                }
            }
            gaps = 0;
            
            /*
            if(*currentPosition == 14){
                while((positionY.top() != intersectionY.top()) && (positionX.top() != intersectionX.top())){
                    currentOrientation = West;
                    w = w-1;
                    currentPosition = &coordinates[l][w]-East;
                    positionY.push(positionY.top());
                    positionX.push(positionX.top()-lineLength);
                }
            }else{
                if(*currentPosition == 13){
                    while((positionY.top() != intersectionY.top()) && (positionX.top() != intersectionX.top())){
                        currentOrientation = North;
                        l = l-1;
                        currentPosition = &coordinates[l][w];
                        positionY.push(positionY.top()-lineHeight);
                        positionX.push(positionX.top());
                    }
                }else{
                    if(*currentPosition == 11){
                        while((positionY.top() != intersectionY.top()) && (positionX.top() != intersectionX.top())){
                            currentOrientation = East;
                            w = w+1;
                            currentPosition = &coordinates[l][w];
                            positionY.push(positionY.top());
                            positionX.push(positionX.top()+lineLength);
                        }
                    }else{
                        if(*currentPosition == 7){
                            while((positionY.top() != intersectionY.top()) && (positionX.top() != intersectionX.top())){
                                currentOrientation = South;
                                l = l+1;
                                currentPosition = &coordinates[l][w];
                                positionY.push(positionY.top()+lineHeight);
                                positionX.push(positionX.top());
                            }
                        }
                    }
                }
            }
*/
        /*
            if((positionY.top() == *prevY) && (positionX.top() == *prevX)){
                stack<int> tempY, tempX, tempY2, tempX2;
                while((intersectionY != positionY) && (intersectionX != positionX)){
                    tempY.push(positionY.top());
                    positionY.pop();
                    tempX.push(positionX.top());
                    positionX.pop();
                }
                for(int i = 0; i < tempX.size(); i++){
                    tempX2.push(tempX.top());
                    tempY2.push(tempY.top());
                }
                while(tempX2.empty() == false){
                    positionX.push(tempX2.top());
                    positionY.push(tempY2.top());
                    tempY2.pop();
                    tempX2.pop();
                }
                while(tempX.empty() == false){
                    positionX.push(tempX.top());
                    positionY.push(tempY.top());
                    tempY.pop();
                    tempX.pop();
                }
            }
    */
    /*
        tempX = positionX;
        tempY = positionY;
        
        while(tempX.empty() == false){
            finalStepsX.push(tempX.top());
            finalStepsY.push(tempY.top());
            tempY.pop();
            tempX.pop();
        }
        while(finalStepsX.empty() == false){
            playerCircle.setPosition(finalStepsX.top(), finalStepsY.top());
            cout << finalStepsX.top() << " , " << finalStepsY.top() << endl;
            finalStepsY.pop();
            finalStepsX.pop();
        }
        
        window.draw(playerCircle);
        */  //alg end here
        window.draw(playerCircle);
        Event event;
        while (window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        window.display();
}
}

