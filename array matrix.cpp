

#include <iostream>
using namespace std;

// 1D-Array---Row major mapping 
int* row(int arr[][4], int x, int y) {

    static int a[16];
    int z = 0;
    for (int i = 0;i < x;i++) {
        for (int j = 0;j < y;j++) {
            a[z] = arr[i][j];
            z++;
        }
    }
    return a;
}

// 1D-Array---column major mapping 
int* col(int arr[][4], int x, int y) {

    static int a[16];
    int z = 0;
    for (int i = 0;i < x;i++) {
        for (int j = 0;j < y;j++) {
            a[z] = arr[j][i];
            z++;
        }
    }
    return a;
}

// Extract diagonal from 2D 
int* extract(int arr[][4], int n) {
    static int diag1D[4];
    for (int i = 0; i < n; i++) {
        diag1D[i] = arr[i][i];
    }
    return diag1D;
}

// Rebuild diagonal 2D matrix from 1D
int* reverseDiag(int diag1D[], int n) {
    static int r[16];
    int z = 0;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (i == j)
                r[z] = diag1D[i];
            else
                r[z] = 0;
            z++;
        }
    }
    return r;
}

// Extract lower triangular from 2D 
int* extractLower(int arr[][4], int n) {
    static int lower1D[10];
    int z = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            lower1D[z] = arr[i][j];
            z++;
        }
    }
    return lower1D;
}


// Rebuild lower triangular 2D from 1D 
int* reverseLower(int lower1D[], int n) {
    static int r[16];
    int z = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j) {
                r[i * n + j] = lower1D[z];
                z++;
            }
            else {
                r[i * n + j] = 0;
            }
        }
    }
    return r;
}


// Extract upper triangular from 2D 
int* extractUpper(int arr[][4], int n) {
    static int upper1D[10];
    int z = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            upper1D[z] = arr[i][j];
            z++;
        }
    }
    return upper1D;
}

// Rebuild upper triangular 2D from 1D 
int* reverseUpper(int upper1D[], int n) {
    static int r[16];
    int z = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                r[i * n + j] = upper1D[z];
                z++;
            }
            else {
                r[i * n + j] = 0;
            }
        }
    }
    return r;
}


// Function to map symmetric matrix (n x n) → 1D 
int* map(int sym[4][4], int n) {
    int size = n * (n + 1) / 2;
    int* oneD = new int[size];
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            oneD[k] = sym[i][j];
            k++;
        }
    }
    return oneD;
}


// Reverse map 1D back → full symmetric 2D 
int* To2Dflat(int* oneD, int n) {
    int* sym2D = new int[n * n];

    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            sym2D[i * n + j] = oneD[k];   // element at (i,j)
            sym2D[j * n + i] = oneD[k];   // mirror at (j,i)
            k++;
        }
    }
    return sym2D;
}





