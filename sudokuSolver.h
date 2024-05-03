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
        void printSolvedGrid();
        bool isValid();
    
    private:
        vector <vector <int> > aGrid;
        bool isValidCol(int num);
        bool isValidRow(int num);
        bool isValidSquare(int num);

};

