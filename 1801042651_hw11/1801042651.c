#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define OP_NUM 4
#define NODE_SIZE 8

typedef struct dnode{

    int data;
    struct dnode * next;
}node;

typedef struct{

    int n1,n2;
}arr;

int * read_array(char*, int*);
void print_time_taken_for_read_array_function(int*, int, clock_t);
void print_time_taken_for_read_linkedlist_function(node*, int, clock_t);
node * read_linkedlist(char*, int*);
float * stats_array(int*);
float * stats_linkedlist(node*);
float finding_min_value(int*, float);
float finding_max_value(int*);
float calculating_mean_value(int*);
float calculating_std_value(int*, float);
float finding_min_value_linklist(node*, float);
float finding_max_value_linklist(node*);
float calculating_mean_value_linklist(node*);
float calculating_std_value_linklist(node*, float);
arr * find_different_numbers_between_two_array();
int * take_elements_dynamical_array(int*, int*);
void take_elements_linklist(node**);

void main(void){
    clock_t end_array=0,start_array=0,start_link=0,end_link=0;
    int * ip=0,* integers,byte_array=0,byte_link=0;
    node * root=(node*)malloc(sizeof(node)),*head;
    arr * differ;
    float average_array=0,average_link=0;

    start_array = clock();     integers=read_array("list.txt",&byte_array);     end_array = clock();     byte_array=0;   average_array += end_array-start_array;
    start_link = clock();      head=read_linkedlist("list.txt",&byte_link);     end_link = clock();      byte_link=0;    average_link += end_link-start_link;
    start_array = clock();     integers=read_array("list.txt",&byte_array);     end_array = clock();     byte_array=0;   average_array += end_array-start_array;
    start_link = clock();      head=read_linkedlist("list.txt",&byte_link);     end_link = clock();      byte_link=0;    average_link += end_link-start_link;
    start_array = clock();     integers=read_array("list.txt",&byte_array);     end_array = clock();     byte_array=0;   average_array += end_array-start_array;
    start_link = clock();      head=read_linkedlist("list.txt",&byte_link);     end_link = clock();      byte_link=0;    average_link += end_link-start_link;
    start_array = clock();     integers=read_array("list.txt",&byte_array);     end_array = clock();                     average_array += end_array-start_array;
    start_link = clock();      head=read_linkedlist("list.txt",&byte_link);     end_link = clock();                      average_link += end_link-start_link;
    print_time_taken_for_read_array_function(integers,byte_array,average_array/4);
    print_time_taken_for_read_linkedlist_function(head,byte_link,average_link/4);
    printf("\nif we use the link list method, it will take more time and use more memory. but with the dynamic array method it takes both less memory and less time.\n\n");

    differ=find_different_numbers_between_two_array(ip,root);

    for(int i=0;differ[i].n1 != -1;i++)
        printf("\nDIFFERENT NUMBERS ->>> %d\t%d\n",differ[i].n1,differ[i].n2);

    free(differ);
}

void print_time_taken_for_read_array_function(int* integers, int byte, clock_t average){
    float * ops;
    clock_t strt,nd;

    /*it calculates that how long time takes functions of stats_array and read_array*/
    strt = clock();     ops = stats_array(integers);          nd=clock();
    
    free(integers);

    printf("\n~~~~~~~~FOR READ_ARRAY FUNCTION~~~~~~~~~\n\n");
    printf("required number of bytes = %d\ttime taken = %lf\tmin value = %f\tmax value = %f\tmean value = %f\tstd deviation = %f\n\n",byte,(double)average/CLOCKS_PER_SEC,*(ops+1),*ops,*(ops+2),*(ops+3));
    printf("\n~~~~~~~~FOR STATS_ARRAY FUNTION~~~~~~~~~\n\ntime taken = %lf\n",(double)(nd-strt)/CLOCKS_PER_SEC);
    free(ops);
}

/*in this algoirithm, max min mean and std deviation are found in array and these are stored in ops*/
float * stats_array(int * integers){
    float * ops;

    ops=(float*)calloc(OP_NUM,sizeof(float));           
    *ops = finding_max_value(integers);
    *(ops+1) = finding_min_value(integers,*ops);
    *(ops+2) = calculating_mean_value(integers);
    *(ops+3) = calculating_std_value(integers,*(ops+2));

    return ops;
}

void print_time_taken_for_read_linkedlist_function(node* root, int byte, clock_t average){
    float * op;
    clock_t strt,nd;

    strt = clock();     op = stats_linkedlist(root);                     nd=clock();
    
    free(root);

    printf("\n~~~~~~~~FOR READ_LINKEDLIST FUNCTION~~~~~~~~~\n\n");
    printf("required number of bytes = %d\ttime taken = %lf\tmin value = %f\tmax value = %f\tmean value = %f\tstd deviation = %f\n\n",byte,(double)average/CLOCKS_PER_SEC,*(op+1),*op,*(op+2),*(op+3));
    printf("\n~~~~~~~~FOR STATS_LINKEDLIST FUNCTION~~~~~~~~~\n\ntime taken = %lf\n",(double)(nd-strt)/CLOCKS_PER_SEC);
    free(op);
}

float * stats_linkedlist(node* root){
    float * op;

    op=(float*)calloc(OP_NUM,sizeof(float));          
    *op = finding_max_value_linklist(root);
    *(op+1) = finding_min_value_linklist(root,*op);
    *(op+2) = calculating_mean_value_linklist(root);
    *(op+3) = calculating_std_value_linklist(root,*(op+2));
    
    return op;
}

