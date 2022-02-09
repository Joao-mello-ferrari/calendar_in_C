#include <stdio.h>
#include <string.h>

void showInitialMessage();
void showHelpMessage();
int getCommand(char command[20], char base[20]);
void retry(int *insert, int *retreat);

int main()
{
    showInitialMessage();
    
    char firstCommand[10];
    scanf("%s", firstCommand);
    
    if(!strcmp(firstCommand, "help")){
        showHelpMessage();
        scanf("%s", firstCommand);
    }
    
    int shouldInsert = getCommand(firstCommand, "insert");
    int shouldRetreat = getCommand(firstCommand, "retreat");
    
    if(!(shouldInsert || shouldRetreat))
        retry(&shouldInsert, &shouldRetreat);
    
    
    if(shouldInsert){
        // Inserir e salvar
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
    printf("Exemplo: retreat|30/03/20:00\n");
    
    printf("Agora, fique à vontade para utilizar o programa!\n");
    printf("Digite o seu comando: ");
}

int getCommand(char command[20], char base[20]){
    int counter=0, matched=1;
    while(command[counter] != '|'){
        if(command[counter] != base[counter]){
            matched=0;
            break;
        }
        
        counter++;
    }
    
    return matched;
}

void retry(int *insert, int *retreat){
    char command[20];
    printf("Opps, comando não identificado. Tente novamente: \n");
    scanf("%s", command);
    *insert = getCommand(command, "insert");
    *retreat = getCommand(command, "retreat");
}
