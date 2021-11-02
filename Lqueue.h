// David Kravets
// A templated LL queue that functions similarly to a vector but uses linked lists
// created for a project requiring Linked lists that can be resorted and modified easily
//

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {  //Node class for storing nodes of data (usually objects)
public:
    Node( const T& data ); //Overloaded constructor
    T& GetData(); //Getter
    void SetData( const T& data ); //Setter
    Node<T>* GetNext(); //Getter
    void SetNext( Node<T>* next ); //Setter
private:
    T m_data; //Data stored in node
    Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
    m_data = data;
    m_next = NULL;
}

template <class T>
T& Node<T>::GetData() {
    return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
    m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
    return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
    m_next = next;
}

template <class T>
class Lqueue {
public:
    //Lqueue() (Linked List Queue) - Default Constructor
    Lqueue();
    //~Lqueue() - Destructor
   ~Lqueue();
    //Lqueue (Copy Constructor)
    Lqueue(const Lqueue&);
    //operator= (Overloaded Assignment Operator)
    Lqueue<T>& operator = (Lqueue&);
    void Push(const T&);   //  Adds a new node to the end of the lqueue.
    T Pop();     // Removes first node in the lqueue, returns data from first node.
    void Display();     // Displays the data in each node of lqueue
    T Front();    // Returns whatever data is in front
    bool IsEmpty();   //Returns if queue is empty
    int GetSize();    //Returns m_size
    void Swap(int);   //Swaps the nodes at the index with the node prior to it.
    void Clear();   //Removes all nodes in a lqueue
    void RemoveInsertEnd(int); // Moves a node from somewhere to the end of the lqueue
    // Returns an ostream with the data from each node on different line
    template <class U>
    friend ostream& operator<<(ostream& output, const Lqueue<U>&);
    T& operator[] (int x);  //Overloaded [] operator to pull data from Lqueue
private:
    Node <T> *m_head; //Node pointer head
    Node <T> *m_tail; //Node pointer tail
    int m_size; //Number of nodes in queue
};

//*********************************************************************

template <class T>
Lqueue<T>::Lqueue(){
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
}

template <class T>
Lqueue<T>::~Lqueue(){
    Node<T> *temp = m_head;
    Node<T> *deleteNode;

    while(temp->GetNext()!=NULL){
        deleteNode = temp;
        temp = temp->GetNext();
        delete deleteNode;
    }

}

template <class T>
Lqueue<T>::Lqueue(const Lqueue& queue){
    m_size = queue.m_size;
    m_head = queue.m_head;
    m_tail = queue.m_tail;
}

template <class T>
Lqueue<T>& Lqueue<T>::operator = (Lqueue& queue){
    Lqueue<T> *que = new Lqueue<T>(queue);
    return *que;
}

template <class T>
void Lqueue<T>::Push(const T& data){
    Node<T> *temp = new Node<T>(data);
    Node<T> *curr;
    m_size++;
    //temp->SetData(data);
    if(m_head == NULL){
        m_head = temp;
        m_head->SetNext(m_tail);
    }
    else{
        curr = m_head;
        while(curr->GetNext() != NULL){
            curr = curr->GetNext();
        }
        curr->SetNext(temp);
        temp->SetNext(m_tail);
    }

}

template <class T>
T Lqueue<T>::Pop(){
    Node<T> *ptr = m_head->GetNext();
    delete m_head;
    m_head = ptr;
    m_size--;
}

template <class T>
void Lqueue<T>::Display(){
    int i = 0; //counts how many nodes are printed
    if(m_head == NULL){
        cout << "empty" << endl;
    }else {
        Node<T> *temp = m_head;
        while(temp != NULL){
            cout << temp->GetData();
            i++;
            temp = temp->GetNext();
            cout << "\n";
        }
    }
}

template <class T>
T Lqueue<T>::Front(){
    return m_head->GetData();
}

template <class T>
bool Lqueue<T>::IsEmpty(){
    if (m_head == NULL){return true;}
    else{return false;}
}

template <class T>
int Lqueue<T>::GetSize(){
    Node<T> *temp = m_head;
    int i=0;
    while(temp != NULL){
        temp = temp->GetNext();
        i++;
    }
    return i;

}

template <class T>
void Lqueue<T>::Swap(int ind){
/*
    Node<T> *temp = m_head;
    Node<T> *temp2;
    Node<T> *temp3;
    for(int i=0; i<=ind-2; i++){
        temp = temp->GetNext();
    }
    temp2 = temp->GetNext();
    temp3 = temp->GetNext()->GetNext();
    temp->SetNext(temp3);
    temp2->SetNext(temp3->GetNext());
    temp3->SetNext(temp2);
*/

    if(ind>0 && ind <= GetSize()) {
        int index = ind-1;
        Node<T> *temp = m_head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->GetNext();
        }
        Node<T> data1(m_head->GetData());
        Node<T> data2(m_head->GetData());
        data1.SetData(temp->GetData());
        data2.SetData(temp->GetNext()->GetData());
        temp->SetData(data2.GetData());
        temp->GetNext()->SetData(data1.GetData());
    }

}

template <class T>
void Lqueue<T>::Clear(){
    Node<T> *temp = m_head;
    Node<T> *deleteNode;

    while(temp->GetNext()!=NULL){
        deleteNode = temp;
        temp = temp->GetNext();
        delete deleteNode;
    }
}

template <class T>
void Lqueue<T>::RemoveInsertEnd(int index){
    if(index>=0 && index <= GetSize()) {
        Node<T> *temp = m_head;
        for (int i = 0; i < index; i++) {
            temp = temp->GetNext();
        }
        Node<T> *temp2 = temp;
        while(temp->GetNext() != NULL){
            temp = temp->GetNext();
            Swap(index+1);
            index++;
        }
        temp->SetNext(temp2);
        temp2->SetNext(m_tail);
    }
}

template <class U>
ostream& operator<<(ostream& output, const Lqueue<U>& queue){
    for(int i=0; i<queue.m_size; i++) {
        output << queue[i] << endl;
    }
    return output;
}

template <class T>
T& Lqueue<T>::operator[] (int x){
    Node<T> *temp = m_head;
    if(x>=0 && x <= GetSize()) {
        for (int i = 0; i < x; i++) {
            temp = temp->GetNext();
        }
    }
    return temp->GetData();
}//Overloaded [] operator to pull data from Lqueue




