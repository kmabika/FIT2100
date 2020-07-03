/*Author :Kudzai Mabika
 *Student ID: 28897854
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "ctail.h"

	/*Function to print our size_t value */
	void print_n(size_t n) 
	{
    		if (n / 10) 
		{
        		print_n(n / 10);
   		}
    		
			char c = '0' + n % 10;
    			write(1, &c, 1);
	}	
	
	/*OUr readfile function which is supposed to read a file if there is no specified 
	file from the arguments, accepts a int for the file, this file does not take a n value because if performing
	default 200 characters.
	If the value of f < 1 indication an error the program returns an error*/
	void readfile(int f)
	{
	if((f) < 0)
		{
		char * errorString = "Error opening file.txt\n";	
		write(2,errorString,strlen(errorString));
		exit(1);
		}	
	}
	
	/*Our readfile function to deal with arguments entereed by a user
	If the value of f < 1 indication an error the program returns an error*/
	void readfile_arg(int f)
	{
		if((f) < 0)
		{
			char * errorString = "Error opening file.txt\n";	
			write(2,errorString,strlen(errorString));
			exit(1);
			}	
	
	}
	
	/*The function which calculates the number of lines in a file, it's default is supposed print the last 10 lines
	starts from 9 because an array is storing the file(0-9), The function will aslo return all of the file if lines are 
	less than 10*/
	void linecounter(int file, int n)
	{
	size_t lines = 0;
	
	char l;
		if (n == 0){
		n = 9;
		}
			else{
			n--;	
			}
				while (read(file, &l, 1) == 1) 
				{
					if (l == '\n') 
					{	
					write(1,&l,1);	
					lines++;
					}
					if(lines == n)
					{
					break;
					}	
				
				}
	
		if(lines > 0)
		{
		lines++;
		}
			else
			{
			lines = 0;	
			}	
	
	write(1, "\n", 1);
	write(1,"Number of lines: ",strlen("NUmber of lines: "));	
	print_n(lines);
	write(1, "\n", 1);	
	exit(0);
	close(file);
	}	
	
	/* This function will to count the last 200 chars of the textfile unless specified it allows user input
	The function should also return the total number of chars if they are lesser than 200 or specified user input*/
	void lastchar(int file, int n){
	
	int length;
	size_t characters = 0;
	size_t total = 0;
	char c;	
		
		while (read(file, &c, 1) == 1) {
	    	if (c !='\n') 
			{
			total++;
			}
		}	
	
	if(n > total)
		{
		lseek(file,0,SEEK_SET);
		while (read(file, &c, 1) == 1) {
	    	if (c !='\n') 
		{
		write(1,&c,1);
		characters++;}
		}		
		}
	else
		{	
		lseek(file, 0, SEEK_END);
		length = lseek(file,0,SEEK_CUR);
		lseek(file,(length - n),SEEK_SET);
		
		 	while (read(file, &c, 1) == 1) 
			{
		    		if (c !='\n') 
				{
				write(1,&c,1);
				characters++;
				}
			}		
		}
	
	 write(1, "\n", 1);
	 write(1,"Character count: ",strlen("Character count: "));
	 print_n(characters);
	 write(1, "\n", 1);	
         exit(0);
         close(file);
	}
