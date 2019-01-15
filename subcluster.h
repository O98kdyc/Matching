#ifndef SUBCLUSTER_H_INCLUDED
#define SUBCLUSTER_H_INCLUDED
#include <fstream>
#include "seqList.h"
//此处仅仅考虑4谓词情形,分类谓词选定数量为2

class subcluster
{
private:
    struct clusterNode
    {
       seqList<int> id;
       seqList<int> v1;
       seqList<int> v2;
       seqList<int> v3;

       clusterNode *next;
       int req;  //反映谓词个数

       clusterNode(int e,clusterNode *n=NULL) {next=n;req=e;seqList<int> id;}
    };


    struct clu
    {
        clusterNode *head;
        int r;   //分类依据要求

        clu(clusterNode *h=NULL) {head=h;}
    };

    clu *cluList;
    void advocate(clusterNode *p,int i,int x[]);
    //int num;
public:
    subcluster();
    void insert(int x,int r1,int r2,int r3,int r4);
    void remove(int x);
    void advocate(int a0,int a1,int a2,int a3);
    ~subcluster();

    int n=0;
};

subcluster::subcluster()
{
   cluList=new clu[2];
   for(int i=0;i<2;i++)
   {
     cluList[i].r=i;
     for(int j=3;j>=i;j--)
         cluList[i].head=new clusterNode(j,cluList[i].head);
   }
}

subcluster::~subcluster()
{
   clusterNode *p;
   for(int i=0;i<2;i++)
      while((p=cluList[i].head)!=NULL)
      {
        cluList[i].head=p->next;
        delete p;
      }
    delete []cluList;
}

void subcluster::insert(int x,int r0,int r1,int r2,int r3)
{
   int count=0;//订阅所要求的谓词数目
   clusterNode *p;
   if(r1==1) count++;if(r2==1) count++;if(r3==1) count++;if(r0==1) count++;
   if(count==0) return;
   if(r0==1)
   {
      p=cluList[0].head;
      for(int i=0;i<count-1;i++) p=p->next;
      p->id.insert(p->id.length(),x);
      int l=1;
      switch (count)
      {
        case 1:break;
        case 2:if(r1==1) p->v1.insert(p->v1.length(),1);
               if(r2==1) p->v1.insert(p->v1.length(),2);
               if(r3==1) p->v1.insert(p->v1.length(),3);
               break;
        case 3:if(r1==1&&r2==1) p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),2);
               if(r1==1&&r3==1) p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),3);
               if(r2==1&&r3==1) p->v1.insert(p->v1.length(),2);p->v2.insert(p->v2.length(),3);
               break;
        case 4:p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),2);p->v3.insert(p->v3.length(),3);
               break;
      }
   }
   else
   {
     p=cluList[1].head;
     for(int i=0;i<count-1;i++) p=p->next;
     p->id.insert(p->id.length(),x);
     switch (count)
     {
       case 1: if(r1==1) p->v1.insert(p->v1.length(),1);
               if(r2==1) p->v1.insert(p->v1.length(),2);
               if(r3==1) p->v1.insert(p->v1.length(),3);
               break;
       case 2: if(r1==1&&r2==1) p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),2);
               if(r1==1&&r3==1) p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),3);
               if(r2==1&&r3==1) p->v1.insert(p->v1.length(),2);p->v2.insert(p->v2.length(),3);
               break;
       case 3: p->v1.insert(p->v1.length(),1);p->v2.insert(p->v2.length(),2);p->v3.insert(p->v3.length(),3);
               break;
     }
   }
}

void subcluster::advocate(int a0,int a1,int a2,int a3)
{
   //ofstream fout("advocate.txt");
   //if(!fout) {cout<<"cannot create"<<endl;return;}
   int a[4]={a0,a1,a2,a3};
   int num=0;//统计事件的谓词个数
   if(a0==1) num++;if(a1==1) num++;if(a2==1) num++;if(a3==1) num++;
   clusterNode *p;
   if(a0==1)
   {
   p=cluList[0].head;
   for(int i=0;i<num;i++)
   {
     advocate(p,i,a);
     p=p->next;
   }
   p=cluList[1].head;
     for(int i=1;i<num;i++)
     {
       advocate(p,i,a);
       p=p->next;
     }
   }
   else
   {
     p=cluList[1].head;
     for(int i=1;i<num+1;i++)
     {
       advocate(p,i,a);
       p=p->next;
     }
   }
}

void subcluster::advocate(clusterNode *p,int i,int x[])
{
   //ofstream fout("advocate.txt");
   //if(!fout) {cout<<"cannot create"<<endl;return;}
   int a[4];
   for(int i=0;i<4;i++) {a[i]=x[i];}
   switch (i){
   case 0://p->id.traverse();
           for(int i=0;i<p->id.length();i++)
           {
           //fout<<p->id.visit(i);
           cout<<p->id.visit(i)<<" ";

           n+=1;
           }
           break;
   case 1:for(int i=0;i<p->id.length();i++)
           {
             if(a[p->v1.visit(i)]==1)
            {
             //fout<<p->id.visit(i)<<" ";
             cout<<p->id.visit(i)<<" ";

             n+=1;
             }
           }
           break;
   case 2:for(int i=0;i<p->id.length();i++)
           {
             if(a[p->v1.visit(i)]==1&&a[p->v2.visit(i)]==1)
             {
             //fout<<p->id.visit(i)<<" ";
             cout<<p->id.visit(i)<<" ";

             n+=1;
             }
           }
           break;
   case 3:for(int i=0;i<p->id.length();i++)
           {
             if(a[p->v1.visit(i)]==1&&a[p->v2.visit(i)]==1&&a[p->v3.visit(i)]==1)
             {
             //fout<<p->id.visit(i)<<" ";
             cout<<p->id.visit(i)<<" ";

             n+=1;
             }
           }
           break;
   }
}

#endif // SUBCLUSTER_H_INCLUDED
