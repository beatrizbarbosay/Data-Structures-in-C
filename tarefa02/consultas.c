#include <stdio.h>
#include <string.h>
struct pacientes {  //estrutura do tipo que armazenará as informaçoes de cada paciente
    char nome1[200];
    char doenca[200];
    char medico[200]; 
    }; 
struct pacientes CIDemDoenca(struct pacientes x){ //funcao para manipular a estrutura e transformar CID em doença
    FILE *file;
    file = fopen("dados/doencas.txt", "r");
    int numerodoencas =0;
    fscanf(file, "%d", &numerodoencas); //le a primeira linha do arquivo e armazena o numero de doenças
    char stringdoenca[1000];
    char cdoencas[151][1000]; //lista para armazenar as doenças
    for(int i=0; i<numerodoencas; i++){
        fscanf(file," %[^\n]",cdoencas[i]);
        int j=0;
        int igual =1;
        strcpy(stringdoenca, x.doenca); //define uma string com o CID da doenca
        while(stringdoenca[j]!='\0' && cdoencas[i][j]!='_'){ //compara se o CID é o mesmo do início da linha do arquivo
            if(stringdoenca[j] != cdoencas[i][j]){
                igual=0;
                break;
            }
            j++;
        }
        if(igual==1 && stringdoenca[j]=='\0' && cdoencas[i][j]==' '){
            strcpy(stringdoenca, cdoencas[i]); //se for igual, coloca o CID e o nome da doença no lugar de somente o CID
            break;
        }
    }

    fclose(file);

    int k=0; // todo o resto da funcao transforma a string "CID doenca" em apenas o nome da doenca para entao retornar o x.doenca para a struct
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
    return x;
}

struct pacientes CRMemMedico(struct pacientes x){ //funcao para manipular estrutura e transformar CRM no nome do médico
    FILE *file;
    file = fopen("dados/medicos.txt", "r");
    int numeromedicos =0;
    fscanf(file, "%d", &numeromedicos);

    char listamedicos[51][1000];//usa se a mesma logica que para transformar CID em doenca, mas com o arquivo medicos.txt
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
            break;
        }
    }
    fclose(file);
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
    return x;
}


int main(void) {
    int vagas = 0;
    char abrir[31];
    scanf("%s %d", abrir, &vagas); //abre a clínica

    struct pacientes dia[1000]; //cria um array de estruturas
    int count =0; //para ir contando o numero de pacientes registrados
    char comando[30];
    scanf("%s", comando);
    while(strcmp(comando, "fechar")!=0){
        if (strcmp(comando, "registrar")==0){
            char nome[200];
            char cid[4];
            char crm[7];
            scanf("%s %s %s", nome, cid, crm); //recebe os scanfs de registro de cada paciente
            struct pacientes registrar;
            strcpy(registrar.nome1,nome); //registra os scanfs na forma da estrutura registrar
            strcpy(registrar.doenca,cid);
            strcpy(registrar.medico,crm);

            registrar = CIDemDoenca(registrar); //passa pela funcao para mudar o CID para o nome da doença
            registrar = CRMemMedico(registrar); //passa pela funcao para mudar o CRM para o nome do medico
            dia[count] = registrar; //registra o paciente na array de estruturas
            count++; //vai para a proxima vaga
        }
        if (strcmp(comando,"remover")==0){
            char nomeremover[200];
            scanf("%s", nomeremover);
            int encontrado = -1; //procura o nome na lista
            for (int i=0; i<count; i++){
                if(strcmp(dia[i].nome1, nomeremover)==0){
                    encontrado=i; //quando encontrar, registra em qual posição da lista ele esta
                    break;
                }
            }
            if(encontrado!=-1){ //abre a vaga para o proximo paciente
                for(int i = encontrado; i<count-1; i++){
                    dia[i] = dia[i+1]; 
                }
                count --;
            }
        }
        if (strcmp(comando, "alterar")==0){
            char nome[200];
            char novadoenca[4];
            scanf("%s %s", nome, novadoenca);

            int encontrado=-1;
            for(int i=0; i<count; i++){ //procura o nome na lista dos pacientes
                if(strcmp(dia[i].nome1, nome)==0){
                    encontrado=i;
                    break;
                }               
            }
            if(encontrado!=-1){
                strcpy(dia[encontrado].doenca,novadoenca); //quando encontrado, muda a doenca anterior para a nova doença
                dia[encontrado]=CIDemDoenca(dia[encontrado]); //passa pela funcao para transformar o CID da nova doença no nome dela
            }
        }
        scanf("%s", comando); //passa para o proximo comando para permitir a entrada "fechar"
    }

    if (strcmp(comando, "fechar")==0){
        for(int i=0; i<count; i++){ //printa toda a lista resultante do dia com suas respectivas alterações
            printf("%s atendido por %s: %s\n", dia[i].nome1, dia[i].medico, dia[i].doenca);
        }
        return 0;
    }
}