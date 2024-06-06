#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

//ESCOLHA O N1 para 100 elementos. N2 para 5000 elementos. N3 para 20000 elementos. N4 para 32000 elementos
#define N1 7000
#define N2 100
#define N3 50
#define N4 30

///ELEMENTO TEM DUAS CHAVES E SEU PRÓXIMO (ENCADEAMENTO SIMPLES)///

struct elemento {
    int chave[2];
    struct elemento *prox;
};


///TIPO 01 DE DISTRIBUIÇÃO DOS ELEMENTOS (ALEATORIEDADE)///

struct elemento *tipo_1(int n_ele){

    int i;
    struct elemento *ini, *fim, *novo;
    ini = NULL;

    for(i = 0; i < n_ele; i++){
        novo = (struct elemento *) malloc(sizeof(struct elemento));
        novo->chave[0] = rand();
        novo->chave[1] = rand();
        novo->prox = NULL;

    if(!ini)
        ini = fim = novo;
    else
        fim->prox = novo;
        fim = novo;
    }

    return ini;
}


///TIPO 02 DE DISTRIBUIÇÃO DOS ELEMENTOS (ORDEM CRESCENTE USANDO O PRIMEIRO COMO BASE)///

struct elemento *tipo_2(int n_ele){

    int i;
    struct elemento *ini, *novo, *aux, *aux_b;
    ini = NULL;

    for(i = 0; i < n_ele; i++){
        novo = (struct elemento *) malloc(sizeof(struct elemento));
        novo->chave[0] = rand();
        novo->chave[1] = rand();
        novo->prox = NULL;

        if(!ini)
            ini = novo;

        else if(novo->chave[0] < ini->chave[0]){
            novo->prox = ini;
            ini = novo;
        }

        else{
            for(aux = ini; aux->prox && novo->chave[0] > aux->prox->chave[0]; aux = aux->prox);
            aux_b = aux->prox;
            aux->prox = novo;
            novo->prox = aux_b;
        }
    }

    return ini;
}


///TIPO 03 DE DISTRIBUIÇÃO DOS ELEMENTOS (ORDEM DECRESCENTE USANDO O PRIMEIRO COMO BASE)///

struct elemento *tipo_3(int n_ele){

    int i;
    struct elemento *ini, *novo, *aux, *aux_b;
    ini = NULL;

    for(i = 0; i < n_ele; i++){
        novo = (struct elemento *) malloc(sizeof(struct elemento));
        novo->chave[0] = rand();
        novo->chave[1] = rand();
        novo->prox = NULL;

        if(!ini)
            ini = novo;

        else if(novo->chave[0] > ini->chave[0]){
            novo->prox = ini;
            ini = novo;
        }

        else{
            for(aux = ini; aux->prox && novo->chave[0] < aux->prox->chave[0]; aux = aux->prox);
            aux_b = aux->prox;
            aux->prox = novo;
            novo->prox = aux_b;
        }
    }

    return ini;
}


///TIPO 04 DE DISTRIBUIÇÃO DOS ELEMENTOS (10% DOS ELEMENTOS BAGUNÇADOS)///

struct elemento *tipo_4(int n_ele){

    int i, j, n, r;
    n = n_ele * 0.10;
    int troca[n];
    struct elemento *ini, *lista, *aux, *aux_b;


    ini = tipo_2(n_ele);

    //Para comparar valores, inicializo o vetor em -1
    for(i = 0; i < n; i++)troca[i] = -1;

    //Garantir que não troque elementos de posições iguais.
    for (i = 0; i < n; i++){
        do{
            r = (rand() % n_ele) +1;
            for(j = 0; j < n && r != troca[j]; j++);
        }while(j != n);

        troca[i] = r;
    }

