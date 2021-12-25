#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
** Author : Merve horuz
*/

#define NUMBER_GAMES 2000
#define NUMBER_GENRE 12
#define NUMBER_PLATFORM 10
#define GENRE_PLATFORM_LENGTH 20
#define NAME_LENGTH 100
#define ALL_INFO 7
#define ROW_LENGTH 200
#define GENRE_INDEX 0
#define PLATFORM_INDEX 1
#define YEAR_INDEX 2
#define NA_INDEX 3
#define EU_INDEX 4
#define GLOBAL_INDEX 5
#define USER_SCORE_INDEX 6

void menu();
void names_function(char row[], char names_array[][NAME_LENGTH], int index);
void genres_function(char temp_genre[], char genres[][GENRE_PLATFORM_LENGTH],int *z);
void platforms_function(char temp_platform[], char platforms[][GENRE_PLATFORM_LENGTH], int *t);
void fill_all_information(float all_information[][ALL_INFO], char row[], int *index, int counter, int i);
void genre_float(float all_information[][ALL_INFO], char genres[][GENRE_PLATFORM_LENGTH], char temp_genre[GENRE_PLATFORM_LENGTH], int index);
void platform_float(float all_information[][ALL_INFO], char platforms[][GENRE_PLATFORM_LENGTH], char temp_platform[GENRE_PLATFORM_LENGTH], int index);
int frequence_platform_genre(int index, float all_information[][ALL_INFO],int genre_or_platform);
void print_genre_platform(char array[][GENRE_PLATFORM_LENGTH], int index);
void take_year_and_until_or_since(int *year, int *a);
void print_game_until_or_since_entered_date(int a, float all_information[][ALL_INFO], char names_array[][NAME_LENGTH], int year);
int find_index_entered_game(char names_array[][NAME_LENGTH], char name[NAME_LENGTH]);
float average(float all_information[][ALL_INFO]);
void print_genre_platform_frequence(char array[][GENRE_PLATFORM_LENGTH], float all_information[][ALL_INFO], int i);
void georographical_info(float all_information[][ALL_INFO], int index);
void all_info_single_game(char names_array[][NAME_LENGTH], char name[], char genres[][GENRE_PLATFORM_LENGTH], char platforms[][GENRE_PLATFORM_LENGTH], float all_information[][ALL_INFO], int index);


void main(void){

    int control=1,selection,k,z=0,t=0,u,j,year,a;
    char names_array[NUMBER_GAMES][NAME_LENGTH],genres[NUMBER_GENRE][GENRE_PLATFORM_LENGTH],platforms[NUMBER_PLATFORM][GENRE_PLATFORM_LENGTH],temp_genre[GENRE_PLATFORM_LENGTH],temp_platform[GENRE_PLATFORM_LENGTH],row[ROW_LENGTH],name[NAME_LENGTH];
    float all_information[NUMBER_GAMES][ALL_INFO];

    while(control > 0){

        FILE *fp=fopen("Video_Games.txt","r");

        menu();

        printf("\n\nplease select an operation-> ");
        scanf("%d",&selection);

        /*skipping first line*/
        fgets(row,ROW_LENGTH,fp);

        for(int i=0;i<NUMBER_GAMES;i++){

            fgets(row,ROW_LENGTH,fp);

            names_function(row,names_array,i);

            /*passed name of game*/
            for(k=0;row[k-1] != ',';k++);

            for(j=0;row[k] != ',';j++,k++)  /*taking genres of games*/
                temp_genre[j] = row[k];

            temp_genre[j] = '\0';
           
            genres_function(temp_genre,genres,&z);
            genre_float(all_information,genres,temp_genre,i);

            k++;
            for(u=0;row[k] != ',';u++,k++)  /*taking platforms of games*/
                temp_platform[u] = row[k];

            temp_platform[u] = '\0';
           
            platforms_function(temp_platform,platforms,&t);
            platform_float(all_information,platforms,temp_platform,i);

            fill_all_information(all_information,row,&k,i,YEAR_INDEX);
            fill_all_information(all_information,row,&k,i,NA_INDEX);
            fill_all_information(all_information,row,&k,i,EU_INDEX);
            fill_all_information(all_information,row,&k,i,GLOBAL_INDEX);
            fill_all_information(all_information,row,&k,i,USER_SCORE_INDEX);
                
        }

        fclose(fp);

        switch(selection){

            case 0:  print_genre_platform(genres,NUMBER_GENRE);                                                                            break;
            case 1:  print_genre_platform(platforms,NUMBER_PLATFORM);                                                                      break;
            case 2:  take_year_and_until_or_since(&year,&a);
                     print_game_until_or_since_entered_date(a,all_information,names_array,year);                                           break;           
            case 3:  all_info_single_game(names_array,name,genres,platforms,all_information,find_index_entered_game(names_array,name));    break;
            case 4:  printf("%f\n",average(all_information));                                                                              break;
            case 5:  georographical_info(all_information,find_index_entered_game(names_array,name));                                       break;
            case 6:  print_genre_platform_frequence(genres,all_information,NUMBER_GENRE);                                                  break;
            case 7:  print_genre_platform_frequence(platforms,all_information,NUMBER_PLATFORM);                                            break;
            case 8:  control = 0;                                                                                                          break;
            default : printf("\n\nTRY AGAIN !\n\n");

        }
    }
}


