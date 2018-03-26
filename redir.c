#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include "redir.h"

//int fd=0;

int redir_check(char **tokens)
{
/*	const char* input = "<";
	const char* output = ">";
	const char* outputA = ">>";
*/
	while(*tokens != '\0')
	{
		if(strcmp(*tokens,"<")==0)
			return 1;			//input from file
		else if(strcmp(*tokens,">")==0)
			return 2;			//output to file
		else if(strcmp(*tokens,">>")==0)
			return 3;			//output to file with append
		*tokens++;
	}
	return 0;
}

int redir_input(char **tokens)
{

	int pos=0,fd;
	while(*tokens != '\0')
	{
		if(strcmp(*tokens,"<")==0)
			break;
		else pos++;
	}

	fd = open(tokens[pos],O_RDONLY,0);

	if(fd<0)
	{
		perror("Cannot open the input file");
		exit(0);
	}

	dup2(fd,0);
	close(fd);

	return 0;
}


int redir_output(char **tokens)
{

	int pos=0,fd;
	while(*tokens != '\0')
	{
		if(strcmp(*tokens,">")==0)
			break;
		else pos++;
	}

	fd = open(tokens[pos+1], O_WRONLY | O_CREAT,0644);

	if(fd<0)
	{
		perror("Cannot open the  output file");
		exit(0);
	}

	dup2(fd,1);

	//execvp(tokens[0]);
	close(fd);

	return 0;
}

int redir_output_append(char **tokens)
{

	int pos=0,fd;
	while(*tokens != '\0')
	{
		if(strcmp(*tokens,">>")==0)
			break;
		else pos++;
	}

	fd = open(tokens[pos],O_WRONLY | O_CREAT | O_APPEND ,0644);

	if(fd<0)
	{
		perror("Cannot open the  output file");
		exit(0);
	}

	dup2(fd,1);
	close(fd);

	return 0;
}

//int main()
/*{
	 char **tokens;
	  tokens[0]="ls";
	  tokens[1]=">";
	  tokens[2]="a.txt";
	  printf("main");
	redir_check(tokens);
	pos_of_file(tokens);
	redir_output(tokens);
}*/