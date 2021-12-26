#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*please while you compile this code, add -lm*/

#define LINE_LENGTH 100
#define FLOAT_NUM_LENGTH 10
#define NAME_LENGTH 5
#define MOST_COMPONENTS_PG 20
#define MOST_2D_OBJE 100
#define ACTION_LENGTH 9
#define PI 3.14159265
#define COEFF_NUM 3

struct objects_point{

    char name[NAME_LENGTH];
    float x_coord;
    float y_coord;
}point[MOST_2D_OBJE];

struct objects_line{

    char name[NAME_LENGTH];
    struct objects_point p_one;
    struct objects_point p_two;
}line[MOST_2D_OBJE];

struct objects_polygon{

    char name[NAME_LENGTH];
    struct objects_point points_pg[MOST_COMPONENTS_PG];
    struct objects_line lines_pg[MOST_COMPONENTS_PG];
}polygon[MOST_2D_OBJE];

void open_file();
void read_file(FILE*);
void take_point_data(char*, int*);
void assignment_struct(char*, int*, int);
void take_line_data(char*, int*, int);
void take_points_on_line(char*, char*, int*, int, int);
void filling_struct_according_to_type_polygon(char*, int*, int, int);
void take_polygon_data(char*, int*, char*, int, int*, int, int);
void find_edge_number_polygon(char*, int*);
int find_point_name_index(char*, int);
int find_line_name_index(char*, int);
int find_polygon_name_index(char*, int);
void take_point_line_polygon_name(char*, int*, char*);
void opening_file_to_be_written(FILE*, char*, int, int,int);
void take_actions(int, FILE*, FILE*, int, int, int);
void calculate_distance(char*, int, int, FILE*, int);
void calculate_angle(char*, int, int, FILE*);
void calculate_length(FILE*, char*, int, int, int, int);
void calculate_area(FILE*, char*, int, int, int);
void two_points_distance_writing_to_file(FILE*, char*, char*, int, int, float*);
void line_and_point_distance_writing_to_file(FILE*, char*, char*, int, int);
void area_with_point_writing_to_file(FILE*, int, char*);
void area_with_line_writing_to_file(FILE*, int, char*, int);
void check_different_points(char corner[][NAME_LENGTH], int, int);
float line_length_calculate(char*, int);
void how_many_edge(int*, int);
void line_equation(int, int*);

void main(void){

    open_file();
}

void open_file(){

    FILE* fp=fopen("commands.txt","r");

    if(fp == NULL)
        printf("\nfatal error in open_file() while opening the file\n");

    else
        read_file(fp);
}

/*in this function, line, point and polygon functions are called to read as much as the number of data.*/
void read_file(FILE* fp){

    char one_line[LINE_LENGTH];
    int point_num=0,line_num=0,polygon_num=0,object_num,point_index=0,line_index=0,pg_index=0;
    
    fgets(one_line,LINE_LENGTH,fp);
    fgets(one_line,LINE_LENGTH,fp);

    object_num=atoi(one_line);

    fgets(one_line,LINE_LENGTH,fp);

    while(object_num > 0){
        
        /*for points*/
        if(one_line[0] == ' ' || isdigit(one_line[0])){
            take_point_data(one_line,&point_index);
            point_num++;
        }
        /*for lines*/
        else if(one_line[6] == 'L'){
            take_line_data(one_line,&line_index,point_num);
            line_num++;
        }
        /*for polygons*/
        else{
            filling_struct_according_to_type_polygon(one_line,&pg_index,point_num,line_num);
            polygon_num++;
        }
        fgets(one_line,LINE_LENGTH,fp);
        object_num--;
    }
    opening_file_to_be_written(fp,one_line,point_num,line_num,polygon_num);
}

void take_point_data(char one_line[], int* point_index){
    int i;
   
    for(i=0;one_line[i] == ' ';i++);
    assignment_struct(one_line,&i,*point_index);
    (*point_index)++;
}

