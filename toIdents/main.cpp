#include <iostream>
#include <fstream>
#include <vector>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;
using namespace std;


string trim(const string& str)
{
    const string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string trimLeft(const string& str)
{
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == string::npos)
        return ""; // no content
    return str.substr(strBegin, str.length() - strBegin);
}

string trimRight(const string& str)
{
    const auto strEnd = str.find_last_not_of(" \t");
    if (strEnd == string::npos)
        return ""; // no content
    return str.substr(0, strEnd + 1);
}

vector<string> readLines(string filename)
{
    ifstream infile(filename);
    vector<string> v;
    string line;
    bool good;
    do {
        good = getline(infile, line).good();
        if (!good && line == "") break;
        v.push_back(trim(line));
    } while (good);
    if (v.empty()) throw "empty file";
    return v;
}

void writeLines(const string& filename, vector<string>& lines) {
    ofstream outfile(filename);
    for (string& line: lines)
        outfile << line << endl;
}

string ProcessLineMy(const string& line) {
    int pos = line.find("->");
    if (pos!=1 && pos!=2) throw "not found ->";
    string result = line.substr(0,pos);
    result += " ->";
    string rhs = line.substr(pos+2);
    if (rhs.empty()||rhs=="eps")
        result += " epsilon";
    else {
        int n = 0;
        while (n < rhs.size()) {
            char c = rhs[n];
            if (c>='A' && c<='Z' && n+1 < rhs.size() && rhs[n+1]=='\''
                || c=='i' && n+1 < rhs.size() && rhs[n+1]=='d') {
                result += " " + string(1,c) + string(1,rhs[n+1]);
                n++;
            }
            else result += " " + string(1,c);
            n++;
        }
    }
    return result;
}

string ProcessLine(const string& line) {
    if (line.empty())
        return line;
    else if (line[0]==';')
        return line;
    else if (line[0]=='#' || line[0]==-17) {
        string res = line;
        res[0] = ';';
        return res;
    }
    else if (line.size()>=2 && line[0]=='/' && line[1]=='/')
        //cout << line << endl;
        throw "other format: ebnf";
    else {
        int pos = line.find("->");
        if (pos == string::npos)
            throw "other format: ebnf";
        else
            return ProcessLineMy(line);
    }
}

vector<string> Process(const vector<string>& v) {
    if (v[0].find("//")==0) return {};
    vector<string> result;
    for (auto &line: v)
        result.push_back(ProcessLine(line));
    return result;
}

void ProcessDir(string dir) {
    fs::path p (dir);
    fs::directory_iterator end_itr;
    // cycle through the directory
    for (fs::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            string current_file = itr->path().string();
            cout << current_file << endl;
            vector<string> v = readLines(current_file);
            vector<string> vres = Process(v);
            //writeLines("../g025c.dat",vres);
            if (vres.empty())
                ;//fs::copy(current_file, "../3/"+itr->path().filename().string());
            else
                writeLines("../2/"+itr->path().filename().string(), vres);
        }
    }
}

int main() {
    ProcessDir("../1");
    return 0;
}
