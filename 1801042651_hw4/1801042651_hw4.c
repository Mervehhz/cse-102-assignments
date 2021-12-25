#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

/*
**Please add -lm at the end when compiling.
**Make sure the terminal is in full screen mode while printing the results in the terminal.
**thank you
*/

/*
**
**in this algorithm, in part1, i decrypted the secret message in the communication of enemies.
**in part2, i decrypted the secret message in the communication of enemies in 2nd file.
**in part3, Unfortunately, also the opponents know that we know their plans. Therefore, 
**they are constantly changing the position of their camps. i made a machine to track 
**the position of the enemy camp.
**in part4, i want to manipulate the enemies’ plans by leaking our messages into their network. 
**
**author : Merve Horuz
**
*/

/*declerating functions i will use*/
void decrypt_and_print (char* file_path);

char decrypt_numbers (int number);

void deep_decrypt_and_print (char* file_path);

void track_machine ();

void refresh_position (int *X, int *Y, double *D, double *R);

void encrypt_messages (char* file_path);

void menu ();

int encrypt_numbers (char symbol);



void main(void){

	menu();

}



/*this is menu function, it allows the user to selection.*/
void menu(){

	int slctn,cntrol=1;

	/*it allows to choose again from the menu after each selection.*/
	while(cntrol > 0){

		printf("\n1-> Decrypt and printf encrypted_p1.img\n");
		printf("2-> Decrypt and printf encrypted_p2.img\n");
		printf("3-> Switch on the tracking machine\n");
		printf("4-> Encrypt the message\n");
		printf("5-> switch off\n\n");

		printf("Please make your choice:\n");
		scanf("%d",&slctn);


	
		if(slctn == 1)

			decrypt_and_print("encrypted_p1.img");

		else if(slctn == 2)

			deep_decrypt_and_print("encrypted_p2.img");

		else if(slctn == 3)

			track_machine();

		else if(slctn == 4)

			encrypt_messages("decrypted_p4.img");

		else if(slctn == 5)

			cntrol = 0;

		else 

			printf("please enter number betweeen 1-5\n");

	}

}



/*decrypt_and_print function decrypts the secret message in encrypted_p1.img and it prints that.*/
void decrypt_and_print (char* file_path){

	int number;
	char buf;

	/*opening the file*/
	FILE *fp = fopen(file_path,"r");

	if(fp == NULL)

		printf("ERROR..\n");


	else{

		/*reading until end of file*/
		while(!feof(fp)){

			/*if character is '\n' then this algorithm applies, and it passes the next line.*/
			if(buf == '\n'){

				printf("\n");
				fscanf(fp,"%c",&buf);
				number = (int)(buf-48);

			}

			/*calling decrypt_numbers function's and printing the result*/
			printf("%c",decrypt_numbers(number));

			/*reading character from fp pointer*/
			fscanf(fp,"%c",&buf);
			/*converting character to integer*/
			number = (int)(buf-48);


		}

		/*closing the file*/
		fclose(fp);

	}

}



/*decrypting of reading character*/
char decrypt_numbers (int number){

	char chrctr;

	switch(number){


		case 0: chrctr = ' '; break;

		case 1: chrctr = '-'; break;

		case 2: chrctr = '_'; break;

		case 3: chrctr = '|'; break;

		case 4: chrctr = '/'; break;

		case 5: chrctr = '\\'; break;

		case 6: chrctr = 'O'; break;

	}

	return chrctr;

}



/*deep_decrypt_and_print function decrypts the secret message in encrypted_p2.img and it prints that */
void deep_decrypt_and_print (char* file_path){

	int x0=0,x1,counter=0;
	char buf;

	/*opening the file*/
	FILE *fp = fopen(file_path,"r");


	if(fp == NULL)

		printf("ERROR..\n");


	else{

		/*reading until end of file*/
		while(!feof(fp)){

			/*emptying the values ​​in x0*/
			x0=0;

			/*number[i]=(number[i]+number[i+1]+number[i+2])%7 ; applying this formula's*/
			for(int i=0;i<3;i++){

				/*if character is '\n' then it passes the next line*/
				if(buf == '\n')

					printf("\n");


				/*reading character from fp pointer*/
				fscanf(fp,"%c",&buf);

				if(buf == '\n')

					buf = 0; /*if end of line then zero the remaining numbers*/

			
				/*converting character to integer*/
				x1 = (int)(buf-48);

				/*addition of three numbers according to the formula and storing in x0 vaariable*/
				x0 += x1;

			}

			/*according to formula, calculating the module operation with seven sum's of three number */
			x0 %= 7;

			/*it counts how many times the loop repeats.*/
			counter++;

			/*calling decrypt_numbers function's and printing the result*/
			printf("%c",decrypt_numbers(x0));
			
			/*file closing and reopening for the file pointer showing the beginning of the file*/									
			fclose(fp);								
			FILE *fp = fopen(file_path,"r");		
			
			/*file pointer to show the next character at the end of each loop*/										
			for(int k=0;k<counter;k++)

				fscanf(fp,"%c",&buf);

		}

	}

	/*closing the file*/
	fclose(fp);

}



