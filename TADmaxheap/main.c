#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"

#define N 50

typedef struct carros{
    char modelo[N];
    int km;
    char placa[N];
    int lugares;
    float preco;
}Carros;

int main(){
    int i, op = 0, x;
    Maxheap m;
    m = CriaHeap();
    Carros a, b;

    while(op != 4){
        printf("O que deseja fazer?\n1-Inserir carro\n2-Remover carro\n3-Imprimir Maxheap\n4-Sair.\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Digite os km rodados: ");
                scanf("%d",&a.km);
                printf("Digite a quantidade de lugares: ");
                scanf("%d", &a.lugares);
                printf("Digite o preco do carro: ");
                scanf("%f", &a.preco);
                printf("Digite a placa do carro: ");
                fflush(stdin);
                gets(a.placa);
                fflush(stdin);
                printf("Digite o modelo do carro: ");
                gets(a.modelo);
                fflush(stdin);
                Insere(m,a.km,&a,sizeof(a));
                break;
            case 2:
                x = Remove(m, &b, sizeof(b));
                if(x == 1){
                    printf("\nQuilometragem rodada: %d\nModelo: %s\nQuantidade de Lugares: %d\nPlaca: %s\nPreco: %.2f\n\n", b.km, b.modelo, b.lugares, b.placa, b.preco);
                }
                break;
            case 3:
                Imprime(m);
                break;
            default:
                if(op!=4)
                    printf("Opcao invalida!\n");

        }
    }
    m = LiberaHeap(m);
    return 0;
}
