//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME: Quine-McKluskey.cpp             ASSIGNMENT #1             Grade: _________   *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     _________________________________________                                   *
//*                                    Hein Htet Zaw                                                  *
//*                                                                                                   *
//*   COURSE #:  CSC 40300 11                                           DUE DATE:  October 17, 2016   *
//*                                                                                                   *
//*****************************************************************************************************
//*****************************************************************************************************
//                                                                                                    *
// Program description: This program is to give an automated tool for producing minimized Boolean     *
//						expressions using the Quine-McKluskey method. Input to this program is given  *
//						in the form of a right-hand side of a Boolean function. The variables in each *
//						term always appears in the same order. Each term always has the same number of*
//						variables but the number of variables in each term varies from expression to  *
//						expression. The maximum number of variables per term is six and the maximum   *
//						number of terms is twelve. Terms are separated by a blank. A TERM sentinel of *
//						'X' indicates the end of the expression. 'S' indicates the end of input file. *
//                                                                                                    *
//*****************************************************************************************************

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <array>
	
		//define the maximum variables and terms in the input file
#define variables 6
#define terms 12

using namespace std;

void header(ofstream &outfile);
void footer(ofstream &outfile);
int compareTerms(int termCount, int data0[][variables+2], int data1[][variables+2]);

int main() {
			//set up input and output files
	ifstream infile("Test_data.txt", ios::in);		//test case
//	ifstream infile("data1.txt", ios::in);
	ofstream outfile("Output.txt", ios::out);

			//print header section before anything
	header(outfile);

			//set up sentinel watcher
	string sentinel;

			//get the very first term
	infile >> sentinel;

			//repeat processing till 'S' appears
	while (sentinel[0] != 'S') {

		//declare a temporary storage variable for inputs
		string temp;

		//create arrays to store the terms / using 3D array in this case
		string readValues[terms];
		int data[3][terms][variables + 2];
		for (int i = 0; i < terms; i++) {
			data[0][i][6] = 0;
			data[0][i][7] = 0;
		}

		//get the very first input -- initiate
		temp = sentinel;

		//keep track of the number of terms and variables
		int termCount = 0;
		int termCount1 = 0;
		int termCount2 = 0;
		int varCount = 0;

		//scan for every term till 'X' appears
		while (temp[0] != 'X') {

			//count the negative variables in each term
			int negatives = 0;

			//update the variable count
			varCount = temp.length();

			//break down each term into variables
			for (int i = 0; i < varCount; i++) {

				//convert the letters to boolean form
				if (temp[i] < 91) data[0][termCount][temp[i] - 65] = 1;
				else data[0][termCount][temp[i] - 97] = 0;
			}
			readValues[termCount] = temp;

			//get the next term
			infile >> temp;

			//increment the term counter
			termCount++;
		}
			termCount1 = compareTerms(termCount, data[0], data[1]);

			outfile << termCount << " terms | " << varCount << " variables" << endl << endl;
			for (int i = 0; i < termCount; i++) {
				for (int j = 0; j < varCount; j++) {
					outfile << data[0][i][j];
				}
				outfile << " | " << data[0][0][6] << " | " << data[0][0][7] << endl;
			}
			outfile << "_____________________" << endl;
					//update the sentinel check
			infile >> sentinel;
		}
	
			//print footer after everything
	footer(outfile);

//	cin.get();

			//return 0 and quit the app when everything is finished
	return 0;
}

//*****************************************************************************************************
int compareTerms(int termCount, int data0[][variables+2], int data1[][variables+2]) {

			// Receives – original data table and an empty data table
			// Task - compare terms in original table and put the results in new table
			// Returns - new data table

	if (termCount == 0) return 0;

	return 0;
}

//*****************************************************************************************************
void header(ofstream &outfile) {

			// Receives – the output file
			// Task - Prints the output preamble
			// Returns - Nothing

	outfile << setw(33) << "Hein Htet Zaw";
	outfile << setw(15) << "CSC 40300";
	outfile << setw(15) << "Section 11" << endl;
	outfile << setw(37) << "Fall 2016";
	outfile << setw(20) << "Assignment #1" << endl;
	outfile << setw(38) << "-------------------------------------------";
	outfile << setw(38) << "------------------------------------------\n\n";

	return;
}

//*****************************************************************************************************
void footer(ofstream &outfile) {

			// Receives – the output file
			// Task - Prints the output salutation
			// Returns - Nothing

	outfile << endl;
	outfile << setw(35) << "----------------------------------" << endl;
	outfile << setw(35) << "|      END OF PROGRAM OUTPUT     |" << endl;
	outfile << setw(35) << "----------------------------------" << endl;

	return;
}
//*****************************************************************************************************
