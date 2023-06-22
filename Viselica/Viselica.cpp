#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Hangman {
public:
    void run() {
        srand(time(NULL));

        cout << "Welcome to Hangman!" << endl;

        vector<string> words = readWordsFromFile("words.txt");

        int wordIndex = rand() % words.size();
        string word = words[wordIndex];
        string hiddenWord(word.size(), '_');

        int tries = 6;
        bool guessed = false;
        time_t startTime = time(NULL);

        while (!guessed && tries > 0) {
            cout << "You have " << tries << " tries left." << endl;
            cout << "The word is: " << hiddenWord << endl;
            char letter = getLetterFromPlayer();
            bool letterFound = checkLetterInWord(word, hiddenWord, letter);
            if (!letterFound) {
                tries--;
            }
            guessed = checkWin(hiddenWord);
        }

        time_t endTime = time(NULL);
        int gameTime = difftime(endTime, startTime);
        cout << "The word was: " << word << endl;
        if (guessed) {
            cout << "Congratulations, you won!" << endl;
        }
        else {
            cout << "Sorry, you lost." << endl;
        }
        cout << "Game time: " << gameTime << " seconds" << endl;
        cout << "Number of tries: " << 6 - tries << endl;
    }

private:
    vector<string> readWordsFromFile(string filename) {
        vector<string> words;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                words.push_back(line);
            }
            file.close();
        }
        return words;
    }

    char getLetterFromPlayer() {
        char letter;
        cout << "Enter a letter: ";
        cin >> letter;
        return letter;
    }

    bool checkLetterInWord(string word, string& hiddenWord, char letter) {
        bool letterFound = false;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == letter) {
                hiddenWord[i] = letter;
                letterFound = true;
            }
        }
        if (letterFound) {
            cout << "The letter " << letter << " is in the word." << endl;
            cout << "The word is now: " << hiddenWord << endl;
        }
        else {
            cout << "Sorry, the letter " << letter << " is not in the word." << endl;
        }
        return letterFound;
    }

    bool checkWin(string hiddenWord) {
        for (int i = 0; i < hiddenWord.length(); i++) {
            if (hiddenWord[i] == '_') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Hangman game;
    game.run();
    return 0;
}
