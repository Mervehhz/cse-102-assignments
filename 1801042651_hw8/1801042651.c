#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/*
**i try to do the part 2 but i can't. i am really sorry :)
** author : Merve Horuz
*/

#define ARRAY_SIZE 500
#define MEAN_SIZE 10
#define N 8
#define NUMBER_ORI 640

void generate_hofstadters_sequence (int *arr, int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);
void menu_part_one();
void menu();
char* remove_duplicates (char* str);
void take_string(char array[]);
void install_pipes (int visited[][N], int x, int y, int orientation, int counter);
void fill_possible_location(int possible_location[], int x, int y, int *a);
void generate_coordinate(int location[], int possible_location[], int *x, int *y, int a);

void main(void){

    int selection,visited[N][N]={0},control=1;
    char string[ARRAY_SIZE],array[ARRAY_SIZE],*ptr;

    while(control > 0){

        menu();
        scanf("%d",&selection);

        switch(selection){

            case 1:  menu_part_one();                         break;
            case 2:  install_pipes (visited,0,0,0,0);         break;
            case 3:  take_string(array);
                     for(int i=1;i<strlen(array)+1;i++)  
                        string[i] = array[i-1];
                     
                    string[0] = 5;
                    ptr = remove_duplicates (string);  
                    printf("%s\n",ptr);                       break;
            case 4: control=0;                                break;
            default:  printf("TRY AGAIN ..");
                                

        }
    }
}


void menu(){

    printf("\n\nwelcome to homework 8, please choose one of the part to continue\n-----------------------------\n");
    printf("1-> Execute part 1\n2-> Execute part 2\n3-> Execute part 3\n4-> Exit\n\n");

}

void install_pipes (int visited[][N], int x, int y, int orientation, int counter){

    int location[N],possible_location[N],previous_location[NUMBER_ORI],a,flag=0,flag1=0;

    location[0] = 8*x+y+25;  //O1
    location[1] = 8*x+y+5;   //O2
    location[2] = 8*x+y-25;  //O3
    location[3] = 8*x+y-5;   //O4
    location[4] = 8*x+y+11;  //O5
    location[5] = 8*x+y+23;  //O6
    location[6] = 8*x+y-11;  //O7
    location[7] = 8*x+y-23;  //O8

    fill_possible_location(possible_location,x,y,&a);
    generate_coordinate(location,possible_location,&x,&y,a);

    previous_location[counter]=location[possible_location[a]];
    
    if(visited[x][y] != 0){

        while(visited[x][y] != 0 && flag < 7){

            fill_possible_location(possible_location,x,y,&a);
            generate_coordinate(location,possible_location,&x,&y,a);
            previous_location[counter]=location[possible_location[a]];
            flag++;
        }
        
        while(visited[x][y] != 0 && flag == 7){
        
            x=previous_location[--counter] / 8;
            y=previous_location[--counter] % 8;
            flag1++;

            fill_possible_location(possible_location,x,y,&a);
        }

        for(int i=0;i<flag1++;i++)
            counter++;
    }

    visited[x][y] = possible_location[a];

    printf("O%d\t",visited[x][y]+1);

    if(orientation % 64 == 0){

        printf("\nA proper orientation set is : ");
        counter=0;
    }
    
    if(orientation < 64){

        ++orientation;
        ++counter;
        install_pipes(visited,x,y,orientation,counter);  
    }
}

void generate_coordinate(int location[], int possible_location[], int *x, int *y, int a){

    *x=location[possible_location[a]] / 8;
    *y=location[possible_location[a]] % 8;
}


void fill_possible_location(int possible_location[], int x, int y, int *a){

    int k=0;

    srand(time(NULL));

    if(8-x > 2 && 8-y > 0){
        possible_location[k]=0; k++;
    }

    if(8-x > 0 && y > 2){
        possible_location[k]=1; k++;
    }

    if(x > 2 && y > 0){
        possible_location[k]=2; k++;
    }

    if(x > 0 && 8-y > 2){
        possible_location[k]=3; k++;
    }

    if(8-x > 0 && 8-y > 2){
        possible_location[k]=4; k++;
    }

    if(8-x > 2 && y > 0){
        possible_location[k]=5; k++;
    }

    if(x > 0 && y > 2){
        possible_location[k]=6; k++;
    }

    if(x > 2 && 8-y > 0){
        possible_location[k]=7; k++;
    }

    /*choosing the location randomly in possible location*/
    *a=rand()%k;
}

void take_string(char array[]){

    printf("\n\nplease enter string\n");
    scanf(" %[^\n]s", array);

}

char* remove_duplicates (char* str){

    char *ptr,new_string[ARRAY_SIZE];
   
    for(int i=1,k=0;i<strlen(str);i++)
        if(str[i] != str[i+1]){
            
            new_string[k] = str[i];
            k++;
        }
    
    ptr = new_string;

    return ptr;
}


void menu_part_one(){

    int op,arr[ARRAY_SIZE] = {0},n;
    double mean[MEAN_SIZE];

    printf("\nplease enter the number\n");
    scanf("%d",&n);
    
    generate_hofstadters_sequence (arr,n);

    while(op != 5){

        printf("\n\nplease make your choice\n----------------\n");
        printf("1-> Fill array\n2-> Find biggest number\n3-> Calculate sum\n4-> Calculate standard deviation\n5-> Exit\n");
        scanf("%d",&op);

        switch (op){
        
            case 1:    generate_hofstadters_sequence (arr,n);              break;
            case 2:    find_max (arr,n,0);                                 break;    
            case 3:    printf("sum of array is %d\n",sum_array (arr));     break;
            case 4:    printf("%lf\n",sqrt(std_array (arr,mean,n,0)));     break;
            default:   printf("TRY AGAIN\n");                              break;

        }
    }
}

/*in this algorithm, arr is filled with hofstadter sequence by using recursive func.*/
void generate_hofstadters_sequence (int *arr, int n){

    if(n > 1)
        generate_hofstadters_sequence(arr,n-1);

    if(n < 3)
        arr[n-1] = 1;

    else   
        arr[n-1] = arr[n-1-arr[n-2]]+arr[n-1-arr[n-3]];

}


int find_max (int arr[], int index, int max_value){

    if(arr[index-1] > max_value)
        max_value = arr[index-1];

        index--;
    
    if(index > 0)
        return find_max(arr,index,max_value);
    
    printf("Maximum value is %d\n",max_value);

}


int sum_array (int arr[]){

    if(*arr != 0 && *arr != ARRAY_SIZE-1)
        return *arr+sum_array(++arr);
}


double std_array (int arr[], double *mean, int n, int index){

    /*finding of sum of array elements*/
    *mean = sum_array(arr)/(float)n;

    if(index != n){
        
        /*calculating of standard deviation of array elements*/
        *(mean+1) += (arr[index]-*(mean))*(arr[index]-*(mean));
        std_array(arr,mean,n,++index);
    }

    else 
       return *(mean+1) /= (n-1);
}