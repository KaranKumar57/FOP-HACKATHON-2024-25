#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void random_shuffle(int winingdigits[]){
	
	int i = 0;
	while(i<=4)
	{
		winingdigits[i] = rand() % 10;
		i++;
	}
}

int main() {
	
	int winingdigits[5];
	int player[5];
    int same = 0;
    
    
    srand(time(0));// seed to the current time (since we used time library)for every time program run
    random_shuffle(winingdigits); // calling function to generate random integers array
    
    printf("Enter 5 Digits Between 0 AND 9\n\n");
	int i = 0;
    while(i<=4 ){
    	int user_integer;
    	printf("Enter Your Digit No. %d: ", i + 1); // taking input from user
    	scanf("%d", &user_integer);
    	if(user_integer>9 || user_integer<0)
		{ // error handling
    		printf("ERROR. Enter Digit between 0 and 9 not beyond or less");
		}
		else{
			player[i] = user_integer; // storing the user's input into players array list each time
			i++;
		}
	}
	
	i = 0;
	while(i<=4)
	{
		if(winingdigits[i] == player[i]){
			same++; // increment the count of same integers
		}
		i++;
	}
	
	//displaying system generated wining digits
	printf("\nWinning Digits: ");
	i = 0;
    while(i<=4 ){
    	printf("\t%d",winingdigits[i] );
    	i++;
	}
	
	//displaying players data
	printf("\nPlayer:\t\t");
	i = 0;
    while(i<=4 ){
    	printf("\t%d",player[i] );
    	i++;
	}
	
	printf("\n\n\n\nHere are the Digits Matched: %d",same); // printing the count of integers which matched
	return 0;
}
