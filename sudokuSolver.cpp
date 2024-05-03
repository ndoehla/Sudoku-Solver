#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "sudokuSolver.h";


using namespace std;


int main() {
    SudokuGrid mygrid;
    mygrid.populateGrid();
    mygrid.printSolvedGrid();
}


SudokuGrid::SudokuGrid() {
    for(int i = 0; i<9; i++) {
        vector <int> row(9);
        aGrid.push_back(row);
    }
}

SudokuGrid::SudokuGrid(vector <vector <int> > pGrid) {
    for(int i = 0; i < 9; i++) {
        vector <int> aRow(pGrid[i].begin(), pGrid[i].end());
        aGrid.push_back(aRow);
    }
}

void SudokuGrid::printSolvedGrid() {
    cout << "\n   ----- My Solved Grid -----";
    cout << "\n\n" << endl;
    for(int i = 0; i < 9; i++) {
        if(i==0 || i== 3 || i == 6) {
            cout << "-------------------------------" << endl;
        }
        for(int j = 0; j < 9; j++) {
            if(j==0 || j==3 || j==6) {
                cout << "| " << aGrid[i][j] << " ";

            } else if (j==8) {
                cout << " " << aGrid[i][j] << " |" << endl;   
            } else {
                cout << " " << aGrid[i][j] << " ";
            }
        }
    }

    cout << "-------------------------------" << endl;

}

void SudokuGrid::populateGrid() {
    aGrid.clear();
    cout << "\nTo populate the sudoku grid, we will fill rows one at a time.\n" << endl;
    for(int i = 0; i < 9; i++) {
        cout << "Please enter 9 numbers with no spaces in between them and then hit enter. Free cells are represented as the number \'0\'" << endl;
        string s;
        
        cin >> s;
        if(s.size()!=9) {
            throw invalid_argument("You did not enter the correct input.");
        }
        vector <int> row;
        int pos = 0;
        for(int j=0; j<s.size(); j++) {
            if(s[j] < 48 || s[j]>57) {
                throw invalid_argument("Sudoku only takes digits 0-9.");
            }
            int val = s[j] - '0';
            row.push_back(val);
        }
        aGrid.push_back(row);
    }
}
