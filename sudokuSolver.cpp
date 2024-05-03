#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>


using namespace std;



class SudokuGrid {
    public:
        SudokuGrid();
        SudokuGrid(vector <vector <int> > pGrid);
        void solve();
        void populateGrid();
        void printGrid();
        bool isValid();
    
    private:
        vector <vector <int> > aGrid;
        bool isValidCol(int num);
        bool isValidRow(int num);
        bool isValidSquare(int num);

};


int main() {
    
    // vector <int> row2{2,0,0,0,0,8,0,3,1};
    // vector <int> row3{0,0,0,0,7,3,2,0,0};
    // vector <int> row4{7,0,0,0,6,5,1,0,3};
    // vector <int> row5{0,0,5,0,0,0,0,7,8};
    // vector <int> row6{0,0,8,0,9,7,0,2,5};
    // vector <int> row7{0,5,2,4,0,0,0,1,9};
    // vector <int> row8{0,4,0,0,8,1,0,0,2};
    // vector <int> row9{0,7,1,5,2,0,8,0,4};

    // vector <vector <int> > aGrid;
    // aGrid.push_back(row1);
    // aGrid.push_back(row2);
    // aGrid.push_back(row3);
    // aGrid.push_back(row4);
    // aGrid.push_back(row5);
    // aGrid.push_back(row6);
    // aGrid.push_back(row7);
    // aGrid.push_back(row8);
    // aGrid.push_back(row9);

    SudokuGrid mygrid;
    mygrid.populateGrid();
    mygrid.printGrid();
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

void SudokuGrid::printGrid() {
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
