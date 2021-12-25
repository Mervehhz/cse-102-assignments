#include <stdio.h>

void menu();
void read_news(char buffer[], char file_path[], int is_Only_Title);
void append_file(char* file_path, char c);
void read_magic_numbers(char buffer_magic[], char buffer_news[]);
double f_func(int x);
double g_func(double f(int x), int a);
void call_read_news(int text_number, int is_Only_Title);

void main(void){
	menu();
}

void menu(){

	int flag=1,flag1=1,text_number,y;
	char c,x,slctn,answr,buffer_magic[10],file_path[20]="readed_news_id.txt", news_buffer_1[500],file_path_1[11]="news/1.txt",file_path_2[11]="news/2.txt",file_path_3[11]="news/3.txt",file_path_4[11]="news/4.txt";

	/*Control flag for menu function looping*/
	while(flag > 0){

		call_read_news(text_number,1);

		printf("\nWhat do you want to do ?\n\n");
		printf("a -> Read a new\n");
		printf("b -> List the readed news\n");
		printf("c -> Get decrypted information from the news\n");

		scanf(" %c",&slctn);

		/*if user want to reads news*/
		if(slctn == 'a'){

			/*opening the readed_news_id.txt for read it*/
			FILE *fp=fopen("readed_news_id.txt","r");

			printf("which news text you want to read ?\n");
			scanf("%d",&text_number);

			/*reading the file's till end of file*/
			while(!feof(fp) && flag1 == 1){

				fscanf(fp," %c",&c);

				/*converting character c to integer*/
				y = (int)(c-48);

				/*if this news was read before*/
				if(text_number == y){

					printf("This news has been read before. Do you want to read it again?(y/n)\n");
					scanf(" %c",&answr);

					/*if user want to read this new again*/
					if(answr == 'y'){

						call_read_news(text_number,0);

						/*flag indicating that you have read the news you want to read*/
						flag1=0;

					}

					else 

						/*the flag which is if it does not want to read the news that it has read before*/
						flag1=0;
				}

			}

			/*if user didnt read this new before*/
			if(flag1 != 0){

				call_read_news(text_number,0);

				x = (char)(text_number);

				/*calling the fuction append_file*/
				append_file(file_path,x);

			}

			flag1=1;

			fclose(fp);

		}


		/*if user want to see the readed news, this function implement that it opens and reads the file and it prints contents of the file*/
		else if(slctn == 'b'){

			FILE *fp=fopen("readed_news_id.txt","r");

			printf("Readed news are listed below:\n");

			while(!feof(fp)){
				fscanf(fp,"%c",&c);

				if(!feof(fp))
					printf("%c. is readed\n",c);
			}
			fclose(fp);
		}

		/*if user want to decrypts the magic numbers in news text*/
		else if(slctn == 'c'){

			printf("which news would you like to decrypt ? -> ");
			scanf("%d",&text_number);

			if(text_number == 1){

				read_news(news_buffer_1, file_path_1, 0);
				printf("\n\nThe number of tests performed is ");
			}
			else if(text_number == 2){

				read_news(news_buffer_1, file_path_2, 0);
				printf("\n\nThe number of sick people is ");
			}
			else if(text_number == 3){

				read_news(news_buffer_1, file_path_3, 0);
				printf("\n\nThe number of deaths is ");
			}

			else{

				read_news(news_buffer_1, file_path_4, 0);
				printf("\n\nExpected number of sick people is ");
			}
			read_magic_numbers(buffer_magic,news_buffer_1);
		}

		/*if user enters something other than a b and c, he gets an error*/
		else
			printf("ERROR !\n");

		printf("\n\nDo you want to continue ? yes(y)/no(n)\n");
		scanf(" %c",&x);

		if(x == 'n'){
			printf("Good bye !\n");
			flag = 0;

		}

		else if(x == 'y');

		else
			printf("Please enter y or n !\n");

		/*if the user enters something other than yes or no to continue, he asks until yes or no.*/
		while(x != 'n' && x != 'y'){
			scanf(" %c",&x);
			if(x == 'n'){
				printf("Good bye !\n");
				flag = 0;
			}
			else if(x == 'y');
			else
				printf("Please enter y or n !\n");
		}
	}
}

/*in this function, read_news function is called according to the news that the user wants to read*/
void call_read_news(int text_number, int is_Only_Title){

	char news_buffer_1[500],file_path_1[11]="news/1.txt",file_path_2[11]="news/2.txt",file_path_3[11]="news/3.txt",file_path_4[11]="news/4.txt";

	if(is_Only_Title == 1){


		printf("\n\n\n**************! Daily Press !*****************\n\n\n");
		
		printf("Title of 1. news:");
		read_news(news_buffer_1,file_path_1,1);

		printf("Title of 2. news:");
		read_news(news_buffer_1,file_path_2,1);

		printf("Title of 3. news:");
		read_news(news_buffer_1,file_path_3,1);

		printf("Title of 4. news:");
		read_news(news_buffer_1,file_path_4,1);

	}

	else{
		if(text_number == 1)
			read_news(news_buffer_1, file_path_1, 0);
		else if(text_number == 2)
			read_news(news_buffer_1, file_path_2, 0);
		else if(text_number == 3)
			read_news(news_buffer_1, file_path_3, 0);
		else
			read_news(news_buffer_1, file_path_4, 0);
	}
}

/*this function reads the file according to the file path and puts it inside the buffer array.*/
void read_news(char buffer[], char file_path[], int is_Only_Title){

	char ch;
	int i=0;

	/*opening the file for reads its*/
	FILE *fp=fopen(file_path,"r");

	/*if file doesnt open this is implemented*/
	if(fp == NULL)

		printf("ERROR !\n");

	else{

		/*if user want to read only title*/
		if(is_Only_Title == 1){

			while(ch != '\n'){

				fscanf(fp,"%c",&ch);

				buffer[i] = ch;

				printf("%c",buffer[i]);

				i++;

			}

			/*to indicate the end of the file*/
			buffer[i+1] = '\0';

		}

		/*if user want to read entire new*/
		else{

			while(!feof(fp)){
		
				fscanf(fp,"%c",&ch);

				buffer[i] = ch;

				i++;

				if(ch == '\n'){

					printf("\n");
					fscanf(fp,"%c",&ch);

					buffer[i] = ch;

					i++;

				}
			}
			buffer[i+1]= '\0';
			printf("%s",buffer);
		}
	}
	fclose(fp);
}

/*file_path = readed_news_id.txt ; to write the name of the readed news files to the file path*/
void append_file(char* file_path, char c){

	int z;
	/*opening the file for appending*/
	FILE *fp=fopen(file_path,"a");

	z = (int)(c);
	fprintf(fp,"%d",z);
	fclose(fp);

}

/*reads the numbers next to the '#' sign in the file.*/
void read_magic_numbers(char buffer_magic[], char buffer_news[]){

	int i=0,k=0;
	double y=0.0;

	while(buffer_news[i] != '\0'){
		if(buffer_news[i] == '#'){
			/*to get the number next to the '#' sign*/
			i++;
			buffer_magic[k] = buffer_news[i];
			
			/*calling the g function when it coincides with the magic number.*/
			y += g_func(f_func,(int)(buffer_magic[k]-48));
			k++;
		}
		i++;
	}
	printf("%lf",y);
}

double f_func(int x){
	return (x*x*x -x*x + 2);
}

double g_func(double f(int x), int a){
	return f(a)*f(a);
}