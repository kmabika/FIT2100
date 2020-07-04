# Instruction Manual

## How to compile the program.
1. Go to your terminal enviroment.
2. Make sure you are in the directory where the file is located.
3. Enter ```make -f Makefile```.
4. After you have complied using makefile, enter program name ```./ctail``` and arguments
 if you want to run the file.
5. The program should complie and work properly
6. To clean the executable files type ```make clean```.


## Functionality offered by program.
1. Print the last 200 characters from the default textfile logfile.txt
2. Print the last 200 characters from any user specified file that is the correct directory.
3. Print the amount of user characters we want from the logfile.txt
4. Print to terminal the last user specified number of characters from a file of our own choice.
5. Print the last 10 lines from the logfile.txt file
6. Specifiy the number of lines the user wants to see from the file

### Function 1.
- To be able to perform this action type ```./ctail``` on your terminal.<br>
- If the file cannot be opened expect an error.<br>

### Function 2.
- To enable this function the user should enter their textfile to the ```./ctail``` argument, the file must be in the current directory  to work or enter directory.<br>
- The user must type ```./ctail``` filename.txt and the last 200 characters will be produced from the file.<br>
- If the file countains less than 200 characters the will print all the file characters to terminal<br>

### Function 2.
- To be able to use this functionality type, for example we want the last 90 characters , type ```./ctail -n 90``` on your terminal don't forget the ``-n`` option otherwise it will give you an error.<br>
- The number has to be positive integer value.<br>
- If the file cannot be opened expect an error.<br>

### Function 3.
- To be able to use this functionality, using an example for 3 last characters from a file type ```./ctail -n 3 filename.txt```<br>
- If the file cannot be opened expect an error.<br>
- The number has to be positive integer value.<br>

### Function 4.
- To print the last 10 lines from the logfile you can type ```./ctail -L``` on your terminal.<br>
- If the file has less than 10 lines all lines should be printed to terminal.<br>
- The function will offer the number of characters so that the user can see.<br>
- If the file cannot be opened expect an error.<br>
- The number has to be positive integer value.<br>

### Function 5.
- To print the last user specified number lines type ```./ctail -n 80 -L filename.txt```.<br>
- If the file has less than 80 all lines should be printed to terminal.<br>
- If the file cannot be opened expect an error.<br>
- The number has to be positive integer value.<br>
