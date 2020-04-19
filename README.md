# GoFish

For rules explanation 	player1 = current player
						player2 = asked player
						player3 = next player in queue
Rules:
1. Each player starts with 7 cards
2. First player is always the player which was created first
3. 	a. Making a book from player2 lets you play again
	b. Making a book from a draw lets you play again if the draw is the same rank as your initial call
4. After a failed call by player1, player2 plays next
5. A player can become player2 even if they do not have cards in their hand
6. If it's a player's turn and they do not have cards in their hand they draw from the deck
7. If a player doesnt have cards in their hand and the deck is empty they are removed from the game and their final bookings is the number they had when removed from the game.

Features:
1. Can be played by 2-5 players
2. Default value is 2 players (can be changed by changing player_no in go_fish.cpp)
3. Players have absolutelly no strategy. They pick a person and a card to ask in random.


How to use:

1. type make in terminal
2. ./fish to run the game
3. text log of the game is saved in gofish_results.txt
