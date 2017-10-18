/*
 * Ethics Statement:
 * Other than anything noted in the disclosures below, the code submitted is of my design and my design alone.
 * I recieved no help nor used any references, resources, and had no discussion with other classmates.
 * I understand the University policy concerning ethics and
 * understand that violating this policy will result in drastic repercussions.
 *
 * Disclosures:
 * No disclosures.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Polynomial.h"
using namespace std;

int main(int argc, const char *argv[])
{
    string poly1;
    string poly2;

    // Gets filepath and creates ifstream object.
    string filePath = string(argv[1]);
    ifstream dataFile;
    dataFile.open(filePath.c_str());

    // Opens file and makes sure it is valid.
    if(dataFile.good())
    {
        // Reads polynomials into string and call constructor
        getline(dataFile, poly1);
        getline(dataFile, poly2);
        Polynomial polynomial1(poly1);
        Polynomial polynomial2(poly2);

        cout << "P1 terms = " << polynomial1.numTerms << endl;
        polynomial1.print();

        int x = 3;
        int result = polynomial1.solve(x);
        if (result == INT_MAX || result == INT_MIN)
        {
            cout << "OVERFLOW" << endl;
        }
        cout << "x = " << x << " ; y = " << result << endl;



        cout << "P2 terms = " << polynomial2.numTerms << endl;
        polynomial2.print();

        x = 3;
        result = polynomial2.solve(x);
        if (result == INT_MAX || result == INT_MIN)
        {
            cout << "OVERFLOW" << endl;
        }
        cout << "x = " << x << " ; y = " << result << endl;


        Polynomial polynomial3;
        polynomial3 = polynomial1 + polynomial2;
        cout << "P1+P2 terms = " << polynomial3.numTerms << endl;
        polynomial3.print();

        polynomial3 = polynomial1 * polynomial2;
        cout << "P1*P2 terms = " << polynomial3.numTerms << endl;
        polynomial3.print();

//        polynomial3 = polynomial1^2;
//        cout << "P1^2 terms = " << polynomial3.numTerms << endl;
//        polynomial3.print();


        // Closes file after successfully reading data into doubly linked list.
        dataFile.close();
    }
    else
    {
        // Closes files since something went wrong.
        // Normally I would include a cout here but the project stated there should be no other output.
        dataFile.close();
    }
    cout << endl << "Everything still works!" << endl;
    return 0;
}