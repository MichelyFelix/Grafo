#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_matriz 2896

int min_e_max(int n, int n1);
int grau_do_maior_vertice(int **matriz);
void mostra_matriz(int **matriz);
void ler_arquivo(char *nome_arquivo, int **matriz);
void escrever_graus_arquivo(char *nome_arquivo, int *graus, int tamanho);
void vertices_isolados(int **matriz);
void vertice_sumidouro(int **matriz);
void vertice_fonte(int **matriz);
void grafo_complementar(int **matriz, char *nome_arquivo);
void vertice_multiplo5(int **matriz, char *nome_arquivo);
//void inverterDirecoes(int **matriz, FILE *arquivo);

int main()
{
    int maior_grau;
    int **matriz = (int **)malloc(tamanho_matriz * sizeof(int *));
    int i;
    for (i = 0; i < tamanho_matriz; i++)
        matriz[i] = (int *)malloc(tamanho_matriz * sizeof(int));
    ler_arquivo("dados_matriz.txt", matriz);
    //mostra_matriz(matriz);

    int *graus = (int *)malloc(tamanho_matriz * sizeof(int));
    for (i = 0; i < tamanho_matriz; i++)
        graus[i] = 0;

    for (i = 0; i < tamanho_matriz; i++)
    {
        int j;
        for (j = 0; j < tamanho_matriz; j++)
        {
            if (matriz[i][j] == 1)
                graus[i]++;
        }
    }

    /*FILE *arquivo = fopen("grafo_invertido.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Inverte as direções e escreve no arquivo
    inverterDirecoes(matriz, arquivo);

    // Fecha o arquivo
    fclose(arquivo);*/

    escrever_graus_arquivo("dados_grafos_graus.txt", graus, tamanho_matriz);
    vertices_isolados(matriz);
    maior_grau = grau_do_maior_vertice(matriz);
   
    printf("\nO vertice com maior grau: %i\n", maior_grau);

    vertice_sumidouro(matriz);
    vertice_fonte(matriz);
    grafo_complementar(matriz,"Matriz_complementar.txt");
    vertice_multiplo5(matriz,"dados_grafos_gerados.txt");
    for (i = 0; i < tamanho_matriz; i++)
        free(matriz[i]);

    return 0;
}

void ler_arquivo(char *nome_arquivo, int **matriz)
{
    FILE *arch;
    char linha[5792];
    char *token;
    int i = 0, j = 0;
    arch = fopen(nome_arquivo, "r");
    while (fgets(linha, tamanho_matriz, arch))
    {
        token = strtok(linha, " ");
        j = 0;
        while (j < tamanho_matriz)
        {

            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
        i++;
        if (i >= tamanho_matriz)
        {
            break;
        }
    }
    fclose(arch);
}

void mostra_matriz(int **matriz)
{
    int i, j;

    for (i = 0; i < tamanho_matriz; i++)
    {
        for (j = 0; j < tamanho_matriz; j++)
        {

            printf(" %i ", matriz[i][j]);
        }
        printf("\n");
    }
}

int grau_do_maior_vertice(int **matriz)
{
    int i, j, maior_grau, aux = 0, vertice_com_maior_grau;
    for (i = 0; i < tamanho_matriz; i++)
    {
        for (j = 0; j < tamanho_matriz; j++)
        {
            if (matriz[i][j] == 1)
            {
                aux++;
            }
        }
        if (aux > maior_grau)
        {
            maior_grau = aux;
            vertice_com_maior_grau = i;
        }
        aux = 0;
    }
    return vertice_com_maior_grau;
}

void escrever_graus_arquivo(char *nome_arquivo, int *graus, int tamanho)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    int i;
    for (i = 0; i < tamanho; i++)
    {
        fprintf(arquivo, "Vertice %d: Grau %d\n", i, graus[i]);
    }

    fclose(arquivo);
}

void vertices_isolados(int **matriz) {
    int isolado, count = 0;

    printf("Vértices isolados: \n");

    for (int i = 0; i < tamanho_matriz; i++) {
        isolado = 1;
        for (int j = 0; j < tamanho_matriz; j++) {
            if (matriz[i][j] != 0) { 
                isolado = 0;
                break;
            }
        }
        if (isolado) {
            printf("%d\n", i);
            count++;
        }
    }
}

void vertice_sumidouro(int **matriz){
    int aux = 0;
    printf("Vertice(s) sumidouros: \n");
    for(int cont = 0; cont < tamanho_matriz; cont++){
        int sumidouro = 1;
        for(int cont2 = 0; cont2 < tamanho_matriz; cont2++){
            if (matriz[cont][cont2] != 0){
                sumidouro = 0;
                break;
            }
        } 
        if(sumidouro){
            printf("%d\n", cont);
            aux++;
        }
    }
    if (aux == 0){ // Se aux ainda for 0, nenhum vértice sumidouro foi encontrado
        printf("Nao foi encontrado vertice sumidouro!\n");
    }
}

 void vertice_fonte(int **matriz){
         int aux = 0; // Inicializa aux com 0
    printf("Vertice(s) fonte:\n");
    for(int cont = 0; cont < tamanho_matriz; cont++){
        int fonte = 1;
        for(int cont2 = 0; cont2 < tamanho_matriz; cont2++){
            if (matriz[cont2][cont] != 0){
                fonte = 0;
                break;
            }
        } 
        if(fonte){
            printf("%d\n", cont);
            aux++;
        }
    }
    if (aux == 0){ // Se aux ainda for 0, nenhum vértice sumidouro foi encontrado
        printf("Nao foi encontrado vertice sumidouro!\n");
    }
    } 

void grafo_complementar(int **matriz, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    for(int i = 0; i < tamanho_matriz; i++){
        for(int j = 0; j < tamanho_matriz; j++){
            if (i == j) { // Verifica se é um elemento da diagonal principal
                fprintf(arquivo, "%d ", matriz[i][j]); // Mantém o valor original
            } else {
                if(matriz[i][j] == 0){
                    matriz[i][j] = 1;
                } else {
                    matriz[i][j] = 0;
                }
                fprintf(arquivo, "%d ", matriz[i][j]);
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void vertice_multiplo5(int **matriz, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "Vertices multiplos de 5:\n");
    for(int i = 0; i < tamanho_matriz; i++){
        if(i % 5 == 0){
            fprintf(arquivo, "%d\n", i);
        }
    }
    fclose(arquivo);
}

    /*void inverterDirecoes(int **matriz, FILE *arquivo)
{

    int *novaMatriz = (int *)malloc(tamanho_matriz * sizeof(int *));

        for (int i = 0; i < tamanho_matriz; i++)
    {
        for (int j = 0; j < tamanho_matriz; j++)
        {
           novaMatriz[i] = (int *)malloc(tamanho_matriz * sizeof(int));
        novaMatriz[j] = (int *)malloc(tamanho_matriz * sizeof(int));
        }
    }

      
    for (int i = 0; i < tamanho_matriz; i++)
    {
        for (int j = 0; j < tamanho_matriz; j++)
        {
            novaMatriz[i][j] = matriz[j][i];
        }
    }

    for (int i = 0; i < tamanho_matriz; i++)
    {
        for (int j = 0; j < tamanho_matriz; j++)
        {
            fprintf(arquivo, "%d ", novaMatriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    for (int i = 0; i < tamanho_matriz; i++)
    {
        free(novaMatriz[i]);
    }
    free(novaMatriz);
}
*/