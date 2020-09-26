//
//  encryptionC.h
//  Encyption project
//
//  Created by ניב גורסקי on 26/09/2020.
//  Copyright © 2020 niv. All rights reserved.
//

#ifndef encryptionC_h
#define encryptionC_h

#include <stdio.h>
#include <stdlib.h>

#define ASCII 95;
#define MAXPATHLEN 30
#define MAXWORD 26
#define ENGLISH 26

//-------------------Function Prototypes------------------------//
void appManager(void);
void Encrypt(char* filePath, char** board);
void decrypt(char* filePath, char** board);
static char* getWordFromUser(void);


#endif /* encryptionC_h */
