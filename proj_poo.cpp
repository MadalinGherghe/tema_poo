#include<iostream>
#include<fstream>
using namespace std;
ifstream f("citire.in");
class Graf;
class Lista;
 class Nod {
    int info;
    Nod *next;
public:
    Nod();
    Nod(int info,Nod* next=0);
    int getInfo();
    Nod* getNext();
    friend class Lista;
    friend class Graf;
  };

Nod::Nod(){
 next=0;
}

Nod::Nod(int info, Nod* next){
 this->info=info;
 this->next=next;
}

int Nod::getInfo(){
     return info;
}

 Nod* Nod::getNext(){
     return next;
}

class Lista {

    Nod *prim;
    Nod *ultim;
      public:
          int nd;         //nodul
          int nr;           //nr de vecini
    Lista();
    ~Lista();
    Lista(const Lista &);
    int isEmpty();                // testeaza daca lista e vida
    void addElement(Nod n);          //adauga un element la sfarsitul listei
    Nod* getFirst();              //intoarce primul elemnt din lista
    Nod* getLast();               //intoarce ultimul element din lista
    friend ostream& operator<<(ostream& out, Lista&);

    Lista &operator =(const Lista& d)
    {
        nd=d.nd;
        nr=d.nr;
        Nod *p;
        if(!this->isEmpty()){
        p=prim;
    Nod *q;
    while(p!=0){
        q = p;
        p = p->next;
        delete q;
       }
        }
       prim=ultim = 0;
    p=d.prim;
    while(p){
        this->addElement(p->info);
        p=p->next;
    }
    return *this;
    }

    friend class Graf;
    };


 Lista::Lista(){
    prim=ultim=0;
}

Lista::~Lista(){
    Nod *p=prim;
    Nod *q;
    while(p!=0){
        q = p;
        p = p->next;
        delete q;
       }
       prim=ultim = 0;
}

Lista::Lista(const Lista &c)
{
    nd=c.nd;
    nr=c.nr;
    prim=ultim=0;
    Nod *p=c.prim;
    while(p)
    {
        this->addElement(p->info);
        p=p->next;
    }
}

 int Lista::isEmpty(){
     return prim==0;
}

void Lista::addElement(Nod n){
   Nod *p;
   p=new Nod(n.info,0);
   if(isEmpty()){
   prim=ultim=p;
     }
     else {
   ultim->next=p;
      ultim = p;
     }
}

Nod* Lista::getFirst(){
     return prim;
}

Nod* Lista::getLast(){
   return ultim;
}

ostream& operator<<(ostream& out, Lista& lista){
     Nod * p=lista.getFirst();
 while(p){
      cout<<p->getInfo()<<",";
      p=p->getNext();
     }
     cout<<"\b ";
 return out;
    }

class Graf{
    int vf;                  //nr de noduri
    Lista *V;                 //Vecinii nodului vf
    int **ma,**ma_dr;
public:
    friend istream& operator>>(istream&,Graf&);
    friend ostream& operator<<(ostream&,Graf&);
    Graf()
    {
        vf=0;
        V=new Lista[vf+1];
    };
    ~Graf();
    Graf(const Graf &);
    void Mat_A();               //creeza matricea de adiacenta
    void Mat_dr();              //creeza matricea drumurilor
    void afis_mat_dr();
    void DFS(int);
    void dfs(int,int[]);
    void BFS(int);
    void sort_top();
    void comp_tconexe();
    int tconex();
    const Graf & operator +(const Graf &c);

    Graf &operator =(const Graf &d)
    {
        vf=d.vf;
        delete []V;
        V=new Lista[vf+1];
        for(int i=1;i<=vf;i++)
            V[i]=d.V[i];
        return *this;
    }

};

Graf::~Graf(){
    int i;
    for (i=1;i<=vf;i++){
        Nod *p=V[i].prim;
       Nod *q;
    while(p!=0){
        q = p;
        p = p->next;
        delete q;
       }
       V[i].prim=V[i].ultim = 0;
    }
}

Graf::Graf(const Graf &c){
    vf=c.vf;
    V=new Lista[vf+1];
    int i;
    for(i=1;i<=vf;i++){
        V[i].prim=V[i].ultim=0;
        Nod *p=c.V[i].prim;
        while(p){
           this->V[i].addElement(p->info);
           p=p->next;
           }
       V[i].nd=c.V[i].nd;
       V[i].nr=c.V[i].nr;
        }

}

void Graf::Mat_A(){
    int i,j;
    ma=new int*[vf+1];
    for(i=1;i<=vf;i++)
        ma[i]=new int[vf+1];
    for(i=1;i<=vf;i++)
        for(j=1;j<=vf;j++)
           ma[i][j]=0;
    Nod *p;
    for(i=1;i<=vf;i++)
    {
        p=V[i].getFirst();
        while(p)
        {
          ma[V[i].nd][p->getInfo()]++;
          p=p->getNext();
        }
    }
}

