# cub3d
<h3>This is a codam project.</h3>
cub3d is based on Wolfenstein 3D.


## Play the game
This works on most Apple computers. It doesn't work on Windows and Linux.

If you want to try this 'game', follow these steps:
- clone the repository.
- in the root of this folder, type 'make'.
- type ./cub3D maps/c.cub (for example)
- a window is opened, you can move around the map with W,A,S,D and you can look left and right with the arrow keys

## Make maps
You can also try other maps, see the maps folder for more examples. Some of them don't work on purpose, to test errors.

You can even make your own map, the extension should be '.cub'. Make sure to include the following lines:

### R 1920 1080
  This determines the resolution. The first number is the width, the second is height.
### F 100,80,196
  This sets the floor colour. The numbers should be in the range 0-255. It works like RGB colours, so the first number is the amount of red, the second stands for green, the last for blue. You can google for 'rgb colour picker' to help you choose a colour.
### C 190,99,0
  This sets the ceiling colour. The numbers should be in the range 0-255. It works the same as the floor colour
### NO ./pics/yellowbrick.png
  You can give a path to a png, this will appear as the texture of the north wall.
### WE ./pics/greystone.png
  You can give a path to a png, this will appear as the texture of the west wall.
### EA ./pics/colorstone.png
  You can give a path to a png, this will appear as the texture of the east wall.
### SO ./pics/redbrick.png
  You can give a path to a png, this will appear as the texture of the south wall.
### S ./pics/barrel.png
  You can give a path to a png of a sprite, this will appear as an item in the game.
### A map.
This is not just one line, but it is a map of the maze you can walk through. A 1 stands for a wall, 0 for walkable space, 2 for items/sprites. Make sure to surround the walkable space with walls.
You also need to specify a starting position for the player, this is the letter N, S, W of E somewhere in the map.
Example:
```
111111
100S01
111011
120001
111111
