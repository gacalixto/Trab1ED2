#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>
#include<ctype.h>
#define tam 1000

typedef struct liv{
 char  ISBN[13],title[30],author[30],year[4];

}Livro;

void openFile(FILE **fil,char *filname);
void insertFile(FILE *fil);
void dumpFile(FILE *fil);

int main()
{
    char opc;
    FILE *file;
    char filename[100];

    do{
        system("cls");
        printf("HELLO MOTHERFUCK!\n");
        printf("[1]-INSERT INTO FILE\ne[4]-Load FILE\n[5]-Dump FILE\n[e]-Close FILE & exit \n");
        opc=getch();

        switch(opc){
            case '1':
                insertFile(file);
              break;

            case '4':
                system("cls");
                printf("FILE NAME: ");
                gets(filename);
                openFile(&file,filename);
                rewind(file);
                break;
            case '5':
                dumpFile(file);
                getch();
                system("cls");
                break;
        }

    }while(opc!='e');
    fclose(file);
    return 0;
}
void openFile(FILE **fil,char *filname){
    *fil = fopen(filname,"r+");

    if(!*fil){

        printf("creating %s",filname);
        Sleep(1000);


        printf(".");
         Sleep(500);

        printf(".");
         Sleep(1000);

        printf(".");
         Sleep(300);
         printf(".");
         Sleep(500);

        printf(".");
         Sleep(1000);

        printf(".");
         Sleep(300);printf(".");
         Sleep(500);

        printf(".");
         Sleep(1000);

        printf(".");
         Sleep(300);printf(".");
         Sleep(500);

        printf(".");
         Sleep(1000);

        printf(".");
         Sleep(300);

        printf(".");
        *fil = fopen(filname,"a+");
    }

}

void dumpFile(FILE *fil){
     char ch[tam];
     int i;
     while(fgets(ch,tam,fil)!= NULL){
       for(i=0;i<strlen(ch);i++){
           if(isprint(ch[i])){
               printf("%X ",ch[i]);
           }
       }

       printf("  %s",ch);

    }


}

void insertFile(FILE* fil){
    Livro book;
    int regSize;
    printf("ISBN:");
    gets(book.ISBN);
    printf("\nTitle:");
    gets(book.title);
    printf("\nAuthor:");
    gets(book.author);
    printf("\nYear:");
    gets(book.year);
    regSize=strlen(strcat(strcat(strcat(book.author,book.ISBN),book.title),book.year));
    printf("REG SIZE:%d\n",regSize);
    getch();

}
