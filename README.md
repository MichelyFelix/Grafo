<h1> Grafo</h1>

### Analise o arquivo dados_grafos.txt, armazenando o grafo em uma estrutura de matriz. Após isto, responda corretamente, em função do grafo produzido a partir de
#### dados_grafo.txt, as questões seguintes ou NA (Não se aplica) quando for necessário:

1. Qual(is) o vértice(s) com maior(es) grau?
2. Apresente em um arquivo chamado dados_grafos_graus.txt o número do vértices seguido pelo seu respectivo grau.
3. Se existir, quais são os vértices isolados?
```c
void vertices_isolados(int **matriz) {
    int isolado, count = 0;

    printf("Vértices isolados:\n");

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
```
4. Existe um vértice sumidouro?
```c
void vertice_sumidouro(int **matriz){
    int aux = 0;
    printf("Vertice(s) sumidouros:\n");
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
```
5. Existe um vértice fonte?
```c
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
   ```
7. Determine o grau de Emissão e Recepção de cada vértice e os coloque em arquivos chamados de "dados_grafos_emissao.txt" e "dados_grafos_recepcao.txt".
8. Apresente um arquivo com o grafo complementar da questão;
9. Inverta a direção de todas as arestas do grafo da questão e apresente-os em um novo arquivo com o nome de "dados_grafos_invertido.txt".
10. Apresente o grafo complementar e os represente em um arquivo com o nome "dados_grafo_complementar.txt".
```c
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
```
10. Apresente um novo arquivo chamado "dados_grafo_gerador.txt" com os vértices múltiplos de 5.

```c
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

```
12. Encontre o maior clique do grafo da questão.
13. Verifique se o primeiro e último vértice estão conectados