/*track_machine function determines location of enemies, the distance to our camp,the distance between current position and the last position of the enemy camp.*/
void track_machine (){

	int x0=1,y0=1,x1=1,y1=1,b=1;
	double D,R;
	char a;

	/*D is the distance of enemy to our camp and calculating D's*/
	D = sqrt((6-x0)*(6-x0)+(6-y0)*(6-y0));
	/*R is the distance between current position and the last position of the enemy camp and calculating R's*/	
	R = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));

	/*calling  the refresh_position function to print the current positions*/
	refresh_position(&x0,&y0,&D,&R);
	
	printf("\nCommand waiting...:");
	scanf(" %c",&a);


	while(b > 0){

		/*if the user chooses R, a new location is generated for the enemy.*/
		if(a == 'R'){

			srand(time(NULL));

			x1=1+rand()%11;
			y1=1+rand()%11;

			/*if the location of the enemy is the same as our camp location, it will generate a new location.*/
			if(x1 == 6 && y1 == 6){

				x1=1+rand()%11;
				y1=1+rand()%11;

			}

			D = sqrt((6-x1)*(6-x1)+(6-y1)*(6-y1));
			R = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));

			/*to calculate the distance between the last position of the enemy and the current position, x0,y0 represents the old position x1,y1 represents the new position.*/
			x0 = x1;
			y0 = y1;

			refresh_position(&x0,&y0,&D,&R);

			printf("\nCommand waiting...:");
			scanf(" %c",&a);


		}

		/*if user wants to terminate the loop then user presses 'E'*/
		else if(a == 'E')

			b = 0;

		/*if user enters something other than 'E' and 'R'*/
		else{

			printf("Please press E to terminate and R to continue.\n");

			printf("\nCommand waiting...:");
			scanf(" %c",&a);

		}

	}

}



/*refresh_position function prints new location, displacement and distance to our camp*/
void refresh_position (int *X, int *Y, double *D, double *R){


	for(int i=1;i<12;i++){

		for(int k=1;k<12;k++){

			if(*X == k && *Y == i){

				printf("E\t");
				k++;

			}

			if(i == 6 && k== 6){

				printf("O\t");
				k++;

			}

			printf(".\t");

		}

		printf("\n");

	}

	printf("Enemies X position:%d, Y position:%d, Displacement:%lf, Distance to our camp:%lf",*X,*Y,*R,*D);

}


/*this function manipulates the enemies’ plans by leaking our messages into their network*/
void encrypt_messages (char* file_path){

	char buffer;
	int y=0,num=0,num1=0,num2;

	/*opening files*/
	FILE *fp = fopen(file_path,"r");
	FILE *fp1 = fopen("encrypted_p4.img","w");


	if(fp == NULL || fp1 == NULL)

		printf("ERROR..\n");


	else{

		/*reading until end of file*/
		while(!feof(fp)){

			fscanf(fp,"%c",&buffer);

			/*if character is '\n' and is not end of file,then applies*/
			while(buffer == '\n' && !feof(fp)){

				/*it prints '\n' to encrypted_p4.img*/
				fprintf(fp1,"\n");

				/*it reads next character */
				fscanf(fp,"%c",&buffer);

				/*if file pointer shows the head of line, num=0 and num1=0*/
				num=0;
				num1=0;

			}

			/*calling the encrypted_numbers function to encrypt the reading values' from the file and storing the returned value in num2.*/
			num2=encrypt_numbers(buffer);

			/*number[i]=(number[i]+number[i-1]+number[i-2])%7   applying of this formula*/
			y = num+num1+num2;

			y %= 7;

			/*printing of encrypted numbers to fp1 file.*/
			fprintf(fp1,"%d",y);

			/*so that the characters in the file pass the next character at the end of each loop.*/
			num = num1;
			num1 = num2;

		}

	}

	/*closing files*/
	fclose(fp);
	fclose(fp1);

}


/*encrypting of reading character*/
int encrypt_numbers (char symbol){

	int number;

	switch(symbol){


		case ' ': number = 0; break;

		case '-': number = 1; break;

		case '_': number = 2; break;

		case '|': number = 3; break;

		case '/': number = 4; break;

		case '\\': number = 5; break;

		case 'O': number = 6; break;


	}

	return number;

}