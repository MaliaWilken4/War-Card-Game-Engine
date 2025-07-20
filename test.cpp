// #include "cards.h"
#include <iostream>
#include <ctime>
using std::cout;
using std::cin;
using std::string;

void playGame();

void settings();

int quitGame();

class Cards {   // Defines all attributes of cards
    public:
        int cardValue;
        string suit;
        

};

class Deck {    // Inherits attributes of cards + shuffle + split
    public:
        int numCards = 52;

        void shuffle() {
            srand(time(NULL));
            //generate random card between value 1-13 but once repeated 4 times that card cant be assigned anymore
            //or
            //generate random card between value 1-13 with assigned suit, but can only be used once
        }

};

class Player {    // Inherits attributes of deck + shuffle
    public:
        string name;

        
};

int main() {

    cout << "Welcome to War!\n";
    cout << "Enter your selection: \n1. Play Game\n2. Settings\n3. Quit Game\n";

    int menuInput;

    switch(menuInput) {
        case 1:
            playGame();
            break;
        case 2:
            settings();
            break;
        case 3:
            quitGame();
            cout << "Thank you for playing War!\n";
            break;
    }

    return 0;
}

void playGame() {

}
void settings() {

}
int quitGame() {
    return 0;
}

/**
    #include <cstdlib> // For rand() and srand()
    #include <ctime>   // For time()

    void fisherYatesShuffle(std::vector<int>& arr) {
        // Seed the random number generator
        std::srand(std::time(0));

        // Start from the last element and swap with a randomly selected element
        for (int i = arr.size() - 1; i > 0; --i) {
            // Generate a random index from 0 to i
            int j = std::rand() % (i + 1);

            // Swap arr[i] with arr[j]
            std::swap(arr[i], arr[j]);
        }
    }
 */