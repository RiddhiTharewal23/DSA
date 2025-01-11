#include<stdio.h>
#include<stdlib.h>
#include"dict.h"
#include<string.h>
#define wordSize 20
#define meanSize 50

//this will convert into the respective array index
int convert_char_to_int(char p){
    int j;
    if(65 <= p && p <= 90){             // for Capital letters
        j = p - 'A';
        return j;
    }
    j = p - 'a';                        //For all other cases
    return j;
}
//This function will create a node1 pointer and will initialize all member with NULL
node1* create_dict(){
    node1* dict = (node1*)malloc(sizeof(node1));        //dict pointer of type node1
    if(dict == NULL){                                   //condition to check if memory is allocated if not returns zero
        return 0;
    }
    dict -> Alphabets = (node1**)malloc(sizeof(node1*)*26);
    dict -> Endofword = 0;
    dict -> meaning = '\0';
    for(int i=0; i < size; i++){
        dict -> Alphabets[i] = NULL;                    //initialize alphabets pointing to NULL
    }
    return dict;
}

//insertion of word with meaning in created trie
void insertWord(node1** dict, char* word, char* mean){
    int len = strlen(word);                          //will give the word length to be inserted
    int i, j;
    node1* q = *dict;
    for(i = 0; i < len; i++){
        j = convert_char_to_int(word[i]);
        if(j== -65 || j==-87){          //-87 is for end of text character
            break;
        }
        else if(j < 0){
            printf("Wrong letter inserted\n");
            return;
        }
        else if(q -> Alphabets[j] != NULL){              //if letters index is already present then simply track
            q = q -> Alphabets[j];
        }
        else{
            q->Alphabets[j] = create_dict();        //else create node for it and proceed
            q = q -> Alphabets[j];
        }
    }
    int t = strlen(mean);                           //This is len of meaning required to allocate mem for meaning pointer
    q->meaning = malloc(sizeof(char)*(t+1));
    strncpy(q->meaning,mean,t);
    q->meaning[t] = '\0';
    q -> Endofword = 1;
    return;
}
//outputs the meaning of given word
char* Display(node1* dict,char *word){
    int len = strlen(word);
    node1* q = dict;
    char* str =(char*) malloc(sizeof(str)*len);   //used if word is not spelled correctly
    int j;
    for(int i = 0; i < len; i++){
        j = convert_char_to_int(word[i]);
        if(j < 0){                               //wrong word/letter is inputted
            if(j == -87){break;}
            else{
                printf("No such data, %s is wrongly inputted",word);
                return NULL;
            }
        }
        else if(q -> Alphabets[j] != NULL){
            q = q -> Alphabets[j];
            str[i] = word[i];
        }
        else if(q->Alphabets[j] == NULL){           //if spelling is wrong then it will correct and gives relevant output
            printf("No such data present\nYou Entered Wrong Spelling\nRelevant outputs are\n");
            showstr(q,dict,str);
            return NULL;
        }
    }
    if(q!=NULL && q->Endofword == 1){
        return q->meaning;
    }
    //for prefix string
    else{
        printf("\nYou Entered Something Which is Not Present\nThe Relevant Output are : ");
        showstr(q,dict,str);
    }
    return NULL;
}
//to check if word is present
int Search(node1* dict,char* str){
    for(int i = 0;i<strlen(str); i++){
        int j = convert_char_to_int(str[i]);
        if(j == -65)
            break;
        if(dict->Alphabets[j] == NULL)
            return 0;
        dict = dict->Alphabets[j];
    }
    if(dict->Endofword == 1 && dict!=NULL){
        return 1;
    }
    return 0;
}
//to check if prefix
int check_Prefix(node1* dict,char* str){
    for(int i = 0; i<strlen(str); i++){
        int j = convert_char_to_int(str[i]);
        if(dict->Alphabets[j] == NULL)
            return 0;
        dict = dict->Alphabets[j];
    }
    return 1;
}
//destroys whole node with all children or simply unload dictionary
int Destroy_dict(node1** dict){
    if(*dict == NULL){
        printf("\nAttempt to deleting the empty node");
        return 0;
    }
    for(int i = 0;i<26;i++){
        if((*dict)->Alphabets[i]!=NULL){
            Destroy_dict(&((*dict)->Alphabets[i]));
            free((*dict)->Alphabets[i]);
            if((*dict)->Endofword == 1){
                free((*dict)->meaning);
            }
        }
    }
    free(*dict);
    *dict = NULL;
    return 1;
}
//This adds the word in dictionary file
void Add_word(){
    char word[wordSize];
    printf("Enter the word to add : ");
    scanf("%s",word);
    printf("Enter the Meaning : ");
    fflush(stdin);
    char mean[meanSize];
    gets(mean);
    FILE* file = fopen("dict.txt","a");
    FILE* file1 = fopen("mean.txt","a");
    if(file != NULL){
        fprintf(file,"%s\n",word);
    }

    if(file1 !=NULL){
        fprintf(file1,"%s\n",mean);
    }

    fclose(file1);
    fclose(file);

    return;
}

