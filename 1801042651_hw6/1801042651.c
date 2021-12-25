#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *one_direction(char *ptr, int y, int z, int dir, char words[], int location[]);
void word_overflow(int *y, int *z, int *dir,char words[]);
void print_word_board(char arr1[], char words[][50]);


void  main(void){

	int k,t,n,column,random,number[15],y[15],z[15],dir[15],e,location[50],all_location[15][50],cast1,cast2,flag=1;
	char row,word,random_word[50],words[15][50],arr2[405],array[50],*arr1,arr[405],slctn[50];
	
	srand(time(NULL));

	/* in this algorithm,with the rand function, a random number
	**is generated and the word on the line with  the random 
	** number generated in the words.txt file is read*/

	while(k != 10){

		FILE *fp = fopen("words.txt","r");

		random = 1+rand()%100;

		/*if a previously used number is created, it generates a different number*/
		for(int r=0;r<k;r++)
			if(random == number[r])
				random = 1+rand()%100;

		/*in number[] array, stores which used numbers*/
		number[k] = random;

		/*for cursor shows line randomth */
		for(int j=0;j != (random-1) && !feof(fp);){
			fscanf(fp,"%c",&word);

			if(word == '\n')
				j++;
		}

		word = 48;

		/*retrieves the word on line randomth*/
		for(t=0;word != '\n' && !feof(fp);t++){
			fscanf(fp,"%c",&word);
			random_word[t] = word;
		}

		random_word[++t] = '\0';

		/*each word is stored in words which two dimensional array*/
		for(n=0;n<t;n++)
			words[k][n] = random_word[n];

			words[k][t-3] = '\0';
			k++;
		fclose(fp);
	}	
	/*for each word it generates row,column and direction*/
	for(int i=0;i<10;i++){
		y[i] = 1+rand()%20;   // line number
		z[i] = 1+rand()%20;	// column number
		dir[i] = 1+rand()%8; // direction

		word_overflow(&y[i],&z[i],&dir[i],words[i]);
	}

	for(int i=0;i<10;i++){

		/*stores the eth word in the array[].*/
		for(e=0;e<strlen(words[i]);e++)

			array[e] = words[i][e];
			array[e] = '\0';
		
		arr1=one_direction(arr,y[i],z[i],dir[i],array,location);

		/*stores every letter of each word on the board in all_location[][] array*/
		for(int f=0;f<strlen(words[i]);f++)
			all_location[i][f]=location[f];
	}
	
	/*to fill empty areas on the board with random character*/
	for(int j=1;j<=400;j++){
		if(arr1[j]<'a' || arr1[j]>'z')
			arr1[j] = 97 + rand()%26;
	}
	print_word_board(arr1,words);

	for(int counter=0;counter<10;counter++){  // if user finds ten words on the board, loop terminates

		flag=1;
		while(flag > 0){

			printf("\n\nPlease enter the coordinate and the word:\n");
			scanf(" %c%d%s",&row,&column,slctn);

			row-=65;
			(int)row;

			for(int y=0;y<10;y++){

				/*if word which user's word is true,this block runs*/
				if(strcmp(words[y],slctn) == 0){
					
					for(int d=0;d<strlen(words[y]);d++){

						/*in this algorithm,if word[y] is written normal order;
						**it checks whether the location where the first letter 
						**of the word is located and the location entered by the user are the same.
						**if word[y] is written reverse order;
						**it checks whether the location where the last letter 
						**of the word is located and the location entered by the user are the same.*/

						if(((row*20+column+1) == all_location[y][0]) || ((row*20+column+1) == all_location[y][strlen(words[y])])){
							cast1=(int)arr1[all_location[y][d]]-32; // converting to uppercase letter
							arr1[all_location[y][d]]=(char)cast1; 
							cast2=(int)words[y][d]-32; // converting to uppercase letter in word list
							words[y][d]=(char)cast2;
							flag=0;
						}
					}
				}
			}
		
			/*if user want to exit*/
			if(row == '('){
				flag -=5;
				counter = 10;
			}
			if(flag > 0)
				printf("\nwrong !!!\n\n\n");
			else
				system("clear");
		}
		print_word_board(arr1,words);
	}
}

