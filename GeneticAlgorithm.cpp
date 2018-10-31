#include<bits/stdc++.h>
using namespace std;
struct chromosome
{
    string a;
    string b;

} pop[5],ch1,ch2;
bool complete(int visA[],int visB[])
{
    for(int i=0; i<8; i++)
    {
        if(visA[i]==0 || visB[i]==0)
        {
            return false;
        }
    }
    return true;
}
void populate()
{
    string str="12345678";
    string str2="qqqqqrrr";
    string g[41000];
    string g2[100];
    int i=0;
    do
    {
        // //cout << str << endl;
        g[i]=str;
        i++;

    }
    while (next_permutation(str.begin(), str.end()));
    i=0;
    do
    {
        // //cout << str << endl;
        g2[i]=str2;
        i++;
    }
    while (next_permutation(str2.begin(), str2.end()));
    int d=0;
    for(int i=0; i<5; i++)
    {
        int x=d+rand()%8064;
        int y=rand()%56;
        pop[i].a=g[x];
        pop[i].b=g2[y];
        //cout<<pop[i].a<<" "<<pop[i].b<<endl;
        d+=8064;

    }
}

string pmx(string pa1,string pa2)
{
    srand(time(NULL));
    string p1=pa1;
    string p2=pa2;

    int a=rand()%8;
    int b=rand()%8;
    while(a==b){
        b=rand()%10;
    }
    if(b<a)swap(a,b);
    string c="********";
    for(int i=a;i<=b;i++){
        c[i]=p1[i];
    }
    //cout<<c<<endl;


    for(int i=a;i<=b;i++){
        int f=0;
        for(int j=a;j<=b;j++){
            if(c[j]==p2[i])f=1;
        }
        if(f==0){
            char c=p2[i];

        }
        else{
            continue;
        }
        bool found=false;
        char e=p2[i];
       // cout<<"Next:"<<e<<endl;
        int x=i;
        while(!found)
        {
            char n=p1[x];
            for(int k=0;k<8;k++){
                if(p2[k]==n){
                    x=k;
                }
            }
            if(x<a || x>b)found=true;

        }
        c[x]=e;

    }
    for(int i=0;i<8;i++){
        if(c[i]=='*'){
            c[i]=p2[i];
        }
    }
    return c;

}

void pmx_crossover(chromosome p1,chromosome p2,struct chromosome *child1,struct chromosome *child2)
{
    child1->a=pmx(p1.a,p2.a);
    child2->a=pmx(p2.a,p1.a);

    random_shuffle(p1.b.begin(), p1.b.end());
    child1->b=p1.b;

    random_shuffle(p2.b.begin(), p2.b.end());
    child2->b=p2.b;

}

