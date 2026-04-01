#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <functional>
#include <unordered_map>

#include "BruteForce.hpp"

using namespace std;

pair<vector<string>, vector<string>> readFile(string filename)
{
    if (!filesystem::exists(filename))
    {
        cout << "File not exist!\n";
        exit(0);
    }

    ifstream fs(filename, ios::in);

    int R, C;
    if (!(fs >> R >> C)) return {};

    vector<string> grid(R, string(C,'\0'));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            fs >> grid[i][j];
        }
    }

    int K;
    fs >> K;
    vector<string> keywords(K);
    for (int i = 0; i < K; ++i) {
        fs >> keywords[i];
    }
    return { grid, keywords };
}

void printStats(string filename, string name, vector<string>& keywords, const vector<vector<tuple<int, int, int, int>>>& occurrences, double time, double comp)
{
    fstream fs(filename, ios::out | ios::trunc);

    int K = keywords.size();

    for (int k = 0; k < K; ++k) {
        cout << keywords[k] << ": ";
        fs << keywords[k] << ": ";
        if (occurrences[k].empty()) {
            cout << "not found" << endl;
            fs << "not found" << endl;
        }
        else {
            for (size_t i = 0; i < occurrences[k].size(); ++i) {
                auto [r1, c1, r2, c2] = occurrences[k][i];
                cout << "(" << r1 << ", " << c1 << ") -> (" << r2 << ", " << c2 << ")";
                fs << "(" << r1 << ", " << c1 << ") -> (" << r2 << ", " << c2 << ")";
                if (i < occurrences[k].size() - 1) {
                    cout << "; ";
                    fs << "; ";
                }
            }
            cout << endl;
            fs << endl;
        }
    }

    cout << "-----------------------------------" << endl;
    cout << "Algorithm: "<< name << endl;
    cout << "Comparisons: " << (unsigned long long)comp << endl;
    cout << fixed << setprecision(2) << "Execution Time: " << time << " ms" << endl;
    fs << "-----------------------------------" << endl;
    fs << "Algorithm: "<< name << endl;
    fs << "Comparisons: " << (unsigned long long)comp << endl;
    fs << fixed << setprecision(2) << "Execution Time: " << time << " ms" << endl;
}

void printHelp()
{
    cout << R"(
Usage: 01.exe -a [ algorithm ] -i [ input_file ] -o [ output_file ]
Options:
    -a [algorithm]      Select algorithm : bf, rk, kmp, bm
    -i [input_file]     Path to user - provided data file
    -o [output_file]    Path to the result output file
Example:
    01.exe -a kmp -i puzzle.txt -o solution.txt
)";
}

int main(int args, char** argv)
{
    if (args > 7) { printHelp(); return 0; }

    if (strcmp(argv[1], "-a") != 0) { printHelp(); return 0; }
    if (strcmp(argv[3], "-i") != 0) { printHelp(); return 0; }
    if (strcmp(argv[5], "-o") != 0) { printHelp(); return 0; }

    auto tmp = bruteForce;
    
    unordered_map<string, 
        pair<string, 
        function<
        tuple<vector<vector<tuple<int, int, int, int>>>, double, double>(const vector<string>& grid, const vector<string>& keywords)>
        >> algo;

    algo.insert({ "bf", { "Brute Force", bruteForce } });

    if(algo.count(argv[2]) == 0) { printHelp(); return 0; }
    if(!filesystem::exists(argv[4])) { printHelp(); return 0; }

    auto resAlgo = algo[argv[2]];

    auto input = readFile(argv[4]);

    auto res = resAlgo.second(input.first, input.second);

    printStats(argv[6], resAlgo.first, input.second, get<0>(res), get<1>(res), get<2>(res));
}