#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <string>
#include <map>

/*
  ItemTracker class
  Purpose: Load an input file of purchased items, build a frequency table,
           and expose operations to query and print results.
  Notes:
    - Header avoids a global 'using namespace std;' to prevent leaking
      names into any file that includes this header.
    - Type aliases allow us to write code without std:: prefixes.
*/
using std::map;
using std::string;

class ItemTracker {
public:
    // Load items from a text file into the frequency map
    // Returns true if the file is read successfully
    bool LoadFromFile(const string& inputFilePath);

    // Write the current frequency table to a backup file (frequency.dat)
    // Returns true if the file is written successfully
    bool WriteBackup(const string& outFilePath = "frequency.dat") const;

    // Get the frequency for a single item name (case insensitive)
    int GetFrequency(const string& item) const;

    // Print all item frequencies as: item count
    void PrintAllFrequencies() const;

    // Print a text histogram where each item shows 'symbol' repeated count times
    void PrintHistogram(char symbol = '*') const;

private:
    // Normalize text to lowercase and strip punctuation for consistent keys
    static string Normalize(const string& s);

    // Map of item -> count (sorted by key for stable output)
    map<string, int> freq_;
};

#endif
