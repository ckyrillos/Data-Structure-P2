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
    // Gets filepath and creates ifstream object.
    string filePath = string(argv[1]);
    ifstream dataFile;
    dataFile.open(filePath.c_str());

    // Validates file
    if(dataFile.good())
    {
        // Reads polynomials into strings and calls constructor
        string poly1;
        string poly2;
        getline(dataFile, poly1);
        getline(dataFile, poly2);
        Polynomial polynomial1(poly1);
        Polynomial polynomial2(poly2);

        // OUTPUT 1: Print Polynomial1 and evaluate at x=10
        cout << "P1 = " << polynomial1;
        cout << "P1(x=10) = ";
        int p1result = polynomial1.solve(10);
        // Checks if int equals sentinel
        if (p1result != INT_MAX)
        {
            cout << p1result << endl << endl;
        }

        // OUTPUT 2: Print Polynomial2 and evaluate at x=10
        cout << "P2 = " << polynomial2;
        cout << "P2(x=10) = ";
        int p2result = polynomial2.solve(10);
        // Checks if int equals sentinel
        if (p2result != INT_MAX)
        {
            cout << p2result << endl << endl;
        }

        // OUTPUT 3: Print sum of Polynomial1 and Polynomial2 and evaluate at x=10
        Polynomial polynomialSum;
        polynomialSum = polynomial1 + polynomial2;
        cout << "P1 + P2  = " << polynomialSum;
        cout << "P1 + P2 (x=10) = ";
        int pSumResult = polynomialSum.solve(10);
        // Checks if int equals sentinel
        if (pSumResult != INT_MAX)
        {
            cout << pSumResult << endl << endl;
        }

        // OUTPUT 4: Print product of Polynomial1 and Polynomial2 and evaluate at x=2
        Polynomial polynomialProd;
        polynomialProd = polynomial1 * polynomial2;
        cout << "P1 * P2  = " << polynomialProd;
        cout << "P1 * P2 (x=2) = ";
        int pProdResult = polynomialProd.solve(2);
        // Checks if int equals sentinel
        if (pProdResult != INT_MAX)
        {
            cout << pProdResult << endl << endl;
        }

        // OUTPUT 5a: Print Polynomial1 raised to third power
        Polynomial polynomialCubed;
        polynomialCubed = polynomial1^3;
        cout << "P1^3  = " << polynomialCubed;

        // OUTPUT 5b: Print Polynomial1 raised to the value of Polynomial2 evaluated at x=5
        cout << "P2(x=5) = ";
        int p2Eval = polynomial2.solve(5);
        // Checks if int equals sentinel
        if (p2Eval != INT_MAX)
        {
            cout << p2Eval << endl;
        }

        Polynomial polynomialExpEval;
        cout << "P1^(P2(x=5)) = ";
        polynomialExpEval = polynomial1^p2Eval;
        cout << polynomialExpEval;

        // Closes file after successfully reading data into doubly linked list.
        dataFile.close();
    }
    else
    {
        // Closes files since something went wrong.
        // Normally I would include a cout here but the project stated there should be no other output.
        dataFile.close();
    }
    return 0;
}