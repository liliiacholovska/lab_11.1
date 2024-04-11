#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

void CreateDataFile(const string& fname) {
    ofstream fout(fname);
    if (!fout.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    cout << "Enter numbers:\n";
    string line;
    getline(cin, line);  
    fout << line;

    fout.close();
}

void ProcessDataAndWriteAverages(const string& inputFileName, const string& outputFileName) {
    ifstream fin(inputFileName);
    ofstream fout(outputFileName);
    if (!fin.is_open() || !fout.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    int num, sum = 0, count = 0;
    int maxNum = numeric_limits<int>::min();
    int minNum = numeric_limits<int>::max();
    while (fin >> num) {
        if (num > maxNum) maxNum = num;
        if (num < minNum) minNum = num;
        sum += num;
        ++count;
    }

    double averageAll = count > 0 ? static_cast<double>(sum) / count : 0.0;
    double averageMinMax = count > 0 ? (maxNum + minNum) / 2.0 : 0.0;

    fout << "Average of max and min components: " << averageMinMax << endl;
    fout << "Average of all components: " << averageAll << endl;

    fin.close();
    fout.close();
}

void PrintFileContents(const string& fname) {
    ifstream fin(fname);
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }

    cout << "Contents of " << fname << ":" << endl;
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

int main() {
    string inputFileName, outputFileName;
    cout << "Enter input file name: ";
    cin >> inputFileName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    CreateDataFile(inputFileName);

    cout << "Enter output file name: ";
    cin >> outputFileName;

    ProcessDataAndWriteAverages(inputFileName, outputFileName);

    PrintFileContents(outputFileName);

    return 0;
}