    //Trocas
    for(i = 0; i < n; i++){

        //Ir com o aux até uma psição anterior do elemento que será trocado (link)
        for(aux = ini; troca[i] > 2; troca[i]--){
            aux = aux->prox;
        }

        //Troca será realizada entre um elemento par(anterior) com o ímpar(atual)
        if(i % 2 == 1){

            //exceção - Para trocar o primeiro elemento de uma lista é diferente.
            if (troca[i] == 1){

                //execeção 2 - Para trocar o segundo elemento com o primeiro é diferente (2 com 1)
                if(aux == aux_b){
                    ini = lista;
                    lista = lista->prox;
                    ini->prox = aux;
                    aux->prox = lista;
                }
                else{
                    ini = lista;
                    lista = lista->prox;
                    ini->prox = aux->prox;
                    aux->prox = lista;
                    aux_b->prox = aux;
                }
            }

            //exceção - Para trocar o primeiro elemento de uma lista é diferente.
            else if(troca[i-1] == 1){

                //execeção 2 - Para trocar o segundo elemento com o primeiro é diferente (1 com 2)
                if(aux == aux_b){
                    ini = lista;
                    lista = lista->prox;
                    ini->prox = aux;
                    aux->prox = lista;
                }
                else{
                    ini = aux->prox;
                    aux_b->prox = ini->prox;
                    ini->prox = lista;
                    aux->prox = aux_b;
                }

            }

            //Ocorrencia tradicional (2 com 10) (20 com 10) (423 com 2314) (7 com 5)
            else{
                aux_b->prox = aux->prox;
                aux->prox = lista;
                lista = lista->prox;
                aux->prox->prox = aux_b->prox->prox;
                aux_b->prox->prox = lista;
            }
        }

        //Colocando ponteiros na posição anterior que será trocada
        else{
            aux_b = aux;
            lista = aux->prox;
        }
    }

    return ini;
}


///GERAR LISTA COM ELEMENTOS ALEATÓRIOS///

struct elemento *gerar_lista(int n_ele, int tipo){

    struct elemento *pri;

    switch (tipo){

    case 1:
        pri = tipo_1(n_ele);
        break;

    case 2:
        pri = tipo_2(n_ele);
        break;

    case 3:
        pri = tipo_3(n_ele);
        break;

    case 4:
        pri = tipo_4(n_ele);
        break;

    default:
        printf("Opção inválida");
        exit(0);

    }

    return pri;
}


///GERAR LISTA COM CHAVES IGUAIS A DA LISTA UM///

struct elemento *gerar_copia(struct elemento *lista_um){

    int i;
    struct elemento *ini, *fim, *novo; //PRIMEIRO pra retornar, ULTIMO pra encadear o próximo NOVO
    ini = NULL;

    while(lista_um){                   //  NÃO PRECISO DE INDICE, POIS CONFIO NO NÚMERO DE ELEMENTOS
        novo = (struct elemento *) malloc(sizeof(struct elemento));
        novo->chave[0] = lista_um->chave[0];
        novo->chave[1] = lista_um->chave[1];
        lista_um = lista_um->prox;
        novo->prox = NULL;

        if(!ini){
            ini = fim = novo;
        }
        else{
            fim->prox = novo;
            fim = novo;
        }

    }

    return ini;
}


///MOSTRAR A LISTA GERADA///

void mostrar_chaves(struct elemento *lista){

    int i;
    struct elemento *aux;
    aux = lista;
    printf("\n\n\n");

    while(lista){
       printf("%d - ", lista->chave[0]);
       lista = lista->prox;
    }

    printf("\n\n\n");

    while(aux){
       printf("%d - ", aux->chave[1]);
       aux = aux->prox;
    }

}


///EXCLUIR A LISTA///

