#include <iostream>
#include <vector>
using namespace std;

vector <vector<int> > from_sr_to_ms(vector< vector<int> > sr)// аргумент функци- список ребер, функция возвращает матрицу смежности
{

int n = sr.size()+1;
vector <vector <int> > ms;
ms.resize(n);
for(int i =0; i<n; i++)
{
    ms.at(i).resize(n);
    ms.at(i).at(0)=i;
    ms.at(0).at(i)=i;
    if(i!=0){
                for(int g=1; g<n; g++)
                {
                    ms.at(i).at(g)=0;
                }
            }
}
for(int i = 0; i < n-1; i++)
{
int l = sr.at(i).at(0);
int r = sr.at(i).at(1);

ms.at(l).at(r)=1;
ms.at(r).at(l)=1;
}
return ms;
}
vector <vector<int> > from_ms_to_ss(vector< vector<int> > ms)// аргумент функци- матрица смежности, функция возвращает список смежности
{
    int n = ms.size()-1;
    vector <vector <int> > ss;
    ss.resize(n);
    for(int i = 1; i<=n; i++)
    {
        ss.at(i-1).resize(0);
        for(int g = 1; g<=n; g++)
        if(ms.at(i).at(g)==1)
        {
            ss.at(i).push_back(g);
        }
    }
    return ss;
}
vector <vector<int> > from_ss_to_mi(vector< vector<int> > ss)// аргумент функци- список смежности, функция возвращает матрицу инцидентности
{
    int n = ss.size()+1, nom=0;
     vector <vector <int> > mi;
     mi.resize(n);
     int b = 0;
     for(int i = 0; i<n-1; i++)
     {
         b = b + ss.at(i).size();
     }
     b=b/2;
     for(int i = 0; i<n; i++)
     {
         for(int g = 1; g< n; g++){mi.at(i).at(g)=0;}
         mi.at(i).resize(b+1);
         mi.at(i).at(0)=i;
         if(i<b+1)mi.at(0).at(i)=i;
     }
     for(int i = 0; i<n-1; i++)
     {
         for(int g =0; g<ss.at(i).size(); g++)
         {
             mi.at(i+1).at(nom+1)=1;

             int minm=ss.at(ss.at(i).at(g)).at(0), j=g;
             for(int f=1; f<ss.at(ss.at(i).at(g)).size(); f++)
             {

                 if(ss.at(ss.at(i).at(g)).at(f)<minm)
                 {
                     minm = ss.at(ss.at(i).at(g)).at(f);

                     j=f;
                 }
             }
             ss.at(i).erase(ss.at(i).begin() + j);

             mi.at(ss.at(i).at(g)).at(nom+1)=1;
            nom++;
         }
     }
     return mi;
}
vector <vector<int> > from_mi_to_sr(vector< vector<int> > mi)// аргумент функци- матрица инцидентности, функция возвращает список ребер
{
    vector <vector<int> > sr;
    int n = mi.at(0).size()-1, s=mi.size(), k;
    sr.resize(n);
    for(int i=0; i<n; i++){sr.at(i).resize(2);}

    for(int i = 1; i<n+1; i++)
    {
        k=0;
        for(int g =1; g<s; g++)
        {
        if(mi.at(g).at(i)==1)
        {
            sr.at(g-1).at(k)=i;
            k++;
        }
        }

    }
    return sr;
}
int main()
{
//пример перевода списка ребер в матрицу смежности
vector < vector <int> > i, n;
i.resize(3);
i.at(0).resize(2);
i.at(1).resize(2);
i.at(2).resize(2);
i.at(0).at(0)=1;
i.at(0).at(1)=2;
i.at(1).at(0)=2;
i.at(1).at(1)=3;
i.at(2).at(0)=3;
i.at(2).at(1)=1;

n = from_sr_to_ms(i);
for(int r =0; r<4; r++)
{
    for(int g =0; g<4; g++)
    {
        cout<<n.at(r).at(g);
    }
    cout<<" "<<endl;
}
    return 0;
}
