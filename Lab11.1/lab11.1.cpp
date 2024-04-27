#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

void CreateNumbersFile(const string& fname) {
    ofstream fout(fname);
    if (!fout.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    cout << "Enter numbers:\n";
    string line;
    getline(cin, line);
    istringstream iss(line);
    int num;
    while (iss >> num) {
        fout.write(reinterpret_cast<char*>(&num), sizeof(num));
    }

    fout.close();
}

void CalculateAverages(const string& input_fname, double& avgMinMax, double& overallAvg) {
    ifstream fin(input_fname, ios::binary);
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    int num;
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    int sum = 0;
    int count = 0;
    while (fin.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (num > max) max = num;
        if (num < min) min = num;
        sum += num;
        count++;
    }
    fin.close();

    if (count == 0) {
        avgMinMax = 0.0;
        overallAvg = 0.0;
        return;
    }

    avgMinMax = (max + min) / 2.0;
    overallAvg = static_cast<double>(sum) / count;
}

void WriteAveragesToFile(const string& output_fname, double avgMinMax, double overallAvg) {
    ofstream fout(output_fname, ios::binary);
    if (!fout.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    fout.write(reinterpret_cast<char*>(&avgMinMax), sizeof(avgMinMax));
    fout.write(reinterpret_cast<char*>(&overallAvg), sizeof(overallAvg));
    fout.close();
}

void ReadAveragesFromFile(const string& fname, double& avgMinMax, double& overallAvg) {
    ifstream fin(fname, ios::binary);
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    fin.read(reinterpret_cast<char*>(&avgMinMax), sizeof(avgMinMax));
    fin.read(reinterpret_cast<char*>(&overallAvg), sizeof(overallAvg));
    fin.close();
}

int main() {
    string input_file, output_file;

    cout << "Enter input file name: ";
    cin >> input_file;
    cout << "Enter output file name: ";
    cin >> output_file;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    CreateNumbersFile(input_file);

    double avgMinMax = 0.0, overallAvg = 0.0;
    CalculateAverages(input_file, avgMinMax, overallAvg);
    WriteAveragesToFile(output_file, avgMinMax, overallAvg);

    double readAvgMinMax, readOverallAvg;
    ReadAveragesFromFile(output_file, readAvgMinMax, readOverallAvg);

    cout << "Average of max and min components: " << readAvgMinMax << endl;
    cout << "Average of all components: " << readOverallAvg << endl;

    return 0;
}
