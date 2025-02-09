#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Sodoku{

public:
    bool PopulateGrid(string inputArray[9]);
    bool CheckGrid(int gridRow, int gridColumn);
    bool CheckSolutions();
    void BlockSolutions(int row, int column);
    void printPuzzle();
    void printStatus();
    void SodokuSolver();
private:
    int sodokuGrid[9][9];
    bool solvedStatus = false;
};                                          

void Sodoku::printStatus(){
    if(solvedStatus == 1){
        cout << "This is a solved sodoku" << endl;
    }
    else{
        cout << "This is NOT a solved sodoku" << endl;
    }
}

bool Sodoku::PopulateGrid(string inputArray[9]){
    int i;
    int j;
    string currString;
    int currInt;

    for(i = 0; i <= 8; ++i){
        currString = inputArray[i];
        for(j = 0; j <= 8; ++j){
            if (isdigit(currString.at(j)) != 0){
                currInt = stoi(currString);
                currInt = (currInt / pow(10,8-j));
                currInt = currInt % 10;                
    
                sodokuGrid[i][j] = currInt;
            }
            else{
                cout << "Error in file input. Item at index \"" << i << "," << j << " \" which is: \"" << currString.at(j) << "\". Not a integer digit." << endl;
                return false;
            }
        }
    }
    return true;
}

void Sodoku::printPuzzle(){
    int i;
    int j;

    for(i = 0; i <=8; ++i){
        for(j = 0; j <= 8; ++j){
            cout << "| " << sodokuGrid[i][j] << " |";
        }
        cout << endl << "---------------------------------------------" << endl;
    }
}

bool Sodoku::CheckGrid(int row, int column){
    int i;
    int j;
    int numCheck = 1;
    bool foundVal = false;

    int rowStart = (row * 3);
    int columnStart = (column * 3);

    //cout << "Grid start: " << endl;
    do{
        for(i = rowStart; i < rowStart + 3; ++i){
            for(j = columnStart; j < columnStart + 3; ++j){
                //cout << sodokuGrid[i][j] << " |";
                if ((sodokuGrid[i][j] == numCheck) && foundVal == false){
                    foundVal = true;
                }
                else if((sodokuGrid[i][j] == numCheck) && foundVal == true){
                cout << "Two integers of the same value found in grid with start index: " << row << " | " << column << endl;
                return false;
                }
            }
            //cout << endl;
        }

        foundVal = false;
        ++ numCheck;
    }while (numCheck <= 9);

    

    return true;
}

bool Sodoku::CheckSolutions(){
    int i = 0;
    int j = 0;
    int numCheck = 1;
    bool foundVal = false;

    do{
    
        if ((sodokuGrid[i][j] == numCheck) && foundVal == false){
            foundVal = true;
            ++j;
        }
        else if((sodokuGrid[i][j] == numCheck) && foundVal == true){
            cout << "Two integers of the same value found in row: " << i +1 << endl;
            return false;
        }
        else if (sodokuGrid[i][j] != numCheck){
            ++j;
        }

        if(j > 8 && foundVal == true){
            foundVal = false;
            j = 0;

            if(numCheck == 9){
                numCheck = 1;
                ++i;
            }
            else{
                ++numCheck;
            }
        }
        else if(j > 8 && foundVal != true){
            cout << "Failed to find a required integer in row: " << i + 1 << endl;
            return false;
        }
    } while (true && i <= 8);

    cout << "Sodoku has been verified for all possible rows. Verifying for columns." << endl;

    i = 0;
    j = 0;
    numCheck = 1;
    foundVal = false;

    do{
    
        if ((sodokuGrid[j][i] == numCheck) && foundVal == false){
            foundVal = true;
            ++j;
        }
        else if((sodokuGrid[j][i] == numCheck) && foundVal == true){
            cout << "Two integers of the same value found in column: " << i +1 << endl;
            return false;
        }
        else if (sodokuGrid[j][i] != numCheck){
            ++j;
        }

        if(j > 8 && foundVal == true){
            foundVal = false;
            j = 0;

            if(numCheck == 9){
                numCheck = 1;
                ++i;
            }
            else{
                ++numCheck;
            }
        }
        else if(j > 8 && foundVal != true){
            cout << "Failed to find a required integer in column: " << i + 1 << endl;
            return false;
        }
    } while (true && i <= 8);
    
    cout << "Sodoku has been verified for all possible columns. Verifying for 3x3 grids." << endl;


    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            if(!CheckGrid(i,j)){
                return false;
            }
        }
    }


    solvedStatus = true;
    return true;
}

