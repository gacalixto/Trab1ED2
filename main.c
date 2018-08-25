#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>
#include<ctype.h>
#define tam 1000

typedef struct liv{
 char  ISBN[14],title[50],author[50],year[5];
	int next;
}Livro;

void openFile(FILE **fil,char *filname);
void insertFile(FILE *fil);
void dumpFile(FILE *fil);
void hashSfile(FILE *fil,int size_data,Livro book,int old);

int main()
{
    char opc;
    FILE *file=NULL;
    char filename[100];

    do{
        system("cls");
        printf("FILE MENAGER\n\n\n");
        printf(" [1]-INSERT INTO FILE\n\n [4]-Load FILE\n\n [5]-Dump FILE\n\n [e]-Close FILE & exit \n");
        opc=getch();

        switch(opc){
            case '1':
            	
            	if(file){
				
                	insertFile(file);
          			break;
				}
				system("cls");
				printf("File is not defined!!\n\nPRESS ANY BUTTON");
				getch();
				
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
   
    /*inicia lista de posi��es disponiveis v�zia */
		
		fprintf(*fil,"%d",-1);
        
        
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
    int regSize,list;
    
    system("cls");
    
	printf("ISBN:");
    gets(book.ISBN);
    printf("\nTitle:");
    gets(book.title);
    printf("\nAuthor:");
    gets(book.author);
    printf("\nYear:");
    gets(book.year);
    regSize=strlen(strcat(strcat(strcat(book.author,book.ISBN),book.title),book.year));
    rewind(fil);
    fscanf(fil,"%d",&list);
    if(list==-1){
		fseek(fil,SEEK_END,SEEK_CUR);
		hashSfile(fil,regSize,book,0);
		return;
	}
	
	/*BUSCA DE POSI��ES DISPONIVEIS*/
	//implementar
	
    
    
    
    

}

void hashSfile(FILE *fil,int size_data,Livro book,int old){
	
	
if(!old) {
	fprintf(fil,"%d",size_data+3);
}else{
	fseek(fil,sizeof(int),SEEK_CUR);
}
	
	fputs(book.ISBN,fil);
	fputc('#',fil);
	fputs(book.title,fil);
	fputc('#',fil);
	fputs(book.author,fil);
	fputc('#',fil);
	fputs(book.year,fil);
	
	
	
	
	
	
}
