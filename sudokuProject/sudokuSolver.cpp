#include "sudokuSolver.h"


using namespace std;


int main() {
    SudokuGrid mygrid;
    mygrid.populateGrid();
    mygrid.solve();
    mygrid.writeSolution();
}

SudokuGrid::SudokuGrid(){}

string SudokuGrid::getPuzzleName() {return puzzleName;}


void SudokuGrid::printSolvedGrid() {
    ifstream myfile(getPuzzleName()+"Solved.txt");

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
    string name;
    cout << "\nEnter the name of today's puzzle: ";
    getline(cin, name);
    setPuzzleName(name);


    aGrid.clear();
    solvedGrid.clear();

    cout << "\nTo populate the sudoku grid, we will fill rows one at a time.\n" << endl;
    for(int i = 0; i < 9; i++) {
        cout << "Please enter 9 numbers with no spaces in between them and then hit enter. Free cells are represented as the number \'0\':\n";
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
    if(solveGrid(solvedGrid, 0, 0)) {
        makeSolvedPuzzle(getPuzzleName());
    }
    else {
        cout << "Your sudoku puzzle is impossible to solve. Not a valid entry." << endl;
    }
}


bool SudokuGrid::checkSolution(vector <vector <int> > mySolution) {
    solve();
    mySolution.shrink_to_fit();
    solvedGrid.shrink_to_fit();

    if(mySolution.size()!=9) return false;

    for(int i = 0; i < 9; i++) {
        mySolution[i].shrink_to_fit();
        if(mySolution[i].size()!=9) {
            return false;
        }
    }

    for(int j = 0; j < 9; j++) {
        for(int k = 0; k < 9; k++) {
            if(mySolution[j][k]!=solvedGrid[j][k]) return false;
        }
    }
    return true;

}

void SudokuGrid::writeSolution() {
    vector <vector <int> > solutionVector;

    for(int i = 0; i < 9; i++) {
        cout << "For your solution, please enter 9 numbers with no spaces in between them and then hit enter (subsequent rows to follow):" << endl;
        string s;
        cin >> s;
        if(s.size()!=9) {
            throw invalid_argument("You did not enter the correct input.");
        }
        
        vector <int> row;
        int pos = 0;
        for(int j=0; j<s.size(); j++) {
            if(s[j] < 47 || s[j]>57) {
                throw invalid_argument("Solution only takes digits 1-9.");
            }
            int val = s[j] - '0';
            row.push_back(val);
        }
        solutionVector.push_back(row);
    }

    if(checkSolution(solutionVector)) {
        cout << "Your inputted solution is correct!!!" << endl;
    }

    else {
        cout << "Incorrect solution. Try solving again!" << endl;
    }
}









//PRIVATE FUNCTIONS
bool SudokuGrid::isValidCol(vector <vector <int> > &board, int col, int value) {
    for(int i = 0; i < 9; i++) {
        if(board[i][col]==value) return false;
    }
    return true;

}

bool SudokuGrid::isValidRow(vector <vector <int> > &board, int row, int value) {
    for(int i = 0; i < 9; i++) {
        if(board[row][i]==value) return false;
    }
    return true;
}

bool SudokuGrid::isValidSquare(vector <vector <int> > &board, int row, int col, int value) {
    int startRow = 3*(row/3);
    int startCol = 3*(col/3);

    for(int i = startRow; i < startRow + 3; i++) {
        for(int j = startCol; j < startCol + 3; j++) {
            if(board[i][j]==value) return false;
        }
    }
    return true;
}

bool SudokuGrid::solveGrid(vector <vector <int> > &board, int row, int col) {

    if(col==9) {
        if(row==8) {
            return true; // solved the board
        }
        //at the end of a column, move to next row
        col = 0;
        row += 1;
    }

    //check for empty cells

    //if not empty, recurse on the next cell in column
    if(board[row][col]!=0) {
        return solveGrid(board, row, col+1);
    }

    //here we try recursive backtracking on each cell
    for(int i = 1; i<10; i++) {
        if(isValidCol(board, col, i) && isValidRow(board, row, i) && isValidSquare(board, row, col, i)) {
            board[row][col] = i;
            if(solveGrid(board, row, col+1)) {
                return true;
            }
        }
        board[row][col] = 0; //reset and backtrack, previous value didn't work

    }
    return false; // board not possible to solve

}

void SudokuGrid::makeSolvedPuzzle(string filename) {
    ofstream myfile;
    myfile.open(filename+"Solved.txt");

    if(!myfile.is_open()) {
        throw invalid_argument("Could not create sudoku file.");
    }

    myfile << "\n   ----- " << filename << " Solved "<< "-----";
    myfile << "\n\n" << endl;
    for(int i = 0; i < 9; i++) {
        if(i==0 || i== 3 || i == 6) {
            myfile << "+---------+---------+---------+" << endl;
        }
        for(int j = 0; j < 9; j++) {
            if(j==0 || j==3 || j==6) {
                myfile << "| " << solvedGrid[i][j] << " ";

            } else if (j==8) {
                myfile << " " << solvedGrid[i][j] << " |" << endl;   
            } else {
                myfile << " " << solvedGrid[i][j] << " ";
            }
        }
    }

    myfile << "+---------+---------+---------+" << endl;

    myfile.close();

}

void SudokuGrid::setPuzzleName(string name) {puzzleName = name;}

