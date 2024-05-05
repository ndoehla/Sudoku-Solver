#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


class SudokuGrid {
    public:
        SudokuGrid();
        void solve();
        void populateGrid();
        string getPuzzleName();
        void makePuzzle(string filename); 
        void printSolvedGrid();
        void writeSolution();
        bool checkSolution(vector <vector <int> > mySolution);
    
    private:
        vector <vector <int> > aGrid;
        vector <vector <int> > solvedGrid;
        string puzzleName;


        bool isValidCol(vector <vector <int> > &board, int col, int value);
        bool isValidRow(vector <vector <int> > &board, int row, int value);
        bool isValidSquare(vector <vector <int> > &board, int row, int col, int value);
        bool solveGrid(vector <vector <int> > &board, int row, int col);
        void makeSolvedPuzzle(string filename);
        void setPuzzleName(string name);
        

};

