•	Game Explanation:
You the user are a spaceship, you move left and right using the arrow keys,
And shoot using space. Your mortal enemies are weird looking squids and crabs.
The goal in the game is to get to the boss level, the evil squid monster.
The simple enemies move as a group (an army).
The boss squid has a lot more health and moves in a different way.

•	Files and classes:
1.	Main.cpp 
The main file that runs the start of the GameManager, pushes a menu state.
2.	Macros.h 
The file holds all defines and consts, enums, structs as well as usings and includes used throughout the program.
3.	Resources
The resources class is in charge of loading and holding all outer files, 
Such as pictures, music’s and fonts.
It is a static Singleton class.
4.	Chronometer:
A namespace which is an expansion of sf::clock, it has an addition of a pause and resume function which allows us to pause and resume the game clock when we pass between states.
5.	Logger
A singleton static class, the class holds the logger file. The logger file will hold times of major things that happened throughout the program. such as Exceptions, collisions and more.
If the program has ever failed, the logger file will allow us to know the reason.
6.	Bullet, Enemy, PowerUp factories
These classes are each in charge of creating objects.
The class holds a static map which holds a key matching to the proper objects and a pointer to a function which creates the object. Each object is in charge of registering itself to the factory.
7.	Level Manager:
The level manager gets the vector of entities and updates them by using the outer level files. It creates the objects according to the char in the file using the factories.
8.	HighScoreManager:
The manager is in charge of getting the file if it exists and creates a new one if it doesn’t. it adds all the existing high scores to a multimap.
9.	GameManager:
The gameManager runs the main game loop.
It holds a stack of states like menu, help, highscore, pause, play 
Generically it calls a set of functions for the state that’s on the top of the stack.
It has a push and pop function which are called when we want to move between game states.
10.	MyExceptions:
Holds all the exceptions needed throughout the game, the exceptions inherit from std::exception.
11.	State
State is an abstract class that represents possible game states.
12.	Menu state:
The class inherits from state, represents the main menu state.
It is the first state pushed into the stack of states.
It holds a vector of pointers that inherit from command,
Help, start, exit, highscore.
13.	playingState
This state is the playing state, it holds the vectors of entities and is in charge of all playing updates, like movement, shooting, collision, deletion of objects….
14.	PauseState
The state pauses all game clocks…
15.	GameOverState.
The state is in charge of ending the playing state.. cleaning everything getting 
users name and adding it to the multimap of high scores.
16.	Command:
Abstract class that represents all buttons in games, has an execute function
17.	Exit
Inherits from command, exits the game…. Writes high scores to highscore file.
18.	Help:
Inherits from command, opens a help screen
19.	HighScore:
Inherits from command, loads from multimap, makes sf::Texts and draws them on the window.
20.	NewGame:
Pushes the playingState.
21.	MoveStrategy:
Abstract class that represents the enemy’s movements.
22.	SimpleMove
Inherits from MoveStrategy, is the default move for the simple enemies.
Moves them in an army motion.
23.HorizontalMove
Inherits from MoveStrategy, this move is given to the enemy that was just 
teleported in front of the ship.
24.	BossMove
Inherits from MoveStrategy and moves the boss
25.	Entity:
Abstract class which represents a game object.
26.	Bullet:
Abstract class represents a bullet
27.	SimpleEnemyBullet:
Bullet for enemy
28.	DefaultBullet
Default hero bullet
29.	WaveBullet
Bullet for hero gotten after a powerup
30.	Weaponable
Abstract class represents an enemy or hero
31.	Ship
Inherits from weaponable, is the hero class
32.	Enemy.
Inherits from weaponable, is abstract
33.	SimpleEnemy
Inherits from enemy
34.	smartEnemy
Inherits from enemy
35.	BossEnemy
Inherits from enemy
36. PowerUp
Abstract class that inherits from entity.
37. Shield
38. WaveBullet
39. Life


•	DataStructures:

1.	Map:
All factories hold a map
2.	Multimap:
For high score, is multimap because we want it sorted and allow the duplicate keys.
3.	Stack:
GameManager holds stack of game states.
4.	Vectors:
Entities, textures, sounds …… 

•	Bugs:
No knows bugs.

	
