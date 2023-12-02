# ICS_CP_OthelloCrafters
Team members names: Radhika Agarwal, Reshma Maurya, Nishu Verma, Sarah Fatima

1. inputs players' name, there are 2 players, one is O other is X
2. board prints which is 8x8, starting 4 cells are filled initially
3. we add locations in x,y coordinate system
4. each player inputs locations alternatively
5. it checks if the input is valid using check_valid
6. opponents disc should get sandwiched. this is checked using func
7. if the disc is sandwiched it gets flipped
8. the func is called 8 times, to check in 8 directions
9. declare result checks if the total 64 cells are filled
10. through this, we get an option to restart or exit
11. apart from other options of ending game, there is a function endgame which checks if all the cells are occupied by a single player
12. if a player is not able to sandwich any disc in any direction, they need to pass the turn to the next player
13. this is done using func as well
14. if both the players are unable to sandwich their respective opponent's disc, the game ends providing exit and restart option
