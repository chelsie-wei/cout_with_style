//
// print_with_style.cpp
// name: chelsie wei
// date: 2022/1/30
// purpose: a program that takes input through cin (temporarily, will be able to take in file inputs) and prints to
//          cout (temporarily, will be able to take in file outputs). 
//          ./typewriter typewrite [file] [output]
//          1). prints like a typewriter
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void typewriter(string word, ostream &output);
void initialize(istream &input, ostream &output);
int main (int argc, char *argv[]);

template< class Rep, class Period >
void sleep_for( const std::chrono::duration<Rep, Period>& sleep_duration );

void pleaseQuit(string message);

template<typename streamtype>
void openOrDie(streamtype &stream, string fileName);


// ./typewriter typewrite [file] [output]
int main (int argc, char *argv[])
{
    ifstream fileName;
    ofstream outstream;

    if (argc < 2 or argc > 4)
        pleaseQuit("umm there has been some issues with your command line args");
    else if (argc == 2) {
        initialize(cin, cout);
    } else if (argc == 3) {
        openOrDie(fileName, argv[2]);
        initialize(fileName, cout);
    } else if (argc == 4) {
        openOrDie(fileName, argv[2]);
        openOrDie(outstream, argv[3]);
        initialize(fileName, outstream);
    }


    return 0;
}

void initialize(istream &input, ostream &output)
{
    string toPrint;

    while (getline(input, toPrint)) {

        if (toPrint == "quit") {
            output << "bye!" << endl;
            return;
        }

        typewriter(toPrint, output);
        output << "\n";
    }

}

//      O       OOOO     OOOO   OOOOO    OOOOOO  OOOOOO     OOOOO
//     O O      O   O   O       O    O   O       O         O     
//    O O O     OOOO    O       O    O   OOOOOO  OOOOOO    O  OOOO
//   O     O    O   O   O       O    O   O       O         O     O
//  O       O   OOOO     OOOO   OOOOO    OOOOOO  O          OOOOO


//
//  O   O
//  O---O
//  O   O
//  O   O


// typewriter
// Parameters: a string that we wish to print in typewriter-style
// Purpose: takes in a string and prints the string in typewriter-style by temporarily stopping the program
// Return: returns nothing; couts result to terminal
void typewriter(string word, ostream &output)
{
     int length = word.size();
     char arr[length];

    for (int i = 0; i < length; i++) {    // to print letter by letter, separate string by char
        arr[i] = word[i];
    }

    for (int j = 0; j < length; j++) {
        output << arr[j];
        output.flush();
        this_thread::sleep_for(chrono::milliseconds(50));
    }

}

void pleaseQuit(string message)
{
    cerr << message << endl;
    exit(EXIT_FAILURE);

}

template<typename streamtype>
void openOrDie(streamtype &stream, string fileName)
{
    stream.open(fileName);

    if (not stream.is_open()) {
        cerr << "Error: cannot open file " << fileName << endl;
    }

}