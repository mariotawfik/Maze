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

void functions::drawMaze(){
    RenderWindow window(VideoMode(4000, 2000), "SFML window");
    int lineWidth = 5.f;
    int lineHeight = 100.f;
    int lineLength = 100.f;
    int playerRadius = (lineLength/lineHeight)*20;
    bool positionsReversed = false;
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
        //Moving Alg starts here
        int w = 0, l = 2;
        int gaps = 0;
        int *prevX, *prevY;
        prevX = new int;
        prevY = new int;
        currentPosition = coordinates[2][0];
        stack<int> finalStepsY, finalStepsX;
        while((positionY.top() != (coordinates[1][0])*lineLength) && (positionX.top() != (coordinates[1][1]*lineHeight))){
            if((15-currentPosition) & North){
                gaps++;
            }
            if((15-currentPosition) & West){
                gaps++;
            }
            if((15-currentPosition) & East){
                gaps++;
            }
            if((15-currentPosition) & South){
                gaps++;
            }
            if(gaps >= 2){
                intersectionY.push(positionY.top());
                intersectionX.push(positionX.top());
            }
            if((15-currentPosition) & West){
                currentPosition = coordinates[l][w+1];
                prevY = &positionY.top();
                prevX = &positionX.top();
                positionY.push(positionY.top());
                positionX.push(positionX.top()+lineLength);
            }else{
                if((15-currentPosition) & South){
                    prevY = &positionY.top();
                    prevX = &positionX.top();
                    currentPosition = coordinates[l+1][w];
                    positionY.push(positionY.top()+lineHeight);
                    positionX.push(positionX.top());
                }else{
                    if((15-currentPosition) & East){
                        prevY = &positionY.top();
                        prevX = &positionX.top();
                        currentPosition = coordinates[l][w-1];
                        positionY.push(positionY.top());
                        positionX.push(positionX.top()-lineLength);
                    }else{
                        if((15-currentPosition) & North){
                            prevY = &positionY.top();
                            prevX = &positionX.top();
                            currentPosition = coordinates[l-1][w];
                            positionY.push(positionY.top()-lineHeight);
                            positionX.push(positionX.top());
                        }
                    }
                }
            }
            gaps = 0;
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
        }
        
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
            finalStepsY.pop();
            finalStepsX.pop();
        }
        window.draw(playerCircle);
        //alg end here
        Event event;
        while (window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        window.setFramerateLimit(1);
        window.display();
        }
}
