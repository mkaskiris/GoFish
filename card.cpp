

#include "card.h"

Card::Card(){
    myRank = 1;
    mySuit = spades;
}

Card::Card(int rank, Suit suit){
    myRank = rank;
    mySuit = suit;
}

string Card::toString() const {
    return rankString(myRank) + suitString(mySuit);
}

//not used
bool Card:: sameSuitAs(const Card& c) const{
    return c.mySuit == this->mySuit;
}  // true if suit same as c

int Card:: getRank() const {
    return myRank;
}// return rank, 1..13

string Card:: suitString(Suit s) const{
    switch(s){
        case spades:
            return  "s";
        case hearts:
            return "h";
        case diamonds:
            return "d";
        default:
            return "c";
    }
}// return "s", "h",...

string Card::rankString(int r) const{
    switch(r){
        case 11:
            return "J";
        case 12:
            return "Q";
        case 13:
            return "K";
        default:
            return to_string(r);
    }
}  // return "A", "2", ..."Q"


bool Card:: operator == (const Card& rhs) const{
    return rhs.myRank == myRank && mySuit == rhs.mySuit;
}
//uncesessary
bool Card:: operator != (const Card& rhs) const{
    return rhs.myRank != myRank || mySuit != rhs.mySuit;
}