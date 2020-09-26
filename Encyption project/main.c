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
void Encrypt(char* filePath, char** board);
void decrypt(char* filePath, char** board);

char** createBoard(void);
char* getWordFromUser(void);
long int getFileSize(FILE* stream);
char* getTextFromFile(FILE* stream, long int size);
void writeBackToFile(char* text, FILE* stream,long int fileSize);

void encryption(char* text,char** board,char* word);
void decryption(char* text,char** board,char* word);
int wordIsValid(char* word);
int getOffset(char** board,int j,int k);


void myFreeBoard(char** board);



///פונקציות לבדיקה
void printBoard(char** board);
void createBoardInFile(char** board);
///



int main(int argc, char * argv[]) {
    
   
    
    appManager(argv[1]); //צריך לראות אם משאירים ככה או שמבקשים מהמשתמש אחר כך להכניס מילה
    return 0;
    
    
   
}




//----------------implementations---------------------//
void appManager(char* txtFile){
    
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

    encryption(text, board, word);
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

    decryption(text,board,word);
    
    printf("\n\n||%s||\n\n",text);

    writeBackToFile(text,stream,fileSize);
    fclose(stream);

}

char** createBoard(void)
{
    //building 127*127 board (according to ascii table)
    int numLetters = ASCII;
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
            board[i][j] = letter;
            letter++;
            if(letter> 126)
                
               letter = ' ';
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
    long int i;
    char* text = (char*)malloc(size+1* sizeof(char));
    
    for(i=0;i<size;i++)
    {
        text[i] = fgetc(stream);
    }
    text[i]='\0';
    
    return text;
}

void encryption(char* text,char** board,char* word)
{
    int i = 0,l = 0;
    char j,k;

    while(text[i]!='\0')  //running thorugh the text
    {
        j = text[i]; //getting the current letter in text
        k = word [l];  // getting the index of current letter in encripyion word

        text[i] = board[k-' '][j-' ']; //swap the current letter in text with board according to index

        l++;
        i++;

        if(word[l]=='\0') //if the word has ended going back to the beginning
            l = 0;
    }
}

void decryption(char* text,char** board,char* word)
{
    
    int i = 0,l = 0,m;
    char j,k;

    while(text[i]!='\0')  //running thorugh the text
    {
        j = text[i]; //getting the current letter in text
        k = word [l];  // getting the index of current letter in encripyion word
        m = getOffset(board,j,k);
        

        ///
        //printf("|this is first:%c|\n",board['A'-' '][m]);
        //printf("text: %s",text);
        ///
        
        
        
        //text[i] = board[0][i];
        text[i] = board[0][m]; //swap the current letter in text with board according to index

        l++;
        i++;

        if(word[l]=='\0') //if the word has ended going back to the beginning
            l = 0;
    }
    
}

void myFreeBoard(char** board)
{
    int i,k = ASCII;
    
    for(i=0;i<k;i++)
    {
        free(board[i]);
        
    }
    free(board);
    
}


void printBoard(char** board)
{
    int i,j, k = ASCII;
    
    for(i=0;i<68;i++)
    {
        for(j=0;j<68;j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("\n\n");
    }
}


void writeBackToFile(char* text, FILE* stream,long int fileSize)
{
    rewind(stream);
    int i =0;
    for(i=0;i<fileSize;i++)
    {
        fputc(text[i], stream);
        
    }
    
}

int getOffset(char** board,int j,int k)
{
    int m;
    
    if(j>=k)
    {
        m = (j - k);
    }
    
    else
        m = 95 -(k - j);
    return m;
}

void createBoardInFile(char** board)
{
    char filePath[40];
    int i,j;
    char string[10];
    FILE* stream;
    printf("\n please enter file path:");
    
    scanf("%s", filePath);
    stream = fopen(filePath, "w");
    
//    i=0;
//    for(j=0;j<50;j++)
//            {
//    //            sprintf(string, "|%d.",j);
//    //            fputs(string, stream);
//                fputc(board[i][j], stream);
//                fputc('|', stream);
//
//            }
    
//     fputc('\n', stream);
    
    
    for(i=32;i<95;i++)
    {
        for(j=0;j<95;j++)
        {
//            sprintf(string, "|%d.",j);
//            fputs(string, stream);
            fputc(board[i-' '][j], stream);
            fputc('|', stream);
                 
           
        }
        fputc('\n', stream);
    
    }
    
    fclose(stream);
    
    
    
    
}
