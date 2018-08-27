#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>
#include<ctype.h>
#define tam 50

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

    do{ system("COLOR 0A");
        system("cls");
        printf("LIBRARY FILE MANAGER\n\n\n");
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
    *fil = fopen(filname,"r+b");

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
        fclose(*fil);

		*fil = fopen(filname,"a+b");


    /*inicia lista de posições disponiveis vázia */

		fprintf(*fil,"%d ",-1);


    }
    fclose(*fil);

	*fil = fopen(filname,"a+");
}

void dumpFile(FILE *fil){

	 char ch[tam],ch2[tam];
     int i;
     rewind(fil);
     system("cls");
     printf("$$ DUMP OF FILE by:Calixtoguerreiro $$\n\n");
	 while(fgets(ch,tam,fil)!= NULL){
       i=0;
       while(i<tam){
           if(isprint(ch[i])){
               printf("%1X ",ch[i]);
               ch2[i]=ch[i];
           }
           else if(!isprint(ch[i]))
           {
               ch2[i]='.';
               printf("00 ");

           }
           i++;

       }
       ch2[i-1]='\0';

       printf("  %s\n",ch2);

    }
   printf("\n");
   printf("\n\n\nPRESS ANY KEY....");
   getch();

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
    regSize=strlen(book.ISBN) + strlen(book.author) + strlen(book.title) +strlen(book.year); // Soma de todos os tamanhos de strings da STRUCT
    rewind(fil);
    fscanf(fil,"%d",&list); //Recebe primeiro inteiro do arquivo que indica a primeira posição da lista (-1 se a lista estiver vazia)


    if(list==-1){
    	printf("Livro Salvo !!\a");
    	Sleep(2000);
		fseek(fil,SEEK_END-SEEK_CUR,SEEK_CUR); //Rola para o fim do arquivo atual
		hashSfile(fil,regSize,book,0);
		return;
	}else{


		/*BUSCA DE POSIÇÕES DISPONIVEIS*/
		//implementar

	}




}

void hashSfile(FILE *fil,int size_data,Livro book,int old){

	/******** Essa função tem como único e exclusivo Objetivo gravar um dado de um livro
	no arquivo,

	int size_data = Tamanho total da soma de strings da struct
	Livro book = struct livro
	int old = indica se é uma nova gravação ou uma REgravação

	obs: se for regravação os primeiros bytes que indicam o tamanho da posição não mudam

	Exemplo de gravação:

	-1 (size_data + 4)(ISBN)#(Titulo)#(Autor)#(Ano)|

	| a pipe indica final do registro

	*****************************************************************************/


if(!old) {
	fprintf(fil,"%d",size_data+4);
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
	fputc('|',fil);






}
