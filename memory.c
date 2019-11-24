#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print_board(char array[4][8]){
  printf("\n    0   1   2   3\n");
  for(int i = 0; i<4; i++){
    printf("%d ", i);
    for(int j = 0; j<4; j++){
      printf("| %c ", array[i][j]);
    }
    printf("\n-----------------\n");
  }
}
void print_round(char array[4][8], int row1, int column1, int row2, int column2){
  printf("\n    0   1   2   3\n");
  for(int i = 0; i<4; i++){
    printf("%d ", i);
    for(int j = 0; j<4; j++){
      if(i == row1 && j==column1) printf("| %c ", array[i][j+4]);
      else if(i == row2 && j == column2) printf("| %c ", array[i][j+4]);
      else printf("| %c ", array[i][j]);
    }
    printf("\n-----------------\n");
  }
}
void fill_board(char array[4][8]){
  srand(time(0));
  for (int i = 0; i < 4; i++) {
    for(int j = 4; j<8; j++){
      int num = (rand() % (90 - 65 + 1)) + 65;
      array[i][j]= num;
    }
  }
}
void check_board(char array[4][8], int row1, int column1, int row2, int column2, int *points){
  int lett1 = array[row1][column1+4];
  int lett2 = array[row2][column2+4];
  if(lett1 == lett2){
    array[row1][column1] = lett1;
    array[row2][column2] = lett2;
    *points += 1;
    print_board(array);
    printf("Cards match! You get a point!\nYour current points: %d\n", *points);
  }
  else{
    print_round(array, row1, column1, row2, column2);
    printf("Cards do not match! Try again!");
  }
}

int
main(void){
  char board[4][8];
  for(int i = 0; i<4; i++){
    for(int j = 0; j<4; j++){
      board[i][j] ='$';
    }
  }
  int points = 0;
  char option;
  fill_board(board);
  printf("Welcome to Memory! Ready Player One...\n");
  while(option != 'Q'){
    printf("\nHere's the board:\n");
    print_board(board);
    printf("\nChoose an option:\n(F) Find a match \n(Q) Quit\n");
    printf("Choice: ");
    scanf(" %c", &option);
    if(option == 'Q' || option == 'q') break;
    int row1, column1, row2, column2;
    printf("Pick first card (row, column): ");
    scanf(" %d , %d", &row1, &column1);
    printf("Pick second card (row, column): ");
    scanf(" %d , %d", &row2, &column2);
    check_board(board, row1, column1, row2, column2, &points);
    if(points == 8) break;
  }
  if(points == 8)   printf("You WON the Game!! \nYour total points: %d. Goodbye!\n", points);
  printf("Your total points: %d. Goodbye!\n", points);
return 0;
}
