//
// Created by David Kravets
// Sparce Adjacency Matrix
// Creates a graph object that holds all non zero data from a graph.
// Stores data from large graphs in non-zero data arrays.
// Useful for large, sparce graphs with weighted edges.
// Contains iterators for easily pulling data from Graph objects.
//
#include "Graph.h"
#include <iostream>
#include <string>

Graph::Graph(int n){ //Creates graph object with N nodes
    if(n <1){
        throw out_of_range ("The number you entered is out of range");
    }
    else {
        m_cap = 0;
        m_numVert = n;
        m_re = new int[m_numVert + 1];
        m_ci = new int[m_cap];
        m_nz = new int[m_cap];

        for (int i = 0; i <= m_numVert; i++) {
            m_re[i] = 0;
        }
    }
}

// Graph copy constructor
Graph::Graph(const Graph& G){
    m_cap = G.m_cap;
    m_numVert = G.m_numVert;
    m_re = new int[m_numVert+1];
    m_ci = new int[m_cap];
    m_nz = new int[m_cap];

    for(int i=0;i<m_cap;i++){
        m_nz[i] = G.m_nz[i];
        m_ci[i] = G.m_ci[i];
    }
    for(int i=0;i<=m_numVert;i++){
        m_re[i] = G.m_re[i];
    }

}

// Graph destructor
Graph::~Graph(){
    delete[]m_re;
    delete[]m_ci;
    delete[]m_nz;
}

// Graph assignment operator
const Graph& Graph::operator= (const Graph& rhs){
    Graph *G = new Graph(rhs.m_numVert);

    G->m_cap = rhs.m_cap;
    G->m_numVert = rhs.m_numVert;
    G->m_re = new int[G->m_numVert+1];
    G->m_ci = new int[G->m_cap];
    G->m_nz = new int[G->m_cap];

    for(int i=0;i<m_cap;i++){
        G->m_nz[i] = rhs.m_nz[i];
        G->m_ci[i] = rhs.m_ci[i];
    }
    for(int i=0;i<=m_numVert;i++){
        G->m_re[i] = rhs.m_re[i];
    }

    return *G;
}

// return number of vertices
int Graph::numVert(){
    return m_numVert;
}

// return number of edges
int Graph::numEdge(){
    return m_cap/2;
}

// add edge between u and v with weight x
void Graph::addEdge(int u, int v, int x){
    if(u==v){m_cap++;}
    else {
        m_cap = m_cap+2;
    }
    int z = 0; // used for assignment loop
    int temp = m_re[u];
    for(int i = u+1; i<=m_numVert; i++) {
        m_re[i]++;
    }
    int temp2 = m_re[v];

    for(int i = v+1; i<=m_numVert; i++) {
        m_re[i]++;
    }
    int *tmpArrNz = new int[m_cap];
    int *tmpArrCi = new int[m_cap];

    for(int i=0;i<m_cap;i++){
        if(i==temp){
            tmpArrNz[i]=x;
            tmpArrCi[i]=v;
            z++;
        }
        else if(i==temp2){
            tmpArrNz[i]=x;
            tmpArrCi[i]=u;
            z++;
        }
        else {
            tmpArrNz[i] = m_nz[i - z];
            tmpArrCi[i] = m_ci[i - z];
        }
    }
    delete[]m_nz;
    delete[]m_ci;

    m_nz = tmpArrNz;
    m_ci = tmpArrCi;

}

// print out data structure
void Graph::dump(){
    cout << "Dump of graph (numVert = " << m_numVert << ", numEdge = " << m_numEdge << ")\n";
    cout << "m_nz: ";
    for(int i=0; i<m_cap; i++) {
       cout  << m_nz[i] << " ";
    }
    cout << "\n";
    cout << "m_ci: ";
    for(int i=0; i<m_cap; i++) {
        cout  << m_ci[i] << " ";
    }
    cout << "\n";
    cout << "m_re: ";
    for(int i=0; i<m_numVert+1; i++) {
        cout  << m_re[i] << " ";
    }

}
//----------------------------------------------------------------------
// Edge Iterator inner class

    // Edge Iterator; indx can be used to
    // set m_indx for begin and end iterators.
    Graph::EgIterator::EgIterator(Graph *Gptr, int indx){
        if(Gptr!=NULL) {
            Graph *tmp = new Graph(*Gptr);
            m_Gptr = tmp;
        }
        else{m_Gptr = NULL;}
        m_indx = indx;
}

    // Compare iterators;
    bool Graph::EgIterator::operator!= (const EgIterator& rhs){
        return m_indx != rhs.m_indx;
}

    // Move iterator to next printable edge
    void Graph::EgIterator::operator++(int dummy){
    m_indx++;
}

    // return edge at iterator location
    std::tuple<int,int,int> Graph::EgIterator::operator*(){
    int x=0;
    int y=0;
    int w=0;
    x = m_Gptr->m_ci[m_indx];
    while(m_indx >= m_Gptr->m_re[y+1]){
        y++;
    }
    while(y<x) {
        x=0;
        y=0;
        w=0;
        m_indx++;
        x = m_Gptr->m_ci[m_indx];
        while(m_indx >= m_Gptr->m_re[y+1]){
            y++;
        }
    }
    w = m_Gptr->m_nz[m_indx];
    return make_tuple(x, y, w);

}

    Graph::EgIterator Graph::egBegin(){
        return EgIterator(this, 0);
}

// Make an end iterator for edge iterator
    Graph::EgIterator Graph::egEnd(){
    return EgIterator(this, m_cap);

}
//----------------------------------------------------------------------

    // Iterator for vertices adjacent to vertex v;
    // indx can be used to set m_indx for begin and end iterators
    Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx){
    if(Gptr!=NULL) {
        Graph *tmp = new Graph(*Gptr);
        m_Gptr = tmp;
    }
    else{m_Gptr = NULL;}
    m_indx = indx;
    m_row = v;
}

    // Compare iterators; used to compare with end iterator
    bool Graph::NbIterator::operator!=(const NbIterator& rhs){
        return m_indx != rhs.m_indx;
}
    // Moves iterator to next neighbor
    void Graph::NbIterator::operator++(int dummy){
    m_indx++;
}

    // Returns neighbor at current iterator position
    int Graph::NbIterator::operator*(){
    return this->m_Gptr->m_ci[m_indx];
}



// Initial neighbor iterator
    Graph::NbIterator Graph::nbBegin(int v){
    return NbIterator(this,v,m_re[v]);

}

// End neighbor iterator
    Graph::NbIterator Graph::nbEnd(int v){
    return NbIterator(this,v,this->m_re[v+1]);
}
//----------------------------------------------------------------------

