#include "grafi.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 graph *nuovoGrafo(int numeroVertici)
{
     graph *G = ( graph *)malloc(sizeof(graph));

    if (G == NULL)
    {
        printf("\nErrore di allocazione\n");
    }
    else
    {
        G->adj = ( edge **)malloc(numeroVertici * sizeof( edge *));

        if (G->adj)
        {
            G->nv = numeroVertici;

            for (int i = 0; i < numeroVertici; i++)
                G->adj[i] = NULL;
        }
        else
        {
            printf("\nErrore di allocazione\n");
            free(G);
            G = NULL;
        }
    }

    return G;
}

void aggiungiArco( graph *G, int u, int v, int peso)
{
     edge *nnew;
     edge *e; //attraversa la lista

    nnew = ( edge *)malloc(sizeof( edge));

    if (nnew)
    {
        nnew->peso = peso;
        nnew->key = v;
        nnew->next = NULL; // all inizio il nuovo nodo � l'ultimo nella lista

        if (G->adj[u] == NULL) // verifica se la lista di adiacenza del vertice u � vuota
        {
            G->adj[u] = nnew;
        }
        else  // se la lista non � vuota la attraversa  fino all'ultimo nodo
        {
            e = G->adj[u];

            while (e->next != NULL)
            {
                e = e->next;
            }
            e->next = nnew;
        }
    }
    else
    {
        printf("\nErrore di allocazione");
    }
}

 graph *aggiungiNodo( graph *G)
{
     edge **e;

    if (G == NULL)
    {
        G = nuovoGrafo(1);
    }

    e = realloc(G->adj, (G->nv + 1) * sizeof( edge *));

    if (e)
    {
        G->adj = e;
        G->adj[G->nv] = NULL;  // imposta il puntatore associato al nuovo vertice su null (nessun arco inizialmente)
        G->nv++;
    }

    return G;
}

void stampa_grafo( graph *G)
{
    int numeroArchi = 0; // Inizializziamo a zero

    if (G == NULL)
    {
        printf("Il grafo � vuoto\n");
    }
    else
    {
        printf("Il grafo ha %d vertici\n", G->nv);

        for (int i = 0; i < G->nv; i++)
        {
            struct edge *e = G->adj[i];
            printf("Nodi adiacenti al nodo %d: ", i);

            while (e != NULL)
            {
                printf("%d [peso: %d] -> ", e->key, e->peso);
                numeroArchi++;
                e = e->next;
            }
            printf("\n");
        }
        printf("Il grafo ha %d archi\n", numeroArchi);
    }
}

void rimuoviArco( graph *G, int u, int v)
{
    if (G == NULL)
    {
        printf("\nErrore\n");
        return;
    }

    if (u < 0 || u >= G->nv || v < 0 || v >= G->nv)
    {
        printf("\nErrore\n");
        return;
    }

     edge *e = G->adj[u];
     edge *prev = NULL;

    while (e != NULL)
    {
        if (e->key == v)
        {
            if (prev == NULL)
            {
                // Se l'arco da rimuovere � il primo nella lista
                G->adj[u] = e->next;
            }
            else
            {
                prev->next = e->next;
            }
            free(e);
            return;
        }
        prev = e;
        e = e->next;
    }

    printf("\nArco non trovato\n");
}

