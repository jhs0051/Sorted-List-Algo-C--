#include <fstream>
#include <iostream>
using namespace std;

/* declare your user-defined functions
do not forget to describe each function */
int combine_and_sort(int iArray1[], int iArray1_size, int iArray2[], int iArray2_size, int arrayOut[]);
int read_file(int input_array[], ifstream& instream);
void writefile(int arrayOut[], int newArrayOut);
void merge(int array[], int x, int y, int z);
void merge_sort(int array[], int x, int z);

/* Max size of arrays as shown by handout */
const int MAX_SIZE = 100;

/* sorts the data in given files */
void merge_sort(int array[], int x, int y) 
{ 
    if (x < y) { 
        int merged = (x + (y - x) / 2); 
   
        merge_sort(array, x, merged); 
        merge_sort(array, (merged + 1), y); 
        merge(array, x, merged, y); 
    } 
}

/* combines the numbers from the two input files and sorts them into the output file. */
int combine_and_sort(int iArray1[], int iArray1_size, int iArray2[], int iArray2_size, int arrayOut[]) {
    int newArrayOut = (iArray1_size + iArray2_size);

    for (int i = 0; i < iArray1_size; i++) {
        arrayOut[i] = iArray1[i];
            for (int i = 0; i < iArray2_size; i++) {
                arrayOut[i + iArray1_size] = iArray2[i];
        }
    }
    merge_sort(arrayOut, 0, newArrayOut - 1);
    return newArrayOut;
}

/* Merge the numbers in two specified files and write all the numbers 
* to a specified third file sorted in ascending order.
* Return: 1 Program completed successfully. (int) */
void merge(int array[], int x, int y, int z) { 
    int firstNum = (y - x + 1); 
    int secondNum = (z - y); 
    int * newFirstNum = new int[firstNum];
    int * newSecondNum = new int[secondNum];
    int i;
    int j;
    int k; 

    for (i = 0; i < firstNum; i++) {
        newFirstNum[i] = array[x + i];
            for (j = 0; j < secondNum; j++) {
                newSecondNum[j] = array[y + 1 + j];
        } 
    }
  
    i = 0; j = 0; k = x;

    while (i < firstNum && j < secondNum) { 
        if (newSecondNum[j] >= newFirstNum[i]) { 
            array[k] = newFirstNum[i]; 
            i++; 
        } 
        else { 
            array[k] = newSecondNum[j]; 
            j++; 
        } 
        k++; 
    }
  
    while (i < firstNum) { 
            array[k] = newFirstNum[i]; i++; k++; 
        while (j < secondNum) { 
            array[k] = newSecondNum[j]; j++; k++; 
       }
    }
} 

int read_file(int input_array[], ifstream& instream) {
    int pointer = 0;

    instream >> input_array[pointer];
    while (!instream.eof()) {
        pointer++;
        instream >> input_array[pointer];
    }
    return pointer;
}

/* Asks users for output file name */
void writefile(int arrayOut[], int newArrayOut) {
    ofstream outstream; string fileOutput;
    cout << "Enter the output file name: ";
    cin >> fileOutput;

    /* Copies new data over to the output file and closes it */
    outstream.open((char*)fileOutput.c_str());
    for (int i = 0; i < newArrayOut; i++) {
        outstream << arrayOut[i] << "\n";
    }
    outstream.close();
    cout << "*** Please check the new file - " << fileOutput << " ***\n";
}

/* declare your variables
 * used varibale names from project 3 handout */
int main() {
    int iArray1[MAX_SIZE];
    int iArray1_size = 0;
    int iArray2[MAX_SIZE];
    int iArray2_size = 0;
    
    /* Input file stream. (ifstream) */
    ifstream instream; string firstFile;
    bool firstValidFile = false;
    
    /* Get name of file one + starts program output with hello message */
    cout << endl << "*** Welcome to Jon's sorting program ***\n";
    while (firstValidFile == false) {
        cout << "Enter the first input file name: ";
        cin >> firstFile;
        instream.open((char*)firstFile.c_str());
        firstValidFile = instream.good();
        if (firstValidFile == true) {
            cout << "File input is invalid, please enter a valid input file name\n" << endl;
        }
    }
    
    /* Closes and display numbers from file one. */
    iArray1_size = read_file(iArray1, instream);
    instream.close();
    cout << "The list of " << iArray1_size << " numbers in file " << firstFile << " is:\n";
    for (int i = 0; i < iArray1_size; i++) {
        cout << iArray1[i] << "\n";
    }
    cout << endl;

    /* Get name of file two. */
    string secondFile;
    bool secondValidFile = false;
    while (secondValidFile == false) {
        cout << "Enter the second input file name: ";
        cin >> secondFile;
        instream.open((char*)secondFile.c_str());
        secondValidFile = instream.good();
        if (secondValidFile == true) {
            cout << "File input is invalid, please enter a valid input file name\n" << endl;
        }
    }
    
    /* Closes and display numbers from file two. */
    iArray2_size = read_file(iArray2, instream);
    instream.close();
    cout << "The list of " << iArray2_size << " numbers in file " << secondFile << " is:\n";
    for (int i = 0; i < iArray2_size; i++) {
        cout << iArray2[i] << "\n";
    }
    cout << endl;

    /* Write combined arrays to output file. */
    int arrayOut[MAX_SIZE];
    int newArrayOut = combine_and_sort(iArray1, iArray1_size, iArray2, iArray2_size, arrayOut);
    cout << "The sorted list of " << newArrayOut << " numbers is:";
    for (int i = 0; i < newArrayOut; i++) {
        cout << " " << arrayOut[i];
    }
    cout << endl;
    writefile(arrayOut, newArrayOut);

    /* End Program */
    cout << "*** Goodbye. ***" << endl;
    return 0;
}