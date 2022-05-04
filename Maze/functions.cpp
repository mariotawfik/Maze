//
//  functions.cpp
//  Maze
//
//  Created by Mary Tamry on 27.04.22.
//

#include "functions.hpp"
#include <iostream>
#include <fstream>
using namespace std;

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
    ifstream file("/Users/marytamry/Desktop/Work/Maze/Maze/maze1.txt");
    if(file.is_open()){
        cout << "file is open" << endl;
        while (file.eof() != true){
            if(linenum == 0){
                file >> intnum;
                file >> linenum;
                coordinates = new int*[linenum+3];
                for(int i = 0; i < 3; i++){
                    if (i == 0) {
                        coordinates[i] = new int[2];
                    }
                    else {
                        coordinates[i] = new int[3];
                    }
                }
                for(int i = 3; i < linenum+3; i++){
                    coordinates[i] = new int[intnum];
                }
            }
            int tempInt = 0;
            for(int i = 0; i < linenum+3; i++){
                for(int k = 0; k < intnum; k++){
                    file >> tempInt;
                    coordinates[i][k] = tempInt;
                }
            }
            
        }
    }else{
        cout << "File is not open" << endl;
    }
}

void functions::printVector(){
    for(int i = 0; i < linenum; i++){
        for(int j = 0; j < intnum; j++){
            cout << coordinates[i][j] << endl;
        }
    }
} 
                            