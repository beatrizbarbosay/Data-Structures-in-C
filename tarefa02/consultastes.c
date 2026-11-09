#include <stdio.h>
#include <string.h>
struct pacientes { 
    char nome1;
    char doenca;
    char medico;
    }; 
struct pacientes CIDemDoenca(struct pacientes x){ //funcao para manipular a estrutura e transformar CID em doença
    FILE *file;
    file = fopen("doencas.txt", "r");
    int numerodoencas =0;
    fscanf(file, "%d", &numerodoencas);
    char stringdoenca[1000];
    char cdoencas[150][1000];
    for(int i=0; i<numerodoencas; i++){
        fscanf(file," %[^\n]",cdoencas[i]);
        int j=0;
        int igual =1;
        strcpy(stringdoenca, x.doenca);
        while(stringdoenca[j]!='\0'){
            if(stringdoenca[j] != cdoencas[i][j]){
                igual=0;
                break;
            }
            j++;
        }
        if(igual==1 && stringdoenca[j]=='\0' && cdoencas[i][j]==' '){
            strcpy(stringdoenca, cdoencas[i]);
        }
    }
    int k=0;
    char doencasolo[1000];
    char doencatotal[1000];
    strcpy(doencatotal, stringdoenca);
    while (doencatotal[k]!= ' ') {
        k++;
    }
    k++;
    int l=0;
    while (doencatotal[k]!='\0') {
        doencasolo[l]=doencatotal[k];
        l++;
        k++;
    }
    doencasolo[l]='\0';
    strcpy(x.doenca,doencasolo);
}

struct pacientes CRMemMedico(struct pacientes x){ //funcao para manipular estrutura e transformar CRM no nome do médico
    FILE *file;
    file = fopen("medicos.txt", "r");
    int numeromedicos =0;
    fscanf(file, "%d", &numeromedicos);

    char listamedicos[50][1000];
    char CRM[1000];
    strcpy(CRM, x.medico);
    for(int i=0; i<numeromedicos; i++){
        fscanf(file," %[^\n]",listamedicos[i]);
        int j=0;
        int igual =1;
        while(CRM[j]!='\0'){
            if(CRM[j] != listamedicos[i][j]){
                igual=0;
                break;
            }
            j++;
        }
        if(igual==1 && CRM[j]=='\0' && listamedicos[i][j]==' '){
            strcpy(CRM, listamedicos[i]);
        }
    }
    int k=0;
    char medicosolo[1000];
    char medicototal[1000];
    strcpy(medicototal, CRM);
    while (medicototal[k]!= ' ') {
        k++;
    }
    k++;
    int l=0;
    while (medicototal[k]!='\0') {
        medicosolo[l]=medicototal[k];
        l++;
        k++;
    }
    medicosolo[l]='\0';
    strcpy(x.medico,medicosolo);
}


int main(void) {
    int vagas = 0;
    char abrir[31];
    scanf("%s %d", abrir, &vagas);

    struct pacientes dia[vagas]; //cria um array de estruturas com o numero maximo de vagas

    char comando[30];
    scanf("%s", comando);

    if (strcmp(comando, "registrar")==0){
        char nome[30];
        char cid[4];
        char crm[7];
        scanf("%s %s %s", nome, cid, crm);
        struct pacientes registrar;
        strcpy(registrar.nome1,nome); //registra os scanfs na forma da estrutura registrar
        strcpy(registrar.doenca,cid);
        strcpy(registrar.medico,crm);
        struct pacientes CIDemDoenca (struct pacientes registrar); //passa pela funcao para mudar o CID para o nome da doença
        struct pacientes CRMemMedico (struct pacientes registrar);//passa pela funcao para mudar o CRM para o nome do medico
        //como fazer para adicionar cada vez que passa pelo registra a uma nova possiçao na array de estruturas ?

    }
    if (strcmp(comando,"remover")==0){
        char nomeremover[30];
        scanf("%s", nomeremover);
        // funcao para remover um dos pacientes da array de vetores?


    }
    if (strcmp(comando, "alterar")==0){
        char nome[30];
        char novadoenca[30];
        scanf("%s %s", nome, novadoenca);
        //funcao para achar a nova doenca relativa ao CID e alterar

    }

    if (strcmp(comando, "fechar")==0){
        //printf a estrutura final 
        //return 0
        
    }




    return 0;
}