/*in this algorithm, retrieves name and coordinates for point data and saves them in the structure*/
void assignment_struct(char one_line[], int* i, int point_index){

    char float_num[FLOAT_NUM_LENGTH],*ptr;
    int k;

    for(k=0;one_line[*i] != ' ';(*i)++,k++)
        float_num[k]=one_line[*i];
    
    point[point_index].x_coord=strtod(float_num,&ptr);
    for(;one_line[*i] == ' ';(*i)++);

    for(k=0;one_line[*i] != ' ';(*i)++,k++)
        float_num[k]=one_line[*i];

    point[point_index].y_coord=strtod(float_num,&ptr);
    for(;one_line[*i] == ' ';(*i)++);

    for(k=0;one_line[*i] != ' ';(*i)++,k++)
        float_num[k]=one_line[*i];

    float_num[k-3]='\0';

    strcpy(point[point_index].name,float_num);
}

void take_line_data(char one_line[], int* line_index, int point_num){

    int k,i=0;
    char names[NAME_LENGTH];
     
    take_points_on_line(names,one_line,&i,*line_index,point_num);    

    /*to take the line name*/
    i++;
    for(k=0;one_line[i+1] != '\n' && one_line[i+1] != '/';i++,k++)
        names[k]=one_line[i];

    strcpy(line[*line_index].name,names);
    (*line_index)++;
}

void take_points_on_line(char names[], char one_line[], int* i, int line_index, int point_num){

    int k,p_index;

    take_point_line_polygon_name(one_line,i,names); /*taking the start point of line name*/
    p_index=find_point_name_index(names,point_num); /*to get the index of this name in point structure*/
    line[line_index].p_one=point[p_index];          /*saving the information in this index of the point structure to the line structure*/
    (*i)++;
    
    take_point_line_polygon_name(one_line,i,names);
    p_index=find_point_name_index(names,point_num);
    line[line_index].p_two=point[p_index];
}

/*in this algorithm, polygon type is determined (points or line)*/
void filling_struct_according_to_type_polygon(char one_line[], int* pg_index, int point_num, int line_num){

    char names[NAME_LENGTH];
    int point_or_line,k,i=0;

    if(one_line[0] == 'P'){
        point_or_line=0;
        take_polygon_data(one_line,pg_index,names,point_or_line,&i,point_num,line_num);
    }
    else{
        point_or_line=1;
        take_polygon_data(one_line,pg_index,names,point_or_line,&i,point_num,line_num);
    }
    take_point_line_polygon_name(one_line,&i,names);
    strcpy((char*)polygon[(*pg_index)-1].name,names);
}

void take_polygon_data(char one_line[],int* pg_index, char names[], int point_or_line, int* i, int point_num, int line_num){
    int k,edge_num=0,p_index,l_index;

    find_edge_number_polygon(one_line,&edge_num);
    
    for(int j=0;j<edge_num;j++){

        take_point_line_polygon_name(one_line,i,names);

        if(!point_or_line){
            p_index=find_point_name_index(names,point_num); /*calculation of which the index of the point structure of the ith corner of the polygon*/
            polygon[*pg_index].points_pg[j]=point[p_index]; /*saving informations to polygon structure*/
        }
        else{
            l_index=find_line_name_index(names,line_num);
            polygon[*pg_index].lines_pg[j]=line[l_index];
        }
        (*i)++;
    }
    (*pg_index)++;
}

void take_point_line_polygon_name(char* one_line, int* i, char* names){

    int k;
    for(k=0;one_line[*i] != ' ' && one_line[(*i)+1] != '\n' && one_line[*i] != '\0';(*i)++,k++)
        names[k]=one_line[*i];
    names[k]='\0';
}

int find_line_name_index(char* names, int line_num){

    for(int k=0;k<line_num;k++)
        if(!strcmp(line[k].name,names))
            return k;
}