void Graf::Mat_dr(){
    int i,j,k;
    ma_dr=new int*[vf+1];
    for(i=1;i<=vf;i++)
        ma_dr[i]=new int[vf+1];
    for(i=1;i<=vf;i++)
        for(j=1;j<=vf;j++)
           ma_dr[i][j]=ma[i][j];
    for(k=1;k<=vf;k++)
        for(i=1;i<=vf;i++)
            for(j=1;j<=vf;j++)
               if(ma_dr[i][j]==0&&i!=k&&j!=k)
                  ma_dr[i][j]=ma_dr[i][k]*ma_dr[k][j];
}

void Graf::afis_mat_dr(){
    int i,j;
    for(i=1;i<=vf;i++){
       for(j=1;j<=vf;j++)
            cout<<ma_dr[i][j]<<" ";
        cout<<"\n";
    }
}

istream& operator>>(istream& in,Graf& a){
    int i,x,k;
    in>>a.vf;
    delete []a.V;
    a.V=new Lista[a.vf+1];
    for(i=1;i<=a.vf;i++)
    {
        in>>a.V[i].nd;
        k=0;
        while(in.get()!='\n')
            {
            in>>x;
        k++;
            a.V[i].addElement(x);
        }
        a.V[i].nr=k;
    }
    return in;
}

ostream& operator<<(ostream& out, Graf& a){
    int i;
    for(i=1;i<=a.vf;i++)
    {
        out<<a.V[i].nd<<':'<<a.V[i]<<"\n";
    }
    return out;
}

void Graf::dfs(int nod_s,int v[]){
 cout<<nod_s<<" ";
 v[nod_s]=1;
 for(int k=1;k<=vf;k++)
      if(ma[nod_s][k]==1&&v[k]==0)
               dfs(k,v);
}

void Graf::DFS(int nod_s){
    cout<<"\nDFS(din "<<nod_s<<"): ";
    int *v,i;
    v=new int[vf+2];
    for(i=1;i<=vf;i++)
        v[i]=0;
    dfs(nod_s,v);
    delete []v;
}

void Graf::sort_top(){
    cout<<"\nSortarea topologica:";
    int *v,i;
    v=new int[vf+2];
    for(i=1;i<=vf;i++)
        v[i]=0;
    for(i=1;i<=vf;i++)
        if(v[i]==0)dfs(i,v);
}

void Graf::BFS(int nod_st){
    cout<<"\nBFS(din "<<nod_st<<"): ";
    int *c,*v,i,prim=1,ultim=1,k;
    c=new int[vf+1];
    v=new int[vf+1];
    for(i=1;i<=vf;i++)
        v[i]=0;
    k=nod_st;
    v[k]=1;
    c[prim]=k;
    while(prim<=ultim){
       k=c[prim];
       for(i=1;i<=vf;i++)
          if(ma[k][i]==1&&v[i]==0)
            {ultim++;
             c[ultim]=i;
             v[i]=1;}
  prim++;
      }
    for(i=1;i<=ultim;i++)
        cout<<c[i]<<" ";
    delete []c;
    delete []v;
}

void Graf::comp_tconexe(){
    int i,nr=0,*v,k;
    v=new int[vf+2];
    for(i=1;i<=vf;i++)
        v[i]=0;
    cout<<"\nComponentele tare conexe sunt:";
    while(nr<vf)     //cat timp mai sunt noduri ce nu apartin niciunei componente conexe
    {
        for(i=1;i<=vf;i++)
           if(v[i]==0)
              {
                  v[i]=1;
                  nr++;
                  k=i;
                  cout<<"\n"<<i<<" ";
                  break;
              }
        for(i=1;i<=vf;i++)
            if(v[i]==0&&ma_dr[i][k]&&ma_dr[k][i])
        {
            v[i]=1;
            nr++;
            cout<<i<<" ";
        }
    }
}

int Graf::tconex(){
    int i,j;
    for(i=1;i<=vf;i++)
        for(j=1;j<=vf;j++)
           if(ma_dr[i][j]==0)return 0;
    return 1;
}

const Graf& Graf::operator +(const Graf &c){
    Graf rez;
    rez.vf=c.vf;
    int i,j;
    rez.V=new Lista[rez.vf+1];
    for(i=1;i<=rez.vf;i++)
        for(j=1;j<=rez.vf;j++)
           if(this->ma[i][j]||c.ma[i][j])
              rez.ma[i][j]=1;
            else rez.ma[i][j]=0;
    for(i=1;i<=rez.vf;i++){
        rez.V[i].addElement(i);
        for(j=1;j<=rez.vf;j++)
            if(rez.ma[i][j])rez.V[i].addElement(j);
    }
    return rez;
}
int main()
{
   Graf g;
    f>>g;
    cout<<g;
    g.Mat_A();
    g.Mat_dr();
    g.afis_mat_dr();
    g.DFS(1);
    g.comp_tconexe();
    if(g.tconex())cout<<"\nGraful este tare conex\n";
      else cout<<"\nGraful NU este tare conex\n";
    g.sort_top();

    /*
    Graf *u;
    int n,i;
    f>>n;
    u=new Graf[n+1];
    for(i=1;i<=n;i++)
        f>>u[i];
    for(i=1;i<=n;i++)
        cout<<u[i]<<endl;
    */
    return 0;
}
