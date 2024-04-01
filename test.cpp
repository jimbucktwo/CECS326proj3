#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream readfile("input.txt");

    int arr[5][4];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++){
            readfile >> arr[i][j];
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    string sss;
    cin >> sss;
    if (sss == "*") {
        cout << "TRUEEE";
    }
}