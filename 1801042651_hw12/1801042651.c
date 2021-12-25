#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_LEN 1500

typedef struct tree{
    int frequence;
    char name;
    struct tree * left,*right;
}b_tree;

typedef struct dnode{
    int frequence;
    char name;
    struct dnode * next;
}node;

void read_file_and_frequences();
int check_previous_input(char*, int);
void huffman_coding(b_tree*);
b_tree * assign_sort_frequences_to_tree(b_tree*, int);
void sorting_frequences(b_tree *, node **);
b_tree * binary_tree(b_tree, b_tree);
void linked_list(b_tree *, node **, int);
void encryptioning_huffman_tree(b_tree*, int*, int);

void main(void){
    read_file_and_frequences();
}

void read_file_and_frequences(){
    char text[TEXT_LEN];
    int counter,k,j;
    b_tree * temp = (b_tree*)malloc(sizeof(b_tree));
    FILE * fp=fopen("reference.txt","r");
    
    for(int i=0;!feof(fp);i++)  fscanf(fp,"%c",&text[i]);   fclose(fp); 
    text[strlen(text)-6]=-1;
    
    for(j=0,k=0;text[k] != -1;k++){
        counter=0;

        for(int i=k;text[i] != -1;i++)
            if(text[k] == text[i])    counter++;
        
        if(check_previous_input(text,k)){
            temp[j].frequence=counter;
            temp[j].name=text[k];
            temp=(b_tree*)realloc(temp,sizeof(b_tree)*(j+2));
            j++;
        }
    }
    temp[j].frequence=-1;
    huffman_coding(temp);
}

int check_previous_input(char * text, int k){

    for(int i=0;i<k;i++)
        if(text[i] == text[k])  return 0;  

    return 1;
}

void huffman_coding(b_tree * temp){
    int size=0,up=0,size_temp;
    int * arr =  (int*) malloc(sizeof(int));

    for(int i=0;temp[i].frequence != -1;i++){
        size++;
        temp[i].left=NULL;  temp[i].right=NULL;
    }
    size_temp = size+1;
    for(int j=0;j<size-1;j++,size_temp--){
        temp = assign_sort_frequences_to_tree(temp,size_temp);
        temp[1] = *binary_tree(temp[0],temp[1]);
        temp[0].frequence=0;
    }
    encryptioning_huffman_tree(&temp[1],arr,up);
}

b_tree * assign_sort_frequences_to_tree(b_tree * temp, int size){
    node * root;
    b_tree temp2[size];
    int j;

    temp[size].frequence = -1;
    sorting_frequences(temp,&root);
    for(j=0;temp[j].frequence != -1;j++) temp2[j] = temp[j];  temp2[size].frequence = -1;
    root=root->next;

    for(int i=0;root != NULL;i++){
        for(int k=0;temp2[k].frequence != -1;k++)
            if(temp2[k].frequence == root->frequence && (temp2[k].name == root->name || root->name == '#'))
                temp[i]=temp2[k];
            
        root = root->next;
    }
    return temp;
}

void encryptioning_huffman_tree(b_tree * tree, int * arr, int up){

    if(tree->left){
        arr = (int*) realloc(arr,sizeof(int)*(up+2));
        arr[up] = 0;
        encryptioning_huffman_tree(tree->left,arr,up+1);
    }
    if(tree->right){
        arr = (int*) realloc(arr,sizeof(int)*(up+2));
        arr[up] = 1;
        encryptioning_huffman_tree(tree->right,arr,up+1);
    }
    if(tree->name != '#'){
        printf("%c -> ",tree->name);
        for(int i=0;i<up;i++)
            printf("%d",arr[i]);
        printf("\n");
    }
}

void sorting_frequences(b_tree * temp, node ** root){
    node *tmp=NULL,*iter;
    int biggest,counter=0;
    *root = (node*) malloc(sizeof(node));

    for(int i=0;temp[i].frequence != -1;i++){
        iter = *root;
        if(!counter){
            iter->name = temp[i].name;
            iter->frequence = temp[i].frequence;
            biggest = temp[i].frequence;
            iter->next = NULL;
        }
        else if((temp[i].frequence < (*root)->frequence) || (temp[i].frequence == (*root)->frequence)){
            tmp = (node*) malloc (sizeof(node));
			tmp->frequence = temp[i].frequence;
            tmp->name = temp[i].name;
			tmp->next = *root;
			*root = tmp;
        }
        else if(temp[i].frequence > biggest){
			while(iter->next != NULL)   iter=iter->next;
			
			iter->next = (node*) malloc (sizeof(node));
			iter->next->frequence = temp[i].frequence;
            iter->next->name = temp[i].name;
			iter->next->next = NULL;
			biggest = temp[i].frequence;
		}
		else{
			while(iter->frequence < temp[i].frequence){
                tmp = iter; 
				iter = iter->next;
			}
			tmp->next = (node*) malloc (sizeof(node));
			tmp->next->frequence = temp[i].frequence;
            tmp->next->name = temp[i].name;
			tmp->next->next = iter;
		}
        counter++;
    }
}

b_tree * binary_tree(b_tree node, b_tree next){
    b_tree * tree = (b_tree*) malloc(sizeof(b_tree));
  
    tree->frequence = node.frequence + next.frequence;
    tree->name = '#';
    tree->left = (b_tree*) malloc(sizeof(b_tree));
    *(tree->left) = node;
    tree->right = (b_tree*) malloc(sizeof(b_tree));
    *(tree->right) = next;
   
    return tree;
}