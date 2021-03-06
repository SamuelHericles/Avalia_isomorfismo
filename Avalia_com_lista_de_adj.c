/*

                    UNIVERSIDADE FEDERAL DO CEARÁ  
                            CAMPUS SOBRAL
                  CURSO DE ENGENHARIA DE COMPUTÇÃO
                        ALGORITMOS E GRAFOS

                      SAMUEL HERICLES - 389118

    Objetivo -> Fazer um verificar de grafos isomorfos.É preciso de 
    pelo menos 5 testes para verificar se é ou não isomorfos, caso
    positivo, um fazer um ultimo teste de força bruta.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define vertex int
typedef struct no *link;
typedef struct grafo *Grafo;

/* Estrutura para represetação do grafo */ 
struct grafo{
    int V;//-> número total de vértices no grafo.
    int A;//-> número total de aresta no grafo.
    link *adj; //-> Ponteiro para dizer o 'proximo' vértice que liga ao vértices.
};

/* Estrutura para conexão e contagem dos vértices na lista de adjacência */
struct no{
    vertex w;//-> número do vértices que eh referencia pelo o vértice raiz da lista.
    link prox;//-> Ponteiro para o próximo vértice da lista.
};

/* Funções para criação e exibição de um grafo aleatório */

/**
 * @brief      Insere um novo nó aresta, diz qual o número 
 *             vértice e aponta para o próximo.
 *
 * @param[in]   w      Número vértice a ser adicionado na lista.
 * @param[in]   prox   prónteiro para o vértice adicionado na lista.
 * 
 * return Ponteiro da lista na memória.
 */
static link Novo_no(vertex w, link prox){
    link a = malloc(sizeof(struct no));
    a->w = w;
    a->prox = prox;
    return a;
}

/**
 * @brief      Gera um grafo sem aresta apenas os vértices.
 *
 * @param[in]  V    Número de vértices a serem cirados.
 * 
 * return Ponteiro para o grafo na memória.
 */
Grafo Gera_Grafo(int V){
    Grafo G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V*sizeof(link));
    for(vertex v = 0; v<V;v++)
        G->adj[v] = NULL;
    return G;
}

/**
 * @brief      Insere uma aresta (v,w) no grafo
 *
 * @param[     G   Grafo a ser adicionado a aresta.
 * @param[in]  v   Vértice raiz que irá apontar algo.
 * @param[in]  w   Vértice que irá ser referencia pela raiz.
 */
void Grafo_insere(Grafo G, vertex v, vertex w){
    for(link a = G->adj[v]; a !=NULL ; a = a->prox)
        if(a->w == w) return;

    G->adj[v] = Novo_no(w, G->adj[v]);
    G->adj[w] = Novo_no(v, G->adj[w]);
    G->A++;

}

/**
 * @brief      Exibe o grafo em lista de adjacência
 *
 * @param  G   Grafo a ser exibido.
 */
void Mostra_Grafo(Grafo G){
    for(vertex v = 0 ; v<G->V; v++){
        printf("|%2d|->",v);
        for(link p = G->adj[v]; p!=NULL; p = p-> prox){
            
            if(p->prox!=NULL) printf("|%2d|->",p->w);
            else printf("|%2d|",p->w);
        }
        printf("\n");
    }
}

/**
 * @brief      Liga os vértices gerando um grafo aleatório
 *
 * @param[in]  num_vertices   Número véritices que serão recebidos com arestas.
 * 
 * return Ponteiro para o grafo na memória.
 */
Grafo Gera_Grafo_Random(int num_vertices,int teto){
    struct grafo *G;
    int prob;
    G = Gera_Grafo(num_vertices);

    for(int i = 0 ; i< G->V; i++){
        for(int j = 0; j<G->V; j++){
            prob = rand()%100;
            if(i != j) if( prob > teto) Grafo_insere(G,i,j);
        }
    }
    return G;
}

/* Funções para teste de isormofismos em dois grafos */

/*          ->>>>>>>>>>>>>>>Busca em profundidade<<<<<<<<<<<<-         */
int cnt;
int pre[1000];
int pre1[1000];

