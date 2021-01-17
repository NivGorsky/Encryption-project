//
//  encryptionC.c
//  Encyption project
//
//  Created by ניב גורסקי on 26/09/2020.
//  Copyright © 2020 niv. All rights reserved.
//

#include "encryptionC.h"
//-------------------Function Prototypes------------------------//

//private
static char* getWordFromUser(void);
static char** createBoard(void);
static int wordIsValid(char* word);
static long int getFileSize(FILE* stream);
static char* getTextFromFile(FILE* stream, long int size);
static void encryption(char* text,char** board,char* word,long int size);
static void decryption(char* text,char** board,char* word,long int size);
static void myFreeBoard(char** board);
static void writeBackToFile(char* text, FILE* stream,long int fileSize);
static int getOffset(char** board,int j,int k);
//debugging
static void printBoard(char** board);
static void createBoardInFile(char** board);


//----------------IMPLEMENTATIONS---------------------//

//public
void appManager(void){
    
    int in;
    char** board = createBoard();
    char filePath[100];
    //createBoardInFile(board);
    


    printf("Welcome. Please enter file path:");
    scanf("%s", filePath);

    printf("\nChoose from the following:\nFor encyprtion press 1\nFor decryption press 0\n");
    scanf("%d", &in);
    
    if(in)
        Encrypt(filePath,board);

    else
        decrypt(filePath,board);

    printf("Finished the process:\n");
    myFreeBoard(board);
}
void Encrypt(char* filePath, char** board){


FILE* stream = fopen(filePath,"r+");
if(!stream)

    printf("\nfile opening eror");


char* word = getWordFromUser();
long int fileSize = getFileSize(stream);
char* text = getTextFromFile(stream, fileSize);

encryption(text, board, word,fileSize);
//
printf("\n\n||%s||\n\n",text);


writeBackToFile(text,stream,fileSize);
fclose(stream);

free(text);
free(word);

}
void decrypt(char* filePath, char** board){

    FILE* stream = fopen(filePath,"r+");
    char* word = getWordFromUser();
    long int fileSize = getFileSize(stream);
    char* text = getTextFromFile(stream, fileSize);

    decryption(text,board,word,fileSize);
    
    printf("\n\n||%s||\n\n",text);

    writeBackToFile(text,stream,fileSize);
    fclose(stream);

}

//private
static char* getWordFromUser(void){


    char* word = (char*)malloc(MAXWORD* sizeof(char));  //allocating an array for the word
    int flag = 1;

    printf("Please enter encryption word (word can't contain letters that occure more than once)\n");
    while(flag)
    {
     scanf("%s", word);
     if(wordIsValid(word)) //checking if the word is valid
        flag = 0;

     else
        printf("please enter a valid word\n");
    }

    return word;

}
static char** createBoard(void){

    
    int numLetters = ASCII ;
    int i,j;
    char** board;
    unsigned char letter;
    
    
    board = (char**)malloc((numLetters) * sizeof(char*));
    for(i=0;i<numLetters;i++)
    {
        board[i]= (char*)malloc(numLetters * sizeof(char));
        letter = ' '+i;
        for(j=0;j<numLetters;j++)
        {
            if (letter == 127)
                board[i][j] = '\n';
            else
                board[i][j] = letter;
                        
            letter++;
            
            if(letter> 127)
                
               letter = ' ';
        }
    }
    
    
    return board;
    
}
static int wordIsValid(char* word){

    char counter [95] = {};
    int i = 0;
    char letter;

    while(word[i]!='\0')
    {
        letter = word[i];
        if(counter[letter-' ']!= 0)
            return 0;
        else
            counter[letter - ' '] = 1 ;

        i++;
    }
    return 1;

}
static long int getFileSize(FILE* stream){

    long int bytes;
    fseek(stream,0,SEEK_END);

    bytes = ftell(stream);
    fseek(stream,0,SEEK_SET);

    return bytes;
}
static char* getTextFromFile(FILE* stream, long int size){

    long int i;
    char token;
    char* text = (char*)malloc((size+1)* sizeof(char));
    
    for(i=0;i<size;i++)
    {
        token = fgetc(stream);
        //debug
        if(token =='\0')
            printf("\n zero is here %d\n", i);
        //
        text[i] = token;
    }
    text[i]='\0';
    
    return text;
}
static void encryption(char* text,char** board,char* word,long int size){

    int i = 0,l = 0;
    char j,k;

    for(i=0;i<size;i++)  //running thorugh the text
    {
        j = text[i]; //getting the current letter in text
        k = word [l];  // getting the index of current letter in encripyion word

        if(j=='\n')
            text[i] = board[k-' '][127-' '];
        else
            text[i] = board[k-' '][j-' ']; //swap the current letter in text with board according to index
            
        l++;
        i++;

        if(word[l]=='\0') //if the word has ended going back to the beginning
            l = 0;
    }
}
static void decryption(char* text,char** board,char* word,long int size){

    
    int i = 0,l = 0,m;
    char j,k;

    for(i=0;i<size;i++)  //running thorugh the text
    {
        j = text[i]; //getting the current letter in text
        k = word [l];  // getting the index of current letter in encripyion word
        m = getOffset(board,j,k);
        
        text[i] = board[0][m]; //swap the current letter in text with board according to index

        l++;
        i++;

        if(word[l]=='\0') //if the word has ended going back to the beginning
            l = 0;
    }
    
}
static void myFreeBoard(char** board){

    int i,k = ASCII;
    
    for(i=0;i<k;i++)
    {
        free(board[i]);
        
    }
    free(board);
    
}
static void writeBackToFile(char* text, FILE* stream,long int fileSize){

    rewind(stream);
    int i =0;
    for(i=0;i<fileSize;i++)
    {
        fputc(text[i], stream);
        
    }
    
}
static int getOffset(char** board,int j,int k){

    int m;
    
    if(j>=k)
    {
        m = (j - k);
    }
    
        
    else
        m = 96 -(k - j);
    
    return m;
}

//debugging
static void printBoard(char** board){

    int i,j;
    
    for(i=0;i<68;i++)
    {
        for(j=0;j<68;j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("\n\n");
    }
}
static void createBoardInFile(char** board){

    char filePath[40];
    int i,j,len = ASCII;
    FILE* stream;
    printf("\n please enter file path:");
    
    scanf("%s", filePath);
    stream = fopen(filePath, "w");

    
    for(i=32;i<len;i++)
    {
        for(j=0;j<len;j++)
        {
            fputc(board[i-' '][j], stream);
            fputc('|', stream);
                 
           
        }
        fputc('\n', stream);
    }
    
    fclose(stream);
}
