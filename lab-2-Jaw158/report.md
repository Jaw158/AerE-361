# commands

* *>* sends the output of a command to a file

* *|* sends the outputs of one command to another

* *mkdir* will make directories (files)

* *export* can write commands or sequences of commands to a string

* *$* refers to a specified variable

* *echo* prints the output of a command, mainly used to check what directory a created command will send you to

* *cp* will copy files from one folder to another

* *mv* will cut files from one folder to another

* *rm* deletes files
	* add *-r* to remove whole directories
	* if asked type *y* to confirm that you want to delete certain objects

* *tail* can be used to set the start point of an output with multiple lines
	* use *-n*, followed by *-'number'* to specify what line to start outputting

* *head* can be used to indicate how many lines to print out
	* *-'number'* indictes the number of lines to print

* *awk* is used to specify which columns of an output should be printed
	* *{print &'number'}* specifies which column number(s) to print

* *chmod* is used to change the read, write, and execute positions. Look up approriate number codes to change permissions

* _*_ is used as a variable for strings of characters, i.e. __*'text'__ will have the command only act on files ending in __'text'__

* *grep* finds outputs matching a set list of characters

* *whereis* can find the location of executable files

* *find* finds the location of any given files matching set parameters
	* the first argument specifies the directory to start the search from
	* the second argument specifies what parameter should be searched for, i.e. the name of the file
	* the third argument is the string of characters to match

* *top* is the linux version of task manager

# realizations

*grep* is useful for outputting files matching a set of characters to the command line. It is not ideal for sending a set of files to another command. If you want a command to run a set of files matching a pattern use _*'text'_

This isn't exactly news, but Google is your friend. man pages are also extremely useful, often better than Google if you're trying to find something out about a specific command.

Git won't save a directory (folder) unless there is a file inside it. You can get around this by creating a . (hidden) file. If there are other files in the directory but you only want to save the folder you can write a code

    *
    !.gitignore

to ignore the other files in the directory.
