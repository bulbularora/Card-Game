#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <random>
#include <math.h>

using namespace std;

int rnd_num(int MIN, int MAX) {  // for random generation, used from A1
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::uniform_int_distribution<int> dist(MIN, MAX);
	return dist(rng);
}

struct card {
	int rank;  // 6 -14 (11 jack, 12 queen, 13 king, 14 ace
	int suit;  // 0-club, 1- diamond, 2- spades, 3- hearts
};

struct RemovedCards { // so the removed card can have a name(like A) and and a rank and suit(c). 
	card c;
	char remCardName;
};

char tempChar = 'A';

class CardDeck {
private:
	int uniqueCardsRem=0;  // for random generation when adding a random card.
	stack<card> cards;
	vector<card> uniqueDeck;  // unique deck that stores all unique cards at an instance.
	vector<RemovedCards>removedCards;  // A vector for all the cards we removed from each deck.
public:
	void createUniqueDeck();
	void setCards(int num);  // setter for cards by random initialization
	void printCards();   // prints all cards in deck
	void addCard();      // adds a card to the existing deck
	void removeCard();   // removes a card and saves it into a vector
	void destroyDeck();  // destroys existing deck i.e. pops all cards out the stack. Also destroys uniqueDeck and removedCards vectors for a clean slate
	int getDeckSize();   // returns the size of the stack
	void shuffleDeck();   // changes the order of the cards stack
	void cutDeck();       // cuts deck by n cards.
};


void CardDeck::createUniqueDeck() { // a vector that contains all the cards in a full deck.

	for (int i = 0; i < 4; i++) {
		for (int j = 6; j < 15; j++) {
			card c;
			c.rank = j;
			c.suit = i;
			uniqueDeck.push_back(c);
		}
	}
}

int CardDeck::getDeckSize() {   // gets the size for our stack of cards.
	return cards.size();
}

void CardDeck::setCards(int num) {
	int temp = 35;   
	while (num > 0) {

			int randomIndex = rnd_num(0, temp);    // chooses a random index b/w 0 and temp.
			cards.push(uniqueDeck[randomIndex]);   // a card from uniqueDeck is pushed into cards(stack)
			uniqueDeck.erase(uniqueDeck.begin() + randomIndex);  //the card from the above step has now been deleted from the uniqueDeck so no repetition will happen. 
			num--; // for the while loop
			uniqueCardsRem = uniqueDeck.size(); // to keep track of how many unique cards are remaining. // this is later used to add a unique card. 
			temp--; // so we dont get a segmentation fault while using uniqueDeck.
	}
		cout << "Your unique deck has been created with " << cards.size() << " cards." << endl;  // prints the size of the unique deck. 
}
	


void CardDeck::printCards() {
	vector <card> temp; // a vector for efficient printing. 

	if (cards.empty()) {
		cout << "A deck does not exist." << endl; // if no decks exists, print the message
	}

	else {
		while (!cards.empty()) { // push back in a vector for printing easily.

			card c = cards.top();  
			temp.push_back(c);  // top card gets pushed into the vector so it can be printed from bottom to top.
			cards.pop();  // empty the stack for now. 
		}
		cout << "Your deck contains the following cards (From bottom to top): "<<endl;
		for(int i = temp.size()- 1; i >= 0; i--) {        // print the contents of the stack and push into stack again without modifying the order.
			cards.push(temp[i]);      // push from the last element of temp to the first element in order to not change the order. 
			if (cards.top().rank == 6 || cards.top().rank == 7 || cards.top().rank == 8 || cards.top().rank == 9 || cards.top().rank == 10) { // if rank is a number
				switch (cards.top().suit) {  // switches the suit so it feels like a real card game.
				case 0:
					cout << cards.top().rank << " of Clubs" << endl;  // 
					break;
				case 1:
					cout << cards.top().rank << " of Diamonds" << endl;
					break;
				case 2:
					cout << cards.top().rank << " of Spades" << endl;
					break;
				case 3:
					cout << cards.top().rank << " of Hearts" << endl;
				}
			}
			else if (cards.top().rank == 11) {  // if rank is 11, prints jack
				switch (cards.top().suit) {  // switches the suit where 0-clubs, 1-diamonds, 2-spades, 3- hearts.
				case 0:
					cout << "Jack" << " of Clubs" << endl;
					break;
				case 1:
					cout << "Jack" << " of Diamonds" << endl;
					break;
				case 2:
					cout << "Jack" << " of Spades" << endl;
					break;
				case 3:
					cout << "Jack" << " of Hearts" << endl;
				}
			}
			else if (cards.top().rank == 12) {  // if rank is 12, prints Queen
				switch (cards.top().suit) {  // switches the suit
				case 0:
					cout << "Queen" << " of Clubs" << endl;
					break;
				case 1:
					cout << "Queen" << " of Diamonds" << endl;
					break;
				case 2:
					cout << "Queen" << " of Spades" << endl;
					break;
				case 3:
					cout << "Queen" << " of Hearts" << endl;
				}
			}
			else if (cards.top().rank == 13) {  // if rank is 13, prints king
				switch (cards.top().suit) { // switches the suit
				case 0:
					cout << "King" << " of Clubs" << endl;
					break;
				case 1:
					cout << "King" << " of Diamonds" << endl;
					break;
				case 2:
					cout << "King" << " of Spades" << endl;
					break;
				case 3:
					cout << "King" << " of Hearts" << endl;
				}
			}
			else if (cards.top().rank == 14) {  //n if rank is 14, prints ace
				switch (cards.top().suit) {  // switches the suit
				case 0:
					cout << "Ace" << " of Clubs" << endl;
					break;
				case 1:
					cout << "Ace" << " of Diamonds" << endl;
					break;
				case 2:
					cout << "Ace" << " of Spades" << endl;
					break;
				case 3:
					cout << "Ace" << " of Hearts" << endl;
				}
			}

		}
	}
}

