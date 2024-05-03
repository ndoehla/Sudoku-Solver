#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


class SudokuGrid {
    public:
        SudokuGrid(string pPuzzleName);
        void solve();
        void populateGrid();
        void printSolvedGrid(string filename);
        string getPuzzleName();
        bool checkSolution(vector <vector <int> > mySolution);
        void makePuzzle(string filename);
    
    private:
        vector <vector <int> > aGrid;
        vector <vector <int> > solvedGrid;
        bool isValidCol(int num);
        bool isValidRow(int num);
        bool isValidSquare(int num);
        void solveGrid(vector <vector <int> > &board, int row, int col);
        string puzzleName;

};

