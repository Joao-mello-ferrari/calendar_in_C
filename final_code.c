#include <stdio.h>
#include <string.h>

#define DATASize 50
#define cacheSize 100*50

typedef struct data{
    char title[30];
    char date[13];
    char hour[7];
} DATA;

void setup(DATA *cache, int *cacheC);
void showInitialMessage();
void showHelpMessage();
int getCommand(char command[20], char base[20], int flag);
int insert(char string[DATASize], DATA *cache, int *cacheC);
int retrieve(char string[20], DATA *cache, int cacheC);
int delete(char string[40], DATA cache[cacheSize], int *cacheC);

int main()
{
    DATA cache[cacheSize];
    int cacheC;
    setup(cache, &cacheC);
    
    showInitialMessage();
    
    char command[sizeof(DATA)];
    int shouldInsert, shouldRetrieve, shouldDelete;
    
    while(1){
        fgets(command, sizeof(DATA), stdin);
        
        if(getCommand(command, "help", 4)){
            showHelpMessage();
            continue;
        }
        
        if(getCommand(command, "exit", 4)){
            printf("\nEncerrando...");
            break;
        }
        
        shouldInsert = getCommand(command, "insert",0) || getCommand(command, "i",0);
        shouldRetrieve = getCommand(command, "retrieve",0) || getCommand(command, "r",0);
        shouldDelete = getCommand(command, "delete",0) || getCommand(command, "d",0);
    
        if(!(shouldInsert || shouldRetrieve || shouldDelete))
            printf("Opps, comando não identificado. Tente novamente: ");
    
        if(shouldInsert){
            int hasInserted = insert(command, cache, &cacheC);
            if(hasInserted)
                printf("\nInserção realizada! Digite novamente, se quiser: ");
            else
                printf("\nOpps, parece que seu comando não estava no formato correto. Tente novamente: ");
        }
        
        if(shouldRetrieve){
            int hasFound = retrieve(command, cache, cacheC);
            if(hasFound)
                printf("\nBusca realizada! Digite novamente, se quiser: ");
            else 
                printf("\nNão foram encontrados dados. Digite novamente: ");
        }
        
        if(shouldDelete){
            int hasDeleted = delete(command, cache, &cacheC);
            if(hasDeleted)
                printf("\nDeleção realizada! Digite novamente, se quiser: ");
            else 
                printf("\nNão foi possível deletar o registro/registro não encontrado. Digite novamente: ");
        }
    }
    
    return 0;
}