void CardDeck::addCard() {
	int opt = 0;
	bool t_f = false;
	int tempIndex;
	if (cards.size() != 0) {   // if cards exist in the deck, go ahead and start the process of adding a card.
		cout << "What would you like to do? " << endl
			<< "1. Add a specific card" << endl   // where you enter a rank and suit and if it exists in the unique deck, you add it on. 
			<< "2. Add a random unique card" << endl  // adds a unique random card from uniqueDeck to our stack(cards)
			<< "3. Add a card you previously removed" << endl;   // adds a previously removed cards from cards(stack)
		cin >> opt;
		if (opt == 1) {
			int tempSuit;  // user-entered suit
			int tempRank;   // user-enetered rank
			cout << "Please enter the suit (0-Clubs, 1- Diamonds, 2- Spades, 3- Hearts) :" << endl;
			cin >> tempSuit;
			cout << "Please enter the rank ( 6 , 7 , 8 , 9 , 10 , 11(Jack) , 12(Queen) , 13(King), 14(Ace) :" << endl;
			cin >> tempRank;
			card c;  // temporary card.
			c.rank = tempRank;
			c.suit = tempSuit;
			for (unsigned int i = 0; i < uniqueDeck.size(); i++) {
				if (c.rank == uniqueDeck[i].rank && c.suit == uniqueDeck[i].suit) {  // if the user enetered rank and suit match a card from uniqueDeck
					t_f = true;   // return true and the index i
					tempIndex = i;
					break;
				}
				else {
					t_f = false;    //else return false so we can print a message saying that this card does not exist in the unique deck.
				}
			}
			if (t_f == true) {
				cards.push(uniqueDeck[tempIndex]);   // if true was returned, we push the user-entered card into our stack(cards)
				cout << "The unique card has been added to your deck." << endl;
				uniqueDeck.erase(uniqueDeck.begin() + tempIndex);  // erase the user-entered card from unique deck.
			}
			else if (t_f == false) {
				cout << "The card you entered was not found in the main, unique deck or has been already used." << endl;  // if returned false, prints a message and does not add any card to the stack.
			}
		}

		if (opt == 2) {
			int randomIndex = rnd_num(0, uniqueCardsRem-1);   // creates a random index from 
			cards.push(uniqueDeck[randomIndex]);  // pushes the random card into our stack(cards)
			cout << "A unique, random card has been added to your deck." << endl;   
			uniqueDeck.erase(uniqueDeck.begin() + randomIndex);  // deletes the previous card from our unique deck.

		}
		if (opt == 3) {
			char temp;
			bool t_f1 = false;
			cout << "Enter the name of the card you want to re-add: (Example: A, B etc.) ";  // user inputs a name that has been assigned to the card by the program. 
			cin >> temp;
			for (unsigned int i = 0; i < removedCards.size(); i++) {   // loops through the removedCards vector that contains a structire of removed card(card and name)
				if (temp == removedCards[i].remCardName) {  // checks if the name entered is equal to one of the names of cards in the removedCards vector
					cards.push(removedCards[i].c);  // if found- pushes that removed card into our stack(cards)
					cout << "Your card has been readded to the top of the deck." << endl; 
					removedCards.erase(removedCards.begin() + i);  // deletes the re-added card from the removedCards vector. 
					t_f1 = true; 
					break;
				}
				else {
					t_f1 = false; // prints a message if the card does not exist.
				}
			}
			if (t_f1 == false) {
				cout << "The card " << temp << " does not exist." << endl;
			}
		}
	}
	else {  // else prints a message that deck does not exist.
		cout << "A deck does not exist." << endl;
	}
}

