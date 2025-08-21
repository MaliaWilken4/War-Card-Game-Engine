//#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <algorithm>
using std::string;
using std::vector;
using std::list;
using std::cout;
using std::cin;

class Card {
    private:
        int cardValue;
        int cardSuit;

    public:
        Card(int value, int suit) {
            cardValue = value;
            cardSuit = suit;
        }

        int getValue() {
            return cardValue;
        }

        int getSuit() {
            return cardSuit;
        }

        string printCard() {
            string valueStr;
            string suitStr;

            switch (cardValue) {          
                case 11:
                    valueStr = "Jack";
                    break;                
                case 12:
                    valueStr = "Queen";
                    break;
                case 13:
                    valueStr = "King";
                    break;
                case 14:
                    valueStr = "Ace";
                    break;
                default:
                    valueStr = std::to_string(cardValue);
                    break;
            }

            switch (cardSuit) {
                case 0:
                    suitStr = "Hearts";
                    break;
                case 1:
                    suitStr = "Diamonds";
                    break;
                case 2:
                    suitStr = "Clubs";
                    break;
                case 3:
                    suitStr = "Spades";
                    break;
            }
            return valueStr + " of " + suitStr;
        }

        // Tells card class how to compare card objects
        bool operator>(const Card& other) const {
            return cardValue > other.cardValue;
        }

        bool operator<(const Card& other) const {
            return cardValue < other.cardValue;
        }

        bool operator==(const Card& other) const {
            return cardValue == other.cardValue;
        }
};

class Deck {
    private:
        vector<Card> cards;

    public:
        // Deck Constructor
        Deck() {
            for (int i = 2; i <= 14; i++) {
                for (int j = 0; j < 4; j++) {
                    Card newCard(i, j);
                    cards.push_back(newCard);
                }
            }
        }

        // Deal card function
        Card dealCard() {
            if (!cards.empty()) {
                Card top = cards.back();
                cards.pop_back();
                return top;
            }
            else {
                return Card(0,0);
            }
        }

        // Shuffle deck function
        void shuffle()      // std::shuffle uses the Fisher-Yates shuffle algorithm
        {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::shuffle(cards.begin(), cards.end(), generator);
        }
};

class Game {
    private:
        int roundCounter = 1;
        bool roundComplete = false;

        bool isRunning() {
            if (!((hand1.empty() && board1.empty() && wonPile1.empty()) || 
                   (hand2.empty() && board2.empty() && wonPile2.empty()))) {
                return true;
            }
            return false;
        }

        bool outOfCards() {
            if ((hand1.empty() && !wonPile1.empty()) || (hand2.empty() && !wonPile2.empty())) {
                return true;
            }
            return false;
        }

        // Used to convert hand into vector and shuffle for adding winPile to hand
        void shuffleHand(list<Card>& hand) {    //any list passed in would be a reference of hand
            vector<Card> temp;
            // Optional, for efficiency
            // vector<Card> temp;
            // temp.reserve(hand.size());

            // Move all cards into vector
            while (!hand.empty()) {
                temp.push_back(hand.front());
                hand.pop_front();
            }

            // Shuffle vector
            std::random_device rd;
            std::mt19937 generator(rd());
            std::shuffle(temp.begin(), temp.end(), generator);

            // Move shuffled cards back into list
            for (const Card& card : temp) {
                hand.push_back(card);
            }

            // Previous for loop is equivalent to 
            // for (size_t i = 0; i < temp.size(); ++i) {
            //     const Card& card = temp[i];
            //     // do something with card
            // }
            
        }

    public:
        list<Card> hand1;
        list<Card> hand2;

        list<Card> board1;
        list<Card> board2;

        list<Card> wonPile1;
        list<Card> wonPile2;

        string winner;

        //To show the cards in the board for a UI or printout, iterate over list<Card>

        Game()                  // Set up for game
        {
            dealHands();
            int nextRound;
            
            // Game Loop Starts Here
            while (isRunning()) {
                /*I need to put everything in an if statement to account for 
                when hand runs out of cards then add winpile and shuffle*/
                if (outOfCards()) {
                    if (hand1.empty() && !wonPile1.empty()) {
                        while (!wonPile1.empty()) {
                            hand1.push_back(wonPile1.front());
                            wonPile1.pop_front();
                            shuffleHand(hand1);
                        }
                    }
                    else if (hand2.empty() && !wonPile2.empty()) {
                        while (!wonPile2.empty()) {
                            hand2.push_back(wonPile2.front());
                            wonPile2.pop_front();
                            shuffleHand(hand2);
                        }
                    }
                }
                else {
                    //Display stats
                    cout << "\nRound " << roundCounter << ":\n";

                    //Display number of cards in players' hands
                    cout << "Player 1 has " << hand1.size() << " cards in their hand.\n";
                    cout << "Player 2 has " << hand2.size() << " cards in their hand.\n";

                    //Display number of cards in players' winPile
                    cout << "Player 1 has " << wonPile1.size() << " cards in their win pile.\n";
                    cout << "Player 2 has " << wonPile2.size() << " cards in their win pile.\n";

                    //Each player plays top card
                    cout << "Player 1 plays: " << hand1.front().printCard() << '\n';
                    cout << "Player 2 plays: " << hand2.front().printCard() << '\n';

                    Card topCard1 = hand1.front();
                    Card topCard2 = hand2.front();

                    hand1.pop_front();
                    hand2.pop_front();

                    if (topCard1 > topCard2) {
                        //Add card to player 1 win pile
                        cout << "Player 1 wins the round!\n";
                        wonPile1.push_back(topCard1);
                        wonPile1.push_back(topCard2);
                        roundCounter++;
                        roundComplete = true;
                    } 
                    else if (topCard1 < topCard2) {
                        //Add cards to player 2 win pile
                        cout << "Player 2 wins the round!\n";
                        wonPile2.push_back(topCard1);
                        wonPile2.push_back(topCard2);
                        roundCounter++;
                        roundComplete = true;
                    } 
                    else if (topCard1 == topCard2) {
                        War();      //Initiate War
                    }

                    if (roundComplete) {
                        //Provide pause between rounds
                        cout << "\nPress ENTER to proceed to the next round: ";
                        //cin.ignore(1000, '\n');
                        cin.get();
                        roundComplete = false;
                    }
                }

                //Declare Winner Logic
                if (hand1.empty() && wonPile1.empty()) {
                    winner = "2";
                    wonGame(winner);
                    exit(0);
                    break;
                }
                
                if (hand2.empty() && wonPile2.empty()) {
                    winner = "1";
                    wonGame(winner);
                    exit(0);
                    break;
                }
            }
        }

