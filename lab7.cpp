#include <iostream>
#include <limits>
using namespace std;

const int MAX_M = 50;
const int MAX_N = 50;

// Input matrix (2..50) with validation
void inputMatrix(int a[MAX_M][MAX_N], int &m, int &n) {
    while (true) {
        cout << "Enter number of rows m (2..50): ";
        cin >> m;
        cout << "Enter number of columns n (2..50): ";
        cin >> n;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input error. Try again.\n\n";
            continue;
        }

        if (m < 2 || m > 50 || n < 2 || n > 50) {
            cout << "Error: m and n must be in range 2..50. Try again.\n\n";
            continue;
        }
        break;
    }

    cout << "Enter matrix elements (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

// Print matrix
void printMatrix(const int a[MAX_M][MAX_N], int m, int n) {
    cout << "Matrix (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t";
        }
        cout << "\n";
    }
}

// ===================== Table 1: Matrix28 =====================
// Given MxN matrix. Find the minimum among the maximum elements of its columns.
int minOfColumnMax(const int a[MAX_M][MAX_N], int m, int n) {
    int answer = numeric_limits<int>::max();

    for (int j = 0; j < n; j++) {
        int colMax = a[0][j];
        for (int i = 1; i < m; i++) {
            if (a[i][j] > colMax) colMax = a[i][j];
        }
        if (colMax < answer) answer = colMax;
    }
    return answer;
}

void taskMatrix28() {
    int a[MAX_M][MAX_N];
    int m, n;

    cout << "\n=== Task Matrix28 (Table 1) ===\n";
    cout << "Find the minimum among the maximum elements of the columns.\n\n";

    inputMatrix(a, m, n);
    cout << "\n";
    printMatrix(a, m, n);

    int result = minOfColumnMax(a, m, n);
    cout << "\nMinimum among column maximums = " << result << "\n\n";
}

// ===================== Table 2: Matrix71 =====================
// Given MxN matrix. Duplicate the column that contains the minimal element of the matrix.
// Implementation: duplicate column is inserted immediately to the RIGHT of that column.
bool duplicateColumnWithGlobalMin(int a[MAX_M][MAX_N], int m, int &n) {
    if (n >= MAX_N) return false; // no space for new column

    int minVal = a[0][0];
    int minCol = 0;

    // find global minimum and its column
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < minVal) {
                minVal = a[i][j];
                minCol = j;
            }
        }
    }

    // shift right and insert duplicate (row by row)
    for (int i = 0; i < m; i++) {
        for (int j = n; j > minCol + 1; j--) {
            a[i][j] = a[i][j - 1];
        }
        a[i][minCol + 1] = a[i][minCol];
    }

    n++;
    return true;
}

void taskMatrix71() {
    int a[MAX_M][MAX_N];
    int m, n;

    cout << "\n=== Task Matrix71 (Table 2) ===\n";
    cout << "Duplicate the column that contains the minimal element of the matrix.\n";
    cout << "(The duplicate is inserted immediately to the RIGHT of that column.)\n\n";

    inputMatrix(a, m, n);
    cout << "\nInitial ";
    printMatrix(a, m, n);

    bool ok = duplicateColumnWithGlobalMin(a, m, n);
    if (!ok) {
        cout << "\nCannot duplicate: n = 50 (no space for a new column).\n\n";
        return;
    }

    cout << "\nAfter duplication ";
    printMatrix(a, m, n);
    cout << "\n";
}

// ===================== Menu =====================
int main() {
    int choice;

    do {
        cout << "=============================\n";
        cout << "Lab work: Matrices\n";
        cout << "1 - Matrix28 (Table 1)\n";
        cout << "2 - Matrix71 (Table 2)\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: taskMatrix28(); break;
            case 2: taskMatrix71(); break;
            case 0: cout << "Exit.\n"; break;
            default: cout << "Invalid choice. Try again.\n\n"; break;
        }
    } while (choice != 0);

    return 0;
}