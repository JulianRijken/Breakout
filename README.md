# Breakout
## Made by Julian Rijken

The game and engine was made in 5 work days.

The engine takes a lot of inspiration from Julgen (an engine I made before) but opts for a Node-based system similar to Godot's. This is done for simplicity, allowing for maximum flexibility over performance.

The game was made from the ground up and takes inspiration from the original Breakout Atari game.

## Future engine improvements / notes
* Nodes and transforms could be separated
* Nodes do all the processing (opposed to something like an ECS) for maximum flexibility
* Project uses west const
* Friends are used to stop the user from using engine specific behavior, should be reconsidered
* Use of floats instead of doubles
* non-size consistent int, should consider int32_t
* Events need to be public and can't be returned const as the events do changes when adding a listener. Better yet, they need mutable data like the nodes so they can be made const!
* Consider always having a root node to remove checking for parent, allowing for fewer checks and more readable code 
* Sound should further be abstracted to allow for playing a random set of sounds 
* The matrix math for world to screen is done very very inefficiently and should be done on the GPU!
* The Service Locator pattern is not correctly implemented and is currently just a fake Singleton. It is however there for future maintenance 
* I only use std::runtime_error or assert, proper hard and soft error handling would be great


## Future game improvements / notes
* Paddle is controlled by Breakout and ideally should be split in controller / controlled
* Trails are used for the ball, but a particle system should be considered 
* Sounds are played from all over the game and not called based on observing for simplicity