
#include "bogglesolver.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char** Boggle;

//load the boggle
int load_boggle(){
    int a,b;
    printf("\nEnter Number of rows in grid    >>..........");
    scanf("%d",&a);
    printf("\nEnter Number of columns in grid >>..........");
    scanf("%d",&b);
    Row = a;
    Col =b;
    modifysize(a, b);
    Boggle = (char**)malloc(sizeof(char*)*Row);
    if(Boggle == NULL)
        return 0;
    char c;
    printf("\nEnter the character \nYou can Enter only %d Character",Row*Col);
    for(int i = 0;i < Row;i++){
        Boggle[i] = (char*)malloc(sizeof(char)*Col);
        if(Boggle[i] == NULL)
            return 0;
        for(int j = 0;j<Col; j++){
            scanf("%c",&c);
            while(c == ' ' || c =='\n'){scanf("%c",&c);}
            Boggle[i][j] = c;
        }
    }
    for(int j = 0;j < Row;j++){
        for(int i = 0; i<Col; i++){
            printf(" ___ ");
        }
        printf("\n");
        for(int k = 0; k<Col;k++){
            printf("| %c |",Boggle[j][k]);
        }
        printf("\n");
        for(int t = 0;t<Col;t++){
            printf(" ___ ");
        }
        printf("\n");
    }
    char correct;
    printf("Is Above Boggle Right");
    fflush(stdin);
    scanf("%c",&correct);
    if(correct != 'y' && correct != 'Y'){
        free_boggle();
        load_boggle();
    }
    return 1;
}
int check_valid(int x, int y){
    if(x < 0  || y < 0 || x > Row-1 || y > Col-1)
        return 0;
    return 1;
}
void solveboggle(){
    node1* Dict;
    if(!load_boggle()){
        printf("\nGrid Cannot be loaded due to space");
        return;
    }
    Dict = create_dict();
    Dict = load_dic();

    list1 *path;
    init_LL(&path);
    Set *arr;
    create_Set(&arr);
    node1 *copy;
    copy = create_dict();
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            findword(i, j, &path, &arr, copy,Dict);
        }
    }
    Destroy_dict(&copy);
    Destroy_dict(&Dict);
    count = 0;
    destroy_LL(&path);
    destroy_Set(&arr);
    free_boggle();
    return;
}
//Solve the boggle by checking the word is present in dictionary
void findword(int x, int y, list1** p, Set** arr, node1* copy,node1* Dict){
    if(!check_valid(x, y))
        return;
    if(find(*arr, x, y))
        return;
    insertNode(p, Boggle[x][y]);
    char* word = getstr(*p);
    if (Search(Dict, word) && !Search(copy, word)){
        printf("%s : ", word);
        printf("%s",Display(Dict,word));
        insertWord(&copy,word,Display(Dict,word));
    }

    if (check_Prefix(Dict, word)){
        insert_val(arr, x, y);
        for(int i = x - 1;i<=x+1;i++){
            for(int j = y-1;j<=y+1; j++){
                if(i == x && j == y){}
                else{
                    findword(i,j,p,arr,copy,Dict);
                }
            }
        }

        remove_val(arr, x, y);
    }

    removeNode(p);
}
//this will deallocate the memory allocated by grid
int free_boggle(){
    for(int i = 0;i<Row; i++){
        free(Boggle[i]);
        Boggle[i] = NULL;
    }
    free(Boggle);
    Boggle = NULL;
    return 1;
}
