
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <time.h>
#include <map>
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

//// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
int player_status(Player &p, Deck &d);
void remove(Player &p, vector<Player> &players, vector<Player> &removed);
int nextp(vector<Player> const &players, Player &current);
int get_next(vector<Player> const &players, int cur);
void player_creation(vector<Player> &players, std::string name, Deck &d);


int main() {

    Deck d;
    d.shuffle();

    vector<Player> players;
    vector<Player> removed;
    std::vector<std::string> player_names = { "Andy", "Bob", "Catarina", "Dean", "Elena" };

    int player_no = 2;

    for(int i=0;i<player_no;i++){
        player_creation(players, player_names[i], d);
    }

    auto currentTime = (unsigned) time(NULL);
    srand(currentTime); //RANDOM SEED

    //Game:
    int bookings = 0;
    int cur = 0; //initial index of current player
    int round = 0;
    int index;

    ofstream myfile("gofish_results.txt");

    if(!myfile.is_open()) {
        myfile << "Error opening file" << std::endl;
        return 0;
    }

    //check hand of each player for bookings from the deal
    Card one;
    Card two;
    for (auto &p : players) {
        while (p.checkHandForBook(one, two)) {
            myfile << p.getName() << "'s hand: " << p.showHand() <<std::endl;
            myfile << p.getName() << " has a booking from the deal" <<" with " << one.toString() << " and "<< two.toString() << std::endl;
            p.bookCards(p.removeCardFromHand(one), p.removeCardFromHand(two));
            bookings++;
        }
    }

    //player1 starts the game
    Player current = players.front(); //should be just iterators
    Player next;

    while (bookings < 26) {

        round++;

        myfile<<std::endl;

        myfile << "Round " << round << ", current bookings: " << bookings << " Deck size: "<<d.size()<<std::endl;
        myfile << "Current player: "<<current.getName()<<std::endl;

        //check current player's status
        switch (player_status(current, d)) {

            //player has cards in hands
            case 0:
                //just continue the game
                break;
                //player has empty hand and deck exists
                //player draws and passes turn to next player
            case 1: {
                auto draw = d.dealCard();
                myfile << current.getName() << " draws " << draw.toString() << std::endl;
                current.addCard(draw);
                players[cur] = current; //update current player and go to next
                index = nextp(players, current);
                cur = index;
                current = players[index];
                break;
            }
                //current player has empty hand and empty deck
            case 2:
                myfile << "Deck empty, cannot draw" << std::endl;
                remove(current, players, removed);
                myfile << current.getName() << " removed from game" << std::endl;
                index = nextp(players, current); //next player in line
                cur = index;
                current = players[index];
                break;
        }

        //choose next player randomly
        do{
            index = rand()%players.size();
        }while(players[index].getName() == players[cur].getName());

        //index = nextp(players,current);

        next = players[index]; //just iterators
        myfile << "Asked player: "<<next.getName()<<std::endl;

        //next has empty hand full deck
        if(player_status(next, d) == 1){
            Card draw = d.dealCard();
            next.addCard(draw);
            players[index] = next;
        }
        //next has empty hand empty deck
        else if(player_status(next, d) == 2){
            remove(next,players, removed);
            index = get_next(players, cur); //get new random next player
            next = players[index];
        }

        myfile << std::endl;
        myfile << current.getName() << "'s hand: " << current.showHand() << "   Bookings: " << current.showBooks() << std::endl;
        myfile << next.getName() << "'s hand: " << next.showHand() << "   Bookings: " << next.showBooks()<< std::endl;
        myfile << std::endl;

        ////Now we have our current player and next player

        //choose a card from hand to call for
        Card c = current.chooseCardFromHand();
        myfile << current.getName() << " asks " << next.getName() << "- Do you have "<< c.rankString(c.getRank()) << std::endl;

        switch (next.rankInHand(c)) {

            case true:
                myfile << next.getName() << " says - Yes, I have a " << c.rankString(c.getRank()) << std::endl;
                current.bookCards(next.removeCardFromHand(c), current.removeCardFromHand(c));
                myfile << current.getName() << " has completed a pair and booked it!"<<std::endl;

                //update current and next player in vector
                players[index] = next;
                players[cur] = current;
                bookings++;
                break;

            case false:
                myfile << next.getName() << " says - Go Fish " << std::endl;
                switch (d.size()) {
                    //deck is empty
                    case 0:
                        myfile << "No more cards in the deck" << std::endl;
                        //update current and make previous next new current
                        players[cur] = current;
                        current = next;
                        cur = index;
                        break;
                    default: {
                        Card draw = d.dealCard();
                        myfile << current.getName() << " drew " << draw.toString();

                        //if card drawn == card called player1 makes pair and plays again
                        if (draw.getRank() == c.getRank()) {
                            myfile <<" and made a booking with card drawn and plays again!"<< std::endl;
                            current.bookCards(current.removeCardFromHand(c), draw);
                            players[cur]=current;
                            bookings++;
                        }
                            //card drawn makes a pair with a card in players hand
                        else if (current.rankInHand(draw)) {
                            myfile <<" and made a booking with card drawn but doesnt play again"<< std::endl;

                            Card dummy = current.removeCardFromHand(draw); //remove paired card from hand
                            current.bookCards(draw, dummy); //book cards

                            bookings++;

                            //update current and next players
                            players[cur] = current;
                            cur = index;
                            current = next;
                        }
                            //card drawn has no pair in player1 hand
                        else {
                            myfile<<" No book"<<std::endl;
                            current.addCard(draw);
                            players[cur] = current;
                            cur = index;
                            current = next;
                        }
                        break;
                    }
                }
        }
    }

    myfile<<std::endl;
    myfile <<"All bookings have been found, game is over!"<<std::endl;
    myfile<<std::endl;

    ////for the game to end all 26 pairs must be found, therefore all players will be removed from 'players' and placed into 'removed'

    //winner is a vector of all winners in the current game if it resulted in a draw
    vector<Player> winner;
    Player dummy;
    winner.push_back(dummy);

    for(int i=0; i<players.size();i++)
        removed.push_back(players[i]);
    players.clear();

    for(auto p : removed)
        myfile<<p.getName()<<" has "<<p.getBookSize()/2<<" bookings"<<std::endl;

    for(auto c: removed){
        if(c.getBookSize() > winner[0].getBookSize())
            winner[0] = c;
        else if(c.getBookSize() == winner[0].getBookSize())
            winner.push_back(c);
    }

    if(winner.size()>1){
        myfile<<"Draw between ";
        for(auto p : winner){
            myfile<<p.getName() << " and ";
        }
        myfile<<"with " << winner[0].getBookSize()/2<< " bookings";
    } else
        myfile<<"Winner is " <<winner[0].getName()<<" with " << winner[0].getBookSize()/2<< " bookings";


    std::cout<<"Game ended successfully"<<std::endl;
    myfile.close();
    return 0;
}

void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

int player_status(Player &p, Deck &d){
    if(p.getHandSize() != 0)
        return 0;
    else if(p.getHandSize() == 0 && d.size() != 0)
        return 1;
    else
        return 2;
}

void remove(Player &p, vector<Player> &players, vector<Player> &removed){
    for(int i=0;i<players.size();i++) {
        if (players[i].getName() == p.getName()) {
            players.erase(players.begin() + i);
            removed.push_back(p);
        }
    }
}

int nextp(vector<Player> const &players, Player &current) {
    for(int i=0;i<players.size();i++){
        if(current.getName() == players[i].getName()){
            if(i != players.size() -1) {
                return i+1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

int get_next(vector<Player> const &players, int cur){
    //get a random player to be next
    int index = rand() % players.size();

    //check that next player is not current player
    while (index == cur) {
        index = rand() % players.size();
    }
    return index;
}

void player_creation(vector<Player> &players, std::string name, Deck &d){
    Player p1(name);
    dealHand(d, p1, 7);
    players.push_back(p1);
}