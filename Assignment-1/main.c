/*Name : Kudzai Mabika 
  Student ID : 28897854
  Start date-19 August 2019 End date-30 August 2019
  
Main for ctail program with a number of functionalities:
1.Print the last 200 characters of logfile.txt file
2.Print the last 200 charaters of a textfile entered through command line arguments
3.Print the last 10 lines of a default textfile when option -L is entered.
4.Print the last user specified number of characters from the logfile.txt file, user enters through command line
5.Print the last user specified number of lines entered by a user from arguments.
6.Print the last user specified number of characters entered from arguments from a argument entered file.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "ctail.h"


	
/*argc and argv are very helpful in our program as they are used as counters and 
also get values of our arguments from argv*/
	
int main(int argc, char * argv[])
{
	/*These are our global varibales n represesnts the number which will be used for character output
	   Outfile represents the variable for the file which will be used for read() and open() 
	   lines represents the number of lines to be printed.
	*/
	int n, outfile,lines;
	
	/*If the number of arguments is 1 meaning program name only then it should call the functions */
	if (argc == 1)
	{  
		n = DEFAULT;
		outfile = open("logfile.txt",O_RDONLY);
		readfile(outfile);
		lastchar(outfile, n);
	}
	/*If the number of arguments is 2 meaning program name and text file it should if theres -L print the 10 lines of a file if 
	there's fewer lines print all lines this is all done in the linecounter() function and secondly if there is a another argument and it's a file
	print the last 200 characters of that file*/
	
	else if(argc == 2 && (((strcmp(argv[1],"-L") ==0 )) || (argv[1] != 0)))
	{	
		/* Here we compare the value argv[1] to our required argument to make sure we are printing last 10 lines or last 200 characters*/
 		if(((strcmp(argv[1],"-L") ==0 )))
		{
			outfile = open("logfile.txt",O_RDONLY);
			/*convert the string that is argv[1] into an integer to produce a inetger value
			we use atoi to convert this value*/			
			lines = atoi(argv[1]);
			/*Performs the last 10 line characters from the logfile.txt*/
			linecounter(outfile,lines);
		}else
		{
		n = DEFAULT;
		outfile = open(argv[1],O_RDONLY);
		readfile_arg(outfile);
		lastchar(outfile,n);
		}
	}
	/*If the number of arguments is 3 meaning program name,-n and number only then  should it call the functions
	This also checks if the option entered is -L or -n to allow linecounter to happen */
	else if(argc == 3 && (((strcmp(argv[1],"-L") ==0 )) || ((strcmp(argv[1],"-n") ==0 ))))
	{
		

		n = atoi(argv[2]);
		/*This if statements purpose is to make sure that the argument -L exists to perform the 
		 line counting function otherwise continue with character counting*/
		if(((strcmp(argv[1],"-L") ==0 )))
		{
		lines = atoi(argv[2]);
		outfile = open("logfile.txt",O_RDONLY);	
		readfile(outfile);
		linecounter(outfile,lines);
		}	

		n = atoi(argv[2]);
		outfile = open("logfile.txt",O_RDONLY);	
		readfile(outfile);
		lastchar(outfile, n);	
	}
	/*If the number of arguments is 4 meaning program name,-n,numner and textfile it should perform the following 
	functions  */	
	else if(argc == 4 && (strcmp(argv[2],"-n") ==0 ))
	{
		n = atoi(argv[3]);	
		outfile = open(argv[1],O_RDONLY);
		readfile_arg(outfile);
		lastchar(outfile, n);
	}
	/*If the number of arguments is 5 allowing a user to specify the number and text file to be dealt with and produce the number of lines */
	else if(argc == 5 && (strcmp(argv[1],"-n") ==0 ))
	{
		lines = atoi(argv[2]);
		outfile = open(argv[4],O_RDONLY);
		readfile_arg(outfile);
		linecounter(outfile,lines);
	}
	/*If the number of arguments is not equal to any of the above we have an error which gives the user detailed information and
	how to perform command line arguments*/
	else{
	write(2,"Wrong number/order of arguments",strlen("Wrong number/order of arguments"));
	write(1, "\n", 1);	
	write(2,"Instructions on how to use below",strlen("Instructions on how to use below"));	
	write(1, "\n", 1);		
	write(2,"Usage: ./ctail",strlen("Usage: ./ctail"));	
	write(1, "\n", 1);	
	write(2,"Usage: ./ctail filename.txt",strlen("Usage: ./ctail filename.txt"));
	write(1, "\n", 1);	
	write(2,"Usage: ./ctail -L",strlen("Usage:./ctail -L"));
	write(1, "\n", 1);
	write(2,"Usage: ./ctail filename.txt -n [positivenumner]",strlen("Usage: ./ctail filename.txt -n [positivenumner]"));
	write(1, "\n", 1);
	write(2,"Usage: ./ctail -n 80 -L filename",strlen("Usage: ./ctail -n 80 -L filename"));
	write(1, "\n", 1);
	}
	
	
}
	
