# Breakout
## Made by Julian Rijken


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


## Future game improvements / notes
* Paddle is controlled by Breakout and ideally should be split in controller / controlled
* Trails are used for the ball but a particle system should be considered 
* Sounds are directly called and not called based on observing for simplicity