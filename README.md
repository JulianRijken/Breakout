# Breakout
## Made by Julian Rijken

The game and engine was made in 5 works days.

The engine takes a lot of inspiration from Julgen (an engine I made before) but opted for a Node based system similar to Godot. This is done for simplicity allowing maximum flexibility over performance.

The game was made from the ground up and took inspiration from the original Breakout Atari game.

## Future engine improvements / notes
* Nodes and transforms could be separated
* Nodes do all the processing (opposed of something like a ECS) this is for maximum flexibility
* Projects uses west const 
* Friends are used to stop the user from using engine specific behaviour, should be reconsidered
* Use of floats instead of double
* non type consistent int, should consider int32_t
* Events need to be public and can't be returned const as the events do changes when adding a listener
* Consider always having a root node to remove checking for parent allowing for less checks and more readable code 
* Sound should further be abstracted to allow for playing a random set of sounds 
* The matrix math for world to screen is done very very insufficiently and should be done on the GPU! 


## Future game improvements / notes
* Paddle is controlled by Breakout and ideally should be split in controller / controlled
* Trails are used for the ball but a particle system should be considered 
* Sounds are directly called and not called based on observing for simplicity