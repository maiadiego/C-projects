#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"

#define N 50

typedef struct alunos{
    int mat;
    int CR;
    char nome[N];
    char curso[N];
}Aluno;

int main()
{
    int i, op = 0, x;
    Maxheap m;
    m = CriaHeap();
    Aluno a, b;

    while(op != 4){
        printf("O que deseja fazer?\n1-Inserir aluno\n2-Remover aluno\n3-Imprimir Maxheap\n4-Sair.\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Digite a matricula do aluno: ");
                scanf("%d",&a.mat);
                printf("Digite o CR: ");
                scanf("%d",&a.CR);
                printf("Digite o nome do aluno: ");
                fflush(stdin);
                gets(a.nome);
                fflush(stdin);
                printf("Digite o curso do aluno: ");
                gets(a.curso);
                fflush(stdin);
                Insere(m,a.CR,&a,sizeof(a));
                break;
            case 2:
                x = Remove(m, &b, sizeof(b));
                if(x == 1){
                    printf("\nCR: %d\nNome: %s\nMatricula: %d\nCurso: %s\n\n", b.CR, b.nome, b.mat,b.curso);
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