void Sodoku::BlockSolutions(int row, int column){
    int i;
    int j;
    int k;
    unsigned long z;

    cout << "Checking block: " << row << " " << column << endl;

    vector<int> possibleNumbers = {1,2,3,4,5,6,7,8,9};

    for(k = 1; k <= 9; ++k){
        for(i = 0; i < 9; ++i){
            if(sodokuGrid[i][column] == k){
                auto deleteNum = find(possibleNumbers.begin(), possibleNumbers.end(), k);

                if(deleteNum != possibleNumbers.end()){
                    possibleNumbers.erase(deleteNum);
                }
            }
        }
        

        for(j = 0; j < 9; ++j){
            if(sodokuGrid[row][j] == k){
                auto deleteNum = find(possibleNumbers.begin(), possibleNumbers.end(), k);

                if(deleteNum != possibleNumbers.end()){
                    possibleNumbers.erase(deleteNum);
                }
            }
        }
    }

    cout << "Rows and columns sorted, remaining possibles: ";
    for(z = 0; z < possibleNumbers.size(); ++z){
        cout << possibleNumbers[z] << " ";
    }
    cout << endl;

    int rowStart = (row / 3);
    int columnStart = (column / 3);
    for(k = 1; k <=9; ++ k){
        for(i = rowStart * 3; i < (rowStart * 3) + 3; ++i){
            for(j = columnStart * 3; j < (columnStart * 3) + 3; ++j){
                if (sodokuGrid[i][j] == k){
                auto deleteNum = find(possibleNumbers.begin(), possibleNumbers.end(), k);

                if(deleteNum != possibleNumbers.end()){
                    possibleNumbers.erase(deleteNum);
                }
                }
            }
        }
    }

    cout << "Checking end vector: " << possibleNumbers.size() << endl;

    for(z = 0; z < possibleNumbers.size(); ++z){
        cout << possibleNumbers[z] << " ";
        if( z == possibleNumbers.size() -1 ){
            cout << endl;
        }
    }

    if(possibleNumbers.size() == 1){
        sodokuGrid[row][column] = possibleNumbers[0];
    }
}

void Sodoku::SodokuSolver(){
    int i = 0;
    int j = 0;
    bool solved = false;
    int iterations = 0;
    

    do{
        solved = true;
        for(i = 0; i < 9; ++i){
            for(j = 0; j < 9; ++j){
                if(sodokuGrid[i][j] != 0){
                    continue;
                }
                else{
                    solved = false;
                    BlockSolutions(i,j);
                }
            }
        }
        ++iterations;

        if(iterations >= 100){
            solved = false;
            cout << "Error: Timeout. Impossible sodoku." << endl;
            break;
        }

    }while(solved == false);

    if(iterations < 100){
        cout << "Solved in: " << iterations << " loops" << endl;
    }


}

int main(){
    ifstream textSolution;

    Sodoku currSodoku;
    string fileName;
    string textArray[9];
    unsigned int i;

    int menuSelection;

    do{
        cout << "Please input your desired command for the program." << endl;
        cout << "\t1: Input a completed Sodoku and verify solution." << endl;
        cout << "\t2: Input a partial Sodoku and automatically solve." << endl;
        cout << "\t3: Quit program." << endl;

        cin >> menuSelection;
        
        try{
            if(menuSelection != 1 && menuSelection != 2 && menuSelection != 3){
                throw runtime_error("Menu selection is not a number.");
            }
            else if(menuSelection == 1){
                do {
                
                cout << "Please input the name of the solution file you wish to open (input 0 to quit): " << endl;
                cin >> fileName;

                if(fileName == "0"){
                    cout << "Aborting program." << endl;
                    return false;
                }

                textSolution.open(fileName);

                if(textSolution.is_open()){
                    cout << "Opening solution for: " << fileName << endl;
                    break;
                }
                else if(!textSolution.is_open()){
                    cout << "Error in opening text filed named \"" << fileName << "\". Please input a valid file name." << endl;
                    continue;
                }

                } while (true);

                for(i = 0; i <= 8; ++i){
                    textSolution >> textArray[i];
                }

                if(currSodoku.PopulateGrid(textArray) == false){
                    continue;;
                }

                currSodoku.printPuzzle();

                if(currSodoku.CheckSolutions() == false){
                    currSodoku.printStatus();
                    continue;
                };

                currSodoku.printStatus();
                
                textSolution.close();
        
                cout << "Input 1 to repeat program and anything else to exit." << endl;
                cin >> menuSelection;
                if(menuSelection != 1){
                    return false;
                }
            }
            else if(menuSelection == 2){
                do {
                
                cout << "Please input the name of the partially completed sodoku file you wish to open (input 0 to quit): " << endl;
                cin >> fileName;

                if(fileName == "0"){
                    cout << "Aborting program." << endl;
                    return false;
                }

                textSolution.open(fileName);

                if(textSolution.is_open()){
                    cout << "Opening solution for: " << fileName << endl;
                    break;
                }
                else if(!textSolution.is_open()){
                    cout << "Error in opening text filed named \"" << fileName << "\". Please input a valid file name." << endl;
                    continue;
                }

                } while (true);

                for(i = 0; i <= 8; ++i){
                    textSolution >> textArray[i];
                }

                if(currSodoku.PopulateGrid(textArray) == false){
                    continue;;
                }

                currSodoku.printPuzzle();

                currSodoku.SodokuSolver();

                cout << "Processed sodoku: " << endl << endl;

                currSodoku.printPuzzle();

            }
            else if(menuSelection == 3){
                break;
            }
            else{
                cout << "Invalid input, please enter a number from the menu." << endl;
            }
        }
        catch (runtime_error& excpt){
            cout << "Invalid menu input: " << excpt.what() << endl;
            return 0;
        }
        
        if(textSolution.is_open()){
            textSolution.close();
        }
    }while (true);
    cout << "Program terminated." << endl;
}