int fitness(chromosome c)
{
    int fitness = 28;

    for(int i=0; i<7; i++)
    {
        for (int j=i+1; j<8; j++)
        {
            int x=c.a[i]-'0';
            int y=c.a[j]-'0';
            //(c.a[i]-'0')- (c.a[j]-'0')
            if (abs(i-j) == abs(x-y))
            {
                if (c.b[i]=='q' or c.b[j]=='q')
                {
                    //cout<<fitness<<endl;
                    fitness--;
                   // cout<<i<<" "<<j<<endl;
                }
            }
        }
    }
    return fitness;
}
void cycleCrossover(chromosome parent1,chromosome parent2,struct chromosome *child1,struct chromosome *child2)
{
    //srand(time(NULL));
    random_shuffle(parent1.b.begin(), parent1.b.end());
    child1->b=parent1.b;

    random_shuffle(parent2.b.begin(), parent2.b.end());
    child2->b=parent2.b;

    if(parent1.a==parent2.a)
    {
        child1->a=parent1.a;
        child2->a=parent2.a;
        return;
    }
    child1->a="00000000";
    child2->a="00000000";
    string a=parent1.a;
    string b=parent2.a;
    int visA[]= {0,0,0,0,0,0,0,0};
    int visB[]= {0,0,0,0,0,0,0,0};
    string ac[100];
    string bc[100];
    for(int i=0; i<8; i++)
    {
        ac[i]="";
        bc[i]="";
    }
    int nu=1;
    while(!complete(visA,visB))
    {
        int x;
        char h;
        for(int i=0; i<8; i++)
        {
            if(visA[i]==0)
            {
                visA[i]=nu;
                h=a[i];
                x=i;
                ////cout<<h<<" "<<b[x]<<endl;
                visB[x]=nu;
                break;
            }
        }
        int cycle=0;
        while(cycle==0)
        {
            for (int i=0; i<8; i++)
            {
                if (a[i]==b[x])
                {
                    visB[x]=nu;
                    visA[i]=nu;
                    x=i;
                    ////cout<<x<<" "<<a[i]<<" "<<b[x]<<endl;
                    //int t;
                    //cin>>t;
                    break;
                }
            }
            if (b[x]==h)
            {

                visB[x]=nu;
                cycle=1;

                nu++;

            }
        }
    }
    nu--;
    for(int i=0; i<8; i++)
        //cout<<visA[i]<<" ";
        //cout<<endl;

        for(int i=1; i<=4; i++)
        {
            if(i%2==1)
            {
                for(int k=0; k<8; k++)
                {
                    if(visA[k]==i)
                    {
                        child1->a[k]=parent1.a[k];
                    }
                }
            }
            else
            {
                for(int k=0; k<8; k++)
                {
                    if(visA[k]==i)
                    {
                        child1->a[k]=parent2.a[k];
                    }
                }
            }
        }
    for(int i=1; i<=nu; i++)
    {
        if(i%2==1)
        {
            for(int k=0; k<8; k++)
            {
                if(visA[k]==i)
                {
                    child2->a[k]=parent2.a[k];
                }
            }
        }
        else
        {
            for(int k=0; k<8; k++)
            {
                if(visA[k]==i)
                {
                    child2->a[k]=parent1.a[k];
                }
            }
        }
    }
    ////cout<<child1->a<<" "<<child2->a<<endl;
    ////cout<<endl;
    //for(int i=0; i<8; i++)
    //  //cout<<child1->a[i]<<" ";
    ////cout<<endl;
    //for(int i=0; i<8; i++)
    //  //cout<<child2->a[i]<<" ";

    ////cout<<child1.b<<" "<<child2.b<<endl;
    ////cout<<child1->a<<" "<<child2->a<<endl;



}
void rank_selection(chromosome s[],struct chromosome *p1,struct chromosome *p2)
{
    //srand(time(NULL));
    for(int i=0; i<4; i++)
    {
        for(int j=i+1; j<5; j++)
        {
            if(fitness(s[i])>=fitness(s[j]))
            {
                string tempa =s[i].a;
                string tempb =s[i].b;
                s[i].a=s[j].a;
                s[i].b=s[j].b;
                s[j].a=tempa;
                s[j].b=tempb;
            }
        }
    }
    int t=10;
    int r=rand()%10;
    int sum=0;
    //cout<<r<<endl;
    int pdx;
    for(int i=0; i<5; i++)
    {
        sum+=i;
        if(sum>=r)
        {
            pdx=i;
            p1->a=s[i].a;
            p1->b=s[i].b;
            break;
        }
    }
    int t1=10;
    int r1=rand()%10;
    if(r1==r)
    {
        while(r1-r==0)
        {
            r1=rand()%10;
        }
    }
    int sum1=0;
    int pdx2;
    for(int i=0; i<5; i++)
    {
        sum1+=i;
        if(sum1>=r1)
        {
            pdx2=i;
            p2->a=s[i].a;
            p2->b=s[i].b;
            break;
        }
    }
    if(pdx==pdx2)
    {
        p1->a=p2->a;
        p1->b=p2->b;
    }
    ////cout<<p1->a<<" "<<p2->a;
}
chromosome scramble_mutation(chromosome so)
{
    string s=so.a+so.b;
    int i1=rand()%16;
    int i2=rand()%16;
    if(i1>i2)swap(i1,i2);
    string x="";
    for(int i=i1;i<=i2;i++){
        x+=s[i];
    }
    random_shuffle(x.begin(), x.end());
    //cout<<s<<endl;
    int j=0;
    for(int i=i1;i<=i2;i++){
        s[i]=x[j++];
    }
    //cout<<s<<endl;
    chromosome ms;
    ms.a="";
    ms.b="";
    for(int i=0; i<16; i++)
    {
        if(s[i]=='q' || s[i]=='r')
        {
            ms.b+=s[i];
        }
        else
        {
            ms.a+=s[i];
        }
    }
    //cout<<ms.a<<" "<<ms.b;
    return ms;

}
chromosome swap_mutation(chromosome so)
{
    string s=so.a+so.b;
    int i1=rand()%16;
    int i2=rand()%16;
    swap(s[i1],s[i2]);
    chromosome ms;
    ms.a="";
    ms.b="";
    for(int i=0; i<16; i++)
    {
        if(s[i]=='q' || s[i]=='r')
        {
            ms.b+=s[i];
        }
        else
        {
            ms.a+=s[i];
        }
    }
    //cout<<ms.a;
    return ms;
}
int main()
{
    srand(time(NULL));
    //populate();
    //chromosome p1,p2;
    //rank_selection(pop,p1,p2);
    ////cout<<p1.a<<" "<<p2.a;
    //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    ////cout<<r;
    //chromosome n=swap_mutation(pop[1]);
    ////cout<<n.a<<endl;
    populate();
    chromosome p1,p2,c1,c2,best;
    best.a=pop[0].a;
    best.b=pop[0].b;

    for(int i=0; i<5; i++)
    {
        //cout<<fitness(pop[i])<<endl;
        if(fitness(pop[i])>fitness(best))
        {
            best.a=pop[i].a;
            best.b=pop[i].b;
        }
    }
    chromosome Q[5];
    int idx=0;
    for(int i=0; i<2; i++)
    {
        rank_selection(pop,&p1,&p2);
        pmx_crossover(p1,p2,&c1,&c2);
        Q[idx].a=c1.a;
        Q[idx+1].a=c2.a;
        Q[idx].b=c1.b;
        Q[idx+1].b=c2.b;
        idx+=2;
    }
    ////cout<<endl;
    //for(int i=0; i<4; i++)
    //{
    ////cout<<Q[i].a<<" "<<fitness(Q[i])<<endl;
    //}

    for(int k=0; k<100; k++)
    {
        for(int j=0; j<5; j++)
        {
            ////cout<<fitness(pop[j])<<endl;
            if(fitness(Q[j])>=fitness(best))
            {
                best.a=Q[j].a;
                best.b=Q[j].b;
            }
        }

        idx=0;
        for(int i=0; i<2; i++)
        {
            rank_selection(pop,&p1,&p2);
            pmx_crossover(p1,p2,&c1,&c2);
           //pmx_crossover(p1,p2,&c1,&c2);
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(r<=0.01)
            {
                c1=swap_mutation(c1);
            }
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(r<=0.01)
            {
                c2=swap_mutation(c2);
            }
            Q[idx].a=c1.a;
            Q[idx+1].a=c2.a;
            Q[idx].b=c1.b;
            Q[idx+1].b=c2.b;
            idx+=2;
        }
    }
    //cout<<best.a<<" "<<best.b<<endl;
    cout<<"\nSolution:";
    //cout<<fitness(best)<<endl;
    if(!(best.a[0]>='1' && best.a[0]<='8')){
        int A[]={0,0,0,0,0,0,0,0,0};
        for(int i=1;i<8;i++){
            int x=best.a[i]-'0';
          //  cout<<x<<"h"<<endl;
            A[x]=1;
        }
        for(int i=1;i<=8;i++){
            if(A[i]==0){best.a[0]=i+'0';}
        }
        int q=0;
        int r=0;
        for(int i=1;i<8;i++){
            if(best.b[i]=='q')q++;
            if(best.b[i]=='r')r++;
        }
        if(q<5)best.b[0]='q';
        else if(r<3)best.b[0]='r';
    }
    chromosome solution;
    solution.a="";
    solution.b="";
    for(int i=0;i<8;i++){
        solution.a+=best.a[i];
        solution.b+=best.b[i];
    }
    cout<<fitness(solution)<<endl;
    for(int i=0; i<8; i++)
    {
        cout<<best.a[i];
    }
    cout<<endl;
    for(int i=0; i<8; i++)
    {
        cout<<best.b[i];
    }
    cout<<endl;


    string board[8];
    for(int i=0; i<8; i++)
    {
        board[i]="";
        for(int j=0; j<8; j++)
        {
            board[i]+="*";
        }
    }
    for(int i=0; i<8; i++)
    {
        board[i][(best.a[i]-'0')-1]=best.b[i];

    }

    for(int i=0; i<8; i++)
    {
        for(int j=0;j<8;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl<<endl;
    }

    chromosome x;
    x.a="12345678";
    x.b="rrrqqqqq";
    x=swap_mutation(x);
    cout<<x.a<<" "<<x.b<<endl;
}
//71863425 71863425

//43587162
//qqrqrqrq
