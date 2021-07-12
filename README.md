# Chess
1)Description of The Application:

Chess is a board game for two players. It is played in a square board, made of 64 smaller squares, with eight squares on each side. Each player starts with sixteen pieces: eight pawns, two knights, two bishops, two rooks, one queen and one king. The goal of the game is for each player to try and checkmate the king of the opponent. “CHECKMATE” is a threat ('check') to the opposing king which no move can stop. It ends the game. 

The Features it provides:

1)	On each player’s turn the user is asked to choose from these 5 options:
-Play (move): If the move is invalid a message will appear to him in order to enter another valid one. If the move is valid the piece will be moved.
-Save: The user can save the game at any time and continue that game at another time.
-Undo: The game can be undone till the first move.
-Redo: All the undone moves can be returned till the player chooses to play a new    move.
-Exit(quit): The user can exit the game at any time.
2)	If one of the two players whose turn it is to move has no legal move and is not in check, it is called “STALEMATE”, which make the game ends directly in a DRAW.
3)	If one of the two players whose turn it is to move has no legal moves and it is in “CHECK!”,
It is called “CHECKMATE” which means that the other player wins and the game ends.
4)	If there is a “DEAD POSITION” which means (K vs K) or (K vs N&K) or (K vs B&K) or (K&B vs K&B (B of same color squares)) or vice versa -> all of this means that no one of the two players can win so it will be dead position and the game ends directly in a DRAW.
5)	The eaten pieces by the white player and the eaten pieces by the black player are displayed in each turn.
6)	When the user starts the game he is asked to choose one of 3 choices: 
Either to start a new game or to load a previous saved game or to exit.
7)	If one of the players’ pawn’s went to the last row opposite to him, it is called promotion case, 
 and that player has to promote this pawn to another piece from those 4 pieces only (queen, knight, bishop, and rook).

2)DESIGN OVERVIEW:

-The first user interface is a 3 options menu that the user should choose one of them (new game, load a previous game, and exit).
-If the user wants to load a previous game, a message will appear to him to enter the saved file’s name. if the file’s name is not correct or found it will return a message “NOT FOUND” and asks him to enter a correct file name.
-The game interface is board containing 64 places and 32 letters, the capital letters are for the white pieces and the small ones are for the black pieces. There are numbers from 1 to 8 on both sides of the board indicating the row index and letters from a to h above and below the board indicating the column index. So when the user wants to play a move he will write the indices of the place of the piece he wants to move followed by the place he wants this piece to be moved to (ex: a7 a5) and he should enter the letter in small letter (a not A). The eaten pieces by the black and white players will be displayed also.
-If there is a king in a check a message will appear above “CHECK!” and it will not disappear until that king’s owner play a valid safe move. If that player has no legal moves to play, then the game will end in CHECKMATE and the other player will be the winner. (And for kind of celebrating balloons will appear).
-If there is a stalemate (no legal moves for a player who is not in check), or a dead position the game will end in a DRAW. 
-If the it’s time for promotion, a message will appear to the player who last move his pawn telling him what he wants to promotes him pawn to, and the player should enter either queen, rook, bishop, or knight (only the first letter of their names as Q, b, r, ...etc capital or small it will be handled according to the player’s color).
-if the user wants to save the game he wiil choose save and enter then the file name or if he wants to just exit he will choose exit and the game will end.
-The user can undo by enter “U” or redo by entering “R”.


3)ASSUMPTIONS:

There is only one assumption is that the player undoes the other player’s move, then the turn is shifted to the other player. (ex: if it is the white’s turn and he entered undo, then the previous black’s move is undone and it’s black’s turn to choose what to play or to do).

4)DATA STRUCTURE:

-chessboard: For chess board, a 2D array (8*8) is used to store all the positions of all the pieces, if the position is not occupied by any piece it will be ‘-‘ or ‘.’ According to the color of that square.

-eatenB: A 1D array (16) is used to store the white pieces eaten by the black player.

-eatenW: A 1D array (16) is used to store the black pieces eaten by the white player.

