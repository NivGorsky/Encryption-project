//
//  main.c
//  Encyption project
//  Created by ניב גורסקי on 11/09/2020.
//  Copyright © 2020 niv. All rights reserved.
//




#include <Header.h>


//-------------------declaratinos------------------------//
void appManager(char* txtFile);
void encrypt(char* filePath, char** board);
void decrypt(char* filePath, char** board);
char** createBoard(void);
char* getWordFromUser(void);
int getFileSize(FILE* stream);
char* getTextFromFile(FILE* stream, int size);
void writeBackToFile(char* text, FILE* stream);

void encryption(char* text,char** board,char* word);
void decryption(char* text,char** board,char* word);




int main(int argc, char * argv[]) {
    
   
    
    appManager(argv[1]); //צריך לראות אם משאירים ככה או שמבקשים מהמשתמש אחר כך להכניס מילה
    return 0;
    
    
   
}




//----------------implementations---------------------//
void appManager(char* txtFile){
    
    int in;
    char** board = createBoard();
    char filePath[30];
    
    printf("Welcome. Please enter file path:");
    scanf("%s", filePath);
    
    printf("\nChoose from the following:\n For encyprtion press 1/n for decryption press 0\n");
    scanf("%d", &in);
    
    if(in)
        encrypt(filePath,board);
    
    else
        decrypt(filePath,board);
    
    printf("Finished the process:\n");
}

void encrypt(char* filePath, char** board){
    printf("Please enter encryption word (word can't contain letters that occude more than once)\n");
    
    FILE* stream = fopen(filePath,"r+");
    char* word = getWordFromUser();
    int fileSize = getFileSize(stream);
    char* text = getTextFromFile(stream, fileSize);
    
    encryption(text, board, word);
    
    writeBackToFile(text,stream);
    
}

void decrypt(char* filePath, char** board){
    printf("Please enter an encryption word (word can't contain letters that occude more than once)\n");
    
    FILE* stream = fopen(filePath,"r+");
    char* word = getWordFromUser();
    int fileSize = getFileSize(stream);
    char* text = getTextFromFile(stream, fileSize);
    
    decryption(text,board,word);
    
    writeBackToFile(text,stream);
    
}

char** createBoard(void)
{
    //Assuming the language is English, building 26*26 board
    int numLetters = ENGLISH
    int i,j;
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



