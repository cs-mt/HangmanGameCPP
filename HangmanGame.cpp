// Copyright (C) cs-mt github.com/cs-mt
// 2023-07-26 08:55 PM

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;

vector<string> getWords()
{
    ifstream infile("WordList.txt");

    vector<string> words;

    string line;
    while (getline(infile, line))
    {
        words.push_back(line);
    }

    return words;
}

string randomElement(vector<string> v)
{
    vector<string> out;
    sample(v.begin(), v.end(), back_inserter(out), 1, mt19937{random_device{}()});
    return out[0];
}

int main()
{
    vector<string> words = getWords();
    string randWord = randomElement(words);
    randWord.pop_back();

    int wordLength = randWord.length();

    string hangmanString = "";
    int attempts = 0;

    for (int i = 0; i < wordLength; i++)
    {
        hangmanString += "_";
    }

    cout << "======= Hangman Game =======" << endl
         << endl;
    cout << "Try to guess the word or a single letter within the word." << endl;
    cout << endl;

    while (true)
    {
        cout << "Attempts: " + to_string(attempts) << endl;
        cout << hangmanString << endl;

        cout << "Your guess: ";

        string prediction;
        cin >> prediction;
        ++attempts;

    
        if (prediction.length() == 1)
        {
            int count = 0;

            // Letter prediction
            for (int i = 0; i < randWord.length(); i++)
            {
                char letter = randWord[i];
                if (letter == prediction[0])
                {
                    // Correct guess, replace the i-th char with the prediction in the hangman string.
                    hangmanString[i] = letter;
                }
                
                if(hangmanString[i] == '_'){
                    ++count; 
                }             
            }

            if(count == 0){
                break;
            }
            
        }
        else
        {
            // Whole word prediction
            if (prediction == randWord)
            {
                hangmanString = randWord;
                break;
            }
        }
    }

    cout << endl << endl << "Attempts: " << attempts << endl;
    cout << hangmanString << endl << endl;


    cout << "Congrats! You won with " << attempts << " attempts!";

    return 0;
}
