#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *createCommand(size_t size){

  char *block;

  block = (char *) calloc (size, sizeof(char));

  return block;

}

char **createCommands(int n) {

  char **array;

  array = (char **) calloc (n, sizeof(char *));

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
  array[0] = createCommand(size);
  for (int i = 1; i < n; i++) {
    array[i] = array[i-1] + size;
  }
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

int stringLength(char *string){
  int i = 0;
  for (i = 0; ++i && (*string != '\0') ; string++);
  return --i;
}

char *stringCat(char *string1, char *string2){
  int length1 = stringLength(string1);
  int length2 = stringLength(string2);
  int totalLength = length1 + length2 - 1;
  char *res = calloc(totalLength, sizeof(char));
  for (int i = 0; i < length1; i++){
    res[i] = string1[i];
  }
  for (int j = 0; j < length2; j ++){
    res[length1 + j] = string2[j];
  }
  return res;
}

void printCommandLengths(char **commands, int n) {
  assert (commands != NULL);
  for (int i = 0; i < n; i++) {
    printf("%s - %d\n", commands[i], stringLength(commands[i]));
  }  
}

void printCommandConcat(char **commands, int n) {
  assert (commands != NULL);
  char *res;
  char *temp = stringCat(commands[0], commands[1]);
  for (int i = 2; i < n; i++){
    res = stringCat(temp, commands[i]);
    free(temp);
    temp = res;
  }
  printf("%s\n", res);
  free(res);
  free(temp);
}


int main (int argc, char **argv) {

  int noOfCommands = atoi(argv[1]);

  int lengthOfCommands = atoi(argv[2]);

  assert (noOfCommands >= 3 && lengthOfCommands >= 50); 

  char **commandArray;
  
  commandArray = getCommands(noOfCommands, lengthOfCommands);

  printCommand(commandArray, noOfCommands);
  
  printCommandLengths(commandArray, noOfCommands);

  printCommandConcat(commandArray, noOfCommands);

  freeCommands(commandArray, noOfCommands);
 
  return EXIT_SUCCESS;
}
