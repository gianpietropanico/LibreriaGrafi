   #define MAX 100
    typedef struct edge
    {
        int peso;
        int key;
        struct edge *next;
    }edge;

    typedef struct graph
    {
        int nv;
        struct edge **adj;
    }graph;


    graph *nuovoGrafo(int numeroVertici);

    void aggiungiArco( graph *G, int u, int v, int peso);

    graph *aggiungiNodo( graph *G);

    void stampa_grafo( graph *G);

    void rimuoviArco( graph *G, int u, int v);

    void deleteGraph(graph* g);

    int gradoEntrante( graph *G, int nodo);

    int gradoUscente( graph *G, int nodo);

    void modifica_peso_arco( graph *g, int u, int v, int nuovo_peso);

    edge *trovaArcoPesoMaggiore( graph *grafo);

    edge *trovaArcoPesoMinore(graph *grafo);

    void dijkstra( graph *g, int sorgente, int *distanze, int *prev);

    void dfs1(graph *g, int i, int *aux);

    void dfs(graph *g);

    void bfs1(graph* g, int start, int* aux);

    void bfs(graph* g);

    graph *creaTrasposto (graph *G);

    int **graphToAdjMatrix(graph *g);

    graph *adjMatrixToGraph(int **adjMatrix, int nv);

    graph* sommaGrafi(graph* g1, graph* g2);