int find_point_name_index(char* names, int point_num){

    for(int k=0;k<point_num;k++)
        if(!strcmp(point[k].name,names))
            return k;
}

int find_polygon_name_index(char* names, int polygon_num){

    for(int k=0;k<polygon_num;k++)
        if(!strcmp(polygon[k].name,names))
            return k;
}

void find_edge_number_polygon(char one_line[], int* edge_num){
    int i=0;

    while(one_line[i] != 'G'){
        if(one_line[i] == ' ')
            (*edge_num)++;

        i++;
    }
}

void opening_file_to_be_written(FILE* fp, char* one_line, int point_num, int line_num, int polygon_num){
    int actions_num;

    while(strcmp(one_line,"actions")){
        fgets(one_line,LINE_LENGTH,fp);
        one_line[strlen(one_line)-2]='\0';
    }
    fgets(one_line,LINE_LENGTH,fp);
    one_line[strlen(one_line)-2]='\0';

    FILE* fd=fopen(one_line,"w");

    if(fd == NULL)
         printf("\nfatal error in opening_file_to_be_written() while opening the file\n");

    else{
        fgets(one_line,LINE_LENGTH,fp);
        actions_num=atoi(one_line);     /*atoi function coverts ascii to integer*/
        take_actions(actions_num,fp,fd,point_num,line_num,polygon_num);
    }
}

/*this function gets actions*/
void take_actions(int actions_num, FILE* fp, FILE* fd, int point_num, int line_num, int polygon_num){

    char actions[actions_num][LINE_LENGTH],act[ACTION_LENGTH];
    int k;

    for(int i=0;i<actions_num;i++){
        fgets(actions[i],LINE_LENGTH,fp);

        for(k=0;actions[i][k] != ' ';k++)
            act[k]=actions[i][k];
        act[k]='\0';
       
        if(!strcmp(act,"Distance"))    calculate_distance(actions[i],k,point_num,fd,line_num);
        else if(!strcmp(act,"Angle"))  calculate_angle(actions[i],k,line_num,fd);
        else if(!strcmp(act,"Length")) calculate_length(fd,actions[i],k,line_num,polygon_num,point_num);
        else                           calculate_area(fd,actions[i],k,polygon_num,point_num);
    }
    fclose(fp);
    fclose(fd);
}

void calculate_distance(char* actions, int k, int point_num, FILE* fd, int line_num){
    char name_one[NAME_LENGTH],name_two[NAME_LENGTH];
    int flag=1;
    float result;
    
    k++;take_point_line_polygon_name(actions,&k,name_one);  /*taking the first name*/
    k++;take_point_line_polygon_name(actions,&k,name_two);  /*taking the second name*/
    
    if(name_one[0] == 'P' && name_two[0] == 'P')
        two_points_distance_writing_to_file(fd,name_one,name_two,point_num,flag,&result);
    else
        line_and_point_distance_writing_to_file(fd,name_one,name_two,point_num,line_num);
}

/*if we are asked to calculate the distance between two points*/
void two_points_distance_writing_to_file(FILE* fd, char* name_one, char* name_two, int point_num, int flag, float* result){
    int one,two;

    one=find_point_name_index(name_one,point_num);
    two=find_point_name_index(name_two,point_num);
    
    /*result = sqrt((x2-x1)^2 + (y2-y1)^2)*/
    *result=sqrt(pow(point[two].x_coord-point[one].x_coord,2)+pow(point[two].y_coord-point[one].y_coord,2));

    if(flag)
        fprintf(fd,"Distance(%s,%s) = %.1f\n",name_one,name_two,*result);
}

