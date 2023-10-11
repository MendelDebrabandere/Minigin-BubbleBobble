# Minigin-BubbleBobble
GitHub repo: https://github.com/MendelDebrabandere/Minigin-BubbleBobble

A game engine made myself in the Programming 4 course in DAE:
![BubbleBobble](https://github.com/MendelDebrabandere/Minigin-BubbleBobble/assets/95921047/ada02a54-47c9-4378-bb1b-a12e8a51baaa)

This is a project that is based on this simple start project: https://github.com/avadae/minigin

The start project is basically just a C++ Visual Studio project with SDL set up.
All the game engine stuff is added by myself.

## Minigin
This is the engine part of the project. It is written and designed in a way that it is a self-sufficient engine, as if it was made for publishing.
It is by no means a big or impressive engine like Unreal or Unity, but it is a simple and clean 2D engine that uses some core game programming patterns.
Most of the patterns come from the book "Game Programming Patterns" by Robert Nystrom (https://gameprogrammingpatterns.com).
As said in the beginning, this is a project that was made for the programming 4 course in DAE where we learned about the patterns of the book in class.

Here is a list of the patterns the game engine contains:
- Command
- Observer
- Singleton
- State
- Game Loop
- Component
- Event Queue
- Service Locator

## Bubble Bobble
This is the game I made on the engine. It is a partial remake of the original Bubble Bobble by Taito Corporation.
This is made as test/proof that the features of the engine actually work, for what is a game engine if no games are made using it.
The game can be played singleplayer, co-op multiplayer or versus multiplayer. In all 3 cases it supports controller input.

## Networking in Minigin
One of my teachers in DAE, that used to work at Larian studios told me that, when he worked at Larian, the test for programming interns was to make Tetris with online networking .\
After hearing this I wanted to add networking to this project, so I started coding this in, but this is my first time ever trying to use networking or sending packets. \
I am far from finished with this, but I have a good start and can send game state packages and inputs, meaning that it already kind of works. But there is still a lot of work to do and it isn't uncommon to have runtime errors while running online multiplayer in the current state of the project.
