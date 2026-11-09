#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *file;
    file = fopen("doencas.txt", "r");
    int numerodoencas =0;
    fscanf(file, "%d", &numerodoencas);
    char doenca[100];
    scanf("%s", doenca);
    char cdoencas[150][1000];
    for(int i=0; i<numerodoencas; i++){
        fscanf(file," %[^\n]",cdoencas[i]);
        int igual=1;
        int j=0;
        while(doenca[j]!='\0'){
            if(doenca[j] != cdoencas[i][j]){
                igual=0;
                break;
            }
            j++;
        } 
        if(igual==1 && doenca[j]=='\0' && cdoencas[i][j]==' '){
           strcpy(doenca, cdoencas[i]);
        }
    }

    int k=0;
    char doencasolo[150];
    while (doenca[k]!= ' ') {
        k++;
    }
    k++;
    int l=0;
    while (doenca[k]!='\0') {
        doencasolo[l]=doenca[k];
        l++;
        k++;
    }
    doencasolo[l]='\0';

    printf("%s", doencasolo);

    char CRM[1000];
    scanf("%s",CRM);
    file = fopen("medicos.txt", "r");
    int numeromedicos =0;
    fscanf(file, "%d", &numeromedicos);

    char listamedicos[50][1000];
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
    int u=0;
    char medicosolo[1000];
    char medicototal[1000];
    strcpy(medicototal, CRM);
    while (medicototal[u]!= ' ') {
        u++;
    }
    u++;
    int m=0;
    while (medicototal[u]!='\0') {
        medicosolo[m]=medicototal[u];
        m++;
        u++;
    }
    medicosolo[m]='\0';
    strcpy(CRM,medicosolo);
    printf("%s", CRM);
    return 0;
}


