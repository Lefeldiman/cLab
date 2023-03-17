/*
 * File:   main.c
 * Author: root
 *
 * Created on October 18, 2013, 6:08 PM
 * and update in 17 of march of 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

// Definicao de Registro da Agenda

typedef struct reg
{
    char nome[20];
    long long int cpf;
    long int tel;
    int status;
} tag;

int busca(long int cpf);
void inserir(long int cpf);
void listagem(int status);
char tela();

int main()
{
    char linha[80];
    char opcao;
    int sair = 0, valor, st;

    FILE *arq;
    arq = fopen("agenda.txt", "r");
    if (arq == NULL)
    {
        arq = fopen("agenda.txt", "a+");
        fclose(arq);
    }
    else
    {
        fclose(arq);
    }

    do
    {
        opcao = tela();
        switch (opcao)
        {
        case 'i':
            puts("\nDigite o Cpf ...: ");
            fgets(linha, sizeof(linha), stdin);
            ;
            sscanf(linha, "%ld", &valor);
            inserir(valor);
            break;
        case 'r':
            puts("\nQual contato deseja remover? [digite o cpf]");
            fgets(linha, sizeof(linha), stdin);
            ;
            sscanf(linha, "%ld", &valor);
            // remover(ptlista, valor);
            break;
        case 'l':
            st = 1;
            listagem(st);
            break;
        case 'p':
            busca(valor);
            break;
        case 's':
            sair = 1;
            break;
        default:
            puts("\nOpcao invalida.");
            break;
        }
        system("clear");
    } while (!sair);
}

char tela()
{
    char opcao, linha[80];
    puts("Agenda Simples");
    puts("\n[I]nserir \n[L]istar, \n[R]emover, \n[P]esquisar \n[S]air");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%c", &opcao);
    return tolower(opcao);
}

int busca(long int cpf)
{
    FILE *arq;
    tag reg;
    int pos = 0;

    arq = fopen("agenda.txt", "r");
    fread(&reg, sizeof(reg), 1, arq);
    while ((cpf != reg.cpf) && (!feof(arq)))
    {
        fread(&reg, sizeof(reg), 1, arq);
        pos = pos + 1;
        fread(&reg, sizeof(reg), 1, arq);
    }
    if (cpf == reg.cpf)
        return (pos);
    else
        return (-1);
    fclose(arq);
}

void inserir(long int cpf)
{
    int pos;
    FILE *arq;
    tag reg;

    pos = busca(cpf);
    if (pos >= 0)
    {
        printf("\nCpf jah existente!");
        arq = fopen("agenda.txt", "r");
        fseek(arq, pos * sizeof(reg), SEEK_SET);
        fread(&reg, sizeof(reg), 1, arq);
        printf("\nCpf ...: %ld\n", reg.cpf);
        printf("\nNome ...: %s\n", reg.nome);
        fclose(arq);
    }
    else
    {
        arq = fopen("agenda.txt", "a+");
        reg.cpf = cpf;
        printf("\nNome ...: ");
        scanf("%s", &reg.nome);
        printf("\nTelefone ...: ");
        scanf("%ld", &reg.tel);

        reg.status = 1;
        fwrite(&reg, sizeof(reg), 1, arq);
        fclose(arq);
        getchar();
    }
}

void listagem(int status)
{
    FILE *arq;
    tag reg;
    int qtde = 0;
    arq = fopen("agenda.txt", "r");
    while (!feof(arq))
    {
        fread(&reg, sizeof(reg), 1, arq);
        qtde = qtde + 1;

        if (reg.status == status)
        {
            printf("Cpf ...: %ld\n", reg.cpf);
            printf("Nome ...: %s\n", reg.nome);
            printf("Telefone ...: %ld\n", reg.tel);
            printf("------------------------------------------------\n");
        }
    }
    fclose(arq);
    getchar();
}