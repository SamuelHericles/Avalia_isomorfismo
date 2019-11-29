/*

                    UNIVERSIDADE FEDERAL DO CEARÁ  
                            CAMPUS SOBRAL
                  CURSO DE ENGENHARIA DE COMPUTÇÃO
                        ALGORITMOS E GRAFOS

                      SAMUEL HERICLES - 389118

    Objetivo -> Fazer um verificador de grafos isomorfos.É preciso de 
    pelo menos 5 testes para verificar se é ou não isomorfo.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Estrutura para represetação do grafo */ 
typedef struct Grafo *grafo;

/* Estrutura para conexão e contagem dos vértices na matriz de adjacência */
struct Grafo{
    int tamanho;
    int *adjMatrix;
};

            /* Funções para criação e exibição de um grafo aleatório */


/**
 * @brief      Pecorre um vetor 'matriz' de adjacência
 *
 * @param[in]   i   número da coluna
 * @param[in]   j   número da linha
 * @param[in]   n   tamanho da matriz quadrada
 * 
 * return Posicao da célula na 'matriz' de adj
 */
int getIndex(int i, int j, int n){
        if(i<j)
            return (2*n-i-1)*i/2+(j-i)-1;
        else
            return (2*n-j-1)*j/2+(i-j)-1;
}

/**
 * @brief      verifica uma valor em uma célula da matriz
 *             para representar a inserção de dois vértices.
 *
 * @param[in]   i   número da coluna
 * @param[in]   j   número da linha
 * @param[in]   g   struct do grafo
 * 
 * return valor na célula do vetor 'matriz' de adj
 */
int edge(int i, int j, grafo g){
    return g->adjMatrix[getIndex(i, j, g->tamanho)];
}

/**
 * @brief      Define um valor para conectar ou apagar 
 *             dois vértices.
 *
 * @param[in]   valor   valor para inserir na matriz de adjacência
 * @param[in]   j       número da linha
 * @param[in]   g       struct do grafo
 * 
 */
void setEdge(int valor, int i, int j, grafo g){
    g->adjMatrix[getIndex(i, j, g->tamanho)] = valor; 
}



/**
 * @brief      Exibe o grafo em lista de adjacência
 *
 * @param  g   Grafo a ser exibido.
 */
