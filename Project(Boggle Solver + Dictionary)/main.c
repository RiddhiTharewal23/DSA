/*
Name:Riddhi Ganesh Tharewal
Mis:111903068
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bogglesolver.h"
#define max_size 20
#include<windows.h>


int main(){
    //HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  //  SetConsoleTextAttribute(h,2);
    node1 *p = NULL;
    int i, choice;
    char ch;
    count = 0;
    do{
        //SetConsoleTextAttribute(h,2);

        printf("\n-----------------------------------------------------");
        printf("\n|                                                    |");
        printf("\n|      1)->Boggle Solver With Meaning                |");
        printf("\n|      2)->Dictionary                                |");
        printf("\n|      3)->QUIT                                      |");
        printf("\n|                                                    |");
        printf("\n-----------------------------------------------------\n");
        printf("\n Please Enter Your Choice >>>>.. ");
        fflush(stdin);
        scanf("%d", &choice);
        switch(choice){
        case 1:
            //SetConsoleTextAttribute(h,4);
            printf("\n****--- Boggle Solver ---****\n");
            solveboggle();
            break;
        case 2:
           // SetConsoleTextAttribute(h,3);
            do{

                printf("\n***************************---Dictionary---**************************************\n");
                printf("\n1)Add Word ");
                printf("\n2)Load Dictionary ");
                printf("\n3)Display Meaning");
                printf("\n4)Destroy Dictionary");
                printf("\n5)Display Whole Dictionary");
                printf("\n6)Number of Words in Dictionary");
                printf("\n7)Delete Word");
                printf("\n8)Quit");

                printf("\n Enter Your Choice : ");
                scanf("%d",&i);
                char* word = (char*)malloc(max_size*sizeof(char));
                switch(i){
                case 1:Add_word();
                    break;
                case 2:p = load_dic();
                    break;
                case 3:printf("\nEnter the word to be searched : ");
                    fflush(stdin);
                    printf("\n%s",Display(p,gets(word)));
                    free(word);
                    break;
                case 4:
                    if(Destroy_dict(&p)){
                        printf("\nData Unloaded Successfully !!!!");
                        count = 0;
                    }
                    break;
                case 5:
                    Autofill(p,"");
                    break;
                case 6:
                    printf("\n%d is count ",count);
                    break;
                case 7:
                    printf("\nEnter the Word to be deleted ");
                    fflush(stdin);

                    if(Delete(&p,gets(word))){
                        count--;
                        printf("%s is Successfully Deleted",word);
                    }
                    break;
                case 8:Destroy_dict(&p);
                        break;
                default:
                    printf("\nYou Have Entered Wrong Choice ");
                    break;
                }
                printf("\nIf you Want to Clear Screen......... ");
                fflush(stdin);
                scanf("%c",&ch);
                if(ch == 'y' || ch =='Y')
                    system("cls");
            }while(i!=8);
            break;
        case 3:break;
        default:
             printf("\nPlease Enter the correct Choice ...");
             break;
        }
        system("pause");
        system("cls");
    }while(choice!=3);
    printf("\nProgram Finished Successfully  ........");
    return 0;
}