        //Hand Dealing Logic
        void dealHands() {
            Deck deck;                  // Initliaze deck object  
            deck.shuffle();             // Shuffle deck

            // Split deck between player1 and player2 hands
            for (int i = 0; i < 52; i++) {
                if (i % 2 == 0) {   //if even deal to hand1; odd to hand2
                    Card dealt = deck.dealCard();   //Calls dealCard and stores in dealt
                    hand1.push_back(dealt);         //Pushed dealt card into hand1 list
                } else {
                    Card dealt = deck.dealCard();
                    hand2.push_back(dealt);
                }
            }
        }

        //War Logic
        void War() {
            printf("\nTie! Time for War!!\n");

            // Check if players have enough cards
            if (hand1.size() < 4 || hand2.size() < 4) {
                // Check if player has at least 4 cards if not check wonPile for empty
                // if empty they lose, if has cards move to hand and continue placing cards
                if (wonPile1.empty()) {
                    winner = "2";
                    wonGame(winner);
                    exit(0);
                }
                else if (!wonPile1.empty()) {
                    //Move all wonPile1 cards to hand
                    while (!wonPile1.empty()) {
                        hand1.push_back(wonPile1.front());
                        wonPile1.pop_front();
                        shuffleHand(hand1);
                    }
                }
                else {
                    exit(1);
                }

                if (wonPile2.empty()) {
                    winner = "1";
                    wonGame(winner);
                    exit(0);
                }
                else if (!wonPile2.empty()) {
                    //Move all wonPile2 cards to hand
                    while (!wonPile2.empty()) {
                        hand2.push_back(wonPile2.front());
                        wonPile2.pop_front();
                        shuffleHand(hand2);
                    }
                }
                else {
                    exit(1);
                }
            }

            //Place 3 Cards face down in board
            cout << "Place 3 cards face down.\n";
            for (int i = 0; i < 3; i++) {
                board1.push_back(hand1.front());
                hand1.pop_front();
                cout << "Player 1 has placed card " << i + 1 << '\n';

                board2.push_back(hand2.front());
                hand2.pop_front();
                cout << "Player 2 has placed card " << i + 1 << '\n';
            }

            //Last card (fourth) is placed face up
            Card warCard1 = hand1.front();
            hand1.pop_front();
            cout << "Player 1 places " << warCard1.printCard() << " face up.\n";

            Card warCard2 = hand2.front();
            hand2.pop_front();
            cout << "Player 2 places " << warCard2.printCard() << " face up.\n";

            board1.push_back(warCard1);
            board2.push_back(warCard2);

            //Compare face cards
            if (warCard1 > warCard2) {
                while (!board1.empty()) {
                    while (!board2.empty()) {
                        wonPile1.push_back(board2.front());
                        board2.pop_front();
                    }
                    wonPile1.push_back(board1.front());
                    board1.pop_front();
                }
                cout << "Player 1 wins the round!\n";               
                roundCounter++;
                roundComplete = true;
            }
            else if (warCard2 > warCard1) {
                while (!board2.empty()) {
                    while (!board1.empty()) {
                        wonPile2.push_back(board1.front());
                        board1.pop_front();
                    }
                    wonPile2.push_back(board2.front());
                    board2.pop_front();
                }
                cout << "Player 2 wins the round!\n";
                roundCounter++;
                roundComplete = true;
            }
            else {
                War();  //Recurse for tie
            }
        }

        // Win Game Message Function
        void wonGame(string winner) {
            string winMessage = "\nPlayer " + winner + " wins the game!\n" 
                                "\nThank you for playing War!\n";
            cout << winMessage;
        }
};

class Menu {
    public:
        Menu() {
            cout << "Welcome to War!\n";
            cout << "Enter your selection: \n1. Play Game\n2. Settings\n3. Quit Game\n";

            int menuInput;

            cin >> menuInput;

            switch(menuInput) {
                case 1:
                    playGame();
                    break;
                case 2:
                    settings();
                    break;
                case 3:
                    quitGame();
                    break;
            }
        }

        void playGame() {
            Game game;
        }

        void settings() {

        }

        void quitGame() {
            cout << "\nThank you for playing War!\n";
            exit(0);
        }
};


int main() {

    Menu menu;
    Menu();

    return 0;
}