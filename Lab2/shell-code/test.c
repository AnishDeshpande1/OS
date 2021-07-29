#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	char *currentloc;
	currentloc = (char *)malloc(sizeof(char)*1024);
	FILE* fp;
	if(argc == 2) {
		fp = fopen(argv[1],"r");
		if(fp < 0) {
			printf("File doesn't exist.");
			return -1;
		}
	}

	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		if(argc == 2) { // batch mode
			if(fgets(line, sizeof(line), fp) == NULL) { // file reading finished
				break;	
			}
			line[strlen(line) - 1] = '\0';
		} else { // interactive mode
			printf("%s$",currentloc);
			scanf("%[^\n]", line);
			getchar();
		}
		//printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
   
       //do whatever you want with the commands, here we just print them
/*
		for(i=0;tokens[i]!=NULL;i++){
			printf("found token %s (remove this debug output later)\n", tokens[i]);
		}
*/
		if(tokens[0]==NULL){
			//printf("No command entered guys\n");
			continue;
		}
		//printf("command is:%s",tokens[0]);
		if(strcmp(tokens[0],"cd")==0){
			//printf("cd detected\n");
			if(tokens[1]!=NULL){
				//printf("Folder to go to is %s",tokens[1]);

				if(chdir(tokens[1])!=0){
					printf("Shell: Incorrect Command");
					continue;
				}

				char cwd[PATH_MAX]; 
				if (getcwd(cwd, sizeof(cwd)) != NULL){
					currentloc = cwd;
				}
			}
			else{
				chdir(getenv("HOME"));
				char cwd[PATH_MAX]; 
				if (getcwd(cwd, sizeof(cwd)) != NULL){
					currentloc = cwd;
				}
			}
			continue;
		}
		//if()
		int rc = fork();
		if(rc==0){
			//printf("I am now the child process, pid = %d \n",getpid());
			if(execvp(tokens[0],tokens)<0){
				printf("Shell: Incorrect command '%s'\n",tokens[0]);
			}
			exit(1);
		}
		else{
			wait(NULL);
			//printf("The child has been reaped, the parent is back now pid %d\n",getpid());
		}

       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
