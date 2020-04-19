#include <time.h>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "player.h"

Player::Player() {
    myName = "";
}

void Player::addCard(Card c) {
    //adds card to hand
    myHand.push_back(c);
}

void Player::bookCards(Card c1, Card c2){
    //makes a pair
    myBook.push_back(c1);
    myBook.push_back(c2);

    //remove cards from hand
    for(int i=0;i<myHand.size();i++){
        if(c2 == myHand[i]) {
            myHand.erase(myHand.begin()+i);
            break;
        }
    }
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

bool Player::checkHandForBook(Card &c1, Card &c2){
    for(int i=0;i<myHand.size();i++){
        for(int j=i+1;j<myHand.size();j++){
            if(myHand[i].getRank() == myHand[j].getRank()) {
                c1 = myHand[i];
                c2 = myHand[j];
                return true;
            }
        }
    }
    return false;
}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
bool Player::rankInHand(Card c) const {
    for(auto card : myHand){
        if(card.getRank() == c.getRank())
            return true;
    }
    return false;
}

//uses some strategy to choose one card from the player's
//hand so they can say "Do you have a 4?"
Card Player::chooseCardFromHand() const{//chooses random card from hand
    auto currentTime = (unsigned) time(NULL);
    srand(currentTime); //RANDOM SEED

    int size = getHandSize();
    int index = rand()%size;

    return myHand[index];
}

//Does the player have the card c in her hand?
//implemented but never used, unnecessary
bool Player::cardInHand(Card c) const{
    for(auto c1: myHand) {
        if (c1 == c)
            return true;
    }
    return false;
}

//Remove the card c from the hand and return it to the caller
Card Player::removeCardFromHand(Card c){
    Card n;
    for(int i=0; i<myHand.size();i++){
        if(myHand[i].getRank() == c.getRank()) { //erases cards based on rank since a player can never have 2 cards of the same rank in his hand
            n = myHand[i];
            myHand.erase(myHand.begin() + i);
            break;
        }
    }
    return n;
}

string Player::showHand() const{
    std::string hand;
    for(auto c : myHand) {
        hand.append(c.toString());
        hand.append(" ");
    }
    return hand;
}
string Player::showBooks() const{
    std::string book;
    for(auto c :myBook) {
        book.append(c.toString());
        book.append(" ");
    }
    return book;
}

int Player::getHandSize() const{
    return myHand.size();

}
int Player::getBookSize() const{
    return myBook.size();
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

//bool Player::checkHandForPair(Card &c1, Card &c2){
//    return false;
//}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
//e.g. will return true if the player has a 7d and the parameter is 7c

//bool Player:: sameRankInHand(Card c) const{
//    return false;
//}
