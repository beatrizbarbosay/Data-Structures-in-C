#include <stdio.h>
#include <string.h>

//obs: confunfi a palavra "homônimos" com "homologos"e fiz o código todo escrevendo assim kkk
void quemsaoparentes(char listanomes[][31], int numero, char quem[]) { //funcao para encontrar os parentes
    char parentes[100][31]; 
    int numerop = 0;
    for(int i =0; i<numero; i++) { //confere para todos os pacientes da lista
        char paciente1[31];
        strcpy(paciente1,listanomes[i]);
        int j=0;
        int igual =1; 
        while(paciente1[j]!='_' && paciente1[j]!='\0'){ // le o caractere a partir do '_'até o final da string
            j++;
        }
        j++; // começa a ler a partir de '_'
        int k=0;
        while(paciente1[j]!='\0' && quem[k]!='\0'){ //compara todos os caracteres, até o final, do paciente com o scanf do sobrenome dado
            if (paciente1[j] != quem[k]){
                igual=0; 
                break; //para aqui se nao for parente
            }
            j++;
            k++;
        }         
        if (igual==1 && quem[k]=='\0'&& paciente1[j]=='\0') { 
            strcpy(parentes[numerop], paciente1); //cria uma lista com os parentes do sobrenome dado
            numerop++;
        }
        
    }
    for(int i = 0; i < numerop; i++) { //printa a lista dos parentes
        printf("%s\n", parentes[i]);
    }
}

void quaishomologos(char listanomes[][31], int numero, char quem[]) { //funcao para ver se sao homologos
    char homologos[100][31]; //mesma logica que para os parentes, mas para homologos
    int numerohomo = 0;
    for(int i =0; i<numero; i++) { 
        char paciente1[31];
        strcpy(paciente1,listanomes[i]);
        int j=0;
        int igual =1; 
        int k=0;
        while(paciente1[j]!='_'){  //le apenas o nome inicial antes do _
            if (paciente1[j] != quem[k]){
                igual=0; 
                break; 
            }
            j++;
            k++;
        }         
        if (igual==1 && quem[k]=='\0'&& paciente1[j]=='_') { //cria um array com os homologos
            strcpy(homologos[numerohomo], paciente1); 
            numerohomo++;
        }
        
    }
    for(int i = 0; i < numerohomo; i++) { //printa os homologos
        printf("%s\n", homologos[i]);
    }
}


int main(void) {
    int numero = 0;
    scanf ("%d", &numero); 

    char paciente[100][31]; //cria uma lista com as strings recebidas pelo usuario
    for(int i=0; i<numero; i++) {
        scanf(" %[^\n]%*c", paciente[i]);
    }
    char oque[31]; //homologo ou parente
    char quem[31]; //nome 
    scanf("%s %s", oque, quem); 

    if(strcmp(oque, "homonimos")==0){
        quaishomologos(paciente,numero,quem);
    }
    if(strcmp(oque, "parentes")==0){
        quemsaoparentes(paciente,numero,quem);
    }

    return 0;
}