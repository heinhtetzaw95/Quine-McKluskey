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

//define the maximum variables and terms in the input file
#define variables 6
#define terms 12
#define col 3

using namespace std;

void header(ofstream &outfile);
void footer(ofstream &outfile);
int compareTerms(int termCount, string data0[][col], string data1[][col]);
int mergeDuplicates(int termCount, string data0[][col]);

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
		string data[5][terms][col];

				//get the very first input -- initiate
		temp = sentinel;

				//keep track of the number of terms and variables
		int termCount[5] = { 0 };

				//scan for every term till 'X' appears
		while (temp[0] != 'X') {

					//count the negative variables in each term
			int negatives = 0;
			int varCount = 0;

					//update the variable count
			varCount = temp.length();

					//break down each term into variables
			for (int i = 0; i < varCount; i++) {

						//check number of lower case letters
				if (islower(temp[i])) negatives++;
			}
					//store the term in the array
			data[0][termCount[0]][0] = temp;

					//keep negative count and merged status in the array
			data[0][termCount[0]][1] = to_string(negatives);
			data[0][termCount[0]][2] = "F";

					//get the next term
			infile >> temp;

					//increment the term counter
			termCount[0]++;
		}

				//compare elements in the original table and get new table
		for (int i = 0; i < 4; i++) {
			termCount[i+1] = compareTerms(termCount[i], data[i], data[i+1]);
		}
		
		for (int i = 0; i < termCount[0]; i++) {
			outfile << data[0][i][0] << " | " << data[0][i][1] << " | " << data[0][i][2] << endl;
		}
		outfile << termCount[1] << endl;
		for (int i = 0; i < termCount[1]; i++) {
			outfile << data[1][i][0] << " | " << data[1][i][1] << " | " << data[1][i][2] << endl;
		}
		outfile << termCount[2] << endl;
		for (int i = 0; i < termCount[2]; i++) {
			outfile << data[2][i][0] << " | " << data[2][i][1] << " | " << data[2][i][2] << endl;
		}
		outfile << termCount[3] << endl;
		for (int i = 0; i < termCount[3]; i++) {
			outfile << data[3][i][0] << " | " << data[3][i][1] << " | " << data[3][i][2] << endl;
		}
		outfile << termCount[4] << endl;
		for (int i = 0; i < termCount[4]; i++) {
			outfile << data[4][i][0] << " | " << data[4][i][1] << " | " << data[4][i][2] << endl;
		}
		outfile << "------------------------------" << endl;

				//update the sentinel check
		infile >> sentinel;
	}

			//print footer after everything
	footer(outfile);

	cin.get();

			//return 0 and quit the app when everything is finished
	return 0;
}

//*****************************************************************************************************
int compareTerms(int termCount, string data0[][col], string data1[][col]) {

		// Receives – original data table and an empty data table and number of terms in original table
		// Task - compare terms in original table and put the results in new table
		// Returns - new data table and its term counts

	if (termCount == 0) return 0;

			//get the number of variables in the term
	int varCount = data0[0][0].length();
	int newCount = 0;

			//compare the elements in the list
	for (int i = 0; i < termCount-1; i++) {
		for (int j = i + 1; j < termCount; j++) {
				
					//set up new string to put in the new table
			string newString; 
				
					//record the differences
			int diff = 0; 

					//store the status to merge or not
			bool marged = false;

					//compare the characters one by one
			for (int k = 0; k < varCount; k++) {
				
						//replace the reducable characters with underscore
				if (data0[i][0][k] != data0[j][0][k]) {
					newString += "_";

							//change mergable status
					marged = true;

							//increment the number of different characters
					diff++;
				}

						//put unmergable characters in a new string
				else {
					newString += data0[j][0][k];
				}
			}

					//put the string in the new list if there is only one difference		
			if (diff == 1) {

						//put the new string
				data1[newCount][0] = newString;

						//put merged status
				data1[newCount][2] = "F";

						//increment the number of 
				newCount++;

						//change the merged status
				if (marged == true) {
					data0[i][2] = data0[j][2] = "T";
				}
			}
		}
	}
			//eliminate duplicates in new array before returning
	newCount = mergeDuplicates(newCount, data1);

	return newCount;
}

//*****************************************************************************************************
int mergeDuplicates(int termCount, string data0[][col]) {

		// Receives – a table with terms and number of terms
		// Task - eliminate the duplicate data and keep only one
		// Returns - table without duplicate terms and new term count

			//look for duplicate elements
	for (int i = 0; i < termCount; i++) {
		for (int j = i + 1; j < termCount; j++) {
					
					//eliminate the second one if duplicate is found
			if (data0[i][0] == data0[j][0]){

						//reduce the table size
				termCount--;

						//replace the duplicate with the next element and move table forward
				for (int k = j; k < termCount; k++) {
					data0[k][0] = data0[k + 1][0];
					data0[k][1] = data0[k + 1][1];
					data0[k][2] = data0[k + 1][2];
				}
			}
		}
	}
	return termCount;
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