void excluir_lista(struct elemento *lista){

    struct elemento *aux;

    while(lista){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}


///BUBBLE SORT///

struct elemento *bubble_sort(struct elemento *lista, int valor){

    int flag;
    struct elemento *aux, *ini;
    ini = lista;

    if(!ini || !ini->prox)
        return ini;

    do{
        flag = 0;
        for(lista = ini; lista->prox->prox; lista = lista->prox){
            if(lista->prox->chave[valor] > lista->prox->prox->chave[valor]){
                flag = 1;
                aux = lista->prox;
                lista->prox = aux->prox; // 20 ligou 40
                aux->prox = lista->prox->prox; // 60 ligou no 70
                lista->prox->prox = aux; // 40 ligou no 60
            }
        }
    }while(flag);

    if(ini->chave[valor] > ini->prox->chave[valor]){
        lista = ini->prox;                          //Arrumar início
        ini->prox = lista->prox;
        lista->prox = ini;
        ini = lista;

        for( ; lista->prox->prox; lista = lista->prox){
            if(lista->prox->chave[valor] > lista->prox->prox->chave[valor]){
                aux = lista->prox;
                lista->prox = aux->prox;
                aux->prox = lista->prox->prox;
                lista->prox->prox = aux;
            }
        }
    }

    return ini;
}


///INSERTION SORT///

struct elemento *insertion_sort(struct elemento *lista, int valor){

    struct elemento *aux, *aux_b, *ini;
    ini = lista;

    if(!ini || !ini->prox)
        return ini;

    for(aux = lista; aux->prox; lista = aux_b = ini){

        for( ;aux->prox->chave[valor] >= lista->chave[valor] && lista->prox != aux->prox; aux_b = lista, lista = lista->prox);

        if(aux->prox->chave[valor] < lista->chave[valor]){
            if(lista == ini){
                ini = aux->prox;
                aux->prox = aux->prox->prox;
                ini->prox = lista;
            }
            else{
                aux_b->prox = aux->prox; //liga 10 no 20
                aux->prox = aux->prox->prox; //liga 30 no 40
                aux_b->prox->prox = lista; //liga 20 no 30
            }
        }
        else{
            aux = aux->prox;
        }

    }
    return ini;
}



///SELECTION SORT///

struct elemento *selection_sort(struct elemento *lista, int valor){

    struct elemento *ini, *aux_b, *aux;
    ini = lista;

    if(!ini || !ini->prox)
        return ini;

    for(aux_b = aux = ini; lista->prox; lista = lista->prox){       //Primeira passada eu encontro o ini
        if(lista->prox->chave[valor] < aux->chave[valor]){
            aux_b = lista;
            aux = lista->prox;
        }
    }
    if(aux != aux_b){
        aux_b->prox = aux->prox;
        aux->prox = ini;
        ini = aux;
    }

    for(aux = ini; aux->prox; aux = aux->prox){                     //Depois não mexo mais no ponteiro inicial
        for(aux_b = aux ,lista = aux->prox; lista->prox; lista = lista->prox){
            if(lista->prox->chave[valor] < aux_b->prox->chave[valor]){
                aux_b = lista;
            }
        }
        lista = aux_b->prox;
        aux_b->prox = aux_b->prox->prox;
        lista->prox = aux->prox;
        aux->prox = lista;
    }

    return ini;
}


///QUICK SORT///

struct elemento *particiona(struct elemento *pivo, int valor){

    struct elemento *ini, *aux, *ant;

    //Se não tem o pivo ou ele não tem próximo, então já está ordenado
    if(!pivo || !pivo->prox)
        return pivo;

    //Ini começa em NULL, para caso não tenha trocas (return NULL) e para apontar para inicio de menores
    ini = NULL;

    //Aux começa depois do pivo e anterior começa em pivo
    aux = pivo->prox;
    ant = pivo;

    while(aux){
        //Realiza a troca ja avançando aux. O ant não precisa trocar pois ele já se ligará no aux
        if(aux->chave[valor] < pivo->chave[valor]){
            aux = aux->prox;
            ant->prox->prox = ini;
            ini = ant->prox;
            ant->prox = aux;
        }
        //Se não trocar avança o aux e o ant, pois eles tem que andar junto (ant à retaguarda)
        else{
            ant = ant->prox;
            aux = aux->prox;
        }
    }

    return ini;
}

struct elemento *quick_sort(struct elemento *pivo, int valor){

    struct elemento *menor, *aux, *teste;

    menor = particiona(pivo, valor);

    if(menor && menor->prox){
        menor = quick_sort(menor, valor);
    }

    if(pivo->prox && pivo->prox->prox){
        pivo->prox = quick_sort(pivo->prox, valor);
    }

    if(!menor){
        return pivo;
    }
    else{
        for(aux = menor; aux->prox; aux = aux->prox);
        aux->prox = pivo;
        return menor;
    }

}




///MERGE SORT///

struct elemento *mesclar(struct elemento *esq, struct elemento *dir, int valor){

    //Novo ini de cada parte, que no final será o ponteiro inicial
    struct elemento *nini;

    /*Meu return será feito quando cada elemento estiver solo, e no if e else
    ligação entre elementos*/
    if(!esq){
        return dir;
    }
    if(!dir){
        return esq;
    }
    //Se o elemento da esquerda for <=, mantem ordem relativa = estável
    if(esq->chave[valor] <= dir->chave[valor]){
        nini = esq;
        nini->prox = mesclar(esq->prox, dir, valor);
    }
    else{
        nini = dir;
        nini->prox = mesclar(esq, dir->prox, valor);
    }
    return nini;
}


struct elemento *merge_sort(struct elemento *ini, int valor){

    struct elemento *meio, *esq, *dir, *fim;

    //Se a lista n existe ou tem 1 elemento, já ta ordenada.
    if(!ini || !ini->prox){
        return ini;
    }

    //Sempre vou parar no ponto médio da lista, se ela for par para no último da esq (divisão)
    for(meio = ini, fim = ini->prox; fim && fim->prox; fim = fim->prox->prox, meio = meio->prox);

    esq = ini;
    dir = meio->prox;
    meio->prox = NULL;

    //dividir a lista até o talo, ou seja, ter um elemento, ai n pode mais dividir
    esq = merge_sort(esq, valor);
    dir = merge_sort(dir, valor);

    return mesclar(esq, dir, valor);
}


double calcDuracao(clock_t i, clock_t f) {
    return (double) (f - i) / CLOCKS_PER_SEC;
}


void main(){
setlocale(LC_ALL, "portuguese");

    clock_t inicio, fim;
    double duracao = 0, rb[4][10], ri[4][10], rs[4][10], rq[4][10], rm[4][10];
    int i, j, k;
    struct elemento *l_um[4][10], *l_dois[4][10], *l_tres[4][10], *l_quatro[4][10], *lista;
    srand((unsigned) time(NULL));

    //Gerar a lista total.
    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            l_um[i][j] = gerar_lista(100, i+1);
            l_dois[i][j] = gerar_lista(5000, i+1);
            l_tres[i][j] = gerar_lista(20000, i+1);
            l_quatro[i][j] = gerar_lista(32000, i+1); //32400 max
        }
    }

    printf("\nGEROU LISTAS\n");



    //100 ELEMENTOS
    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            for(duracao = k = 0; k < N1; k++){
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
            }
            rb[i][j] = duracao;

            for(duracao = k = 0; k < N1; k++){
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                ri[i][j] = duracao;
            }
            ri[i][j] = duracao;

            for(duracao = k = 0; k < N1; k++){
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rs[i][j] = duracao;
            }
            rs[i][j] = duracao;

            for(duracao = k = 0; k < N1; k++){
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rq[i][j] = duracao;
            }
            rq[i][j] = duracao;

            for(duracao = k = 0; k < N1; k++){
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_um[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rm[i][j] = duracao;
            }
            rm[i][j] = duracao;

        }
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\n                      TEMPO DE ORDENAÇÃO - 100 ELEMENTOS - N1 VALENDO %d\n", N1);
    printf("----------------------------------------------------------------------------------------------------------------------");

    printf("\nBUBBLE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rb[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    printf("\nINSERTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", ri[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nSELECTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rs[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nQUICK SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rq[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nMERGE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rm[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n\n\n");


    //5000 ELEMENTOS
    printf("\nTEMPO DE ORDENAÇÃO - 5000 ELEMENTOS\n");
    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            for(duracao = k = 0; k < N2; k++){
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
            }
            rb[i][j] = duracao;

            for(duracao = k = 0; k < N2; k++){
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                ri[i][j] = duracao;
            }
            ri[i][j] = duracao;

            for(duracao = k = 0; k < N2; k++){
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rs[i][j] = duracao;
            }
            rs[i][j] = duracao;

            for(duracao = k = 0; k < N2; k++){
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rq[i][j] = duracao;
            }
            rq[i][j] = duracao;

            for(duracao = k = 0; k < N2; k++){
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_dois[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rm[i][j] = duracao;
            }
            rm[i][j] = duracao;

        }
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\n                      TEMPO DE ORDENAÇÃO - 5000 ELEMENTOS - N2 VALENDO %d\n", N2);
    printf("----------------------------------------------------------------------------------------------------------------------");

    printf("\nBUBBLE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rb[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    printf("\nINSERTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", ri[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nSELECTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rs[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nQUICK SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rq[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nMERGE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rm[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    //20000 ELEMENTOS
    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            for(duracao = k = 0; k < N3; k++){
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
            }
            rb[i][j] = duracao;

            for(duracao = k = 0; k < N3; k++){
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                ri[i][j] = duracao;
            }
            ri[i][j] = duracao;

            for(duracao = k = 0; k < N3; k++){
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rs[i][j] = duracao;
            }
            rs[i][j] = duracao;

            for(duracao = k = 0; k < N3; k++){
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rq[i][j] = duracao;
            }
            rq[i][j] = duracao;

            for(duracao = k = 0; k < N3; k++){
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_tres[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rm[i][j] = duracao;
            }
            rm[i][j] = duracao;

        }
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\n                      TEMPO DE ORDENAÇÃO - 20000 ELEMENTOS - N3 VALENDO %d\n", N3);
    printf("----------------------------------------------------------------------------------------------------------------------");

    printf("\nBUBBLE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rb[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    printf("\nINSERTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", ri[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nSELECTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rs[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nQUICK SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rq[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nMERGE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rm[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    //32000 ELEMENTOS
    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            for(duracao = k = 0; k < N4; k++){
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = bubble_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
            }
            rb[i][j] = duracao;

            for(duracao = k = 0; k < N4; k++){
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = insertion_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                ri[i][j] = duracao;
            }
            ri[i][j] = duracao;

            for(duracao = k = 0; k < N4; k++){
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = selection_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rs[i][j] = duracao;
            }
            rs[i][j] = duracao;

            for(duracao = k = 0; k < N4; k++){
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = quick_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rq[i][j] = duracao;
            }
            rq[i][j] = duracao;

            for(duracao = k = 0; k < N4; k++){
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 0);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                lista = gerar_copia(l_quatro[i][j]);
                inicio = clock();
                lista = merge_sort(lista, 1);
                fim = clock();
                duracao += calcDuracao(inicio, fim);
                excluir_lista(lista);
                rm[i][j] = duracao;
            }
            rm[i][j] = duracao;

        }
    }

   printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\n                      TEMPO DE ORDENAÇÃO - 32000 ELEMENTOS - N4 VALENDO %d\n", N4);
    printf("----------------------------------------------------------------------------------------------------------------------");

    printf("\nBUBBLE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rb[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");

    printf("\nINSERTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", ri[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nSELECTION SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rs[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nQUICK SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rq[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nMERGE SORT\n");
    for(i = 0; i < 4; i++){
        printf("\nTIPO %d\n", i+1);
        for(j = 0; j < 10; j++){
            printf("%.3f  ", rm[i][j]);
        }
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");


    for(i = 0; i < 4; i++){
        for(j = 0; j < 10; j++){
            excluir_lista(l_um[i][j]);
            excluir_lista(l_dois[i][j]);
            excluir_lista(l_tres[i][j]);
            excluir_lista(l_quatro[i][j]);
        }
    }
}