void menu(){

    printf("\n\n0-> list of the genres\n");
    printf("1-> list of the platforms\n");
    printf("2-> list of the games through the years\n");
    printf("3-> all informations of a single game\n");
    printf("4-> average of the user scores\n");
    printf("5-> georographical information of a single game\n");
    printf("6-> frequence of the genres\n");
    printf("7-> frequence of the platforms\n");
    printf("8-> exit\n\n");
}

/*in this algorithm, all informations are printed about single game*/
void all_info_single_game(char names_array[][NAME_LENGTH], char name[], char genres[][GENRE_PLATFORM_LENGTH], char platforms[][GENRE_PLATFORM_LENGTH], float all_information[][ALL_INFO], int index){

    printf("\n\n\nNAME\t\t->\t%s\n",name);
    printf("GENRE\t\t->\t%s\n",genres[(int)all_information[index][GENRE_INDEX]]);
    printf("PLATFORM\t->\t%s\n",platforms[(int)all_information[index][PLATFORM_INDEX]]);
    printf("YEAR\t\t->\t%0.2f\n",all_information[index][YEAR_INDEX]);
    printf("SALES IN NA\t->\t%0.2f\n",all_information[index][NA_INDEX]);
    printf("SALES IN EU\t->\t%0.2f\n",all_information[index][EU_INDEX]);

    if(all_information[index][GLOBAL_INDEX] == 0.0)
        printf("TOTAL SALES\t->\tnot available\n");
    
    else
        printf("TOTAL SALES\t->\t%0.2f\n",all_information[index][GLOBAL_INDEX]);

    printf("USER SCORE\t->\t%0.2f\n\n\n",all_information[index][USER_SCORE_INDEX]);

}



void georographical_info(float all_information[][ALL_INFO], int index){

     if(all_information[index][NA_INDEX] > all_information[index][EU_INDEX])
        printf("\nThis game was more popular in North America.\n");

    else if(all_information[index][NA_INDEX] < all_information[index][EU_INDEX])
        printf("\nThis game was more popular in Europe.\n");

    else 
        printf("\nThis game was popular in North America and Europe equally\n");

}



void print_genre_platform_frequence(char array[][GENRE_PLATFORM_LENGTH], float all_information[][ALL_INFO], int i){

    if(i == 10)

        for(int k=0;k<i;k++)
            printf("%-15s%-10d\n",array[k],frequence_platform_genre(k,all_information,PLATFORM_INDEX));
    else

        for(int k=0;k<i;k++)
            printf("%-15s%-10d\n",array[k],frequence_platform_genre(k,all_information,GENRE_INDEX));

}

/*in this algorithm, the arithmetic average is calculated to find the average of the user score*/
float average(float all_information[][ALL_INFO]){

    float result=0;

    for(int i=0;i<NUMBER_GAMES;i++)
        result += all_information[i][USER_SCORE_INDEX];

    return result/NUMBER_GAMES;
}


int find_index_entered_game(char names_array[][NAME_LENGTH],char name[NAME_LENGTH]){

    printf("\n\nplease enter the name of the game\n");
    scanf("%s",name);

     for(int m=0;m<NUMBER_GAMES;m++)
        if(strcmp(names_array[m],name) == 0)
            return m;

}


