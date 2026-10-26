#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(void) {
    Lista* li = malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

void libera_lista(Lista* li){
    if(li == NULL){
        return;
    }
    if((*li) != NULL){
        Elem* aux, *no = *li;
        while(no->prox != *li){
            aux = no;
            no = no->prox;
            free(aux);
        }
        free(no);
    }
    free(li);
}

int tamanho_lista(Lista* li){
    if(li == NULL || *li == NULL){
        return 0;
    }
    int cont = 1;
    Elem *no = *li;
    while(no->prox != *li){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    (void)li;
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL){
        return  1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL){
        return 0;
    }
    Elem *no = malloc(sizeof(Elem));
    if(no == NULL){
        return 0;
    }
    no->dados = al;
    if(*li == NULL){
        *li = no;
        no->prox = no;
    }
    else{
        Elem *aux = *li;
        while(aux->prox != *li){
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;
    }
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL){
        return 0;
    }
    Elem *no = malloc(sizeof(Elem));
    if (no == NULL){
        return 0;
    }
    no->dados = al;
    if(*li == NULL){
        *li = no;
        no->prox = no;
    }
    else{
        Elem *aux = *li;
        while(aux->prox != *li){
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL){
        return 0;
    }
    Elem *no = malloc(sizeof(Elem));
    if(no == NULL){
        return 0;
    }
    no->dados = al;
    int mat = no->dados.matricula;
    if(*li== NULL){
        *li = no;
        no->prox = no;
        return 1;
    }
    Elem *aux = *li;
    if((*li)->dados.matricula > mat){
        while(aux->prox != *li){
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;
        return 1;
    }
    else{
        while(aux->prox != *li && aux->prox->dados.matricula < mat){
        aux = aux->prox;
        }
        no->prox = aux->prox;
        aux->prox = no;
    }
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL || (*li) == NULL){
        return 0;
    }
    if((*li)->prox == *li){
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while(atual->prox != *li){
        atual = atual->prox;
    }
    Elem *no = *li;
    atual->prox = (*li)->prox;
    (*li) = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL || (*li) == NULL){
        return 0;
    }
    if((*li)->prox == *li){
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = (*li)->prox, *ant= *li;
    while(atual->prox != *li){
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = *li;
    free(atual);
    return 1;
}

int remove_lista(Lista* li, int mat){
    if( li == NULL || *li == NULL){
        return 0;
    }
    Elem *atual = *li;
    if(atual->dados.matricula == mat){
        if(atual->prox == atual){
            free(*li);
            *li = NULL;
            return 1;
        }
        else{
            while(atual->prox != *li){
            atual = atual->prox;
            }
            atual->prox = (*li)->prox;
            atual = *li;
            *li = atual->prox;
            free(atual);
            return 1;   
        }  
    }
    atual = (*li)->prox;
    Elem *ant = *li;
    while(atual != *li && atual->dados.matricula != mat){
        ant = atual;
        atual = atual->prox;
    }
    if(atual == *li){
        return 0;
    }
    else{
        ant->prox = atual->prox;
        free(atual);
        return 1;
    }
}

int busca_lista_pos(Lista* li, int pos, struct aluno *al){
    if( li == NULL || *li == NULL || pos < 0){
        return 0;
    }
    int cont = 1;
    Elem *atual = *li;
    while( cont != pos && atual->prox != *li){
        atual = atual->prox;
        cont++;
    }
    if (cont != pos){
        return 0;
    }
    else{
        *al = atual->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al){
    if(  li == NULL || *li == NULL){
        return 0;
    }
    Elem *atual = *li;
   do {
        if(atual->dados.matricula == mat){
            *al = atual->dados;
            return 1; 
        }
        atual = atual->prox;
    } while(atual != *li);
    
    return 0;
}

// Questao 1:

void imprime_lista(Lista* li){
    if( li == NULL || *li == NULL){ // verificando se a lista existe e se esta vazia
        return;
    }
    Elem *atual = *li;
    do{ 
        printf("%d ", atual->dados.matricula);
        atual = atual->prox;
    }while(atual != *li); // escolha do while porque se fosse while do o laço nunca seria inciado 

    printf("\n"); // garatindo queba de linha no final
}

// Questao 2:

int maior_matricula(Lista* li, int *mat){
    if( li == NULL || *li == NULL){ // verificando se a lista existe e se esta vazia
        return 0;
    }
    Elem *atual = *li;
    *mat = atual->dados.matricula;
    do{
        if(atual->dados.matricula > *mat){ // substitui a matriula caso seja maior
            *mat = atual->dados.matricula;
        }
        atual = atual->prox;
    }while(atual != *li);

    return 1;
}

// Questao 3
// erro 1: a funcao nao confere se a lista existe ou se a lista exta vazia. O que acontece na execução: Se a função receber um ponteiro de lista inválido
// ou uma lista recém-criada e vazia , a instrução Elem *no = *li; tentará desreferenciar um ponteiro nulo. 
// Isso gera imediatamente um erro de acesso à memória (Segmentation Fault) e encerra o programa de forma abrupta
// erro 2: a condicao de parada esta errada e causa um loop infinito, pois uma lista circular nao termina apontando para NULL mas sim para o ponteiro de inicio.
// Na execução O ponteiro no continuará avançando indefinidamente em um loop infinito, impedindo que a função retorne o resultado.

int conta_aprovados(Lista* li){
    if( li == NULL || *li == NULL){  // verificando se a lista existe e se esta vazia
        return 0;
    }
    int cont = 0;
    Elem *no = *li;
        do{
            float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
            if(media >= 7.0)
            cont++;
            no = no->prox;
        }while(no != *li);
    return cont;
}

// Questao 4:

int busca_ciclica(Lista* li, int k, struct aluno *al){
    if(li == NULL || *li == NULL || k <= 0){  // verificando se a lista existe e se esta vazia
        return 0;
    }
    int tam = tamanho_lista( li);
    if( k > tam){ // se a posicao for maior qu eo tamanho é necessário realizar operações para descobrir a posicao "real"
        k = tam % k;
        if( k == 0){
            k = tam;
        }
    }
    Elem *no = *li;
    int pos = 1;
    while(pos != k){ // iterando ate encontrar a posicao
        no = no->prox;
        pos++;
    }
    *al = no->dados;
    return 1;
}

// Questao 5:

int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL){  // verificando se a lista existe e se esta vazia
        return 0;
    }
    if(pos == 1){ // no caso de remover o primeiro elemento podemos usar a funcao remover_lista_inicio que ja foi implementada
        return remove_lista_inicio(li); 
    }
    Elem *atual = (*li)->prox, *ant = *li;
    int cont = 2;
    while( atual!= *li && cont != pos ){ // procurando a posicao
        ant = atual;
        atual = atual->prox;
        cont ++;
    }
    ant->prox = atual->prox;
    free(atual);
    return 1;
}

// Questao 6:
// Resposta 1: para numeros pequenos o custo é O(k) pois nao e necessario descolar nenhum elemento da lista, apenas mover o ponteiro de inicio
// Resposta 2: o custo seria no minimo O(n), pois seria necessário percorrer toda a lista para redistribuir os elementos do inicio no final 

int rotaciona_lista(Lista* li, int k){
    if( li == NULL || *li == NULL || k < 0){ // verificando se a lista existe, se esta vazia e se k é negativo
        return 0;
    }
    for(int i = 0; i < k; i++){
        *li = (*li)->prox; // movendo apenas o inicio da fila
    }
    return 1;
}

// Questao 7
// Resposta: o custo dessa operacao cairia de O(n) para O(1), ja que, nao seria necessario percorrer as listas para encontrar o final

int concatena_listas(Lista* li1, Lista* li2){
    if (li1 == NULL || li2 == NULL){ // verificando se a lista as listas existem
        return 0;
    }
    if(*li2 == NULL){ // se li2 estiver vazia li1 volta inalterada
        return 1;
    }
    if(*li1 == NULL){ // se li1 estiver vazia é necessário apenas transferir o inicio de li2 para li1 e deixar li2 vazia
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }
    Elem *no1 = *li1;
    Elem *no2 = *li2;
    while(no1->prox != *li1){ // encontrando o final de li1
        no1 = no1->prox;
    }
    while(no2->prox != *li2){ // encontrando o final de li2
        no2 = no2->prox;
    }
    no1->prox = *li2; // conectando o final de li1 ao inicio de li2
    no2->prox = *li1; // conectando o final de li2 ao inicio de li1
    *li2 = NULL;
    return 1;
}

// Questao 8:

int josephus(Lista* li, int k, int *sobrevivente){
    if( li == NULL || *li == NULL || k <= 0){ // verificando se a lista existe, se esta vazia e se k e nao positivo
        return 0;
    }
    while((*li)->prox != *li){ // no caso de um unico elemento ele nao cumpriria a condicao inicial e nao entraria no laço de repetição
        Elem *ant = *li, *atual = (*li)->prox;
        for(int i = 1; i < k; i++){
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = atual->prox;
        *li = atual->prox; // mudando o inicio para a pessoa logo apos a eliminada
        free(atual); // liberando a posicao da pessoa eliminada
    }
    *sobrevivente = (*li)->dados.matricula;
    free(*li); // esvaziando a lista
    *li = NULL;
    return 1;
}