void mostraGrafo(grafo g){
    printf("\n");
    for( int i = 0; i < g->tamanho ; i++){
        for(int  j = 0; j < g->tamanho ; j++){
            if(i != j)printf("%d ",edge(i,j,g));
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief      Exibe o grafo em lista de adjacência
 *
 * @param  g1   Grafo a ser exibido.
 * @param  g2   Grafo a ser exibido.
 */
void mostra_dois_grafo(grafo g1,grafo g2){

    printf(" Grafo 1\n");
    mostraGrafo(g1);
    printf(" Grafo 2\n");
    mostraGrafo(g2);

}

/**
 * @brief      Criação do grafo aleatoriamente
 *
 * @param  n    número de vértices do grafo.
 * @param  p    probabilidade de inserção de cada aresta.
 * 
 * return  retorna o grafo criado inserido arestas aleatoriamente
 */
grafo criaGrafo(int n,int p){
    grafo g = malloc(sizeof(grafo));
    g->tamanho = n;
    g->adjMatrix =  malloc((g->tamanho*(g->tamanho-1)/2)*sizeof(grafo));

    for(int i = 0; i < (g->tamanho*(g->tamanho-1)/2) ; i++){
        int prob = rand()%100;
        if(prob < p) g->adjMatrix[i] = 1;
        else g->adjMatrix[i] = 0;
    }
    //printf("\n");
    return g;
}

/**
 * @brief      Mede e exibe o tempo de cálculo das verificações 
 *             para isormofismo.
 *
 * @param  t_ini Tempo inicial do ciclo de repeticação
 * @param  t_ini Tempo fim do ciclo de repeticação
 */
double Exibe_tempo(clock_t t_ini, clock_t t_fim){

    double tempo = (t_fim-t_ini)*1000.0/CLOCKS_PER_SEC;
    //printf("\tTempo total de compilacao: %.2f ms\n",tempo);
    return tempo;

}
/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||||||||||||||||||||| BUSCA EM PROFUNDADE ||||||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/
/**
 * @brief      visita e marca os vértices da estrutura do grafo
 *
 * @param  g      struct do grafo
 * @param  cor    endereço do vetor de cor
 * @param  pais   endereço do vetor que armazena a descendência ao vértice raiz
 * @param  i      vetor a ser analisado seu caminho      
 * @param  aux    endenreço do vetor auxiliar para o vetor pai
 *   
 */
void bpVisit2(grafo g, int *cor, int *pais, int i, int *aux){
 int j;
 cor[i]=-1; 
 for(j=0;j<g->tamanho;j++){
  if(i!=j){
   if(edge(i,j,g)==1){
       if(cor[j]==-1){
        if(pais[i]!=j){
         *aux=1;
     }
    }else if(cor[j]==0){
        pais[j] = i;
        bpVisit2(g, cor, pais, j, aux);
    }
   }
  }
 }
 cor[i] = 1;
}

/**
 * @brief        Algortimo de busca em profundidade para armazenar os pais com o intuito de 
 *               descobrir se o grafo possui circuito
 *
 * @param  g     estrutura de grafo para ser visitado so vértice
 *
 *
 * return bool 1 para caso não tiver circuito e 0 para caso tiver circuito.
 */
int Busca_em_profundidade_para_pai(grafo g) {
 int cor[g->tamanho];
 int pais[g->tamanho];
 int aux = 0;
 int circuito = 0;
 int i,j = 0;

 for(i=0;i<g->tamanho;i++){
     cor[i] = 0; 
     pais[i] = -1;
 }  
 for(i=0;i<g->tamanho;i++){
     bpVisit2(g, cor, pais, i, &aux);
     if(aux==1){
      return 1;//quando tem circuito
     }
 }return 0; // quando n tem circuito
}

/**
 * @brief      visita e marca os vértices da estrutura do grafo
 *
 * @param  g         estrutura de grafo para ser visitado so vértice
 * @param  vertice   ponteiro para o vetor vértice que a função
 *                   'Busca_em_profundidade' busca
 *
 * @param  i         posição do vetor 'vertice' a ser visitada
 */
void BP_visit(grafo g,int *vertice, int i){ 
    vertice[i] = -1;
    for(int j = 0; j < g->tamanho; j++){
        if(edge(i,j,g) == 1){
            if(vertice[j] == 0){
                BP_visit(g,vertice,j);
            }
        }
    }
    vertice[i] = 1;
}

/**
 * @brief      algoritmo de busca em profundiade modificado para contar
 *             o número de componentes conexas
 *
 * @param  g   estrutura de grafo para ser visitado os vértice
 * 
 * return  a   número de componentes conexas
 */
int Busca_em_profundidade(grafo g){ 
   //-1 cinza
   // 0 branco
   // 1 preto
   int a = 0;
   int vertices[g->tamanho];

   for(int i = 0; i < g->tamanho; i++) 
       vertices[i] = 0;

   for(int i = 0; i < g->tamanho; i++) {
       if(vertices[i] == 0){
           a++;
           BP_visit(g,vertices,i);
       }
       /*    EXIBIR PASSO A PASSO DO ALGORITMO 

        printf("\n%d entrada(s) no BP_visit\n",a);
        printf("\nVertices->");
        for(int i = 0; i < g->tamanho ; i++)
                printf(" |%2d | ",i+1);
        printf("\n");
            printf("          ");
        for(int i = 0; i < g->tamanho ; i++)
                printf(" |%2d | ",vertices[i]);
        printf("\n\n");
       
        */

    }

    return a;
    
}


/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||||||||||||||||||||| FUNÇÕES DE VERIFICIAÇÃO|||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

/**
 * @brief      Verificar se há circuitos no grafos
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 * 
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_circuito(grafo g1, grafo g2){
    if(Busca_em_profundidade_para_pai(g1) != Busca_em_profundidade_para_pai(g2))
        return 1;
    else
        return 0; 

}

/**
 * @brief      verificar se o numero de vértices são iguais para
 *             os dois grafos
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_num_vertices(grafo g1, grafo g2){
    //printf("\n%d||%d",g1->tamanho,g2->tamanho);
    if(g1->tamanho == g2->tamanho)
        return 0;
    return 1;
}

/**
 * @brief      verificar se o numero de arestas são iguais para
 *             os dois grafos
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_num_arestas(grafo g1, grafo g2){
    int a=0;
    int b=0;
    for(int i = 0; i < g1->tamanho ; i++){
        for(int j = i+1; j < g1->tamanho; j++){
            if(edge(i,j,g1)==1){
                a++;             }
        }
    }
    for( int i = 0; i < g2->tamanho ; i++){
        for(int  j = i+1; j < g2->tamanho ; j++){
            if(edge(i,j,g2)==1){
                b++;
            }
        }
    }
    //printf("\n%d||%d",a,b);
    if(a == b)
        return 0;
    return 1;

}

/**
 * @brief   verificar se o numero de vértices de mesmo 
 *          são iguais para os dois grafos
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_vertices_de_mesmo_grau(grafo g1, grafo g2){
 int *temp1, *temp2, i, j,aux;
 temp1 = malloc(g1->tamanho*sizeof(int));
 temp2 = malloc(g2->tamanho*sizeof(int)); 
 
    for(i=0;i<g1->tamanho;i++)
         temp1[i]=0;

    for(i=0;i<g2->tamanho;i++)
        temp2[i]=0;
    
    for(i = 0; i< g1->tamanho;i++){
        aux = 0;
        for(j = 0; j< g1->tamanho;j++)
            if(i!=j)  aux+=edge(i,j,g1);
        temp1[aux]+=1;
    }
    
    for(i = 0; i< g2->tamanho;i++){
        aux = 0;
        for(j = 0; j< g2->tamanho;j++){
            if(i!=j)
                aux+=edge(i,j,g2);
        }
        temp2[aux]++;
    }
    for(i=0;i<g2->tamanho;i++)
        if(temp1[i] != temp2[i]) return 1;
        //printf("%d    %d",temp1[i],temp2[i]);
    return 0;
}

/**
 * @brief   verificar um dos grafos são desconexos
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_desconexo(grafo g1, grafo g2){
    int grafo1 = Busca_em_profundidade(g1);
    int grafo2 = Busca_em_profundidade(g2);
    //printf("    %d||%d ",grafo1,grafo2);
    if((grafo1 > 1)&&(grafo2 > 1)){
       // printf("\nAmbos os grafos sao desconexos\n");
        return 0;
    } else {
        //if(grafo1 > 1) printf("\nGrafo 1 eh desconexo\n");
        //else if(grafo2 > 1 ) printf("\nGrafo 2 eh desconexo\n");
        return 1;
    } 
}

/**
 * @brief   verificar a quantidade componentes conexas de
 *          cada grafo.
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  '0' se for igual e '1' se for diferente
 */
int Verifica_comp_desconexas(grafo g1, grafo g2){

    int grafo1 = Busca_em_profundidade(g1);
    int grafo2 = Busca_em_profundidade(g2);
    if(grafo1 == grafo2){
        //printf("\nAmbos possuem mesma qt de comp desconexas\n");
        return 0;
    } else {
        //printf("\nGrafo 1 -> %d comp desconxa(s)\nGrafo 2 -> %d comp desconxa(s)\n",grafo1,grafo2);
        return 1;
    } 
}

/**
 * @brief   verificar se todos os testes acima resultada em '0'
 *
 * @param  g1   estrutura do grafo 1 
 * @param  g2   estrutura do grafo 2 
 *
 * return  quantidade testes que passaram
 */
int Verifica_isomorfismo(grafo g1, grafo g2){
    int a = 0, b = 0, c = 0, d = 0 ,e = 0,f = 0 ;
    int aux = 0;
    //printf("\n1.Num de vertices-> ");
    a = Verifica_num_arestas(g1,g2);

    //printf("\n2.Num de arestas -> ");
    b = Verifica_num_vertices(g1,g2);

    //printf("\n3.Desconexos-> ");
    c = Verifica_comp_desconexas(g1,g2);

    //printf("\n4.Qt de comp desconexas-> ");
    d = Verifica_desconexo(g1,g2);

    //printf("\n5.Qtd->\n");
    e = Verifica_vertices_de_mesmo_grau(g1,g2);

    //printf("\n6. Se há ou não circuitos->\n");
    f = Verifica_circuito(g1,g2);

    if((a+b+c+d+e+f) == 0){
        aux++;
    }
    //else
        //printf(" |%2d| Os grafos NAO sao isomorfos",a+b+c+d+e);
    return aux;
}

/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||||||||||||||||||||| FUNÇÃO PRINCIPAL||||||||||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

int main(){
    srand(time(NULL));
    struct Grafo *g1,*g2;
    int qt = 0 ;
    clock_t t_ini;
    clock_t t_fim;
    double  tempo = 0, tempo_aux = 0, tempo_medio = 0 ;

    //Testes

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    printf("\n|||||||||||||||||||||||||||| 8 VÉRTICES ||||||||||||||||||||||||||||");
    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    //  25%
    printf("\nCom 25%% de probabilidade de insercao:\n");
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(8,25);
        g2 = criaGrafo(8,25);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  50%
    printf("\nCom 50%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(8,50);
        g2 = criaGrafo(8,50);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }

    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  75%
    printf("\nCom 75%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(8,75);
        g2 = criaGrafo(8,75);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);   

    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);
    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt); 
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    printf("\n|||||||||||||||||||||||||||| 12 VÉRTICES |||||||||||||||||||||||||||");
    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"); 

    //  25%
    printf("\nCom 25%% de probabilidade de insercao:\n");
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(12,25);
        g2 = criaGrafo(12,25);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  50%
    printf("\nCom 50%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(12,50);
        g2 = criaGrafo(12,50);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }

    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  75%
    printf("\nCom 75%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(12,75);
        g2 = criaGrafo(12,75);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);   

    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);
    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt); 
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    printf("\n|||||||||||||||||||||||||||| 16 VÉRTICES |||||||||||||||||||||||||||");
    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
    //  25%
    printf("\nCom 25%% de probabilidade de insercao:\n");
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(16,25);
        g2 = criaGrafo(16,25);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  50%
    printf("\nCom 50%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(16,50);
        g2 = criaGrafo(16,50);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);
    }

    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);

    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt);
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");
    qt = 0;

    //  75%
    printf("\nCom 75%% de probabilidade de insercao:\n");    
    for(int i = 1; i <= 100; i++){
        t_ini = clock();
        g1 = criaGrafo(16,75);
        g2 = criaGrafo(16,75);
        qt += Verifica_isomorfismo(g1,g2);
        t_fim = clock();
        tempo += Exibe_tempo(t_ini,t_fim);   

    }
    tempo_medio = tempo / 100.0;
    printf("Tempo médio: %lf ms\n",tempo_medio);
    if(qt!=0) printf("\tHá possiveís %d grafos isomorfos\n",qt); 
    else printf("\tNenhum grafo isomorfo\n");

    printf("\n");



    
}