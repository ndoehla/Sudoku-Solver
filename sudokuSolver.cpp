#include "sudokuSolver.h"


using namespace std;


int main() {
    SudokuGrid mygrid("puzzle1");
    mygrid.populateGrid();
    mygrid.solve();
    mygrid.printSolvedGrid(mygrid.getPuzzleName());
    
}


SudokuGrid::SudokuGrid(string pPuzzleName) : puzzleName(pPuzzleName){}

string SudokuGrid::getPuzzleName() {return puzzleName;}


void SudokuGrid::printSolvedGrid(string filename) {
    ifstream myfile(filename+"Solved.txt");

    if(!myfile.is_open()) {
        throw invalid_argument("Could not find your sudoku puzzle");
    }

    string myline;
    while(myfile) {
        getline(myfile, myline);
        cout << myline << endl;
    }

}


void SudokuGrid::populateGrid() {
    aGrid.clear();
    solvedGrid.clear();
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
    makePuzzle(getPuzzleName());


    // loop to initialized the solution grid with same values as original


    for(int i = 0; i < 9; i++) {
        vector <int> aRow(aGrid[i].begin(), aGrid[i].end());
        solvedGrid.push_back(aRow);
    }
}



void SudokuGrid::makePuzzle(string filename) {
    ofstream myfile;
    myfile.open(filename+".txt");

    if(!myfile.is_open()) {
        throw invalid_argument("Could not create sudoku file.");
    }

    myfile << "\n   ----- " << filename << " -----";
    myfile << "\n\n" << endl;
    for(int i = 0; i < 9; i++) {
        if(i==0 || i== 3 || i == 6) {
            myfile << "+---------+---------+---------+" << endl;
        }
        for(int j = 0; j < 9; j++) {
            if(j==0 || j==3 || j==6) {
                myfile << "| " << aGrid[i][j] << " ";

            } else if (j==8) {
                myfile << " " << aGrid[i][j] << " |" << endl;   
            } else {
                myfile << " " << aGrid[i][j] << " ";
            }
        }
    }

    myfile << "+---------+---------+---------+" << endl;

    myfile.close();

}

void SudokuGrid::solve() {
    solveGrid(solvedGrid, 0, 0);

    makePuzzle((getPuzzleName() + "Solved"));
}

void SudokuGrid::solveGrid(vector <vector <int> > &board, int row, int col) {

}

