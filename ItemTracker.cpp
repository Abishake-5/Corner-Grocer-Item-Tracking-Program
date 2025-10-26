#include "ItemTracker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

// Use namespace in implementation file as requested
using namespace std;

string ItemTracker::Normalize(const string& s) {
    // Build a lowercase, alphanumeric plus space only string
    string t;
    t.reserve(s.size());
    for (unsigned char ch : s) {
        if (isalnum(ch)) {
            t.push_back(static_cast<char>(tolower(ch)));
        }
        else if (isspace(ch)) {
            t.push_back(' ');
        }
        // All other characters are skipped
    }

    // Trim leading and trailing spaces
    auto start = t.find_first_not_of(' ');
    if (start == string::npos) return "";
    auto end = t.find_last_not_of(' ');
    t = t.substr(start, end - start + 1);
    return t;
}

bool ItemTracker::LoadFromFile(const string& inputFilePath) {
    // Clear any previous state
    freq_.clear();

    ifstream in(inputFilePath);
    if (!in.is_open()) {
        cerr << "Error: Could not open input file: " << inputFilePath << "\n";
        return false;
    }

    // Read file line by line and split into tokens
    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string token;

        // Each token is an item name or part of it
        while (iss >> token) {
            string key = Normalize(token);
            if (!key.empty()) {
                ++freq_[key]; // Increment count for this item
            }
        }
    }

    if (freq_.empty()) {
        cerr << "Warning: Input file contained no recognizable items.\n";
    }
    return true;
}

bool ItemTracker::WriteBackup(const string& outFilePath) const {
    ofstream out(outFilePath);
    if (!out.is_open()) {
        cerr << "Error: Could not write to backup file: " << outFilePath << "\n";
        return false;
    }

    // One line per entry: item count
    for (const auto& kv : freq_) {
        out << kv.first << " " << kv.second << "\n";
    }
    return true;
}

int ItemTracker::GetFrequency(const string& item) const {
    string key = Normalize(item);
    auto it = freq_.find(key);
    if (it == freq_.end()) return 0;
    return it->second;
}

void ItemTracker::PrintAllFrequencies() const {
    if (freq_.empty()) {
        cout << "No data loaded.\n";
        return;
    }

    // Map iteration prints keys in sorted order
    for (const auto& kv : freq_) {
        cout << kv.first << " " << kv.second << "\n";
    }
}

void ItemTracker::PrintHistogram(char symbol) const {
    if (freq_.empty()) {
        cout << "No data loaded.\n";
        return;
    }

    for (const auto& kv : freq_) {
        cout << kv.first << " ";
        for (int i = 0; i < kv.second; ++i) {
            cout << symbol;
        }
        cout << "\n";
    }
}