void eliminaGrafo(graph* g) {

    if (g) {
        for (int i = 0; i < g->nv; i++) {
            edge* current = g->adj[i];
            while (current) {
                edge* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(g->adj);
        free(g);
        printf("Il grafo e' stato deallocato correttamente.\n");
    } else {
        printf("Attenzione: il grafo non � stato deallocato correttamente (puntatore nullo).\n");
    }
}


int gradoEntrante( graph *G, int nodo)
{
    if (G == NULL || nodo < 0 || nodo >= G->nv)
    {
        printf("Grafo non valido o nodo non esistente.\n");
        return -1;
    }

    int grado = 0;

    for (int i = 0; i < G->nv; i++)
    {
         edge *e = G->adj[i];
        while (e != NULL)
        {
            if (e->key == nodo)
                grado++;
            e = e->next;
        }
    }

    return grado;
}

int gradoUscente( graph *G, int nodo)
{
    if (G == NULL || nodo < 0 || nodo >= G->nv)
    {
        printf("Grafo non valido o nodo non esistente.\n");
        return -1;
    }

    int grado = 0;

     edge *e = G->adj[nodo];

    while (e != NULL)
    {
        grado++;
        e = e->next;
    }

    return grado;
}

void modifica_peso_arco( graph *g, int u, int v, int nuovo_peso)
{
     edge *tmp=g->adj[u];

    if(tmp==NULL)
    {
        return;
    }

    while(tmp)
    {
        if(tmp->key==v)
        {
            tmp->peso=nuovo_peso;
            break;
        }
        tmp=tmp->next;
    }
}

// Funzione per trovare l'arco con il peso maggiore
 edge *trovaArcoPesoMaggiore( graph *grafo)
{
    if (grafo == NULL || grafo->nv == 0)
    {

        return NULL;
    }

     edge *arcoMaggiore = NULL;
    int pesoMaggiore = 0;

    // Itera su tutti i vertici nel grafo
    for (int i = 0; i < grafo->nv; i++)
    {
         edge *verticeCorrente = grafo->adj[i];

        // Itera su tutti gli archi del vertice corrente
        while (verticeCorrente != NULL)
        {
            if (verticeCorrente->peso > pesoMaggiore)
            {
                // Se l'arco ha un peso maggiore, aggiorna l'arcoMaggiore e pesoMaggiore
                arcoMaggiore = verticeCorrente;
                pesoMaggiore = verticeCorrente->peso;
            }
            verticeCorrente = verticeCorrente->next;
        }
    }

    return arcoMaggiore;
}

edge *trovaArcoPesoMinore(graph *grafo)
{
    if (grafo == NULL || grafo->nv == 0)
    {

        return NULL;
    }

    edge *arcoMinore = NULL;
    int pesoMinore = INT_MAX;

    // Itera su tutti i vertici nel grafo
    for (int i = 0; i < grafo->nv; i++)
    {
        edge *verticeCorrente = grafo->adj[i];

        // Itera su tutti gli archi del vertice corrente
        while (verticeCorrente != NULL)
        {
            if (verticeCorrente->peso < pesoMinore)
            {
                // Se l'arco ha un peso minore, aggiorna l'arcoMinore e pesoMinore
                arcoMinore = verticeCorrente;
                pesoMinore = verticeCorrente->peso;
            }
            verticeCorrente = verticeCorrente->next;
        }
    }

    return arcoMinore;
}


void dijkstra( graph *g, int sorgente, int *distanze, int *prev)
{
    int visitati[g->nv]; // Array per tenere traccia dei nodi visitati

    for(int i=0; i<g->nv; i++)
    {
        distanze[i]=INT_MAX;
        prev[i]=-1;   //nessun predecessore
        visitati[i]=0;  // Inizializza tutti i nodi come non visitati
    }

    distanze[sorgente]=0;

    for(int i=0; i<g->nv; i++)
    {
        int minima_distanza=INT_MAX;
        int u=-1;

        for(int j=0; j<g->nv; j++)
        {
            if(!visitati[j] && distanze[j]<minima_distanza)
            {
                minima_distanza=distanze[j];
                u=j; // u diventa il nodo con la minima distanza non visitato
            }
        }

        visitati[u]=1; // Segna il nodo u come visitato

        struct edge *e=g->adj[u]; // Itera attraverso gli archi uscenti dal nodo u

        while(e!=NULL)
        {
            int v=e->key;
            int peso=e->peso;
            int alt=distanze[u]+peso;

            if(alt<distanze[v]) // Se la distanza alternativa � pi� breve della distanza registrata:
            {
                distanze[v]=alt;
                prev[v]=u;
            }

            e=e->next;
        }
    }
}


void dfs1(graph *g, int i, int *aux)
{
    edge *e;
    aux[i]=1; //aux � un array di flag che tiene traccia dei nodi visitati

    for(e=g->adj[i]; e; e=e->next)
    {
        if(!aux[e->key]) // Controlla se il nodo adiacente e->key non � stato visitato
        {
            printf("%d ",e->key); // Stampa il nodo adiacente che sta per essere visitato
            dfs1(g,e->key,aux);
        }
    }
}

void dfs(graph *g) //idea: inizia da un nodo e segue il percorso finch� pu� e poi torna indietro per vedere quelli nn esplorati
{
    int i;
    int *aux=calloc(g->nv,sizeof(int));

    if(aux)
    {
        for(i=0;i<g->nv;i++)
        {
            if(!aux[i]) // Controlla se il nodo i non � stato visitato
            {
                printf("\n%d, ",i); // Stampa il nodo iniziale che sta per essere visitato
                dfs1(g,i,aux); // Chiama dfs1 per esplorare il grafo in profondit� a partire da i
            }
        }
        free(aux);
    }
    else
    {
        printf("Errore di allocazione");
    }
}

// La funzione bfs1 visita i nodi raggiungibili da un nodo di partenza
void bfs1(graph* g, int start, int* aux) {

    int coda_visitati[MAX + 2]; // Aggiungiamo 2 per l'indice di inizio e l'indice di fine
    inizializza_queue(coda_visitati);
    enqueue(coda_visitati, start); //mette in coda il nodo di partenza

    while (!empty_queue(coda_visitati)) {
        start = dequeue(coda_visitati);
        aux[start] = 1; //imposta il flag del nodo start a 1 per indicare che � stato visitato

        printf("%d ", start);

        for (edge* e = g->adj[start]; e; e = e->next) { //itera attraverso i nodi adiacenti a start
            if (!aux[e->key]) { //se il nodo adiacente non � stato visitato
                enqueue(coda_visitati, e->key); // accoda il nodo adiacente
                aux[e->key] = 1;
            }
        }
    }
}


void bfs(graph* g) {
    int* aux = calloc(g->nv, sizeof(int));  //aux � un array di flag che tiene traccia dei nodi visitati

    if (aux) {
        for (int i = 0; i < g->nv; i++) {
            if (!aux[i]) { // controlla se il nodo i non � stato visitato
                printf("\nIniziando dal nodo %d: ", i);
                bfs1(g, i, aux);
            }
        }
        free(aux);
    } else {
        printf("Errore di allocazione di memoria.\n");
    }
}

 graph *creaTrasposto( graph *G)
{
     graph *G2 = NULL;
    if(G == NULL)
        printf("\nErrore");
    else
    {
        edge *e;
        G2 = ( graph *)malloc(sizeof( graph));
        if(G2 == NULL)
            printf("\nErrore allocazione\n");
        else
        {
            G2->adj = (edge **)malloc(G->nv * sizeof(edge *));
            if(G2->adj)
            {
                G2->nv = G->nv;
                for(int i = 0; i < G2->nv; i++)
                    G2->adj[i] = NULL;

                for(int i = 0; i < G2->nv; i++)
                {
                    e = G->adj[i];
                    while(e != NULL)
                    {
                        aggiungiArco(G2, e->key, i, e->peso);
                        e = e->next;
                    }
                }
            }
            else
            {
                printf("\nErrore allocazione\n");
                free(G2);
                G2->adj = NULL;
            }

        }

    }
    return G2;
}

int **graphToAdjMatrix(graph *g)
{
    //allocazione e inizializzazione a 0
    int **adjMatrix = (int **)malloc(g->nv * sizeof(int *));
    for (int i = 0; i < g->nv; i++)
    {
        adjMatrix[i] = (int *)malloc(g->nv * sizeof(int));
        for (int j = 0; j < g->nv; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < g->nv; i++)
    {
        edge *currentEdge = g->adj[i];
        while (currentEdge != NULL)
        {
            // la colonna nella matrice � data dalla chiave dell'arco
            int j = currentEdge->key;
            adjMatrix[i][j] = currentEdge->peso; // il valore nella matrice sarebbe il peso dell'arco
            currentEdge = currentEdge->next;
        }
    }

    return adjMatrix;
}

graph *adjMatrixToGraph(int **adjMatrix, int nv)
{
    //allocazione grafo
    graph *g = (graph *)malloc(sizeof(graph));
    g->nv = nv;
    g->adj = (edge **)malloc(nv * sizeof(edge *));

    for (int i = 0; i < nv; i++)
    {
        g->adj[i] = NULL;
        for (int j = 0; j < nv; j++)
        {
            if (adjMatrix[i][j] != 0)   // Se il peso dell'arco � diverso da zero, crea un nuovo arco
            {
                edge *newEdge = (edge *)malloc(sizeof(edge));
                newEdge->peso = adjMatrix[i][j];
                newEdge->key = j;
                newEdge->next = g->adj[i];
                g->adj[i] = newEdge;
            }
        }
    }

    return g;
}

graph* sommaGrafi(graph* g1, graph* g2) {

    if (g1->nv != g2->nv) {
        printf("Errore: i due grafi devono avere lo stesso numero di vertici");
        return NULL;
    }

    for (int i = 0; i < g1->nv; i++) {
        edge* edge1 = g1->adj[i];
        edge* edge2 = g2->adj[i];

        while (edge1 != NULL && edge2 != NULL) {
            edge1 = edge1->next;
            edge2 = edge2->next;
        }

        if (edge1 != NULL || edge2 != NULL) {
            printf("Errore: i due grafi devono avere lo stesso numero di archi");
            return NULL;
        }
    }

    graph* G = nuovoGrafo(g1->nv);

    for (int i = 0; i < g1->nv; i++) {
        edge* edge1 = g1->adj[i];
        edge* edge2 = g2->adj[i];

        while (edge1 != NULL && edge2 != NULL) {
            int pesoSomma = edge1->peso + edge2->peso;
            aggiungiArco(G, i, edge1->key, pesoSomma);
            edge1 = edge1->next;
            edge2 = edge2->next;
        }
    }

    return G;
}



