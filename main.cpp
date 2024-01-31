#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

int positionx = 0;
int positiony = 0;
int sonuc ;

int** mapMatrix;
int** keyMatrix;



void Mapmatrix(fstream &file ,int row, int col){           // i opened a function to create 2d array using pointer for mapmatrix..

    mapMatrix = new int*[row];

    for (auto i = 0; i < row; ++i) {
        mapMatrix[i] = new int[col]();
    }
    for (int j = 0; j < row; ++j) {         //adding the variables from the file to 2d array.
        for (int k = 0; k < col; ++k) {
            file >> mapMatrix[j][k];
        }
    }
    file.close();
}

void Keymatrix(fstream &file_,int keySize){           //function to create 2d array using pointer for keymatrix.



    keyMatrix = new int*[keySize];

    for (auto i = 0; i < keySize; ++i) {
        keyMatrix[i] = new int[keySize]();
    }
    for (int j = 0; j < keySize; ++j) {         //adding variables from the text file to the 2d array.
        for (int k = 0; k < keySize; ++k) {
            file_ >> keyMatrix[j][k];
        }
    }
    file_.close();
}

int first(ofstream &outputFile,int keySize) {           //function for the beginning of the game.

    int n = keySize;

    for (int i = 0; i < n; i++) {           //2 for loops for multiplying the values from the mapmatrix and keymatrix.
        for (int j = 0; j < n; j++) {

            sonuc += keyMatrix[i][j] * mapMatrix[i][j];
        }
    }
    outputFile << n/2 << "," << n/2 << ";" << sonuc << endl;      //printing the center cells and the multiplying result.
    return sonuc;
}

void multipltying(ofstream &outputFile,int row, int col, int keySize) {           // function to do the calculations, i used recursion in this function.


    int n = keySize;
    int a = n/2;

    int modluSonuc = sonuc % 5;             //defining the mod.

    if (modluSonuc == 0) {          // if statement for the case finding the treasure.
        exit(EXIT_SUCCESS);
    }

    else if (modluSonuc == 1) {             // go up function

        sonuc = 0;

        if (positionx >= n){                // determination the border, if the key matrix can slide up then slide it function.
            positionx -= n;
            outputFile << positionx + a << "," << positiony +a << ":" ;     //printing the centers cell.

            for (int i = 0; i < n; i++) {       //for loops to multiply the matrices.
                for (int j = 0; j < n; j++) {

                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                }
            }

            while (sonuc < 0){      //while statement for the  case result of the multiplication is negative.
                    sonuc += 5;
            }
            //cout << sonuc << endl;      //printing the result of the multiplication.
            outputFile << sonuc << endl;
        }


        else{                   //if the key matric cannot slide up.
            positionx += n;

            outputFile << positionx + a << "," << positiony + a << ":" ;      //printing the center cell.

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j]* mapMatrix[i + positionx][j + positiony];      //for loops to multiply the matrices.
                }
            }
            while (sonuc < 0){      //while statement for the  case result of the multiplication is negative.
                sonuc += 5;
            }

            //cout << sonuc << endl;      //printing the result of the multiplication.
            outputFile << sonuc << endl;
        }
        multipltying(outputFile, row, col, keySize);         //recursion to continue to the game.
    }

    else if (modluSonuc == 2) {             // if statement to go down

        sonuc = 0;

        if (row - (positionx + n -1) >n ){       //checking the borders.
            positionx += n;             //updating the coordinate of the keymatrix on the mapmatrix (top left corner).
            outputFile << positionx + a << "," << positiony + a << ":" ;

            for (int i = 0; i < n; i++) {           //for loops to multiply the matrices.
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];     //for loops to multiply the matrices.
                }
            }
            while (sonuc < 0){          //while statement for the  case result of the multiplication is negative.
                sonuc += 5;
            }
            //cout << sonuc << endl;          //printing the result of the multiplication.
            outputFile << sonuc << endl;
        }

        else{           //for the case of key matrix cannot slide down, slide it up.
            positionx -= n;         //updating the coordinate of the mey matrix.
            outputFile << positionx + a << "," << positiony + a << ":" ;

            for (int i = 0; i < n; i++) {           //for loops to multiply the matrices.
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                    }
                }
            while (sonuc < 0){
                sonuc += 5;
            }
        //    cout << sonuc << endl;
            outputFile << sonuc << endl;

        }
        multipltying(outputFile, row, col, keySize);             //recursion call.
    }


    else if (modluSonuc == 3) {     // if statement for going right.

        sonuc = 0;
        if (col - (positiony + n -1) > n){           //key matrix can slide to right.
            positiony += n;             //updating the coordinate of key matrix.
            outputFile << positionx + a << "," << positiony + a << ":" ;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                }
            }
            while (sonuc < 0){
                sonuc+= 5;
            }
            outputFile << sonuc << endl;
            //cout << sonuc << endl;
        }

        else{           //key matrix cannot slide to right on the map matrix,then slide to left.
            positiony -= n;
            outputFile <<  positionx + a << "," << positiony + a << ":";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                }
            }
            while (sonuc < 0){
                sonuc += 5;
            }
            outputFile << sonuc << endl;
            //cout << sonuc << endl;
        }
        multipltying(outputFile, row, col, keySize);
    }


    else if (modluSonuc == 4) {             //if statement for going to left.
        sonuc = 0;

        if (positiony >= n){        //controlling borders if key matrix ca slide to left on map matrix.
            positiony -= n;
            outputFile << positionx + a << "," << positiony + a << ":";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                }
            }

            while (sonuc < 0){
                sonuc += 5;
            }
            outputFile << sonuc << endl;
            //cout << sonuc << endl;
        }

        else{       //else statement for the case key matrix cannot slide to left on map matrix.
            positiony += n;

            outputFile << positionx + a << "," << positiony + a << ":";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sonuc += keyMatrix[i][j] * mapMatrix[i + positionx][j + positiony];
                }
            }
            while (sonuc < 0){
                sonuc += 5;
            }
            outputFile << sonuc << endl;
            //cout << sonuc << endl;
        }
        multipltying(outputFile,row, col, keySize);
    }

}

int main(int argc, char *argv[]){        //main function to call the functions and run the code.




    string arguman = argv[1];
    string delimiter = "x";
    string token = arguman.substr(0,arguman.find(delimiter));
    string token_ = arguman.substr(1+arguman.find(delimiter));

    int row = stoi(token);
    int col = stoi(token_);

    int keySize = stoi(argv[2]);

    ofstream outputFile;
    outputFile.open(argv[5]);

    fstream file;
    file.open(argv[3]);


    fstream file_;
    file_.open(argv[4]);


    Mapmatrix(file,row, col);
    Keymatrix(file_,keySize);
    first(outputFile,  keySize);
    multipltying(outputFile, row, col, keySize);
    outputFile.close();
    file.close();
    file_.close();
    delete[] mapMatrix;
    delete[] keyMatrix;

    return 0;
}
