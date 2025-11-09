#include <iostream>
using namespace std;

class nqueen {
public:
    bool check(int **arr, int row, int col, int n);
    bool solve_nqueen(int **arr, int col, int n);
};

bool nqueen::check(int **arr, int row, int col, int n) {
    // Check left side horizontally
    for (int i = 0; i < col; i++) {
        if (arr[row][i]) return false;
    }
    
    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (arr[i][j]) return false;
    }
    
    // Check lower left diagonal  
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (arr[i][j]) return false;
    }
    
    return true;
}

bool nqueen::solve_nqueen(int **arr, int col, int n) {
    if (col >= n) {
        cout << "ALL QUEENS ARE PLACED\n";
        return true;
    }
    
    for (int i = 0; i < n; i++) {
        if (check(arr, i, col, n)) {
            arr[i][col] = 1;
            
            // Optional: Remove or modify visualization for large n
            if (n <= 8) { // Only show for smaller boards
                cout << "Placed queen at (" << i+1 << "," << col+1 << ")\n";
            }
            
            if (solve_nqueen(arr, col + 1, n)) {
                return true;
            }
            
            arr[i][col] = 0; // Backtrack
            if (n <= 8) {
                cout << "Backtrack from (" << i+1 << "," << col+1 << ")\n";
            }
        }
    }
    
    return false;
}

int main() {
    nqueen q1;
    int n;
    
    do {
        cout << "Enter chessboard size (should be > 3): ";
        cin >> n;
    } while (n <= 3);
    
    // Allocate memory
    int **arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    
    // Solve
    if (q1.solve_nqueen(arr, 0, n)) {
        cout << "\nFINAL SOLUTION:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << (arr[i][j] ? "Q " : ". ");
            }
            cout << "\n";
        }
    } else {
        cout << "No solution exists for n=" << n << "\n";
    }
    
    // Free memory
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    
    return 0;
}