void print_game_until_or_since_entered_date(int a, float all_information[][ALL_INFO], char names_array[][NAME_LENGTH], int year){

    int flag=1,j,k;

    if(a == 0){

        for(j=0;j<NUMBER_GAMES && flag>0;j++)
            if(all_information[j][YEAR_INDEX] > (float)year || all_information[j][YEAR_INDEX] == (float)year)
                flag=0;

        for(int i=0;i<j-1;i++)
            printf("%s\n",names_array[i]);
        
    }

    else{

        for(k=0;k<NUMBER_GAMES && flag>0;k++)
            if(all_information[k][YEAR_INDEX] > (float)year)   
                flag = 0;

    
        for(int i=k-1;i<NUMBER_GAMES;i++)
            printf("%s\n",names_array[i]);

    }

}

void take_year_and_until_or_since(int *year, int *a){

    printf("\n\nenter a year -> ");
    scanf("%d",year);

    printf("until (0) or since (1) %d : ",*year);
    scanf("%d",a);

    if((*year == 1985 && *a == 0) || (*year == 2005 && *a == 1)){

        printf("\nTRY AGAIN\n\n");
        take_year_and_until_or_since(year,a);
    }
}


void print_genre_platform(char array[][GENRE_PLATFORM_LENGTH], int index){

    for(int i=0;i<index;i++)
        printf("%s\n",array[i]);

}


int frequence_platform_genre(int index, float all_information[][ALL_INFO], int genre_or_platform){

    int freq=0;

    for(int i=0;i<NUMBER_GAMES;i++)
        if(all_information[i][genre_or_platform] == (float)index)
            freq++;

    return freq;
    
}



/*this function converts the genre index and it stores all_information[][] array*/
void genre_float(float all_information[][ALL_INFO], char genres[][GENRE_PLATFORM_LENGTH], char temp_genre[GENRE_PLATFORM_LENGTH], int index){

    for(int i=0;i<NUMBER_GENRE;i++)
        if(strcmp(genres[i],temp_genre) == 0)
            all_information[index][GENRE_INDEX] = (float)i;

}

/*this function converts the platform index and it stores all_information[][] array*/
void platform_float(float all_information[][ALL_INFO], char platforms[][GENRE_PLATFORM_LENGTH], char temp_platform[GENRE_PLATFORM_LENGTH], int index){

    for(int i=0;i<NUMBER_PLATFORM;i++)
        if(strcmp(platforms[i],temp_platform) == 0)
            all_information[index][PLATFORM_INDEX] = (float)i;
}


/*this function takes name of game*/
void names_function(char row[], char names_array[][NAME_LENGTH], int index){

    int i;

    for(i=0;row[i] != ',';i++)
        names_array[index][i] = row[i];

    names_array[index][i] = '\0';

}


/*in this algorithm,different genres of game are stored in genres[][] array*/
void genres_function(char temp_genre[], char genres[][GENRE_PLATFORM_LENGTH], int *z){

    int flag=1;

    for(int k=0;k<NUMBER_GENRE;k++)
        if(strcmp(temp_genre,genres[k]) == 0)
            flag=0;

    if(flag != 0){

        strcpy(genres[*z],temp_genre);
        (*z)++;
    }
}

/*in this algorithm,different platforms of game are stored in genres[][] array*/
void platforms_function(char temp_platform[], char platforms[][GENRE_PLATFORM_LENGTH], int *t){

    int flag=1;

    for(int k=0;k<NUMBER_PLATFORM;k++)
        if(strcmp(temp_platform,platforms[k]) == 0)
            flag=0;

    if(flag != 0){

        strcpy(platforms[*t],temp_platform);
        (*t)++;
    }
}


/*in this algorithm, the all_information array is filled with year of release,sales in na, sales in eu, global sales and user score*/
void fill_all_information(float all_information[][ALL_INFO], char row[], int *index, int counter, int i){

    float tod;
    char *ptr,array[15];

    (*index)++;

    if(i != 6)
        for(int j=0;row[*index] != ',';(*index)++,j++)
            array[j] = row[*index];
            
    else
        for(int j=0;row[*index] != '\0';(*index)++,j++)
            array[j] = row[*index];
       
        tod = strtod(array,&ptr);
        bzero(array,15);
        all_information[counter][i] = tod;
        
}