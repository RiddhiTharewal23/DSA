#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED
#define size 26
typedef struct node{
    struct node** Alphabets;        //array node pointer of size 26
    int Endofword;                  //it will be 1 or 0 if word ends it is assigned to 1
    char* meaning;                  //store meaning
}node1;                             // structure for trie

int count;          //keep the count of words loaded in dictionary


int convert_char_to_int(char p);                        //this will convert the character to int which is required in array
node1* create_dict();                                   //this will create node of dictionary
void insertWord(node1** dict,char* word,char* mean);    //used to insert the word and meaning into trie
char* Display(node1* dict,char* word);                  //this will display the meaning of given word
int Destroy_dict(node1** dict);//, char* str);           //will destroy whole dictionary
char* showstr(node1* p,node1* dict,char* str);             //this will be used
int check_Prefix(node1* dict,char* str);                    //this is used to check if the given word is there in anyof the prefix words in dictionary
int Search(node1* dict,char* str);                      //used to check if word is present or not
node1* load_dic();                                      //used to load the whole dictionary
void Add_word();                                        //will add word into text file
char* Appendstr(char* str,int index);                   //append letter to string used in autocomplete
void Autofill(node1* dict,char* str);
int Delete(node1** p, char* str);
int checkalpha(node1* p);
#endif // DICT_H_INCLUDED
