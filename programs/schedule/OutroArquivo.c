#include<ncurses.h>

int busca(long int cpf);
void inserir(long int cpf, WINDOW *J1);
void listagem(int status,int *qtde, WINDOW *j2);


typedef struct ag{
     long int cpf;
     char nome[20];
     long int tel;
     int status;
     }tag;

int busca(long int cpf);
void inserir(long int cpf, WINDOW *j1);
void listagem(int status,int *qtde, WINDOW *j2);

int main()

{
 long int cpf;
 FILE *arq;
 int st;
 int qtde;

 WINDOW *j1,*j2;
 initscr();
 j1=newwin(24,79,0,0);
 j2=newwin(24,79,0,0);
 start_color();
 init_pair(1,COLOR_BLACK,COLOR_BLUE);
 init_pair(2,COLOR_CYAN,COLOR_RED);
 wbkgd(j1,COLOR_PAIR(2));
 wbkgd(j2,COLOR_PAIR(2));

 arq = fopen("arqag.txt","r");
   if(arq==NULL)
     {
       arq = fopen("arqag.txt","a+");
       fclose(arq);
     }
   else{fclose(arq);
   }
    
 mvwprintw(j1,2,2,"DIGITE O CPF: ");
 mvwscanw(j1,2,17,"%ld",&cpf);

 inserir(cpf,j1);
 listagem(1,&qtde,j2);
 wrefresh(j1);
 mvwgetch(j1,0,0);

 
 fclose(arq); 

 endwin();
}


int busca(long int cpf)
{
  FILE *arq;
  tag reg;
  int pos = 0;

  arq = fopen("arqag.txt","r");
  fread(&reg,sizeof(reg),1,arq);
  while((cpf!=reg.cpf)&&(!feof(arq)))
    {
      fread(&reg,sizeof(reg),1,arq);
      pos=pos+1;
      fread(&reg,sizeof(reg),1,arq);
    }
  
  if(cpf==reg.cpf)
    return(pos);
  else
    return(-1);
  fclose(arq);
      
}

void inserir(long int cpf, WINDOW *j1)
{
  int pos;
  FILE *arq;
  tag reg;

  pos=busca(cpf);
  if(pos>=0)
    {
      mvwprintw(j1,6,2,"CPF JA EXISTE");
      arq=fopen("arqag.txt","r");
      fseek(arq,pos*sizeof(reg),SEEK_SET);
      fread(&reg,sizeof(reg),1,arq);
      mvwprintw(j1,8,2,"CPF: %ld",reg.cpf);
      mvwprintw(j1,9,2,"NOME: %s",reg.nome);
      fclose(arq);
    }
  else
    {
      arq=fopen("arqag.txt","a+");
      reg.cpf=cpf;
      mvwprintw(j1,4,2,"DIGITE O NOME: ");
      mvwscanw(j1,4,17,"%s",&reg.nome);
      mvwprintw(j1,5,2,"DIGITE O TELEFONE: ");
      mvwscanw(j1,5,21,"%ld",&reg.tel);

      reg.status=1;
      fwrite(&reg,sizeof(reg),1,arq);
      fclose(arq);
    }
}

void listagem(int status, int *qtde,WINDOW *j2)
{
  FILE *arq;
  tag reg;
  qtde = 0;
  
  arq = fopen("arqag.txt","r");
fread(&reg,sizeof(reg),1,arq);
  for(;!feof(arq);)
  {
    qtde = qtde + 1;
    if (reg.status == status)
      {
	mvwprintw(j2,2,2,"CPF: %ld ",reg.cpf);
	mvwprintw(j2,3,2,"NOME:%s ",reg.nome);
	mvwprintw(j2,4,2,"TELEFONE: %ld",reg.tel);
	wrefresh(j2);
	mvwgetch(j2,0,0);
      }
fread(&reg,sizeof(reg),1,arq);
  }
  fclose(arq);
}

/*
#include<ncurses.h>
#include"lib.h"

typedef struct ag{
     long int cpf;
     char nome[20];
     long int tel;
     int status;
     }tag;


int main()

{
 
 long int cpf;
 FILE *arq;

 WINDOW *j1,*j2;
 initscr();
 j1=newwin(24,79,0,0);
 start_color();
 init_pair(1,COLOR_BLACK,COLOR_BLUE);
 init_pair(2,COLOR_CYAN,COLOR_RED);
 wbkgd(j1,COLOR_PAIR(2));
 wbkgd(j2,COLOR_PAIR(2));

 arq = fopen("arquivo_agenda.txt","r");
   if(arq==NULL)
     {
       arq = fopen("arquivo_agenda.txt","a+");
       fclose(arq);
     }
   else{fclose(arq);
   }
    
 mvwprintw(j1,2,2,"DIGITE O CPF: ");
 mvwscanw(j1,2,17,"%ld",&cpf);

 inserir(cpf,j1);

 wrefresh(j1);
 mvwgetch(j1,0,0);
 
 fclose(arq); 

 endwin();
}*/

	    
  
    