node1* load_dic(){
    char word[20];
    char mean[100];
    FILE *fp = fopen("dict.txt","r");       //dict.txt contains words
    FILE *m = fopen("mean.txt","r");        //mean.txt contains respective meaning

    node1* dict = create_dict();
    if(fp == NULL || m == NULL){
        return NULL;
    }
    while(fgets(word,20,fp) != NULL && fgets(mean,100,m) != NULL){    //till eof
        insertWord(&dict,word,mean);
        count++;                                        //counter of loaded word
    }
    fclose(m);
    fclose(fp);

    return dict;
}
void Autofill(node1* q,char* str){
    int j;
    node1 *p = NULL;
    p = q;
    int len = strlen(str);
    for(int i = 0; i < len;i++){                        //loop till strlen
        j = convert_char_to_int(str[i]);
        p = p->Alphabets[j];
    }
    showstr(p,q,str);//this will find all the words with the prefix str present in dict
    return;
}
char* showstr(node1* p,node1* q,char* str){
    if(p == NULL)
        return NULL;
    if(p->Endofword == 1){
        printf("%s : ", str);
        printf("%s",Display(q, str));                 //if endofword is reached then it will print the word with mean
        printf("\n");
        return NULL;
    }
    for(int i =0; i<26; i++){                         //loop for all 26 alphabets
        if(p->Alphabets[i] !=NULL){
            showstr(p->Alphabets[i], q, Appendstr(str, i));
        }
    }
    return NULL;
}
char* Appendstr(char* str, int index){               //append the letter to string
    int i = 0;
    char* q = malloc(sizeof(char)*strlen(str)+2);
    while(str[i]!='\0'){
        q[i] = str[i];
        i++;
    }
    char c = index+'a';
    q[i++] = c;
    q[i] = '\0';
    return q;
}
// check if any child is present
int checkalpha(node1* p){
    for(int i =0;i<26;i++){
        if(p->Alphabets[i] != NULL)
            return 1;
    }
    return 0;
}
//delete particular word from trie
int Delete(node1** p, char* str){
    if(*p == NULL){
        return 0;
    }
    if(*str){
        int i = convert_char_to_int(*str);
        //check if it the trie is not pointing to null and that alphabet is present and delete will only if that the word present and endofword is zero
        if((*p!=NULL) && (*p)->Alphabets[i] != NULL && Delete(&((*p)->Alphabets[i]),str+1) && (*p)->Endofword == 0){
                if(!checkalpha(*p)){
                    free(*p);
                    *p = NULL;
                    return 1;
                }
                return 0;
           }
    }
    if(*str == '\0' && (*p)->Endofword){
        if(!checkalpha(*p)){
            free((*p)->meaning);
            free(*p);
            *p = NULL;
            return 1;
        }
        else{
            (*p)->Endofword = 0;
            free((*p)->meaning);
            return 0;
        }
    }
    return 0;
}
