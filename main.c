#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>
#define tam 40
// Autores:Gabriel Calixto e Leonardo Bezerra

typedef struct liv
{
    char  ISBN[14],title[50],author[50],year[5];
    int next;
} Livro;
int pega_registro(FILE *p_out, char *p_reg);
void openFile(FILE **fil,char *filname);
void insertFile(FILE* fil,int user, Livro book);
void dumpFile(FILE *fil);
void hashSfile(FILE *fil,int size_data,Livro book,int old);
void read_booklist(FILE *fil, FILE *bklist);
void removeFile(FILE *fil);
int searchRegister(FILE*fil,char *ISBN);
char* init_string(char *str, char w);

int main()
{
    char opc;
    FILE *file=NULL,*bklist=NULL, *last;
    char filename[50], booklist[50],lastfile[]="last.bin",defaultfile[]="library.bin";
    Livro book;

    do
    {

        system("COLOR 0A");
        system("cls");
        printf("LIBRARY FILE MANAGER\n\n\n");
        printf(" [1]-INSERT INTO FILE\n\n [3]-Remove a register from the file\n\n [4]-Load FILE\n\n [5]-Dump FILE \n\n [6]-Load Book List \n\n [r]-Open Last File\n\n [e]-Close FILE & exit \n");
        opc=getch();

        switch(opc)
        {
        case '1':

            if(file)
            {

                insertFile(file,1,book);
                break;
            }
            system("cls");
            printf("File is not defined!!\n\nPRESS ANY BUTTON");
            getch();
            break;

        case '3':
            system("cls");
            if(file)
            {
                rewind(file);
                removeFile(file);
            }

            else{
                printf("File Not Open!\nPress any key to go back to the menu!\n");
                getch();
            }
            system("cls");
            break;
        case '4':
            system("cls");
            printf("FILE NAME: ");
            gets(filename);
            openFile(&file,filename);
            rewind(file);
            last = fopen(lastfile,"w+b");
            rewind(last);
            fwrite(filename,sizeof(lastfile),1,last);
            fclose(last);
            break;

        case '5':
            if(file)
                dumpFile(file);
            else{
                printf("File Not Open!\nPress any key to go back to the menu!\n");
                getch();
            }
            getch();
            system("cls");
            break;

        case '6':

            system("cls");

            printf("FILE NAME (book list): ");
            gets(booklist);
            if((bklist=fopen(booklist,"rb"))!=NULL && file!=NULL)
            {

                rewind(bklist);
                rewind(file);
                read_booklist(file,bklist);
                fclose(bklist);






            }
            else
            {

                printf("List Not found or i/o file not found !! \n\n Press Any key...");

                getch();

            }


            break;
        case 'r':

        	last = fopen(lastfile,"rb");
        	if(last){

				rewind(last);

				fgets(filename,sizeof(lastfile),last);

        		openFile(&file,filename);
            	rewind(file);
         	   	fclose(last);
        	}else{

        		openFile(&file,defaultfile);
            	rewind(file);
         	   	fclose(last);


			}
        break;
        }

    }
    while(opc!='e');
    fclose(file);
    return 0;
}
void openFile(FILE **fil,char *filname)
{
    *fil = fopen(filname,"r+b");

    if(!*fil)
    {

        printf("creating %s",filname);
        Sleep(1000);



        printf(".");
        Sleep(500);

        printf(".");
        Sleep(300);
        printf(".");
        Sleep(500);

        printf(".");
        Sleep(500);

        printf(".");
        Sleep(300);

        printf(".");
        fclose(*fil);

        *fil = fopen(filname,"a+b");


        /*inicia lista de posições disponiveis vázia */

        fprintf(*fil,"%d ",-1);


    }
    fclose(*fil);

    *fil = fopen(filname,"a+b");
}

