# Chess
A Fully Functional Console Chess Game made in C++

# Introduction:

There are a lot of Implementation of Chess Games on the internet which are better than this one. But there is no harm in making one for learning purposes.
This Game is implemented fully on Console and has no GUI. It is lightweight being only 324 Kb. It has no AI.

# Classes:

All the different attributes of the game are specified in different Header Files and Classes along with their Cpp files, some of the main ones are listed with a brief description below:

Spot: Spot Class contains one block of the 8x8 Grid with a Selector for each piece.

Piece: The basic building block of the system, every piece will be placed on a spot. Piece class is an abstract class.The extended classes (Pawn, King, Queen, Rook, Knight,               Bishop) implements the abstracted operations.

Board: Board is an 8×8 set of boxes containing all active chess pieces.

Player: Player class represents one of the participants playing the game.

Move: Represents a game move, containing the starting and ending spot. 

Lastmove: Contains the Last Move done by the User

Game: This class controls the flow of a game. It keeps track of all the game moves, which player has the current turn, and the final result of the game.

# How to Play:

This game runs in a console, i.e., that means no GUI is available to the user. All the input is taken from the keyboard, and for that, it uses the Coordinate Notation.

The white pieces are represented by capital letters and the black pieces are represented in lowercase letters. They are all represented by the first letter of their names, the only exception being the Knight, which is represented by an N, leaving the K for the King):

(P)awn
(R)ook
K(n)ight
(B)ishop
(Q)ueen
(K)ing

# Bugs:

This application is certainly not bug-free. If you encounter an error, a crash, an invalid situation in the game, etc., feel free to submit any issues which you encounter. This Game also has a save feature which make Debugging a million times easier. Please Save the game & send me a .dat file if possible of the bug. Your help is very much appreciated!
