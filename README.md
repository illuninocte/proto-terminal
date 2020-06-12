# Proto-terminal

Project of AEE-SO to make a prototype terminal with the commands:  

1. ls - list elements of current directory  
2. pwd - Print the path to the current directory  
3. cd - Change directory  

Also, the terminal has to be able to use pipeline commands like >, <, | and &.  

#### Fast run

In the first run execute the run.sh file

```
./run.sh
```
if the run.sh don't have permission, execute

```
sudo chmod +x run.sh
```

After the first run you can open the terminal executing
```
build/terminal
```

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

#### Tests

Compile the soma_arg.cpp and quadrado_narg.cpp in the tests/ folder.

Run the project.
Use the cd command to go to the repository path and run:

```
./soma_arg 2 2 | ./quadrado_narg
```
The result should be: 16

(2 + 2)^2