void dumpFile(FILE *fil)
{

    char ch[tam],ch2[tam],c[tam];
    int i;
    rewind(fil);
    system("cls");
    printf("$$ DUMP OF FILE      by:Calixtoguerreiro $$\n\n");
    while(fgets(ch,tam,fil)!= NULL)
    {
        i=0;
        while(i<tam-1)
        {
            if(isprint(ch[i]))
            {
                printf("%X ",ch[i]);
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
		strcpy(ch,init_string(ch,' '));
        printf("  %s\n",ch2);


    }
    printf("\n");
    printf("\n\n\nPRESS ANY KEY....");
    getch();

}

void insertFile(FILE* fil, int user, Livro book)
{

    int regSize,list;

    system("cls");
    if(user)
    {

        printf("ISBN:");
        gets(book.ISBN);
        printf("\nTitle:");
        gets(book.title);
        printf("\nAuthor:");
        gets(book.author);
        printf("\nYear:");
        gets(book.year);
    }
    regSize=strlen(book.ISBN) + strlen(book.author) + strlen(book.title) +strlen(book.year); // Soma de todos os tamanhos de strings da STRUCT
    rewind(fil);
    fscanf(fil,"%d",&list); //Recebe primeiro inteiro do arquivo que indica a primeira posição da lista (-1 se a lista estiver vazia)


    if(list==-1)
    {
        printf("Livro Salvo !!\a");

        fseek(fil,SEEK_END-SEEK_CUR,SEEK_CUR); //Rola para o fim do arquivo atual
        hashSfile(fil,regSize,book,0);
        return;
    }
    else
    {


        /*BUSCA DE POSIÇÕES DISPONIVEIS*/
        //implementar

    }




}


void hashSfile(FILE *fil,int size_data,Livro book,int old)
{

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


    if(!old)
    {
        //fprintf(fil,"%d",size_data+4);isso aqui não estava funcionando, o fseek nao conseguia pular isso por algum motivo
        size_data=size_data+4;
        fwrite(&size_data,sizeof(int),1,fil);
    }
    else
    {
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
int searchRegister(FILE *fil,char *ISBN)
{
    /*Função para percorrer o arquivo e encontrar o ISBN desejado
        que retorna um número equivalente à posição do registro
    */
    int pos,count=0,ct,list,achou=0,tamreg,tamcampo,ptnext;
    char registro[60],campo[26],cha;
    fseek(fil,sizeof(char)*3,SEEK_CUR);
    tamreg = pega_registro(fil,registro);
    while(achou!=1&&tamreg>0)
    {
        pos=0;
        tamcampo = get_field(registro,&pos,campo);
        if(strcmp(ISBN,campo)==0)
            achou=1;

        else
        {
            tamreg = pega_registro(fil,registro);
            count++;
        }


    }
    if(achou==0)
    {
        count = -2;
    }
    return count;
}


void removeFile(FILE *fil)
{
    char ISBN[14];
    int proc=0;
    printf("ISBN:");
    gets(ISBN);
    proc = searchRegister(fil,ISBN);
    if(proc!=-2)
    {
        printf("ISBN found!\nPress any key to continue");
        getch();
        fwrite('*',sizeof(char),1,fil);//isso não está funcionando ainda
        rewind(fil);
        fprintf(fil,"%d ",proc);

    }
    else
    {
        printf("ISBN not found!\nPress any key to continue");
        getch();
    }





}

int pega_registro(FILE *p_out, char *p_reg)
{
    char cha;
     int bytes=0;

     if (!fread(&bytes, sizeof(int), 1, p_out))
       return 0;
     else if(bytes<=60){
            fread(p_reg, bytes, 1, p_out);
            return bytes;
          }
}

int get_field(char *p_registro, int *p_pos, char *p_campo)
{
    char ch;
    int i=0;
    p_campo[i] = '\0';

    ch = p_registro[*p_pos];
    while ((ch != '#') && (ch!=EOF))
    {
        p_campo[i] = ch;
        i++;
        ch = p_registro[++(*p_pos)];
    }
    ++(*p_pos);
    p_campo[i] = '\0';

    return strlen(p_campo);
}

void read_booklist(FILE *fil, FILE *bklist)
{

    Livro book;
    int i=0;
    while(	fread(book.ISBN,sizeof(book.ISBN),1,bklist) )
    {

        fread(book.title,sizeof(book.title),1,bklist);
        fread(book.author,sizeof(book.author),1,bklist);
        fread(book.year,sizeof(book.year),1,bklist);
        insertFile(fil,0,book);
        i++;
    }



}

char* init_string(char *str,char w){
	int i;

	for(i=0;i<tam-1;i++){

		str[i]=w;


	}
	str[i]='\0';


	return str;
}
