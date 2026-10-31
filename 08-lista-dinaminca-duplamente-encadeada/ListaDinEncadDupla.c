#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"


struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* criarlista(){
    Lista* li = malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(*li != NULL){
        Elem *no;
        while(*li != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li){
    if(li == NULL) return 0;
    Elem *no = *li;
    int cont = 1;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    (void) li;
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL || *li == NULL) return 1;
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem *no = malloc(sizeof(Elem));
    if(no == NULL) return 0;

    no->dados = al;
    no->ant = NULL;
    no->prox = *li;

    if(*li == NULL){
        *li = no;
    }
    else{
        (*li)->ant = no;
    }
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem *no = malloc(sizeof(Elem));
    if(no == NULL) return 0;

    no->dados = al;
    no->prox = NULL;

    if(*li == NULL){
        no->ant = NULL;
        *li = no;
    }
    else{
        Elem *aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem *no = malloc(sizeof(Elem));
    if(no == NULL) return 0;
    
    no->dados = al;

    if(*li == NULL){
        no->ant = NULL;
        no->prox = NULL;
        *li = no;
    }
    else{
        Elem *aux = (*li)->prox, *ante = *li;
        if((*li)->dados.matricula > no->dados.matricula){
            (*li)->ant = no;
            no->ant = NULL;
            no->prox = *li;
            *li = no;
        }
        else{
            while(aux != NULL && aux->dados.matricula < no->dados.matricula){
            ante = aux;
            aux = aux->prox;
            }
            if(aux == NULL){
                ante->prox = no;
                no->ant = ante; 
                no->prox = NULL;
            }
            else{
                aux->ant->prox = no;
                no->ant = aux->ant;
                aux->ant = no;
                no->prox = aux;
            }
            
        }
    }
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL){
        (*li)->ant = NULL;
    }
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li;
    while(no->prox != NULL){
        no = no->prox;
    }
    if(no == *li){
        *li = NULL;
        free(no);
    }
    else{
        no->ant->prox = NULL;
        free(no);
    }
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL) return 0; // a matricula nao foi encontrada
    if(no == *li){
        if(no->prox != NULL){
        no->prox->ant = NULL;
        }
        *li = no->prox;
    }
    else{
        no->ant->prox = no->prox;
        
        if(no->prox != NULL){
        no->prox->ant = no->ant;
        }
    }
    free(no);
    return 1;
}

int busca_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || *li == NULL || pos <= 0) return 0;
    Elem *no = *li;
    int cont = 1;
    while(no != NULL && cont != pos){
        no = no->prox;
        cont++;
    }
    if(no == NULL) return 0;
    *al = no->dados;
    return 1;
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li;
    while( no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL) return 0;
    *al = no->dados;
    return 1;
}

// funcoes lista de exercicio

// Questao 1:
// o custo dessa funcao e O(n)

void imprime_lista_inversa(Lista* li){
    if(li == NULL || *li == NULL){ // verificando se a lsita e valida e esta vazia
        printf("lista vazia \n");
        return;
    } 
    Elem *no = *li;
    while(no->prox != NULL){ // chegando no ultimo elemento
        no = no->prox;
    }
    while(no != NULL){ // imprimindo os elemntos do fim ao inicio
        printf("%d ", no->dados.matricula);
        no = no->ant;
    }
    printf("\n");
}

// Questao 2:

int lista_consistente(Lista* li){
    if(li == NULL) return 0;
    if(*li == NULL) return 1; // listas vazias sao consistentes
    Elem *no = *li;
    if(no-> ant != NULL){ // verificando se o campo ant do primeiro elemnto aponta para NULL
        return 0;
    }
    while(no->prox != NULL){ // verificando se todo elemento com sucessos cumpre a regra (o ultimo elemento nao entra no loop)
        if(no->prox->ant != no) return 0;
        no = no->prox;
    }
    return 1;
}

// Questao 3:
// 1) O codigo ira falhar pois nao ha elemnto anterior a 33, causando um segment fail.
// 2) Lista: (NULL <- 33 -> 16), (23 <- 16 -> NULL). Como tamanho_lista depende apenas do campo prox dos elementos ela retornara o tamanho certo
// pois esse campo foi atualizado corretamente na remocao. No entanto, a funcao lista_consistente devolve 0, pois ela analisa se os termos anteriores
/// estao correto, mas no caso da funcao original eles nao sao atualuzados quando o elemento é removido, assim fazendo com que as condicoes da funcao falhem.

int remove_lista(Lista* li, int mat){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat) // procurando elemento
        no = no->prox;
    if(no == NULL) return 0; // caso a matricula nao seja encontrada
    if(no == *li) { // caso o elemnto procurado seja o primeiro da lista
        *li = (*li)->prox;
        if(no->prox != NULL){
            no->prox->ant = NULL;
        }
    }
    else{
        no->ant->prox = no->prox;
        if(no->prox != NULL){ // caso nao seja o ultimo elemento da lista
            no->prox->ant = no->ant;
        }
    }
    free(no);
    return 1;
}

// Questao 4:

int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL || pos <= 0) return 0; // verificando se a lista existe, se esta vazia e se a posicao desejada e positiva
    Elem *no = *li;
    int cont = 1;
    while(no != NULL && cont != pos){ // procurando posicao
        no = no->prox;
        cont++;
    }
    if(no == NULL) return 0; // posicao invalida
    if(no == *li){ // caso o elemento desejado seja o primeiro
        *li = no->prox;
        if(no->prox != NULL){ // caso nao seja uma lista de elemento unico
            no->prox->ant = NULL;
        }
    }
    else{
        no->ant->prox = no->prox;
        if(no->prox != NULL){ // caso nao seja o ultimo elemento
            no->prox->ant = no->ant;
        }
    }
    free(no);
    return 1;
}

// Questao 5:

int move_para_inicio(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL) return 0;
    if(no->ant == NULL){
        return 1;
    }
    no->ant->prox = no->prox;
    if(no->prox != NULL){
        no->prox->ant = no->ant;
    }
    no->prox = (*li);
    (*li)->ant = no;
    no->ant = NULL;
    *li = no;
    return 1;
}

// Questao 6:

int remove_todos(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    Elem *no = *li, *aux;
    int cont = 0;
    do{
        if(no->dados.matricula == mat){
           if(no == *li){
             (*li) = no->prox;
             if(no->prox != NULL){
                no->prox->ant = NULL;
             }
           }
           else{
            no->ant->prox = no->prox;
            if(no->prox != NULL){
                no->prox->ant = no->ant;
            }
           }
           aux = no;
           no = no->prox;
           cont++;
           free(aux);
        }
        else{
            no = no->prox;
        }
    }while(no != NULL);

    return cont;
}

void inverte_lista(Lista* li){
    if(li == NULL || *li == NULL) return;
    Elem *no = *li;
    while(no->prox != NULL){
        no = no->prox;
    }
    Elem *aux;
    (*li) = no;
    while(no != NULL){
        aux = no->ant;
        no->ant = no->prox;
        no->prox = aux;
        no = no->prox;
    }
}

int eh_palindromo(Lista* li){
    if(li == NULL) return 0;
    if(*li == NULL) return 1;
    Elem *no = *li, *aux = *li;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    while(aux != NULL && no != NULL){
        if(aux->dados.matricula != no->dados.matricula){
            return 0;
        }
        no = no->prox;
        aux = aux->ant;
    }
    return 1;
}