/*if we are asked to calculate the distance between one point and one line*/
void line_and_point_distance_writing_to_file(FILE* fd, char* name_one, char* name_two, int point_num, int line_num){
    int one,two;
    int coefficients[COEFF_NUM];
    float result;

    /*first name is point*/
    if(name_one[0] == 'P'){
        one=find_point_name_index(name_one,point_num);
        two=find_line_name_index(name_two,line_num);
        line_equation(two,coefficients);
    
        /*result = |a.x0+b.y0+c| / sqrt(a^2+b^2)*/
        result=abs(coefficients[0]*point[one].x_coord+coefficients[1]*point[one].y_coord+coefficients[2])/sqrt(coefficients[0]*coefficients[0]+coefficients[1]*coefficients[1]);
        fprintf(fd,"distance(%s,%s) = %.1f\n",point[one].name,line[two].name,result);                            
    }
    /*first name is line*/
    else{                                                                       
        one=find_line_name_index(name_one,line_num);
        two=find_point_name_index(name_two,point_num);
        line_equation(one,coefficients);

        result=abs(coefficients[0]*point[two].x_coord+coefficients[1]*point[two].y_coord+coefficients[2])/sqrt(coefficients[0]*coefficients[0]+coefficients[1]*coefficients[1]);
        fprintf(fd,"distance(%s,%s) = %.1f\n",point[two].name,line[one].name,result);   
    }
}

/*in this function, coefficients of equation of line are taked to coefficients array*/
void line_equation(int index, int* coefficients){

    int b=(line[index].p_two.y_coord-line[index].p_one.y_coord);    /*y2-y1*/
    int a=(line[index].p_two.x_coord-line[index].p_one.x_coord);    /*x2-x1*/

    coefficients[0]=b;  coefficients[1]=(-1)*a;  coefficients[2]=-1*(b*line[index].p_two.x_coord)+a*line[index].p_two.y_coord;
}

void calculate_angle(char* actions, int k, int line_num, FILE* fd){
    char name_one[NAME_LENGTH],name_two[NAME_LENGTH];
    int one,two,vector1_x,vector1_y,vector2_x,vector2_y,len1,len2;
    float result;

    k++;take_point_line_polygon_name(actions,&k,name_one);
    k++;take_point_line_polygon_name(actions,&k,name_two);
    
    one=find_line_name_index(name_one,line_num);
    two=find_line_name_index(name_two,line_num);

    /*cos(a) = (x1*x2 + y1*y2)/|L1|*|L2|*/
    vector1_x=line[one].p_two.x_coord-line[one].p_one.x_coord;
    vector1_y=line[one].p_two.y_coord-line[one].p_one.y_coord;
    vector2_x=line[two].p_two.x_coord-line[two].p_one.x_coord;
    vector2_y=line[two].p_two.y_coord-line[two].p_one.y_coord;

    len1=line_length_calculate(name_one,line_num);
    len2=line_length_calculate(name_two,line_num);

    result=(vector1_x*vector2_x+vector1_y*vector2_y)/(len2*len1);

    result = acos(result)*180/PI;

    if(result == 180)
        fprintf(fd,"angle(%s,%s) = 0\n",name_one,name_two);
    else
        fprintf(fd,"angle(%s,%s) = %.1f\n",name_one,name_two,result);
}

/*it checks whether the length of the line or the length of the polygon*/
void calculate_length(FILE* fd, char* actions, int k, int line_num, int polygon_num, int point_num){
    char name[NAME_LENGTH];
    int l_index,p_index,edge_num=0;
    float final_result=0,result;
    
    k++;take_point_line_polygon_name(actions,&k,name);
    
    if(name[0] == 'L'){
        l_index=find_line_name_index(name,line_num);
        fprintf(fd,"length(%s) = %.1f\n",name,line_length_calculate(name,line_num));
    }
    else{
        p_index=find_polygon_name_index(name,polygon_num);
        how_many_edge(&edge_num,p_index);
        
        for(int i=0;i<edge_num;i++){

            /*if polygon consists of lines*/
            if(strlen((char*)polygon[p_index].lines_pg))
                final_result += line_length_calculate((char*)polygon[p_index].lines_pg[i].name,line_num);
            else{
                two_points_distance_writing_to_file(fd,(char*)polygon[p_index].points_pg[i].name,(char*)polygon[p_index].points_pg[i+1].name,point_num,0,&result);
                final_result += result;
            }
        }
        fprintf(fd,"length(%s) = %.1f\n",name,final_result);
    }
}

