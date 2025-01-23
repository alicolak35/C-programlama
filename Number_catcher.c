#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CHECK 3

//!!an interval with negative number is valid. What unsigned int makes the neg. number?

int game_ruler(void);
void limit_describer(int*, int*);
void delay(int);
int opening(void);
int number_caster(int*,int*);
void hint(int);

//özel karakter ekleyince pogram sürekli baştan çalıştı ve son girdiyi konsola yazdırdı->
//**ascii kod aralığı ile girilmesi gereken karakterleri sınırlayabilirim

int main(void){
  
  if(opening() == 0)
    return printf("The Game is ended due to incorrect authentication character!!");

  switch (game_ruler()){
    case 1: printf("The Game is closed due to same number violation...");break;
    case 2: printf("The Game is closed due to invalid number violation!!!");
  }
}

int opening(void){
  char y;
  printf("Welcome to the Number Catcher...\n");
  printf("Rule #1: The game is playing with positive numbers...\n");
  printf("Rule #2: If you enter same and invalid number for several times, the game will be automatically closed...\n");
  printf("Rule #3: You can use hint by pressing '-1'...\n");
  printf("Rule #4: Press '-2' to change current interval...\n");
  delay(10000000);
  printf("Press 'y' to continue...\n");
  delay(10000000);
  scanf("%c", &y);
  
  int check = 0; 

  while( (y != 'y') && (y != 'Y')){  
    printf("You pressed a character different from 'y'...\n");
    printf("Press 'y' to continue...\n");
    
    scanf(" %c", &y);
    ++check;
    if( check >= CHECK)
      return 0;
  }  
  return 1;

}

int game_ruler(void ){
  int num = 0, diff = 0;
  int press_check = 0;
  unsigned int low_limit, high_limit;

  limit_describer(&low_limit, &high_limit);

  int num_to_catch= number_caster(&low_limit, &high_limit);

  printf("Enter the number...\n");
  scanf("%d",&num);
  
  while ((num < low_limit || num > high_limit) && num != -2){
    printf("please enter a valid number between %d and %d\n", low_limit, high_limit);
    scanf("%d",&num);

    ++press_check;

    if(press_check >= CHECK)  return 2;
  }

  diff = abs(num - num_to_catch);
  
  int i = 0;
  int old_guess_check = 0;
  //int hint_cnt = 0;

  while(num != num_to_catch){
    int old_guess = num;
    
    i++;
    
    printf("Enter the number...\n");
    scanf("%d",&num);
    // while(1) -> (num < low ya da num > high) ve (num eşit olmazsa -1'e(=1) ve num eşit olmazsa -2'ye(=1)) 
    while ((num < low_limit || num > high_limit) && (num != -1 && num != -2 )){
      printf("please enter a valid number between %d and %d\n", low_limit, high_limit);
      scanf("%d",&num);
      ++press_check;
      if(press_check >= CHECK)  return 2;
    }
    press_check = 0;

    
    if(num == num_to_catch)
      break;
    
    if(num == old_guess){
      printf("don't wait to catch while entering same number...\n");

      ++old_guess_check;
      if(old_guess_check >= CHECK)
        return 1;
    }
    else{
      if(abs(num_to_catch - num) < diff){
        printf("warmer...\n");
      }
      else
         if(abs(num_to_catch - num) > diff){
            printf("colder...\n");
        }else{
          printf("What is the middle number of %d and %d ?\n", old_guess, num);
        }
      diff = abs(num - num_to_catch);
    }
        
        /*
Enter the number...
-2
colder...
-2
-2
Please enter two numbers that you want to catch between   
    */
    switch(num){

    case -2:
    {
      scanf("%d%d", &low_limit, &high_limit);
      limit_describer(&low_limit,&high_limit);
      num_to_catch = number_caster(&low_limit,&high_limit);
      break;
    }
    case -1:   
      hint(num_to_catch);
      //hint_cnt = -1;
    }
  }

  i++;
  printf("Congrats. You catched the number at your %d. guess :)\n", i);
  return 1;
}

void limit_describer( int *limit1, int *limit2){
  
  printf("Please enter two numbers that you want to catch between\n");
  //aralığı yeniden belirlemeyi ekleyim
  scanf("%d%d", limit1, limit2);

  if(*limit1 > *limit2){
    int temp;
    temp = *limit1;
    *limit1 = *limit2;
    *limit2 = temp; 
  }
}

int number_caster(int *low_limit, int *high_limit){

  time_t t;
  int gap = 0, num=0;
  
  gap = *high_limit - *low_limit;
 
  srand((unsigned) time(&t));

  num = rand() % gap;
  num += *low_limit;
  return num;
}

void hint(int number){
  if(number % 2 == 0) 
    printf("Here is the hint: The number is even!!\n");
  else 
    printf("Here is the hint: The number is odd!!\n");
}

void delay(int delay){
  while(delay > 0)
    delay--;
}