/*in this func, in file numbers are placed to dynamical array*/
int * read_array(char* filename, int* byte){
    int * integers=(int*)malloc(sizeof(int));
    int num,i;
    FILE * fp = fopen(filename,"r");

    if(fp == NULL)
        printf("\nfatal error in main() while opening the file\n");
    else{

        for(i=0;!feof(fp);i++){
            fscanf(fp,"%d,",&num);
            integers[i]=num;
            integers=(int*)realloc(integers,sizeof(int)*(i+2));
            *byte += sizeof(int);
        }
        integers[i]=-1;
        fclose(fp);
    }
    *byte += sizeof(int)*2+sizeof(FILE*);   /*for int num, int i and FILE* fp*/
    return integers;
}

/*in file numbers are placed to linkedlist*/
node * read_linkedlist(char * filename, int* byte){
    node *root,*iter=NULL;
    FILE * fp = fopen(filename,"r");
    int num; 

    while(!feof(fp)){
        fscanf(fp,"%d,",&num);

        /*if linklist is empty, first node is generated*/
        if(iter == NULL){
            iter=(node*)malloc(sizeof(node));
            iter->data=num;
            iter->next=NULL;
            root=iter;
        }
        /*adding to end*/
        else{
            while(iter->next != NULL) iter=iter->next;

            iter->next=(node*)malloc(sizeof(node));
            iter->next->data=num;
            iter->next->next=NULL;
            *byte += NODE_SIZE;
        }
    }
    fclose(fp);
    *byte += NODE_SIZE+sizeof(int)+sizeof(FILE*); /*for int num, size of first node and FILE* fp*/
    return root;
}

float finding_min_value(int* integers, float max){
    float min=max;

    for(int i=0;integers[i] != -1;i++)
        if(integers[i] < min)
            min = integers[i];
    return min;
}

float finding_max_value(int* integers){
    int max=0;

    for(int i=0;integers[i] != -1;i++)
        if(integers[i] > max)
            max = integers[i];
    return max;
}

float calculating_mean_value(int* integers){
    float sum=0;
    int i;
    
    for(i=0;integers[i] != -1;i++)
        sum += integers[i];
    return sum/(i-1);
}

/*sqrt((o-e1)+(o-e2)+(o-e3).../n-1)*/
float calculating_std_value(int* integers, float mean){
    float result=0;
    int i;
    
    for(i=0;integers[i] != -1;i++)
        result += (integers[i]-mean)*(integers[i]-mean);

    result /= (i-2);
    return sqrt(result);
}

float finding_min_value_linklist(node * root, float max){
    float min=max;
    
    root = root->next;
    while(root->next != NULL){
        if(root->data < min)
            min = root->data;
          
        root = root->next;
    }
    return min;
}

float finding_max_value_linklist(node * root){
    float max=0;

    while(root->next != NULL){
        if(root->data > max)
            max = root->data;

        root = root->next;
    }
    return max;
}

float calculating_mean_value_linklist(node * root){
    float sum=0;
    int i;
    
    for(i=0;root != NULL;i++){
        sum += root->data;
        root = root->next;
    }
    return sum/(i-1);
}

/*sqrt((o-e1)+(o-e2)+(o-e3).../n-1)*/
float calculating_std_value_linklist(node * root, float mean){
    float result=0;
    int i;
    
    for(i=0;root->next != NULL;i++){
        result += (root->data-mean)*(root->data-mean);
        root = root->next;
    }
    result /= (i-1);
    return sqrt(result);
}

/*in this algorithm, different numbers are determined in list which user's entered*/
arr * find_different_numbers_between_two_array(int * ip, node * root){
    int *ipb=NULL,i,k;
    arr * diff=(arr*)malloc(sizeof(arr));

    printf("\n\nPART 2 STARTING...\n");

    ip=take_elements_dynamical_array(ip,ipb);
    take_elements_linklist(&root);

    for(i=0,k=0;ip[i] != -1;i++){
        if(ip[i] != root->data){
            diff[k].n1=ip[i];
            diff[k].n2=root->data;
            k++;
            diff=(arr*)realloc(diff,sizeof(arr)*(i+2));
        }
        root = root->next;
    }
    diff[k].n1=-1;

    free(root);
    free(ip);
    return diff;
}

/*it places the first list which users's entered to dynamical array*/
int * take_elements_dynamical_array(int * ip, int * ipb){
    int data,counter=0;

    printf("\n\nenter numbers in dynamical array if you exit, then enter a number less than or equal to zero\n");

    do{
        scanf("%d",&data);
        counter++;

        ip=(int*)calloc(counter,sizeof(int)); /*each time the user enters a number, it is allocated as the total number*/
        for(int i=0;i<counter-1;i++) 
            ip[i] = ipb[i];

        ip[counter-1]=data;
        ipb=ip;
        
    }while(data > 0);  /*if the number smaller than 0 or 0 enters, the loop ends.*/
    ip[counter-1] = -1; /*-1 is placed to end of array to know the end of array*/
    
    return ip;
}

/*it places the second list which users's entered to linked list*/
void take_elements_linklist(node ** root){
    int data;
    node *iter=NULL;
    
    printf("\n\nenter numbers in linked list if you exit, then enter a number less than or equal to zero\n");

    do{
        scanf("%d",&data);

        /*if linklist is empty, first node is generated*/
        if(iter == NULL){
            iter=(node*)malloc(sizeof(node));
            iter->data=data;
            iter->next=NULL;
            *root=iter;
        }
        /*adding to end and elements smaller than 0 and 0 are not added to the list*/
        else if(root != NULL && data > 0){
            while(iter->next != NULL) iter=iter->next;

            iter->next=(node*)malloc(sizeof(node));
            iter->next->data=data;
            iter->next->next=NULL;
        }
    }while(data > 0);
}