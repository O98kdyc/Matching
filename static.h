#ifndef STATIC_H_INCLUDED
#define STATIC_H_INCLUDED
#include "seqList.h"
using  std::ostream;
using  std::istream;

int exp2(int x)
{
    int y=1;
    for(int i=0;i<x;i++) y*=2;
    return y;
}

int exp10(int x)
{
    int y=1;
    for(int i=0;i<x;i++) y*=10;
    return y;
}


class s
{
    friend ostream &operator<<(ostream &os,const s &obj);
public:
    int id;
    int a[10];
};

ostream& operator<<(ostream &os,const s& obj)
{
    os<<obj.id;
    return os;
}

class Node
{
public:
    seqList<s> *elem;
    Node *next;
    Node(int length,Node *n=NULL);
    ~Node() {delete [] elem;}
    void insert(int pos,s s);
    void traverse(int pos);
};

Node::Node(int length,Node *n)
{
    elem=new seqList<s>[length];
    next=n;
}

void Node::insert(int pos,s s)
{
    elem[pos].insert(elem[pos].length(),s);
}

void Node::traverse(int pos)
{
    elem[pos].traverse();
}

class HashNode
{
private:
    int n=2; //每个Node里包括seqList的个数为10^n
    Node *head=NULL;
    void match(int *a,bool visited[]);
    void lmatch(int *a,bool visited[],Node *p);
public:
    HashNode();
    ~HashNode();
    void insert(int *a,int size,int id);
    void match(s event);
};

HashNode::HashNode()

{
    for(int i=0;i<32;i++) head=new Node(exp10(n),head);
}

HashNode::~HashNode()
{
    Node *p;
    while((p=head)!=NULL)
    {
        p=head;
        head=p->next;
        delete p;
    }
}

void HashNode::insert(int *a,int size,int id)
{
    Node *p=head;
    int b[5];
    for(int i=0;i<5;i++)
    {
        if(a[i]==0) b[i]=0;
        else b[i]=1;
    }
    int x=b[0]*16+b[1]*8+b[2]*4+b[3]*2+b[4];
    for(;x>0;x--) p=p->next;
    //int pos=a[5]*10000+a[6]*1000+a[7]*100+a[8]*10+a[9];

    int pos=a[5];
    for(int i=1;i<n;i++) pos=10*pos+a[i+5];

    s s;
    s.id=id;
    for(int i=0;i<10;i++) s.a[i]=a[i];
    p->insert(pos,s);
}

void HashNode::match(s event)
{
    bool *visited=new bool[32];
    for(int i=0;i<32;i++) visited[i]=false;
    int b[10];
    for(int i=0;i<10;i++) b[i]=event.a[i];
    match(b,visited);
}

void HashNode::match(int *a,bool visited[])
{
    int b[5];
    for(int i=0;i<5;i++)
    {
        if(a[i]==0) b[i]=0;
        else b[i]=1;
    }
    int x=b[0]*16+b[1]*8+b[2]*4+b[3]*2+b[4];

    if(visited[x]) return;
    else
    {
        Node *p=head;
        for(int i=0;i<x;i++) p=p->next;

        bool *lvisited=new bool[exp2(n)];
        for(int i=0;i<exp2(n);i++) lvisited[i]=false;

        lmatch(a,lvisited,p);

    }
    visited[x]=true;
    for(int i=0;i<5;i++)
    {
        if(a[i]>0)
        {
            int tmp=a[i];
            a[i]=0;
            match(a,visited);
            a[i]=tmp;
        }
    }
}

void HashNode::lmatch(int *a,bool visited[],Node *p)
{
    //int pos=a[5]*10000+a[6]*1000+a[7]*100+a[8]*10+a[9];
    int pos=a[5];
    for(int i=1;i<n;i++) pos=10*pos+a[i+5];

    int b[5]={0};
    for(int i=0;i<n;i++)
    {
        if(a[i+5]==0) b[i]=0;
        else b[i]=1;
    }
    int t=b[0];
    for(int i=1;i<n;i++) t=2*t+b[i];
    //int t=b[0]*16+b[1]*8+b[2]*4+b[3]*2+b[4];
    //cout<<t<<" "<<visited[t]<<"   ";
    if(visited[t]==true) return;
    else
        for(int i=0;i<p->elem[pos].length();i++)
        {
            bool flag=true;

            for(int k=0;k<5;k++)
            {int t=p->elem[pos].visit(i).a[k];
             if(t!=0&&t!=a[k]) flag=false;}
            for(int m=5+n;m<10;m++)
            {int t=p->elem[pos].visit(i).a[m];
             if(t!=0&&t!=a[m]) flag=false;}

            if(flag) //cout<<p->elem[pos].visit(i).id<<"   ";
                p->elem[pos].visit(i).id;
        }
    visited[t]=true;

        for(int i=5;i<5+n;i++)
        {
            if(a[i]>0)
            {
                int tmp=a[i];
                a[i]=0;
                lmatch(a,visited,p);
                a[i]=tmp;
            }
        }
}

#endif // STATIC_H_INCLUDED
