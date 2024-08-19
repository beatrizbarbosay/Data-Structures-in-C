#include <stdio.h>

long int inverte (long int numero) { //inverte o numero
    long int resto, numeroinvertido=0, numero2;
    numero2 = numero;
    while (numero2 !=0) {
        resto = numero2 % 10;
        numero2 = numero2 / 10;
        numeroinvertido *= 10;
        numeroinvertido += resto;       
    }
    return numeroinvertido;
}

int main ()
{ 
    long int quantidade = 0; //primeira entrada
    scanf ("%ld ", &quantidade);

    long int x =0; //laço para ler a quantidade de números que serão testados
    for (x=1; x<= quantidade; x++) {
        long int numero=0;
        scanf("%ld" ,&numero);

        long int numeroinvertido = inverte(numero);

        if (numeroinvertido == numero) { //comparando o numero invertido com o original
            printf("%ld eh capicua\n", numero);   
        } else {
            printf("%ld nao eh capicua\n", numero);

        }
    }   
    return 0;
}