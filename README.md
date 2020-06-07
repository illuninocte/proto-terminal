# Proto-terminal

Project of AEE-SO to make a prototype terminal with the commands:  

1. ls - list elements of current directory  
2. pwd - Print the path to the current directory  
3. cd - Change directory  

Also, the terminal has to be able to use pipeline commands like >, <, | and &.  

#### Build (and run) instructions

First change the value of "entry_dir" in the file .terminal to the home that you want use in your project, example:

```
entry_dir = /home/caelum-laron/
```

After, open terminal in the directory of project and type this sequence of commands:

```
mkdir build
cd build
cmake ..
make 
cd ..
build/terminal
```