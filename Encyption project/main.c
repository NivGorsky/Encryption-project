//
//  main.c
//  Encyption project
//  Created by ניב גורסקי on 11/09/2020.
//  Copyright © 2020 niv. All rights reserved.
//


//בעיה במערך דליים שבודק את המילה - יש הבדל אם זאת אות קטנה או גדולה
//אינקלודים רלוונטים בהאדר - למשל בשביל המאלוק


#include "Header.h"


//-------------------declaratinos------------------------//
void appManager(char* txtFile);
void encrypt(char* filePath, char** board);
void decrypt(char* filePath, char** board);
char** createBoard(void);
char* getWordFromUser(void);
long int getFileSize(FILE* stream);
char* getTextFromFile(FILE* stream, long int size);
void writeBackToFile(char* text, FILE* stream);

void encryption(char* text,char** board,char* word);
void decryption(char* text,char** board,char* word);
int wordIsValid(char* word);




int main(int argc, char * argv[]) {
    
   
    
    appManager(argv[1]); //צריך לראות אם משאירים ככה או שמבקשים מהמשתמש אחר כך להכניס מילה
    return 0;
    
    
   
}




//----------------implementations---------------------//
void appManager(char* txtFile){
    
    int in;
    char** board = createBoard();
    char filePath[MAXPATHLEN];
    
    printf("Welcome. Please enter file path:");
    scanf("%s", filePath);
    
    printf("\nChoose from the following:\n For encyprtion press 1/n for decryption press 0\n");
    scanf("%d", &in);
    
    if(in)
        encrypt(filePath,board);
    
    else
        decrypt(filePath,board);
    
    printf("Finished the process:\n");
    myFreeBoard(board);
}

void encrypt(char* filePath, char** board){

    
    FILE* stream = fopen(filePath,"r+");
    char* word = getWordFromUser();
    long int fileSize = getFileSize(stream);
    char* text = getTextFromFile(stream, fileSize);
    
    encryption(text, board, word);
    
    writeBackToFile(text,stream);
    
    free(text);
    free(word);
    
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
    int numLetters = ENGLISH;
    int i,j;
    char** board;
    char letter;
    
    
    board = (char**)malloc((numLetters) * sizeof(char*));
    for(i=0;i<numLetters;i++)
    {
        board[i]= (char*)malloc(numLetters * sizeof(char));
        letter = 'A'+i;
        for(j=0;j<numLetters;j++)
        {
            board[i][j] = letter;
            letter++;
            if(letter>'Z')
                
               letter = 'A';
        }
    }
    
    
    return board;
    
}

char* getWordFromUser(void){
    
    
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

int wordIsValid(char* word)
{
    char nominator [ENGLISH] = {};
    int i = 0;
    char letter;
    
    while(word[i]!='\0')
    {
        letter = word[i];
        if(nominator[letter-'A']!= 0)
            return 0;
        else
            nominator[letter]++;
        
        i++;
    }
    return 1;
    
}

long int getFileSize(FILE* stream)
{
    long int bytes;
    fseek(stream,0,SEEK_END);
    
    bytes = ftell(stream);
    fseek(stream,0,SEEK_SET);
    
    return bytes;
}

char* getTextFromFile(FILE* stream, long int size)
{
    char* text = (char*)malloc(size* sizeof(char));
    fgets(text, size, stream);
    return text;
}

void encryption(char* text,char** board,char* word)
{
    int i = 0,j = 0,k = 0,l = 0;
    
    while(text[i]!='\0')  //running thorugh the text
    {
        j = text[i] - 'A'; //getting the current letter in text
        k = word [l]-'A';  // getting the index of current letter in encripyion word
        
        text[i] = board[k][j]; //swap the current letter in text with board according to index
        
        l++;
        i++;
        
        if(word[l]=='\0') //if the word has ended going back to the beginning
            l = 0;
    }
}