/*it determines that polygon how many edge has*/
void how_many_edge(int* edge_num, int p_index){
   
    for(int i=0;strlen((char*)polygon[p_index].lines_pg[i].name) != 0 || strlen((char*)polygon[p_index].points_pg[i].name);i++)
        (*edge_num)++;
}

/*this function calculates length of a line to of length find polygon or line*/
float line_length_calculate(char* name, int line_num){
    int l_index;

    l_index=find_line_name_index(name,line_num);
    return sqrt(pow(line[l_index].p_two.x_coord-line[l_index].p_one.x_coord,2)+pow(line[l_index].p_two.y_coord-line[l_index].p_one.y_coord,2));
}

/*it checks whether polygon consists of lines or points*/
void calculate_area(FILE* fd, char* actions, int k, int polygon_num, int point_num){
    int p_index;
    char name[NAME_LENGTH];
    
    k++;take_point_line_polygon_name(actions,&k,name);
    p_index=find_polygon_name_index(name,polygon_num);
    
    if(strlen((char*)polygon[p_index].points_pg))
        area_with_point_writing_to_file(fd,p_index,name);
    else
        area_with_line_writing_to_file(fd,p_index,name,point_num);
}

/* it calculates area of polygon with help this formula  (x1*y2 + x2*y3 + x3*y1 - x1*y3 - x2*y1 - x3*y2)/2*/
void area_with_point_writing_to_file(FILE* fd, int p_index, char* name){
    float result=0;
    int edge_num=0;
    how_many_edge(&edge_num,p_index);
  
    for(int i=0;i<edge_num;i++){ 
        result += polygon[p_index].points_pg[i].x_coord*polygon[p_index].points_pg[i+1].y_coord;
        result -= polygon[p_index].points_pg[i].y_coord*polygon[p_index].points_pg[i+1].x_coord;
    }
    fprintf(fd,"area(%s) = %.1f\n",name,result/2);
}

void area_with_line_writing_to_file(FILE* fd, int p_index, char* name, int point_num){
    float result=0;
    int edge_num=0,index;
    how_many_edge(&edge_num,p_index);
    char corner[edge_num][NAME_LENGTH];
                                                            /*if polygon has L12,L23,L34,L41 then polygon has four corner and i have to find corner point
                                                            **in corner array, different points are stored with the help check_different_points().
                                                            */
    check_different_points(corner,edge_num,p_index);
    
    for(int i=0;i<edge_num;i++){
        index=find_point_name_index(corner[i],point_num);
        result += point[index].x_coord*point[index+1].y_coord;
        result -= point[index].y_coord*point[index+1].x_coord;
    }
    fprintf(fd,"area(%s) = %.1f\n",name,result/2);
}

void check_different_points(char corner[][NAME_LENGTH], int edge_num, int p_index){
    int flag=0,j=0;

    for(int k=0;k<edge_num;k++){
        flag=0;

        for(int i=0;i<edge_num;i++)
            if(strcmp(corner[i],(char*)polygon[p_index].lines_pg[k].p_one.name))
                flag++;

        if(flag == edge_num){
            strcpy(corner[j],(char*)polygon[p_index].lines_pg[k].p_one.name);
            j++;
        }
    }
    for(int k=0;k<edge_num;k++){
        flag=0;

        for(int i=0;i<edge_num;i++)
            if(strcmp(corner[i],(char*)polygon[p_index].lines_pg[k].p_two.name))
                flag++;
    
        if(flag == edge_num){
            strcpy(corner[j],(char*)polygon[p_index].lines_pg[k].p_two.name);
            j++;
        }
    }
}