#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
int fitness(vector<vector<int>>&v)
{
    int a,b,c;
    unordered_map<int,int>pc;
    for(int i=0;i<5;i++)
    {
        a=v[i][0];
        b=v[i][1];
        c=v[i][2];

        if(a>b && b>c) pc[1]++;
        else if(a>b && a>c) pc[2]++;
        else if(a>b && c>a) pc[3]++;
        else if(b>a && b>c) pc[4]++;
        else if(b>a && c>b) pc[5]++;
    }
    int pathsUsed=pc.size();
    int currfitness= pathsUsed*100/5 ;
    // cout<<currfitness<<endl;
    return currfitness;

}
void mutation(vector<vector<int>>&v)
{
    // min + rand() % (( max + 1 ) - min);
    int i= 0 + rand() % (( 4 + 1 ) - 0);
    int a,b,c;
    a=v[i][0];
    b=v[i][1];
    c=v[i][2];
    int x[8]={0}; int y[8]={0}; int z[8]={0};
    int it=7;
    while(a>0)
    {
        x[it]=a%2; a=a/2; it--;
    }
    it=7;
    while(b>0)
    {
        y[it]=b%2; b=b/2; it--;
    }
    it=7;
    while(c>0)
    {
        z[it]=c%2; c=c/2; it--;
    }
    // min + rand() % (( max + 1 ) - min);
    int random_tc=1+rand() % (3+1-1);
    int ran_bit=0+rand() % (7+1-0);
    if(random_tc==1)
    {
        if(x[ran_bit]==0)x[ran_bit]=1;
        else x[ran_bit]=0;
    }
    else if(random_tc==2)
    {
        if(y[ran_bit]==0) y[ran_bit]=1;
        else y[ran_bit]=0;
    }
    else if(random_tc==3)
    {
        if(z[ran_bit]==0) z[ran_bit]=1;
        else z[ran_bit]=0;
    }

    int d1=0; int d2=0; int d3=0;
        int mul=128;
        for(int bit=0; bit<8; bit++)
        {
            d1+=mul*x[bit];
            d2+=mul*y[bit];
            d3+=mul*z[bit];
            mul=mul/2;
        }
        v[i][0]=d1;
        v[i][1]=d2;
        v[i][2]=d3;


}

void crossover(vector<vector<int>>&v)
{
    int a,b,c;
    for(int i=0;i<5;i++)
    {
        a=v[i][0];
        b=v[i][1];
        c=v[i][2];
        int x[8]={0}; int y[8]={0}; int z[8]={0};
        int it=7;
        while(a>0)
        {
            x[it]=a%2; a=a/2; it--;
        }
        it=7;
        while(b>0)
        {
            y[it]=b%2; b=b/2; it--;
        }
        it=7;
        while(c>0)
        {
            z[it]=c%2; c=c/2; it--;
        }
                                        // cout<<endl<<"printing a b c "<<endl;
                                        //                         for(int i=0;i<8;i++)
                                        //                         cout<<x[i]<<" ";
                                        //                         cout<<endl;
                                        //                         for(int i=0;i<8;i++)
                                        //                         cout<<y[i]<<" ";
                                        //                         cout<<endl;
                                        //                         for(int i=0;i<8;i++)
                                        //                         cout<<z[i]<<" ";
                                        //                         cout<<endl;
        int t1=x[2]; x[2]=y[2]; y[2]=t1;
        int t2=x[3]; x[3]=y[3]; y[3]=t2;
        int t3=x[4]; x[4]=y[4]; y[4]=t3;

        t1=y[5]; y[5]=z[5]; z[5]=t1;
        t2=y[6]; y[6]=z[6]; z[6]=t2;
        t3=y[7]; y[7]=z[7]; z[7]=t3;
                                        // cout<<endl<<"printing after crossover "<<endl;
                                        //                     for(int i=0;i<8;i++)
                                        //                     cout<<x[i]<<" ";
                                        //                     cout<<endl;
                                        //                     for(int i=0;i<8;i++)
                                        //                     cout<<y[i]<<" ";
                                        //                     cout<<endl;
                                        //                     for(int i=0;i<8;i++)
                                        //                     cout<<z[i]<<" ";
                                        //                     cout<<endl;


        int d1=0; int d2=0; int d3=0;
        int mul=128;
        for(int bit=0; bit<8; bit++)
        {
            d1+=mul*x[bit];
            d2+=mul*y[bit];
            d3+=mul*z[bit];
            mul=mul/2;
        }
        v[i][0]=d1;
        v[i][1]=d2;
        v[i][2]=d3;
        // cout<<endl<<"after crosssover ";
        // cout<<endl<<d1<<" "<<d2<<" "<<d3<<endl;

    }

}
void printResult(vector<vector<int>>&v)
{
    int a,b,c;
    cout<<"Test Cases "<<"\t"<<"Path taken "<<endl;
    for(int i=0;i<5;i++)
    {
        a=v[i][0];
        b=v[i][1];
        c=v[i][2];
        cout<<a<<" "<<b<<" "<<c<<"\t\t";
        if(a>b && b>c) cout<<"1"<<endl;
        else if(a>b && a>c) cout<<"2"<<endl;
        else if(a>b && c>a) cout<<"3"<<endl;
        else if(b>a && b>c) cout<<"4"<<endl;
        else if(b>a && c>b) cout<<"5"<<endl;
    }
}
int main()
{
    vector<vector<int>>v;
    vector<int>temp;
    int x;
    //? Initial Population
    cout<<"Enter initial set of test cases ";
    for(int it=0;it<5;it++)
    {
        for(int i=0;i<3;i++)
        {
            cin>>x;
            temp.push_back(x);
        }
        v.push_back(temp);
        temp.clear();
    }
    //? Compute fitness
    //?  If the fitness is less than 95% but more than 75%, then apply mutation 
    //?  else apply crossover operation.
    int currFitness=fitness(v);
    int iteration=1;
    while(currFitness <= 95)
    {
        if(iteration==10)
        {
            iteration=1;
            mutation(v);
        }
        if(currFitness>=75) 
        mutation(v);
        else 
        crossover(v);
        currFitness=fitness(v);
        cout<<currFitness<<" ";
        iteration++;

    }
    cout<<endl<<"Result "<<endl;
    printResult(v);
    return 0;
}
/*
0 6 1
6 4 3
5 1 4
10 5 6
6 2 1
*/
/*
0 60 10
6 14 30
5 1 41
10 501 61
61 2 4
*/
/*
0 6 10
6 14 3
5 1 4
10 5 61
6 2 4
*/