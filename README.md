# IMDb Catalog
> IMDB movie catalog in your memory

## Objective
Utilizing different data structures and algorithms, I developed a IMDB Catalog that users can create, retrieve, update, and delete (CRUD) records. This program loads the lookup dataset into memory then controlled through curses user interface. Multiple users are denoted by multiple datafiles (.log).

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
Finally, to run the program, simply enter `make run` and the user interface will be displayed in terminal.
#### Valgrind
If you have valgrind installed in your environment, `make valgrind` command can help you with memory debugging, memory leak detection, and profiling.
#### Clean
After execution, it is always good to clean up outputted files. This can be done with a make command, `make clean`. This process is to remove object files and the executable.
#### Reset
A make command `make reset` cleans files so that the directory is in the identical state as after cloning. This process removes log files and datasets. This requires you to run the download command once again before compiling and running the project.

## Demo
[![Demo](http://img.youtube.com/vi/Imf1GN_EypU/0.jpg)](http://www.youtube.com/watch?v=Imf1GN_EypU "Demo")


## Use Cases
- Sort
- Filter
- Search
- CRUD

## Extras
For more information about the project, go to <a href="./doc/Documentation.docx">./doc/Documentation.docx</a> for a full documentation. Similar to this README document, this covers the installation process, set up process, and more information in deep detail.

For explanation of the code for this project and its file structure, go to <a href="./doc/Explaining-the-Code.docx">./doc/Explaining-the-Code.docx</a>. This document goes over each of the files included in the directory to provide full explanation of how this project was built and how it works.

For more information about what I learned through working on this project, go to <a href="./doc/What-I-Learned.docx">./doc/What-I-Learned.docx</a>.

## Sources
- <a href="https://www.imdb.com/interfaces/">IMDB Dataset</a>
- <a href="http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html">NCURSES Documentation</a>
- <a href="https://www.youtube.com/playlist?list=PL2U2TQ__OrQ8jTf0_noNKtHMuYlyxQl4v">NCURSES Tutorial</a>
- <a href="https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf">Makefile Lecture</a>