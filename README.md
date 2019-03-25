# IMDb Catalog
> a movie catalog in your memory

## Objective
Utilizing different data structures and algorithms, I developed a IMDB Catalog that users can create, retrieve, update, and delete (CRUD) records. This program loads the lookup dataset into memory then controlled through curses user interface. Multiple users are denoted by multiple datafiles (.log)

## Installation
1. Open Terminal and direct to a directory you wish to download the project.
2. Clone the GitHub repository with command `git clone https://github.com/namitoyokota/imdb-catalog.git`.
3. If ncurses is not installed in your environment, enter command `sudo apt-get install libncurses5-dev libncursesw5-dev` to install.
4. After cloning the git repository, change directory with `cd imdb-catalog`.

## Set Up
#### Download
Downloading the dataset needed for the program to compile can be achieved by running a make command, `make download`. The downloaded file is now in 'data'. Then go to compile step.
#### Compile
Compiling the program is done by running the command, `make` in terminal. This creates object files in 'src' and the main executable in 'bin'. Now, go to run step.
#### Run
Finally, to run the program, simply enter `make run` and the user interface will execute.
#### Clean
After done with execution, it is always good to clean up outputted files. This can be run with a make command, `make clean`. This process to remove object files and the executable.
#### Reset
A make command `make reset` cleans files so that the directory is in the identical state as after cloning. This process removes log files and datasets. This requires you to run the download command once again.

## Tutorial
> Insert video tutorial here

## Use Cases
#### Sort
#### Filter
#### Search
#### Edit

## Sources
- <a href="https://www.imdb.com/interfaces/">IMDB Dataset</a>
- <a href="https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf">makefile</a>
- <a href="https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46">readme</a>