-undoboard: A 3D array (20000*8*8) is used to store the chess board in each turn during the game in order to be used in the undo function (to redo and undo easily).  

-eatenb: A 2D array (20000*16) is used to store the eaten white pieces eaten by the black player in each turn during the game in order to be used in the undoeat function (to redo and undo easily).

-eatenw: A 2D array (20000*16) is used to store the eaten black pieces eaten by the white player in each turn during the game in order to be used in the undoeat function (to redo and undo easily).


5)IMPORTANT FUNCTIONS:

1- undoeat: The function is to store the eaten white and black pieces after each turn to be used in the redo and undo parts.

2- undo: The function is to store the chess board after each turn to be used in the redo and undo parts.

3-save: This function takes a string from the user as a file name for the game the user wants to save. Then we open that file and save the last chessboard array, the eaten pieces of both players, and the next turn’s player. Then we close this file.

4-load: This function takes a string from the user as a file name, and check if that file is found, if not it will give a message not found and to enter another correct name of the file. Then this found file will be opened, then we will get the chessboard contents, the eaten pieces of each player, and the next turn’s player which will return true if it is the black’s turn or false if it is white turn. Then the wanted game will be displayed to play it.

5-drawstate: This function gets the number of each piece type of the 2 players, to see if there is a dead position or not by applying dead positions rules. If there is a dead position it will return true, if else it will return false.

6-movecheck: This function checks if the turn’s player’s king is in check or not, if it is in check it will return 1 else it will return 0.

7-pawnmovevalidity: This function checks if the entered position indices by the player is a valid move to this pawn, the pawn can only move 2 steps forward at first but then it can only move one step forward and when it eats, it eats by moving diagonally, if it is valid it will return true else it will return false.

8-knightmovevalidity: This function checks if the entered position indices by the player is a valid move to this knight, the knight moves like the L letter (2+1 or 1+2), if it is valid it will return true else it will return false.

9-kingmovevalidity: This function checks if the entered position indices by the player is a valid move to the king, the king can move only one step in any direction, if it is valid it will return true else it will return false.

10-rookmovevalidity: This function checks if the entered position indices by the player is a valid move to this rook, it can move to the right or left or forward or backward by any number of steps if there are no pieces in it’s way, if it is valid it will return true else it will return false.

11-bishopmovevalidity: This function checks if the entered position indices by the player is a valid move to this bishop, it can move diagonally by any number of steps if there are no pieces in it’s way, if it is valid it will return true else it will return false.

12-queenmovevalidity: This function checks if the entered position indices by the player is a valid move to this queen, it can move in any direction by any number of steps if there are no pieces in it’s way , if it is valid it will return true else it will return false.

13-movechoose: This function takes the indices entered by the player, it checks if the player wants to move a piece from the other player’s piece, it return false if so, and the move will be invalid, else if the player is moving it’s pieces it will then see what this piece is and then call it’s move validity checking function (ex: rookmovevalidity,…..etc) to see if the move is valid or not.

14-allmovesinvalid: This function checks if there is any valid move for this player to play without making the king eaten, so it loops on the whole board and call the movecheck and movechoose functions, if movecheck gives 0 and movechoose gives true, then there will be no stalemate or checkmate. But if they give anything else, there will be checkmate if movecheck gives 1 and there will be stalemate if movecheck gives false. This function only will return 1 which means all moves are invalid and will return 0 if else.

15-boardinit: This function is the function which the most of the other function are being called. It takes the input from the user and according to it test all of the other functions, then it makes the move happens if it is valid, it prints the board each turn, it calls itself every turn until there is draw or checkmate or exit or save.

16-int main: In the main, the board is declared, the arrays carrying the eaten pieces are declared, it prints the 3 options menu for the user to choose either to start a new game, load a previous game or exit, if he chooses load, it will call the load function then the boardinit function will be called, if he chooses new game, the boardinit function will be called, and if he chooses exit the game will exit.


                                                                    ……………………………………………………………………………………………………………………………