int BP_visit( Grafo G, vertex v, int *pre1){ 
   pre[v] = cnt++; 
   for (link a = G->adj[v]; a != NULL; a = a->prox) {
      vertex w = a->w;
      if (pre[w] == -1)
         BP_visit( G, w,pre1); 
    }
   return 1;
}

int Busca_em_profundidade( Grafo G){ 
   cnt = 0;
   int a = 0;
   vertex v;
    for(vertex v = 0; v < G->V; ++v) 
      pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v){
     if (pre[v] == -1)
       a += BP_visit(G,v,pre1); // começa nova etapa
    }
    return a;
}
/*  ->>>>>>>>>>>>>>>Fim da busca em profundidade<<<<<<<<<<<<-          */

/**
 * @brief      Verifica e compara o número de vértices de dois grafos.
 *
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verifica_num_vertices(Grafo G1, Grafo G2){
    //printf("G1-> %d||G2-> %d\n",G1->V,G2->V);
    if(G1->V == G2->V){
        //printf("--Possuem a mesma quantidade de vertices\n");
        return 1;
    }
    //printf("--Nao possuem a mesma quantidade de vertices\n");
    return 0;
}

/**
 * @brief      Verifica o número total de arestas de dois grafos.
 *
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verifica_arestas(Grafo G1, Grafo G2){
    //printf("G1-> %d||G2-> %d\n",G1->A,G2->A);
    if(G1->A == G2->A){
        //printf("--Possuem a mesma quantidade de arestas\n");
        return 1;
    }
    //printf("--Nao possuem a mesma quantidade de arestas\n");
    return 0;
}

/**
 * @brief      Vérifica os graus de cada vértices de um grafos e 
 *             compara se a outro de mesmo grau no outro grafo.
 *
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verifica_grau_vertices(Grafo G1,Grafo G2){
    int a = 0;
    int grau1[G1->V];
    int grau2[G2->V];
    
    
    for(vertex v = 0 ; v<G1->V; v++){
        for(link p = G1->adj[v]; p!=NULL; p = p-> prox)
            a+=1;
        grau1[v] = a;
        a=0;
    }
    a=0;

    printf(" V-> Vertice\nG1-> Graus grafo 1\nG2-> Graus grafo 2\n");
    printf("__V____G1___G2_\n");
    for(vertex v = 0 ; v<G2->V; v++){
      printf("|%2d|->",v);
      for(link p = G2->adj[v]; p!=NULL; p = p-> prox)
            a+=1;
      grau2[v] = a;
      printf("%2d | %2d\n",grau1[v],grau2[v]);
      a=0;
    }

    printf("\n");
    for(int i = 0 ; i < G1->V ; i++){
      for(int j = 0; j< G1->V ; j++){
        if(grau2[j]!= -1 ){
            if(grau1[i]==grau2[j]){
                grau1[i] = grau2[j] = -1;
                break;
            }
        }
      }
    }
    
    for(int i = 0 ; i<G1->V;i++){
        printf("|%2d|-> %2d | %2d\n",i,grau1[i],grau2[i]);
    }

    for(int i = 0; i<G1->V;i++){
        if(grau1[i]!=-1){
            //printf("--Nao possuem os mesmos graus\n");
            return 0;
        }
    }
    //printf("\n--Possuem os mesmos graus\n");
    return 1;    
}

/**
 * @brief      Verifica se os grafos são desconexos.
 *
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verfica_desconexo(Grafo G1,Grafo G2){
    int a,b;

    a = Busca_em_profundidade(G1);
    b = Busca_em_profundidade(G2);

    //if(a!=1) printf("O Grafo 1 eh desconexo\n");
    //else printf("O Grafo 1 nao eh desconexo\n");

    //if(b!=1) printf("O Grafo 2 eh desconexo\n");
    //else printf("O Grafo 2 nao eh desconexo\n");

    if(a!=b) return 0;
    else return 1;    

}

/**
 * @brief      Conta a quantidade de componentes conexas e
 *             avalia se são iguais ou não
 *
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verifica_componetes_conexas(Grafo G1,Grafo G2){
    int a,b;
    
    a = Busca_em_profundidade(G1);
    b = Busca_em_profundidade(G2);

    //printf("O Grafo 1 tem %d componente(s) conexa(s)\n",a);
    //printf("O Grafo 2 tem %d componente(s) conexa(s)\n",b);

    if(a!=b) return 0;
    else return 1;
}

/**
 * @brief      Verifica se há vértices de grau <= vertices - 1, de
 *             acordo com o teorema.
 * 
 * @param      G1 Grafo para verificação.
 * @param      G2 Grafo para verificação.
 * 
 * return return 0 ou 1 com boleano para True e false, respectivamente.
 */
