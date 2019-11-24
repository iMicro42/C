/*
* Author: Mohammad Raja, mraja2019@my.fit.edu
* Course: CSE 1001, Section 02 Fall 2019
* Filename: war.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void card_finder(int *card){
  int suit[4] = {'S','D','H','C'};
  char suitPrint = suit[*card/13];
  switch(*card % 13)
  {
    case 9:
      *card = 9;
      printf("J");
      break;
    case 10:
      *card = 10;
      printf("Q");
      break;
    case 11:
     *card = 11;
      printf("K");
      break;
    case 12:
      *card = 12;
      printf("A");
      break;
    default:
      printf("%d",(*card%13) + 2);
      *card = (*card%13);
  }
  printf("%c", suitPrint);
} // < - - Prints out and finds the number of each card
void shuffle(int *in_deck, int n){
    srand((unsigned) time(NULL));
    if (n > 1) {
        int i, k, t;
        for (i = 0; i < (n - 1); i++) {
            k = i + rand() / (RAND_MAX / (n - i) + 1);
            t = in_deck[k];
            in_deck[k] = in_deck[i];
            in_deck[i] = t;
        }
    }
} // < - -Shuffles the deck
void deal(int *deck, int *player1, int *player2){
  int count1 = 0;
  int count2 = 0;
  for(int i = 0; i<52; i++)
  {
    if(i%2== 0)
    {
      player1[count1] = deck[i];
      count1++;
    }
    if(i%2 != 0)
    {
      player2[count2] = deck[i];
      count2++;
    }
  }
  for(int i = 26; i<52; i++)
  {
    player1[i] = -1;
    player2[i] = -1;
  }
} // < - - Deals the cards even and odd
void swap(int *player, int *size){
  int temp = player[0];
  for(int i = 0; i<*size; i++)
    player[i] = player[i+1];
  player[*size-1] = temp;
} // < - - it re-organizes the deck to be in the right order
void battle_swap(int *player,int *player2, int*size1,int*size2, int*numCards){
  for(int i = 0; i<*numCards; i++)
  {
    swap(player, size1);
    *size1+=1;
    player[*size1-1] = player2[0];
    swap(player2, size2);
    *size2-=1;
    player2[*size2] = -1;
  }
} // it re-organizes the deck based on battle
void battle(int *player, int *player2, int*size1, int*size2, int*numCards, int *repeat, int*cardPos, int*winner1, int*winner2){
  int card1 = player[*cardPos];
  int card2 = player2[*cardPos];
  printf("\nPlayer 1's card: ");
  card_finder(&card1);
  printf("\nPlayer 2's card: ");
  card_finder(&card2);
  if(card1 > card2){
    printf("\n\nPlayer 1 wins the round! Awarding played cards to Player 1...");
    if(*repeat > 0){
      battle_swap(player,player2,size1,size2,numCards);
    }
    else{
      swap(player,size1);
      player[*size1] = player2[0];
      swap(player2, size2);
      player2[*size2-1] = -1;
      *size1 += 1;
      *size2 -= 1;
    }
  }

  else if(card2 > card1){
    printf("\n\nPlayer 2 wins the round! Awarding played cards to Player 2...");
    if(*repeat > 0){
      battle_swap(player2,player,size2,size1,numCards);
    }
    else{
      swap(player2,size2);
      player2[*size2] = player[0];
      swap(player, size1);
      player[*size1-1] = -1;
      *size2 += 1;
      *size1 -= 1;
    }
  }
  else if(card1 == card2){
    printf("\n\nThe cards match! It’s a battle! \nDrawing 3 cards from each player for battle...\n");
    if(*size1 < 4)
      *winner2 = 1;
    if(*size2 < 4)
      *winner1 = 1;
    *repeat += 1;
    *numCards += 4;
    *cardPos += 4;
    battle(player,player2, size1, size2, numCards, repeat, cardPos, winner1, winner2);
  }
} // < - - This is the battle and decides who wins and who loses

int
main(void)
{
  int deck[52];
  for(int i = 0; i<52; i++)
    deck[i] = i;
  shuffle(deck, 52);
  int player1[52];
  int player2[52];
  printf("Welcome to War! \nShuffling deck... \nDealing cards...");
  int size1 = 26, size2 = 26; // < - - Size of each deck
  int winner1 = 0, winner2 = 0; // < - - Checks wheter or not a player has enough cards to battle out a war inside battle function, if not it feed that info to the starting if statements of do while looop
  char check; // < - - used to check wheter it is play(p) or exit(e)
  deal(deck, player1,player2); // < - - deals the deck out
  int gameDone = 0; // < - - Wheter or not to print out if the game is tie or not
  do{
  if(size1 >= 52 || winner1 == 1){ // < - - Checks wheter or not to end the game here and player1 wins.
    gameDone = 1;
    printf("\n\nPlayer 1 Wins the game! \n\nGoodbye! Thanks for playing War!\n\n");
    break;
  }
  else if(size2 == 52 || winner2 == 1){ // < - - Checks wheter or not to end the game here and player2 wins
    gameDone = 1;
    printf("\n\nPlayer 2 Wins the game! \n\nGoodbye! Thanks for playing War!\n\n");
    break;
  }
  printf("\n\nWould you like to play (p) or exit (e): ");
  scanf(" %c",&check);

  if(check == 'e')
    break;
  int numCards = 1; // < - - How many cards to use in battle swap
  int cardPos = 0; // < - - Position of card to pick from inside the player1 and player2 array's
  int repeat = 0; // < - - Checks wheter or not a War has taken place and indicates if battle swap or swap is nessacery
  battle(player1,player2, &size1, &size2, &numCards, &repeat, &cardPos,&winner1,&winner2);
  } while(check == 'p');
  if(gameDone == 0) // < - - checkers wheter or not to print out game done or not.
    printf("\n\nThis game is a tie!\n\nGoodbye! Thanks for playing War!\n\n");
  return 0;
}
