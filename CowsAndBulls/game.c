#include <stdio.h>
#include  <string.h>

#define NO_GUESSES 4

void read_guess(int *guess){
  int n;
  for (int i = 0; i < NO_GUESSES; i++){
    do {
      printf("Enter your guess : ");
      scanf("%d", &n);
    } while (n < 1 || n > 9);
    guess[i] = n;
  }
}

void toLowerCase(char str[], int size){
  for (int i = 0; i < size; i++){
    if(str[i]>='A' && str[i]<='Z'){
            str[i] = str[i] + 32;
    }
  }
}

int another_game(){
  char truthVal[1];
  do {
    printf("Do you want to play another game ? [ y / n ]: ");
    scanf("%s", &truthVal[0]);
    toLowerCase(truthVal, 1);
    if (strcmp(truthVal, "y") == 0){
      return 1;
    } else if (strcmp(truthVal, "n") == 0){
      return 0;
    }
  } while (truthVal[0] != 'y' || truthVal[0] != 'n');
  return 0;
}

int blackScore(const int guess[], const int code[]){
  int score = 0;
  for (int i = 0; i < NO_GUESSES; i++){
    if (guess[i] == code[i]){
      score++;
    }
  }
  return score;
}

int whiteScore(const int guess[],const int code[]){
  int score = 0;
  for (int i = 0; i < NO_GUESSES; i++){
      for (int j = 0; j < NO_GUESSES; j++){
	if (guess[i] == code[j] && i != j){
	  score++;
	}
      }
  }
  return score;
}

void printScore(const int guess[], const int codes[NO_GUESSES]){
  printf("Your guess was: {");
  for (int i = 0; i < NO_GUESSES; i++){
    printf("%d", guess[i]);
    if (i != NO_GUESSES - 1){
      printf(", ");
    }
  }
  printf("}\n");
  printf("Score = (%d, %d)\n", blackScore(guess, codes), whiteScore(guess, codes));
}



int main(void){
  int anotherGame = 1;
  int gameNo = 0;
  int codes[5][NO_GUESSES] = {{1 , 8 , 9 , 2} , {2 , 4 , 6 , 8} , {1 , 9 , 8 , 3} , {7 , 4 , 2 , 1} , {4 , 6 , 8 , 9}};
  do {
    int guess[NO_GUESSES];
    int round = 0;
    do {
      if (round != 0){
	printf("Not quite the code! Try again\n");
      }
      read_guess(&guess[0]);
      printScore(guess, codes[gameNo]);
      round++;
    } while (blackScore(guess, codes[gameNo]) != NO_GUESSES);
    printf("You guessed the right code!\n");
    gameNo++;
    if (gameNo != 5){
      anotherGame = another_game();
    } else {
      anotherGame = 0;
    }
  } while (gameNo < 5 && anotherGame == 1);
  printf("You finished\n");
  return 0;
}