void CardDeck::removeCard() {
	RemovedCards r;   // create a dummy removedCard
	if (cards.size() > 1) {   // needs at least one card to perform this action.
		r.c.rank = cards.top().rank;  // sets the top card that is to be removed to the dummy removed card.
		r.c.suit = cards.top().suit;
		cards.pop();  // removes the top card
		cout << "The top card has been removed from the deck and has been saved as " << tempChar << endl;
		r.remCardName = tempChar;
		removedCards.push_back(r);  // pushes back the top card into our removedCards vector with the suit, rank and the name so its easier to find the card later. 
		tempChar++;  // so it goes Card1 is named A, card2 is named B so on. to make it easier for the user to locate the card. 

	}
	else
		cout << "The deck only contains one card or no cards and therefore, the top card cannot be removed." << endl;  // if there is only one or no card, print message.
}

void CardDeck::cutDeck() {  
	vector<card>temp;   // creates two vectors, one for the top part and the other for the bottom part. 
	vector<card> temp2;
	unsigned int n;
	cout << "Enter the number of cards you want to cut (n): ";
	cin >> n;
	int num = cards.size() - n;  // so we divide the stack in proper vectors.
	if (n > 1) {
		if (n < cards.size()) {   // check if n is less than the total number of cards in our stack(cards)
			for (unsigned int i = 0; i < n; i++) {  // pushes the top n cards into temp
				card c;
				c = cards.top();
				temp.push_back(c);
				cards.pop();       // removes the card from the stack so we can fill it up in the new order. 
			}

			for (int i = 0; i < num; i++) { //loops through the remainder of cards in stack(cards.size() - n) and pushes into temp2.
				card c;
				c = cards.top();
				temp2.push_back(c);
				cards.pop();     // removes the card from the stack so we can fill it up in the new order. 
			}

			for (int i = temp.size() - 1; i >= 0; i--) {
				cards.push(temp[i]);       // fill it in a new order where the cards in temp are below the cards in temp2.
			}

			for (int j = temp2.size() - 1; j >= 0; j--) {
				cards.push(temp2[j]);
			}


			cout << "Your deck has been cut by " << n << " cards." << endl;
		}
		else {
			cout << "There are not enough cards to cut." << endl;  // prints if user-entered n < cards.size()
		}
	}
	else {
		cout << "To cut the deck, you need to choose a number greater than 1. Please try again."<< endl;
	}

}

void CardDeck::shuffleDeck() {
	vector <card> temp; // rather than stack, use a vector. 

	if (cards.empty()) {
		cout << "There are no cards in the deck and therefore, the deck cannot be shuffled." << endl;   // if there are no cards in the stack, prints message
	}

	else {
		while (!cards.empty()) { // push back in a vector for printing easily.
			card c = cards.top();   
			temp.push_back(c);
			cards.pop();    // pops all the cards and push into temp
		}

		for (unsigned int i = 0; i < temp.size(); i++) {
			cards.push(temp[i]);    // pushes back into temp so the order of the cards is reversed. 
		}
		cout << "The deck has been shuffled." << endl;
	}
}

void CardDeck::destroyDeck() {
	bool t_f = false;
	while (cards.size() != 0) {
		cards.pop();     // pops all cards from the stack.
		t_f = true;

	}
	if (t_f == true) {
		uniqueDeck.clear();  // the previously created uniqueDeck is cleared.
		removedCards.clear();  // he previosuly created removedCards is cleared.
		cout << "Your deck has been destroyed." << endl;
	}
	else
		cout << "A deck does not exist." << endl;
}
