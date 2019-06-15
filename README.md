# My OpenGL project

## operations

Use W, S, A, D, Space, X to move forward,backward, left, right, up, down.
Use Q, R to accelerate or slow down move speed.
Use G to enable gravity effect.
Use ESC to exit the game.

## TODO list:
1. ~~Generate simple map.~~
2. ~~Enable movement, jump, collision detection.~~
3. ~~locate object, create or destroy an object.~~
4. ~~Add light and shadow.~~

## Implement Details

1. Map generation is implemented by a random height map;
2. The movement is done by changing the view matrix according to keyboard and mouse inputs.
3. Jump is implemented by a timer to reduce the increase of height.
4. Because the objects in MC are all rectangle, AABB collision detection algorithm can be used.
5. To locate the object in front of the player, the point centered in the screen has to been 
projected back to its 3D coordinate, then a vector can be got, which can be seen as a ray to be 
delivered to intersect with blocks in the world. If it touches a block, then calculate the direction 
from where it touches, so that we can know where to put the new block.
6. Lights such as ambient lighting, diffuse lighting or specular lighting are all can be done by
a normal vector and a fragment shader.
7. Shadow is the most difficult component which requires render current objects to a depth map with 
a frame buffer, then rerender objects with this depth map. When the depth of the new renderer objects 
is not larger than the depth map, this place will be dimmed.