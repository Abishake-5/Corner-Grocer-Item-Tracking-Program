/*
  Name:        Abishake Shanker
  Date:        October 19, 2025
  Description: Corner Grocer Item Tracking Program (CS 210 Project Three)
               Reads an input file of purchased items, builds a frequency
               table, writes a backup file (frequency.dat), and provides
               a menu with:
                 1) Single item frequency lookup
                 2) Print all item frequencies
                 3) Print histogram
                 4) Exit
               Design centers on the ItemTracker class for clarity and reuse.
*/

#include <iostream>
#include <limits>
#include "ItemTracker.h"

// Use namespace in implementation file as requested
using namespace std;

// Show the main menu to the user
static void ShowMenu() {
    cout << "\nCorner Grocer Item Tracker\n";
    cout << "1. Look up frequency for a single item\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "Choose an option [1-4]: ";
}

// Safely read a menu choice from 1 to 4
static int ReadMenuChoice() {
    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Invalid selection. Enter a number from 1 to 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // Input file must be in the working directory
    const string kInputFile = "CS210_Project_Three_Input_File.txt";

    cout << "Welcome to the Corner Grocer Item Tracker, developed by Abishake Shanker.\n";

    ItemTracker tracker;

    // Load data at startup
    if (!tracker.LoadFromFile(kInputFile)) {
        cout << "Program will exit because input could not be loaded.\n";
        return 1;
    }

    // Write frequency.dat for backup
    tracker.WriteBackup("frequency.dat");

    // Main interaction loop
    while (true) {
        ShowMenu();
        int choice = ReadMenuChoice();

        if (choice == 1) {
            cout << "Enter item to look up: ";
            string query;
            getline(cin, query);

            int count = tracker.GetFrequency(query);
            if (count == 0) {
                cout << "Item not found.\n";
            }
            else {
                cout << query << " " << count << "\n";
            }

        }
        else if (choice == 2) {
            tracker.PrintAllFrequencies();

        }
        else if (choice == 3) {
            tracker.PrintHistogram('*');

        }
        else if (choice == 4) {
            cout << "Thank you for using Corner Grocer Tracker. Goodbye.\n";
            break;
        }
    }

    return 0;
}
