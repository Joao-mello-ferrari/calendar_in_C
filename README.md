# What´s the project
-The idea of this project is to mock a calendar application, in which the user can register, retrieve and delete events.

# Motivation
-The mais purpose of the program is to practice everything it was learnt about C language. This includes working with functions, pointers, strings, chars and new types definition.
-As a plus, there´s a fucntionally that uses .txt files, thus we could learn some commands about this environment.

# Functions and responsabilities
- void setup => Reads data stored in .txt file and puts it into a local variable, using a especific type definition (called DATA)
- void showInitialMessage => Prints to the screen a welcome message
- void showHelpMessage => Prints to the screen the list of commands and how to use them, so the user can use the calendar
- int getCommand => Identifies which command the user is attempting to use
- int insert => Handles a new event insertion
- int retrieve => Handles events retrieving
- int delete => Handles a event deletion

# About architecture
-Even though the whole applications consists in one single file, every single logic block of code is separeted in a especifc function.
Thus, it´s guaranteed that it will be easier to identify a problem inside de program, and some lines of code can be used more than once.

# Project files
-The 'final_code.c' file is the LTS version of the project. In case you are interested in getting the older versions, so you can see how everything started and (mayde) try do it yourself from that part on, we have provided 2 parcial codes.