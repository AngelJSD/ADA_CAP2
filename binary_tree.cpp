#include<iostream>
#include<deque>
#include<stack>

template<class T>

struct c_Node{

    T m_data;
    c_Node<T>* m_child[2];

    c_Node(T dato){

        m_data=dato;
        m_child[0]=0;
        m_child[1]=0;
    }
};

template <class T>
class c_BT_Iterator{

public:
    pair<c_Node<T>*,int> m_pair;
    int m_id;

    deque<pair<c_Node<T>*,int> > m_i;

    c_BT_Iterator<T> operator=(c_BT_Iterator<T> x){

        m_i=x.m_i;
        return *this;
    }

    bool operator!=(c_BT_Iterator<T> x){

        return m_i!=x.m_i;
    }

    c_BT_Iterator<T> operator++(int){

        //Obtengo el tope de mi pila y lo pongo en m_pair IMPORTANTE: inorder y postorder neciesitan una pila
        //lena con el hijo mas izquierdo como tope
        m_pair=m_i.front();

        do{
            m_i.pop_front();
            
            /** *********************************************************************************************
             *                  SECCION QUE VA SIEMPRE A LA IZQUIERDA                                       *
             * **********************************************************************************************/
            ///Solo ingresa si el estado del tope de la pila es igual al ID que manejo
            if(m_pair.second==m_id){

                /// Actualizo el estado del tope de mi pila
                m_i.push_front(make_pair(m_pair.first,(m_id+1)%3));
                
                /// Empilo el de mi izquierda
                if(m_pair.first->m_child[0]) m_i.push_front(make_pair(m_pair.first->m_child[0],m_id));
            }
            /** *********************************************************************************************/
            
            /************************************************************************************************
             *                  SECCION QUE VA SIEMPRE A LA DERECHA                                         *
             * **********************************************************************************************/            
            /* Solo ingresa si el estado del tope de la pila es igual al ID que manejo +1 (como solo tengo 
             * ID:0,1,2 hago %3 para que siempre este en ese rango**/
            
            else if(m_pair.second==(m_id+1)%3){

                // Actualizo el estado del tope de mi pila
                m_i.push_front(make_pair(m_pair.first,(m_id+2)%3));

                // Empilo el de mi izquierda
                if(m_pair.first->m_child[1]) m_i.push_front(make_pair(m_pair.first->m_child[1],m_id));
            }
            /************************************************************************************************/
           m_pair=m_i.front();

        }
        while(m_pair.second!=1 and !m_i.empty());
        return *this;
    }

    T operator*(){

        m_pair=m_i.front();
        return m_pair.first->m_data;
    }

};
template <class T>
class c_BT_Inorder_Iterator : public c_BT_Iterator<T>{

public:
    c_BT_Inorder_Iterator(){

        this->m_id=0;
    }

};

template <class T>
class c_BT_Preorder_Iterator : public c_BT_Iterator<T>{

public:
    c_BT_Preorder_Iterator(){

        this->m_id=1;
    }

};

template <class T>
class c_BT_Postorder_Iterator : public c_BT_Iterator<T>{

public:
    c_BT_Postorder_Iterator(){

        this->m_id=2;
    }

};

template <class T>
class c_BT_BFS_Iterator : public c_BT_Iterator<T>{

public:

    c_BT_BFS_Iterator(){}


    c_BT_Iterator<T> operator++(int){

        this->m_pair=this->m_i.front();
        this->m_i.pop_front();
        if(this->m_pair.first->m_child[0]) this->m_i.push_back(make_pair(this->m_pair.first->m_child[0],0));
        if(this->m_pair.first->m_child[1]) this->m_i.push_back(make_pair(this->m_pair.first->m_child[1],0));

        return *this;

    }

};


template<class Tr>

class c_BinTRee
{
    public:

        c_BinTRee();
        typedef typename Tr::T T;
        typedef typename Tr::C C;

        typedef c_BT_Inorder_Iterator<T> inorder_iterator;
        typedef c_BT_Postorder_Iterator<T> postorder_iterator;
        typedef c_BT_Preorder_Iterator<T> preorder_iterator;
        typedef c_BT_BFS_Iterator<T> bfs_iterator;

        bool find(T , c_Node<T>**&);
        bool insert(T);
        bool remove(T);
        void inorden(c_Node<T>*);

        inorder_iterator inbegin();
        inorder_iterator inend();
        postorder_iterator postbegin();
        postorder_iterator postend();
        preorder_iterator prebegin();
        preorder_iterator preend();
        bfs_iterator bfsbegin();
        bfs_iterator bfsend();

        C m_cmp;
        c_Node<T>*m_root;
};

template<class Tr>

c_BinTRee<Tr>::c_BinTRee()
{
    m_root=nullptr;
}

