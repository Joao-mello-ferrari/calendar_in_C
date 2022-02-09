#include <stdio.h>
#include <string.h>

typedef struct data{
    char title[30];
    char date[13];
    char hour[7];
} DATA;

void showInitialMessage();
void showHelpMessage();
int getCommand(char command[20], char base[20]);
void retry(int *insert, int *retreat);
void insert(char *string);

void setup(DATA *cache){
    
   FILE *filePointer;
   char buffer[100*sizeof(DATA)];
    
   filePointer = fopen("database.txt", "r");
   
   //fprintf(fp, "This is testing for fprintf...\n");
   //fputs("This is testing for fputs...\n", fp);
   int fileC=0, lineC=0, pipeC=0, appendC=0,a=0;
   while(fgets(buffer, 100*sizeof(DATA), (FILE*)filePointer) != NULL){
       DATA *JSON = &cache[fileC];
       
       while(buffer[lineC] != '\n'){
          char c = buffer[lineC];
          if(c == '|'){
              pipeC++;
              lineC++;
              appendC=0;
              continue;
          }
          
          switch(pipeC){
              case 1: JSON->title[appendC]=c;
                break;
              case 2: JSON->date[appendC]=c;
                break;
              case 3: JSON->hour[appendC]=c;
                break;
          }
          
          appendC++;
          lineC++;
       }
       
       pipeC=0;
       appendC=0;
       lineC=0;
       fileC++;
   }
   
   fclose(filePointer);
}

int main()
{
    DATA cache[100*sizeof(DATA)];
    setup(cache);
    
    showInitialMessage();
    
    char command[sizeof(DATA)];
    fgets(command, sizeof(DATA), stdin);
    
    if(!strcmp(command, "help")){
        showHelpMessage();
        scanf("%s", command);
    }
    
    int shouldInsert = getCommand(command, "insert");
    int shouldRetreat = getCommand(command, "retreat");
    
    if(!(shouldInsert || shouldRetreat))
        retry(&shouldInsert, &shouldRetreat);
    
    
    if(shouldInsert){
        insert(command);
    }
        
    if(shouldRetreat){
        // Ler dados e printar
    }
    
    return 0;
}



void showInitialMessage(){
    printf("Bem vindo ao seu calendário\n");
    printf("Para obter ajuda, digite help, caso contrário, fique à vontade!\n");
}

void showHelpMessage(){
    printf("\nPara inserir um registro, escreva: ");
    printf("insert|<NOME>|<DATA>|<HORA>\n");
    printf("Exemplo: insert|Festa de formatura|30/03/2022|20:00\n");
    printf("O FORMATO DO COMANDO DEVE SER IGUAL AO ACIMA, CASO CONTRÁRIO NÃO SERÁ IDENTIFICADO\n\n");
    
    printf("Para ver os resgitros de UM dia, escreva: ");
    printf("retreat|<DATA>\n");
    printf("Exemplo: retreat|30/03/2022\n");
    
    printf("Agora, fique à vontade para utilizar o programa!\n");
    printf("Digite o seu comando: ");
}

int getCommand(char command[sizeof(DATA)], char base[10]){
    int counter=0, matched=1;
    
    while(command[counter] != '|'){
        
        if(command[counter] != base[counter]){
            matched=0;
            break;
        }
        if(counter > 10){
            matched=0;
            break;
        }
        
        counter++;
    }
    
    return matched;
}

void retry(int *insert, int *retreat){
    char command[60];
    printf("Opps, comando não identificado. Tente novamente: \n");
    fgets(command, sizeof(DATA), stdin);
    *insert = getCommand(command, "insert");
    *retreat = getCommand(command, "retreat");
}

void insert(char string[sizeof(DATA)]){
   FILE *filePointer;
   
   filePointer = fopen("database.txt", "a");
   fprintf(filePointer, "%s", out);
   fclose(filePointer);
}
