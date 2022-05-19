first of all, you need a GNU/linux operating system
then you have to install ncurses and g++ (e.g. "sudo apt install libncurses-dev" and "sudo apt install g++")
now use "g++ 3Dv2.1.cpp -o <program_name> -lncurses" to compile the code
finally, you can type "./<program_name>", and then type the name of the file you want to render (e.g. "cube.txt")
keyset:
  x - zoom in
  y - zoom out
  r - switch auto rotate on/off
  q/a - rotate around the x axis   \
  w/s - rotate around the y axis    } manually
  e/d - rotate around the z axis   /
  q - exit
 have fun ;)
