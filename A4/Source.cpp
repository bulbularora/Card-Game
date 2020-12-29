#include "A4.h"


using namespace std;


int main() {
	
	CardDeck deck;
	cout << "Welcome to our card game!" << endl;
	int mainOpt =0;   //  option variable for console
	
	while (mainOpt != 8) {
		cout <<endl<< "Please select one of the following options: " << endl
			<< "1. Create a new deck with upto 36 unique cards!" << endl // use the setCards() function to create a new deck to play with
			<< "2. Add a card to deck " << endl // add a specific, random, or a previously removed card.
			<< "3. Remove the top card from deck " << endl // if there are at least 2 cards remaining, removes a card from deck. 
			<< "4. Cut deck by n cards " << endl  // enter n and the cutDeck() function cuts your deck by n cards.
			<< "5. Display all cards in deck" << endl // prints all cards in the playing stack
			<< "6. Shuffle deck" << endl  // changes the order of the stack.
			<< "7. Destroy deck" << endl  // destroys your playing deck, unique deck and all removed cards. so when you create a new deck, you can choose from all 36 cards again.
			<< "8. End card game" << endl;  //stops the program.
		cin >> mainOpt;
		if (mainOpt == 1) {
			if (deck.getDeckSize() == 0) {    // if the there are no existing cards in the deck, add cards
				cout << "Please provide the number of cards you want to add to the deck: ";
				int numCards;
				cin >> numCards;
				deck.createUniqueDeck();
				deck.setCards(numCards);
				deck.printCards();
			}
			else {
				cout << "A deck already exists. Please choose other options to play the game!" << endl;
			}
		}
		
		if (mainOpt == 2) {
			deck.addCard();   // gives 3 options- adding a specific cards, adding a random card and adding a removed card
		}

		if (mainOpt == 3) {
			
			deck.removeCard();  // removes the card and saves it
		}

		if (mainOpt == 4) {
			if (deck.getDeckSize() != 0) {
				deck.cutDeck();     // cuts deck by n cards
			}
			else cout << "There are no cards in deck." << endl;
		}

		if (mainOpt == 5) {
			if (deck.getDeckSize() != 0) {
				cout << "The deck is made up of " << deck.getDeckSize() << " cards." << endl;	
			}
			deck.printCards();   // if cards exist, prints all the cards in deck
		}

		if (mainOpt == 6) {
			deck.shuffleDeck();  // reverses the order of the cards
		}

		if (mainOpt == 7) {
			deck.destroyDeck();    //deletes all cards in deck 
			
		}

		if (mainOpt == 8) {
			cout << "Thank you for playing! Have a great day." << endl;
		}

	}
	
	
	

}