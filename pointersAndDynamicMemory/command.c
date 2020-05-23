#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *createCommand(size_t size){

  char *block;

  block = (char *) malloc (size * sizeof(char));

  return block;

}

char **createCommands(int n) {

  char **array;

  array = (char **) malloc (n * sizeof(char *));

  return array;

}

void removeNewLine(char *command, size_t size){
  char buff[size];
  int i = 0;
  while (!(command[i] == '\n' || command [i] == '\0') && i < size){
    buff[i] = command[i];
    i++;
  }
  while (i < size) {
    buff[i] = '\0';
    i++;
  }
  strcpy(command, buff);
}
    
char *getCommand(size_t size){
  char *array;
  array = createCommand(size);
  printf("> ");
  fgets(array, size * sizeof(char), stdin);
  if(!strchr(array, '\n')) {  
    while(fgetc(stdin)!='\n');
  }
  removeNewLine(array, size);
  return array;
}

char **getCommands(int n, size_t size){

  char **array;

  array = createCommands(n);

  for (int i = 0; i < n; i++){
    array[i] = getCommand(size);
  }

  return array;
}

void printCommand(char **commands, int n) {
  assert (commands != NULL);
  for (int i = 0; i < n; i++){
    printf("%s\n", commands[i]);
  }
}

void freeCommands(char **commands, int n) {
  assert (commands != NULL);
  for (int i = 0; i < n; i++) {
    free (commands[i]);
    commands[i] = NULL;
  }
  free(commands);
  commands = NULL;
}

int main (int argc, char **argv) {
 
  int noOfCommands = atoi(argv[1]);
  int lengthOfCommands = atoi(argv[2]);

  assert (noOfCommands >= 3 && lengthOfCommands >= 50); 

  char **commandArray;
  
  commandArray = getCommands(noOfCommands, lengthOfCommands);

  printCommand(commandArray, noOfCommands);

  freeCommands(commandArray, noOfCommands);

  printf("done\n");
  return 0;
}