int main() {


    cout << "------------------------------------------\n";
    cout << "         Data Structures Lab              \n";
    cout << "             BSAI-III-A                   \n";
    cout << "             Lab Task - 1                 \n";
    cout << "         Maham Fatima (241408)            \n";
    cout << "------------------------------------------\n\n";

    int r = 4, c = 4;

    // 2D Array 
    int a[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    // Row-major mapping Pointer
    int* array;
    array = row(a, r, c);

    // column-major mapping Pointer
    int* brray;
    brray = col(a, r, c);

    // 2D Array 
    cout << "-------2D-Array (4x4)------\n";
    for (int i = 0;i < r;i++) {
        for (int j = 0;j < c;j++) {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }

    //For representing 2D array as 1D two major mappings are used. Row major mapping and Column Major mapping.

    //Row major mapping
    cout << "\n--- ROW-MAJOR-MAPPING (2D) ---\n";
    for (int i = 0;i < 16;i++) {
        cout << array[i] << "\t";
    }

    cout << endl;

    // In row-major order, a 2D array is converted to a 1D array by storing elements **row by row**.
 // Formula to map 2D index [i][j] to 1D index: index = i * number_of_columns + j

    cout << "\n--- INDEX-MAPPING (2D) ---\n";
    for (int i = 0;i < r;i++) {
        for (int j = 0;j < c;j++) {
            cout << "Index (" << i << "," << j << ") is mapped to:" << (i * c) + j << endl;
        }
    }

    //Column major mapping
    cout << "\n--- COLUMN-MAJOR-MAPPING (2D) ---\n";
    for (int i = 0;i < 16;i++) {
        cout << brray[i] << "\t";
    }

    cout << endl;

    // In column-major order, a 2D array is converted to a 1D array by storing elements **column by column**.
 // Formula to map 2D index [i][j] to 1D index: index = i + j* number_of_rows

    cout << "\n--- INDEX-MAPPING (2D) ---\n";
    for (int i = 0;i < r;i++) {
        for (int j = 0;j < c;j++) {
            cout << "Index (" << i << "," << j << ") is mapped to:" << i + (j * r) << endl;
        }
    }

    cout << endl;

    // Original Diagonal Matrix
    int diag[4][4] = {
        {1,0,0,0},
        {0,2,0,0},
        {0,0,3,0},
        {0,0,0,4}
    };

    // Extract diagonal into 1D
    int* dia = extract(diag, r);

    // Print Original 2D
    cout << "------2D Diagonal Matrix--------\n";
    for (int i = 0;i < r;i++) {
        for (int j = 0;j < c;j++)
            cout << diag[i][j] << "\t";
        cout << endl;
    }

    // Print 1D
    cout << "\n-------1D Diagonal Mapping-------- \n";
    for (int i = 0;i < r;i++) {
        cout << dia[i] << "\t ";
    }

    // Reverse diagonal mapping (1D)
    int* rev = reverseDiag(dia, r);

    cout << "\n\n---------Reverse Mapped 2D Matrix-------\n";
    int z = 0;
    for (int i = 0;i < r;i++) {
        for (int j = 0;j < c;j++) {
            cout << rev[z] << "\t";
            z++;
        }
        cout << endl;
    }

    cout << endl;

    // Original Lower Triangular 2D matrix
    int lower2D[4][4] = {
        {1, 0, 0, 0},
        {5, 6, 0, 0},
        {9, 10, 11, 0},
        {13, 14, 15, 16}
    };

    // Print Original 2D Matrix
    cout << "------ Original Lower Triangular (2D) ------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << lower2D[i][j] << "\t";
        }
        cout << endl;
    }

    // Extract lower triangular into 1D
    int* lower1D = extractLower(lower2D, r);


    // Print 1D Matrix
    cout << "\n------ 1D Lower Triangular Mapping ------\n";
    int total = r * (c + 1) / 2;
    for (int i = 0; i < total; i++) {
        cout << lower1D[i] << "\t";
    }
    cout << endl;

    // Reverse map 1D → 2D
    int* dev = reverseLower(lower1D, c);

    // Print Reverse Mapped 2D Matrix
    cout << "\n------ Reverse Mapped 2D Matrix ------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << dev[i * c + j] << "\t";
        }
        cout << endl;
    }

    cout << endl;

    //  Upper Triangular 2D matrix
    int upper2D[4][4] = {
        {1, 2, 3, 4},
        {0, 5, 6, 7},
        {0, 0, 8, 9},
        {0, 0, 0, 10}
    };

    // Print Original 2D Matrix
    cout << "------ Original Upper Triangular (2D) ------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << upper2D[i][j] << "\t";
        }
        cout << endl;
    }

    // Extract upper triangular into 1D
    int* upper1D = extractUpper(upper2D, r);

    // Print  1D Matrix
    cout << "\n------ 1D Upper Triangular Mapping ------\n";
    int final = r * (c + 1) / 2;
    for (int i = 0; i < final; i++) {
        cout << upper1D[i] << "\t";
    }
    cout << endl;

    // Reverse map 1D → 2D
    int* note = reverseUpper(upper1D, r);

    // Print Reverse Mapped 2D Matrix
    cout << "\n------ Reverse Mapped 2D Matrix ------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << note[i * c + j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    //  symmetric matrix
    int sym[4][4] = {
        {1, 2, 3, 4},
        {2, 5, 6, 7},
        {3, 6, 8, 9},
        {4, 7, 9, 10}
    };

    //  symmetric matrix Display
    cout << "-----------Original Symmetric Matrix-------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) cout << sym[i][j] << "\t ";
        cout << endl;
    }

    // 2D → 1D mapping (lower triangle)
    int* oneD = map(sym, r);
    int size = r * (r + 1) / 2;


    //  1D-Arryay 
    cout << "\n--------Mapped 1D Array (Lower Triangle)--------\n";
    for (int i = 0; i < size; i++)
        cout << oneD[i] << "\t";

    cout << endl;

    // 1D → 2D
    int* symMat = To2Dflat(oneD, c);

    //  Reconstructed symmetric matrix Display
    cout << "\n -------------Reconstructed Symmetric Matrix---------\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << symMat[i * c + j] << "\t";
        }
        cout << endl;
    }

    // Matrix Transpose, Addition, Multiplication, Tridiagonal Check
    int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
    int B[3][3] = { {9,8,7},{6,5,4},{3,2,1} };
    int C[3][3];


    cout << "Matrix arr:\n";
    for (int i = 0;i < 3;i++) { for (int j = 0;j < 3;j++) cout << arr[i][j] << "\t"; cout << "\n"; }


    cout << "Matrix B:\n";
    for (int i = 0;i < 3;i++) { for (int j = 0;j < 3;j++) cout << B[i][j] << "\t"; cout << "\n"; }



    // Transpose
    cout << "\nTranspose of Matrix:\n";
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) cout << arr[j][i] << "\t";
        cout << "\n";
    }


    // Addition
    cout << "\nMatrix Addition (arr + B):\n";
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) C[i][j] = arr[i][j] + B[i][j];
    }
    for (int i = 0;i < 3;i++) { for (int j = 0;j < 3;j++) cout << C[i][j] << "\t"; cout << "\n"; }


    // Multiplication
    cout << "\nMatrix Multiplication (arr * B):\n";
    for (int i = 0;i < 3;i++) for (int j = 0;j < 3;j++) C[i][j] = 0;
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            for (int k = 0;k < 3;k++) C[i][j] += arr[i][k] * B[k][j];
        }
    }
    for (int i = 0;i < 3;i++) { for (int j = 0;j < 3;j++) cout << C[i][j] << "\t"; cout << "\n"; }


    // Tridiagonal Check
    bool tridiag = true;
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            if (abs(i - j) > 1 && arr[i][j] != 0) tridiag = false;
        }
    }
    cout << "\nTridiagonal Check: ";
    if (tridiag) cout << "Tridiagonal\n";
    else cout << "Not Tridiagonal\n";





    cout << "\n------------- Finally Done! No More Mappings Today --------------" << endl;


    return 0;
}























