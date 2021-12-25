#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10
#define SUIT 4
#define FACES 13
#define CARD_NUMBER 52
#define CITY_NUM 6
#define LOC_NUM 4
#define LOC_LENGTH 4

struct Hospital{
    char* name;
    char citiesServed[3];
};

void menu();
int numPathsHome(int, int);
void print_mix_decks(char*, char*, int);
void fill_card_array();
void generate_card_number(int*, int*, int diff_card[][FACES]);
int check_different_card(int, int, int diff_card[][FACES]);
int canOfferCovidCoverage(char _cities[], char _locations[][LOC_LENGTH], int _numHospitals, struct Hospital results[]);
int check_all_cities_cover(char _cities[], char found_location[][LOC_LENGTH], int _numHospitals);
int check_different_city(char found_cities[], char city);

void main(void){

    srand(time(NULL));
    menu();
}

void menu(){

    int street,avenue, _numHospitals,op,control=1,flag;
    char _cities[CITY_NUM]={'A','B','C','D','E','F'}, _locations[][LOC_LENGTH]={"A","CD","BF","CEF","0"};
    struct Hospital results[4];

    while(control > 0){

        printf("\n\n1-> execute part one\n2-> execute part two\n3-> execute part three\n4-> exit\n\nplease select an opearation..\n");
        scanf("%d",&op);

        switch(op){

            case 1: flag=1;
                    while(flag > 0){

                        printf("enter the street number\nstreet -> ");
                        scanf("%d",&street);

                        printf("enter the avenue number\navenue -> ");
                        scanf("%d",&avenue);

                        /*if the genie ali is at home or abroad, it gives an error.*/
                        if((street > 5 || avenue > 5) || (street == 1 && avenue == 1))
                            printf("\n\nTRY AGAIN..\n\n");
                        /*the loop is terminated*/
                        else 
                            flag=0;
                    }

                    printf("\nthe number of optimal paths to back home -> %d\n\n",numPathsHome(street,avenue));     break;
            
            case 2: flag=1;
                    while(flag > 0){

                        printf("enter the maximum number of hospitals that can be constructed -> ");
                        scanf("%d",&_numHospitals);

                        if(_numHospitals > 4)
                            printf("\n\nTRY AGAIN..\n\n");
                        else 
                            flag=0;
                    }
                    canOfferCovidCoverage(_cities,_locations,_numHospitals,results);                                 break;

            case 3: fill_card_array();                                                                               break;
            case 4: control=0;                                                                                       break;
            default: printf("TRY AGAIN..");
        }
    }
}

/*
** in this algorithm i have used combination operation
** for ex: street->3 avenue->5 C(5+3-2,3-1)
*/
int numPathsHome(int street, int avenue){

    /*because of mines two is genie ali's home is (1,1)*/
    float n=street+avenue-2,r;

    /*for ex: C(6,2) -> 6*5/2*1 --- the value of avenue is simplified because it is equal to six minus two the four factoriel.*/
    if(street < avenue){
        r=street-1;
        if(n+1 != avenue)
            return (n/r) * numPathsHome(--street,avenue);
        else 
            return 1;
    }
        
    else{
        r=avenue-1;
        if(n+1 != street)
            return (n/r) * numPathsHome(street,--avenue);
        else 
            return 1;
    }
}

int canOfferCovidCoverage(char _cities[], char _locations[][LOC_LENGTH], int _numHospitals, struct Hospital results[]){

    char found_location[LOC_NUM][LOC_LENGTH];

    /*it resets the elements in the array*/
    bzero(found_location,LOC_NUM);

    for(int i=0;i<_numHospitals;i++)
        strcpy(found_location[i],_locations[i]);

    /*if all cities are covered and is not end of locations array then it prints the structure*/
     if(check_all_cities_cover(_cities,found_location,_numHospitals) == CITY_NUM && strcmp(*_locations,"0") != 0){

        printf("\nYes, can offer health care to all\n\n");
        for(int k=0;k<_numHospitals;k++){
            
            printf("HOSPITAL - %d\n",k+1);
            strcpy(results->citiesServed,found_location[k]);
            printf("hospital locations -> %s\n",results->citiesServed);
        }
    }
    
    /*if all cities are not covered and is not end of locations array then it takes new locations with recursive*/
    if((check_all_cities_cover(_cities,found_location,_numHospitals) < CITY_NUM) && (strcmp(*_locations,"0") != 0)){
      
        if(strcmp(*(_locations+1),"0") == 0)
            printf("\nNo, some cities are not covered\n");

        canOfferCovidCoverage(_cities,++_locations,_numHospitals,results);
    }
}

/*this func. returns the number of found cities*/
int check_all_cities_cover(char _cities[], char found_location[][LOC_LENGTH], int _numHospitals){

    int j=0;
    char found_cities[CITY_NUM];

    for(int k=0;k<_numHospitals;k++){
        for(int i=0;i<strlen(found_location[k]);i++)
            if(check_different_city(found_cities,found_location[k][i])){
            
                found_cities[j]= found_location[k][i];
                j++;
            }
    }
    /*if j is six, this means all cities are covered*/
    return j;
}

/*this function checks if it is same or different city*/
int check_different_city(char found_cities[], char city){

    for(int i=0;i<CITY_NUM;i++)
        if(found_cities[i] == city)
            return 0;
    
    return 1;
}

void fill_card_array(){

    char suits[][LENGTH]={"Hearts","Diamonds","Clubs","Spades"},faces[][LENGTH]={"Ace","Deuce","Three","four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
    int random_suit,random_face, diff_card[SUIT][FACES]={0};

    for(int i=0;i<CARD_NUMBER;i++){
        
        generate_card_number(&random_suit,&random_face,diff_card);
        print_mix_decks(faces[random_face],suits[random_suit],i);
    }
}

/*to mix the decks, this function generates random number(index)*/
void generate_card_number(int* suit, int* face, int diff_card[][FACES]){

    *suit=rand()%SUIT;
    *face=rand()%FACES;

    while(!check_different_card(*suit,*face,diff_card)){

        *suit=rand()%SUIT;
        *face=rand()%FACES;
    }
    diff_card[*suit][*face]=1;
}

/*this function returns 0 if it is a previously created card number.*/
int check_different_card(int suit, int face, int diff_card[][FACES]){

    if(diff_card[suit][face] != 0)
        return 0;
    
    return 1;
}

/*this function assignes suit and face of card to struct elements and prints*/
void print_mix_decks(char *face, char *suit, int i){

    struct card {
        const char *face;
        const char *suit;
    }one_card = {face,suit};

    /*these are (if and else if) for your sight*/
    if(i % 2 == 0 && i != 0)
        printf("%25s of %s\n",one_card.face,one_card.suit);

    else if(i == 27 || i % 2 != 0) 
        printf("%s of %-30s",one_card.face,one_card.suit);
}