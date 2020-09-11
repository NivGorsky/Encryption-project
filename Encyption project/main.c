//
//  main.c
//  Encyption project
//  Created by ניב גורסקי on 11/09/2020.
//  Copyright © 2020 niv. All rights reserved.
//




#include <Header.h>


//-------------------declaratinos------------------------//
void appManager(char* txtFile);
void encrypt(char* txtFile);
void decrypt(char* txtFile);
char** createBoard(void);






int main(int argc, char * argv[]) {
    
   
    
    appManager(argv[1]);
    return 0;
    
    
   
}




//----------------implementations---------------------//
void appManager(char* txtFile){
    
    int in;
    char** Board = createBoard();
    
    printf("Welcome. Please choose from the following:/n For encyprtion press 1/n for decryption press 0\n");
    scanf("%d", in);
    
    if(in)
        encrypt(txtFile);
    
    else
        decrypt(txtFile);
    
    printf("Finished the process:\n");
}

void encrypt(char* txtFile){
    
}

void decrypt(char* txtFile){
    
}

char** createBoard(void)
{
    //Assuming the language is English, building 26*26 board
    int numLetters = ENGLISH, i,j;
    char** board;
    char letter;
    
    
    board = (char**)malloc(numLetters * sizeof(char*));
    for(i=0;i<numLetters;i++)
    {
        board[i]= (char*)malloc(numLetters * sizeof(char));
        letter = 'A';
        for(j=0;j<numLetters;j++)
        {
            board[i][j] = letter;
            letter++;
        }
    }
    
    
    return board;
    
}