template<class Tr>

bool c_BinTRee<Tr>::find(T x, c_Node<T>**&p)
{
    for(p=&m_root; (*p) && (*p)->m_data!=x; p=&(*p)->m_child[ m_cmp((*p)->m_data,x)]);
    return (*p);
}

template<class Tr>

bool c_BinTRee<Tr>::insert(T x)
{
    c_Node<T>**p;

    if(find(x,p)) return 0;

    *p=new c_Node<T>(x);

    return 1;
}

template<class Tr>

bool c_BinTRee<Tr>::remove(T x)
{
    c_Node<T>** p;
    c_Node<T>* temp;

    if(!find(x,p)) return 0;
    temp=(*p);
    if((*p)->m_child[0] && (*p)->m_child[1]){

        for(p=&((*p)->m_child[0]); (*p)->m_child[1]; p=&((*p)->m_child[1]));
        swap((*p)->m_data,temp->m_data);
    }
    temp=(*p);
    (*p)=(*p)->m_child[!!(*p)->m_child[1]];
    return 1;
}

template<class Tr>

void c_BinTRee<Tr>::inorden(c_Node<T>*p){

    if(p){
        inorden(p->m_child[0]);
        inorden(p->m_child[1]);
        cout<<p->m_data<<endl;
    }
}

template<class Tr>

typename c_BinTRee<Tr>::inorder_iterator c_BinTRee<Tr>::inbegin()
{
    c_Node<T>* p=m_root;
    inorder_iterator it;

    it.m_i.push_front(make_pair(p,0));
    //IMPORTANTE!
    it++;

    return it;
}

template<class Tr>

typename c_BinTRee<Tr>::inorder_iterator c_BinTRee<Tr>::inend()
{
    return inorder_iterator();
}

template<class Tr>

typename c_BinTRee<Tr>::preorder_iterator c_BinTRee<Tr>::prebegin()
{
    c_Node<T>* p=m_root;
    preorder_iterator it;

    it.m_i.push_front(make_pair(p,1));

    return it;
}

template<class Tr>

typename c_BinTRee<Tr>::preorder_iterator c_BinTRee<Tr>::preend()
{
    return preorder_iterator();
}

template<class Tr>

typename c_BinTRee<Tr>::postorder_iterator c_BinTRee<Tr>::postbegin()
{
    c_Node<T>* p=m_root;
    postorder_iterator it;

    it.m_i.push_front(make_pair(p,2));
    //IMPORTANTE!
    it++;

    return it;
}

template<class Tr>

typename c_BinTRee<Tr>::postorder_iterator c_BinTRee<Tr>::postend()
{
    return postorder_iterator();
}

template<class Tr>

typename c_BinTRee<Tr>::bfs_iterator c_BinTRee<Tr>::bfsbegin()
{
    c_Node<T>* p=m_root;
    bfs_iterator it;

    it.m_i.push_front(make_pair(p,0));

    return it;
}

template<class Tr>

typename c_BinTRee<Tr>::bfs_iterator c_BinTRee<Tr>::bfsend()
{
    return bfs_iterator();
}


struct c_less
{
    inline bool operator() (T a,T b)
    {return a<b;}
};

template <class T>

struct c_greater
{
    inline bool operator() (T a,T b)
    {return a>b;}
};

struct traits{

    typedef int T;
    typedef c_less<T> C;
};

int main()
{

    c_BinTRee<traits> arbol;
    c_BinTRee<traits>::inorder_iterator it;
    c_BinTRee<traits>::postorder_iterator post_it;
    c_BinTRee<traits>::preorder_iterator pre_it;
    c_BinTRee<traits>::bfs_iterator bfs_it;

    int a,b,c,d,e,f,g;

    a=50;
    b=60;
    c=40;
    d=45;
    e=46;
    f=55;
    g=56;

    arbol.insert(a);
    arbol.insert(b);
    arbol.insert(c);
    arbol.insert(d);
    arbol.insert(e);
    arbol.insert(f);
    arbol.insert(g);

    arbol.inorden(arbol.m_root);

    /*for(it=arbol.inbegin();it!=arbol.inend(); it++){

        cout<<"h"<<endl;
        cout<<*it;
    }*/

    /*for(post_it=arbol.postbegin();post_it!=arbol.postend(); post_it++){

        cout<<"h"<<endl;
        cout<<*post_it;
    }*/

    /*for(pre_it=arbol.prebegin();pre_it!=arbol.preend(); pre_it++){

        cout<<"h"<<endl;
        cout<<*pre_it;
    }*/

    for(bfs_it=arbol.bfsbegin();bfs_it!=arbol.bfsend(); bfs_it++){

        cout<<"h"<<endl;
        cout<<*bfs_it;
    }


    return 0;
}