void print_word_board(char arr1[], char words[][50]){
	int x=0;

	for(int i=0;i<10;i++)
		printf("%s\t",words[i]);

	printf("\n\n0   1   2   3   4   5   6   7   8   9   10   11  12  13  14  15  16  17  18  19\n\n");

	/*to print arr1 and in arr1, the position of each letter of each word is kept in the specific index*/
	for(int p=1;p<=400;p++){
		printf("%c   ",arr1[p]);

		/*since it is a 20x20 board*/
		if(p%20 == 0){
			/*to print row  i.e A,B,C etc.*/
			printf("<-%c\n",65+x); 
			x++;
		}
	}
}

/*this function checks that if the length of the word
 does not fit in the space, it will generate a new position.*/
void word_overflow(int *y, int *z, int *dir,char words[]){

	switch(*dir){

		case 1:		while(*z < strlen(words))			
						*z = 1+rand()%20;										 break;

		case 2:		while((20-*z+1) < strlen(words))	
						*z = 1+rand()%20;										  break;

		case 3:		while(*y < strlen(words))			
						*y = 1+rand()%20;										  break;

		case 4:		while((20-*y+1) < strlen(words))	
						*y = 1+rand()%20;										  break;

		case 5:		while(*z < strlen(words)+1 || *y < strlen(words)+1){	
						*z = 1+rand()%20;
						*y = 1+rand()%20;
					}															   break;	

		case 6:		while(*z < strlen(words)+1 || (20-*y+1) < strlen(words)+1){
						*z = 1+rand()%20;
						*y = 1+rand()%20;
					}															   break;

		case 7:		while((20-*z+1) < strlen(words)+1 || *y < strlen(words)+1){
						*z = 1+rand()%20;
						*y = 1+rand()%20;
					}															    break;

		case 8:		while((20-*z+1) < strlen(words)+1 || (20-*y+1) < strlen(words)+1){
						*z = 1+rand()%20;
						*y = 1+rand()%20;
					}																break;
	}
}

/* this function generates the location according to direction*/
char *one_direction(char *ptr, int y, int z, int dir, char words[], int location[]){

	int k=0,flag=1,flag1=1;

	switch(dir){

		case 1: 	for(int i=0;i<strlen(words);i++)			    // west
						location[i] = (y-1)*20+z-i;				    break;

		case 2: 	for(int i=0;i<strlen(words);i++)			    // east
						location[i] = (y-1)*20+z+i;				    break;

		case 3: 	for(int i=0;i<strlen(words);i++)			    // north
						location[i] = (y-1)*20+z-(i*20);		    break;

		case 4: 	for(int i=0;i<strlen(words);i++)				// south
						location[i] = (y-1)*20+z+(i*20);			break;

		case 5: 	for(int i=0;i<strlen(words);i++)				//northwest
						location[i] = (y-1)*20+z-(i*20)-(i+1);		break;

		case 6: 	for(int i=0;i<strlen(words);i++)				// southwest
						location[i] = (y-1)*20+z+(i*20)-(i+1);  	break;	

		case 7: 	for(int i=0;i<strlen(words);i++)				//northeast
						location[i] = (y-1)*20+z-(i*20)+(i+1);		break;

		case 8: 	for(int i=0;i<strlen(words);i++)				//southeast
						location[i] = (y-1)*20+z+(i*20)+(i+1);      break;

	}
	
	/*for control the conlflict*/
	for(int j=0;j<strlen(words) && flag1>0;j++){

		if(ptr[location[j]] < 'a' || ptr[location[j]] > 'z')
			k++;
		else
			flag1=0;

		if(k == strlen(words))
			flag=0;
	}
	
	if(flag == 0)
		for(int j=0;j<strlen(words);j++)
			ptr[location[j]] = words[j];

	/*it generates a new location if there is a conflict*/	
	if(flag1 == 0){

		y = 1+rand()%20;   // line number
		z = 1+rand()%20;	// column number
		dir = 1+rand()%8; // direction

		word_overflow(&y,&z,&dir,words);
		return one_direction(ptr,y,z,dir,words,location);	
	}
	return ptr;
}