int Verfica_livre_de_circuitos(Grafo G1,Grafo G2){

    int verific1;
    int verific2;

    if(G1->A <= (G1->V - 1))
        verific1 = 1;
    if(G2->A <= (G2->V - 1))
        verific2 = 1;

    if((verific1 == 1) && (verific2 == 1)){
        //printf("--Grafos livre de circuitos");
        return 1;
    }

    if((verific1 == 1) || (verific2 == 1)){
        if(verific1 == 1){
            //printf("--Grafo 1 eh livre de circuitos\n");
            return 0;
        }
       if(verific2 == 1){
            //printf("--Grafo 2 eh livre de circuitos\n");
            return 0;
        } 
    } 
    
    else {
        //printf("--Nenhum grafo eh livre de circuitos\n");
        return 0;
    }
}

int main(){
    setlocale(LC_ALL, "portuguese");

    srand(time(NULL));
    
    struct grafo *G1,*G2;
    printf("\n\n"); 

    /*
    
    G1 = Gera_Grafo_Random(rand()%100+1,p);
    G2 = Gera_Grafo_Random(rand()%100+1,p);
    
    printf("________________GRAFO -> 1________________________\n");
    Mostra_Grafo(G1);
    
    printf("________________GRAFO -> 2________________________\n");
    Mostra_Grafo(G2);
    
    printf("\n>>>NUMERO DE VERTICES DE CADA GRAFO\n");
    int teste_1 = Verifica_num_vertices(G1,G2);

    printf("\n>>>SOMA DOS GRAUS DE CADA GRAFO\n");
    int teste_2 = Verifica_arestas(G1,G2);

    printf("\n>>>DESCONEXO OU NAO\n");
    int teste_3 = Verfica_desconexo(G1,G2);

    printf("\n>>>QUANTIDADE DE COMPONENTES CONEXAS\n");
    int teste_4 = Verifica_componetes_conexas(G1,G2);    

    printf("\n>>>EH LIVRE DE CIRCUITOS OU NAO\n");
    int teste_5 = Verfica_livre_de_circuitos(G1,G2);

    int total = teste_1 + teste_2 + teste_3 + teste_4 + teste_5;
    if(total == 5){
        printf("\n\n>>>>OS GRAFOS SAO ISOMORFOS<<<<<\n");
        printf("\n>>>>FORCA BRUTA:GRAUS DE CADA VERTICE\n");
        Verifica_grau_vertices(G1,G2);

        return 1;
    }
    printf("\n\n>>>>OS GRAFOS NAO SAO ISOMORFOS<<<<<\n\n%d\n",total);
    
    printf("\n\n\n");
    */
    int p;
    int a = 0;
    int i;

    clock_t seconds1 ;
    clock_t seconds2 ;
    clock_t seconds3 ;
    clock_t seconds4 ;
    clock_t seconds5 ;
    clock_t seconds6 ;

    seconds1 = clock();

    for(i = 0; i< 100 ; i++){
        p = 25;
        G1 = Gera_Grafo_Random(rand()%100+1,p);
        G2 = Gera_Grafo_Random(rand()%100+1,p);
        
        //printf("\n\n\n\n");
        int teste_1 = Verifica_num_vertices(G1,G2);
        int teste_2 = Verifica_arestas(G1,G2);
        int teste_3 = Verfica_desconexo(G1,G2);
        int teste_4 = Verifica_componetes_conexas(G1,G2);    
        int teste_5 = Verfica_livre_de_circuitos(G1,G2);
        int total = teste_1 + teste_2 + teste_3 + teste_4 + teste_5;
        if(total == 5){
            printf("\n\n>>>>OS GRAFOS SAO ISOMORFOS<<<<<\n");
            printf("\n>>>>FORCA BRUTA:GRAUS DE CADA VERTICE\n");
            Verifica_grau_vertices(G1,G2);
            a+=1;
        }
        //printf("\n\n>>>>OS GRAFOS NAO SAO ISOMORFOS<<<<<\n\n%d\n",total);    
    }

    seconds2 = clock();

    double tempo = (seconds2-seconds1)*1000.0/CLOCKS_PER_SEC;

    printf("\n___Grafos com %d%% de inserção____\n",p);
    printf("%.2f ms",tempo);
    printf("\n%d grafos isomorfos\n",a*2);

    seconds3 = clock();
    a = 0;
    for(i = 0; i< 100 ; i++){
        p = 50;
        G1 = Gera_Grafo_Random(rand()%100+1,p);
        G2 = Gera_Grafo_Random(rand()%100+1,p);
        
        //printf("\n\n\n\n");
        int teste_1 = Verifica_num_vertices(G1,G2);
        int teste_2 = Verifica_arestas(G1,G2);
        int teste_3 = Verfica_desconexo(G1,G2);
        int teste_4 = Verifica_componetes_conexas(G1,G2);    
        int teste_5 = Verfica_livre_de_circuitos(G1,G2);

        int total = teste_1 + teste_2 + teste_3 + teste_4 + teste_5;
        if(total == 5){
            printf("\n\n>>>>OS GRAFOS SAO ISOMORFOS<<<<<\n");
            printf("\n>>>>FORCA BRUTA:GRAUS DE CADA VERTICE\n");
            Verifica_grau_vertices(G1,G2);
            a+=1;
        }
        //printf("\n\n>>>>OS GRAFOS NAO SAO ISOMORFOS<<<<<\n\n%d\n",total);
    }

    seconds4 = clock();

    double tempo2 = (seconds4-seconds3)*1000.0/CLOCKS_PER_SEC;
    
    printf("\n___Grafos com %d%% de inserção____\n",p);
    printf("%.2f ms",tempo2);
    printf("\n%d grafos isomorfos\n",a*2);
    

    seconds5 = clock();
    a=0;
    for(i = 0; i< 100 ; i++){
        p = 75;
        G1 = Gera_Grafo_Random(rand()%100+1,p);
        G2 = Gera_Grafo_Random(rand()%100+1,p);
        
        //printf("\n\n\n\n");
        int teste_1 = Verifica_num_vertices(G1,G2);
        int teste_2 = Verifica_arestas(G1,G2);
        int teste_3 = Verfica_desconexo(G1,G2);
        int teste_4 = Verifica_componetes_conexas(G1,G2);    
        int teste_5 = Verfica_livre_de_circuitos(G1,G2);

        int total = teste_1 + teste_2 + teste_3 + teste_4 + teste_5;
        if(total == 5){
            printf("\n\n>>>>OS GRAFOS SAO ISOMORFOS<<<<<\n");
            printf("\n>>>>FORCA BRUTA:GRAUS DE CADA VERTICE\n");
            Verifica_grau_vertices(G1,G2);
            a+=1;
        }
        //printf("\n\n>>>>OS GRAFOS NAO SAO ISOMORFOS<<<<<\n\n%d\n",total);
    
    }
    seconds6 = clock();

    double tempo3 = (seconds6-seconds5)*1000.0/CLOCKS_PER_SEC;
    
    printf("\n___Grafos com %d%% de inserção____\n",p);
    printf("%.2f ms",tempo3);
    printf("\n%d grafos isomorfos\n\n\n",a*2);


}