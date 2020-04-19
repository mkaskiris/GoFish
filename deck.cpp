#include <time.h>
#include "card.h"
#include "deck.h"

Deck::Deck(){//new sorted deck
    for(int i=1; i<14;i++) {
        Card d(i, Card::spades);
        myCards[i-1] = d;
    }
    for(int i=1; i<14;i++){
        Card d(i,Card::hearts);
    myCards[13+i-1] = d;
}
    for(int i=1; i<14;i++){
        Card d(i,Card::diamonds);
        myCards[26+i-1] = d;
    }
    for(int i=1; i<14;i++){
        Card d(i,Card::clubs);
        myCards[39+i-1] = d;
    }
    myIndex = 52;
}

void Deck::shuffle() {
    myIndex = SIZE;
    int i = 0;
    int index, index2;

    auto currentTime = (unsigned) time(NULL);
    srand(currentTime); //RANDOM SEED

    while(i < SIZE*10){
        index = rand()%SIZE;
        index2 = rand()%SIZE;
        swap(myCards[index], myCards[index2]);
        i++;
    }
    //use a swap function with rand()
}

Card Deck::dealCard() {
    Card cur = myCards[myIndex - 1];
    myIndex--;
    return cur;
}

int Deck::size() const {
    return myIndex;
}