void setup(DATA *cache, int *cacheC){
   FILE *filePointer;
   char buffer[100*sizeof(DATA)];
    
   filePointer = fopen("database.txt", "r");
   
   int fileC=0, lineC=0, pipeC=0, appendC=0,a=0;
   while(fgets(buffer, cacheSize, (FILE*)filePointer) != NULL){
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
   
   *cacheC=fileC;
   fclose(filePointer);
}

void showInitialMessage(){
    printf("Bem vindo ao seu calendário\n");
    printf("Para obter ajuda, digite help, caso contrário, fique à vontade!\n");
}

void showHelpMessage(){
    printf("\nPara inserir um registro, escreva: ");
    printf("insert|<NOME>|<DATA>|<HORA> ou i|<NOME>|<DATA>|<HORA>.\n");
    printf("Exemplo: insert|Festa de formatura|30/03/2022|20:00.\n\n");
    
    printf("Para ver os resgitros de UM dia, escreva: ");
    printf("retrieve|<DATA> ou r|<DATA>.\n");
    printf("Exemplo: retrieve|30/03/2022.\n\n");
    
    printf("Para deletar um registro com um NOME, escreva: ");
    printf("delete|<NOME> ou d|<NOME>.\n");
    printf("Exemplo: delete|Festa de formatura.\n");
    printf("Para deletar todos os registros com um nome, a flag --all pode ser utilizada.\n");
    printf("Exemplo: delete|Festa de formatura--all.\n\n");
    
    printf("Para sair, digite exit.\n");
    printf("O FORMATO DOS COMANDOS DEVE SER IGUAL AO ACIMA, CASO CONTRÁRIO NÃO SERÁ IDENTIFICADO.\n");
    printf("O TÍTULO DOS EVENTOS NÃO DEVE TER MAIS DO QUE 25 CARACTÉRES.\n\n");
    
    printf("Agora, fique à vontade para utilizar o programa!\n");
    printf("Digite o seu comando: ");
}

int getCommand(char command[DATASize], char base[10], int flag){
    int counter=0, matched=1;
    
    while(command[counter] != '|'){
        if(flag != 0 && counter+1 == flag){
            matched=1;
            break;
        }
        
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

int insert(char string[DATASize], DATA cache[cacheSize], int *cacheC){
   int stringC=0, pipeC=0, appendC=0;
   while(string[stringC] != '\n'){
        DATA *JSON = &cache[*cacheC];
        char c = string[stringC];

        if(c == '|'){
            stringC++;
            pipeC++;
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
        stringC++;
   }
   
   if(pipeC != 3){
       memset(&cache[*cacheC],0,DATASize);
       return 0;
   }
   
   FILE *filePointer;
   
   filePointer = fopen("database.txt", "a");
   fprintf(filePointer, "%s", string);
   fclose(filePointer);

   *cacheC = *cacheC + 1;
   return 1;
}

int retrieve(char string[40], DATA cache[cacheSize], int cacheC){
   char reqDate[12];
   memset(reqDate,0,12);

   int stringC=0, pipeC=0, appendC=0;
   while(string[stringC] != '\n'){
        char c = string[stringC];
        
        if(c == '|'){
            stringC++;
            pipeC++;
            continue;
        }
        
        if(pipeC){
           reqDate[appendC]=c; 
           appendC++;
        }
        
        stringC++;
   }

   int i, firstR=1;
   for(i=0;i<cacheC;i++){
       DATA r = cache[i];
       int isEqual = !strcmp(r.date, reqDate);
       if(isEqual){
           if(firstR)
             printf("\nEvento(s) encontrado(s):\n");
           printf("%s", r.title);
           printf(", dia ");
           printf("%s", r.date);
           printf(", às ");
           printf("%s", r.hour);
           printf("\n");
           
           firstR=0;
       }
   }
   
   return !firstR;
}

int delete(char string[40], DATA cache[cacheSize], int *cacheC){
   char reqTitle[40];
   char reqFlag[10];
   memset(reqTitle,0,40);
   memset(reqFlag,0,10);

   int stringC=0, pipeC=0, appendC=0;
   while(string[stringC] != '\n'){
        char c = string[stringC];
        
        if(c == '|' || c == '-'){
            pipeC++;
            stringC++;
            appendC=0;
            continue;
        } 
        
        switch(pipeC){
            case 1:
                reqTitle[appendC]=c; 
                appendC++;
                break;
            default:
                reqFlag[appendC]=c; 
                appendC++;
                break;
        }
        
        stringC++;
   }

   int i, hasFound=-1, jumpSize=1, deleteAllWithSameName=!strcmp(reqFlag,"all");
   
   for(i=0; i < *cacheC; i++){
       DATA r = cache[i];
       int isEqual = !strcmp(r.title, reqTitle);
       
       if(isEqual){
           if(deleteAllWithSameName && hasFound != -1)
               jumpSize++;
           hasFound=i;
           continue;
       }
       
       if(hasFound != -1){
           cache[i-jumpSize]=cache[i];
       }
   }
   
   if(hasFound == -1)
       return 0;
    
   FILE *filePointer;
   
   filePointer = fopen("database.txt", "w");
   for(i=0; i < *cacheC-jumpSize; i++){
      DATA r=cache[i];      
      fprintf(filePointer, "insert|");
      fprintf(filePointer, "%s", r.title);
      fprintf(filePointer, "|");
      fprintf(filePointer, "%s", r.date);
      fprintf(filePointer, "|");
      fprintf(filePointer, "%s", r.hour);
      fprintf(filePointer, "\n");
   }
   fclose(filePointer);
   
   *cacheC = *cacheC - jumpSize;
   return 1;
}
