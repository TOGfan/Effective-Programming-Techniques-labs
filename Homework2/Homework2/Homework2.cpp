#include <iostream>

using namespace std;

void v_alloc_table_add_5(int iSize) {
    if (iSize <= 0) {
        cout << "Invalid value";
        return;
    }
    int *arr = new int[iSize];
    cout << "Enter  the contents of the array"<<endl;
    for (int i = 0; i < iSize; i++) {
        cin >> arr[i];
        arr[i] += 5;
    }
    for (int i = 0; i < iSize; i++) {
        cout << arr[i]<<endl;
    }
    delete[] arr;
}

bool b_alloc_table_2_dim(int***piTable, int iSizeX, int iSizeY) {
    if (!(iSizeX > 0 && iSizeY > 0)) {
        return false;
    }
    int **temp= new int* [iSizeX];
    *piTable = temp;
    for (int i = 0; i < iSizeX; i++) {
        temp[i] = new int[iSizeY];
    }

    return true;
}

bool b_dealloc_table_2_dim(int***piTable, int iSizeX, int iSizeY) {
    int** temp = *piTable;
    for (int i = 0; i < iSizeX; i++)
        delete[] temp[i];
    delete[] temp;
    delete piTable;
    return true;
}

int main()
{
    int a;
    cout << "Enter the size of the array"<<endl;
    cin >> a;
    v_alloc_table_add_5(a);
    cout << "Enter  the contents of the 2d array" << endl;
    int sizeX = 5;
    int sizeY = 3;
    int*** arr=new int**;
    b_alloc_table_2_dim(arr, sizeX, sizeY);
    int** temp = *arr;
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            cin >> temp[j][i];
        }
    }
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            cout << temp[j][i]<<" ";
        }
        cout << endl;
    }
    b_dealloc_table_2_dim(arr, sizeX, sizeY);
    return 0;
}

