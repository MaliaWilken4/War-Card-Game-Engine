// #include "Card.h"
// #include <iostream>
// #include <string>
// using std::string;

// Card::Card(int value, int suit) {
//     cardValue = value;
//     cardSuit = suit;

// }

// int Card::getValue() {
//     return cardValue;
// }

// int Card::getSuit() {
//     return cardSuit;
// }


// string Card::printCard() {
//     string valueStr;
//     string suitStr;

//     switch (cardValue) {          
//         case 11:
//             valueStr = "Jack";
//             break;                
//         case 12:
//             valueStr = "Queen";
//             break;
//         case 13:
//             valueStr = "King";
//             break;
//         case 14:
//             valueStr = "Ace";
//             break;
//         default:
//             valueStr = std::to_string(cardValue);
//             break;
//     }

//     switch (cardSuit) {
//         case 0:
//             suitStr = "Hearts";
//             break;
//         case 1:
//             suitStr = "Diamonds";
//             break;
//         case 2:
//             suitStr = "Clubs";
//             break;
//         case 3:
//             suitStr = "Spades";
//             break;
//     }
    
//     return valueStr + " of " + suitStr;
// }