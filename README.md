# Skyline-Generator
creates a 2d city skyline utilizing a modified priority queue class

This program reads the x and y coordinates of buildings in a city from the file "input.txt" and describes the skyline by outputing the coordinate changes.

The input should be in the following format:

#_of_buildings

left_x_coordinate y_coordinate right_x_coordinate

left_x_coordinate y_coordinate right_x_coordinate

...

The code returns the x coordinate and the corresponding new y coordinate only when the height of the skyline changes. The output is in the following format:

x_coordinate(always 0) new_y_coordinate

x_coordinate new_y_coordinate

...
