
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

