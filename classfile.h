/*************************************************************************
 > File Name: classfile.h
 > Author: 胡高科
 > Mail: hugaoke@126.com 
 > Version:No:2. 
 > Created Time: 2015年12月14日 星期一 21时03分12秒
 ************************************************************************/
#include <iostream>
#include"randomnumber.h"
#include<cstdlib>
#include<ctime>
using namespace std;

#ifndef __CLASSFILE__H
#define __CLASSFILE__H

struct Structure{           //define the parameter of funnel;
    double high;            //two endpoint in z direction
    double D;               //diameter of funnel
    double d;               //diameter of hole in the funnel
};

class Particle;
class Force{
public:
    int id1,id2; 
    int ty1,ty2;
    Vector x1,x2;
    Vector fs;
    double distance;
    double fn;
    Force(); 
    static vector<Force> filein(string name /*filename*/);
    //定义指针p1,p2分别指向相互作用的两个颗粒
    Particle *p1;
    Particle *p2;

};
Force::Force():id1(0),id2(0),ty1(0),ty2(0),fn(0){
    distance=0;
    fs=Vector(0,0,0);
    x1=Vector(0,0,0);
    x2=Vector(0,0,0);
}
ostream &operator<<(ostream &output, const Force &p ){
    output<<p.id1<<" "<<p.ty1<<" "<<p.x1<<" "<<p.id2<<" "<<p.x2<<" ";
    output<<p.distance<<" "<<p.fn<<" "<<p.fs<<endl;
    return output;
}
istream &operator>>(istream &input, Force &p){
    input>>p.id1>>p.ty1>>p.x1>>p.id2>>p.ty2>>p.x2;
    input>>p.distance>>p.fn>>p.fs;
    return input;
}
vector<Force> Force::filein(string name /*filename*/){
    ifstream fin(name.c_str(),ios::in);
    vector<Force> f;
    if(!fin){
         cerr<<"error!"<<endl;
         return f;
    }
    string s;
    getline(fin ,s);
    Force temp;
    while(!fin.eof()){
    //函数eof判断文件是读取结束
        fin>>temp;
        f.push_back(temp);
    }
    fin.close();
    return f;
}
    
class Particle{
public:
    Particle  ();
    Vector lattice(const Vector tmp /*lattic length */,const Vector temp /* origin*/ ){
        return Vector(ceil((x.x-temp.x)/tmp.x),ceil((x.y-temp.y)/tmp.y)
                ,ceil((x.z-temp.z)/tmp.z));
    }
    //The number tab the lattices is from 1 to N;
    static vector<Particle> filein(string name);
    int id,tyid,motion;     
    //id标记不同颗粒 tyid标记不同的颗粒物质 motion？？？？？
    double r;               
    //r标记颗粒半径
    Vector x,v,a,w;         
    //x：颗粒位置； v：颗粒速度； a：颗粒加速度； w：颗粒角速度
    vector <Force*> fp;
    //定义指针数组fp 存储该 颗粒参加的相互作用。
};
Particle::Particle():id(0),tyid(0),motion(0),r(0){
    x=Vector(0,0,0); 
    v=Vector(0,0,0);
    a=Vector(0,0,0);
    w=Vector(0,0,0);
    }
ostream &operator<<(ostream &output, const Particle &p ){
    output<<p.id<<" "<<p.tyid<<" "<<p.motion<<" ";
    output<<p.r<<" "<<p.x<<" "<<p.v<<" "<<p.a<<" "<<p.w;
    return output;
}
istream &operator>>(istream &input, Particle &p){
    input>>p.id>>p.tyid>>p.motion>>p.r>>p.x>>p.v>>p.a>>p.w;
    return input;
}
vector<Particle> Particle::filein(string name /*filename*/){
    ifstream fin(name.c_str(),ios::in);
    vector<Particle> temp;
    if(!fin){
        cout<<"error!"<<endl;
        return temp;
    }
    int num;
    fin>>num;
    string s;
    getline(fin,s);
    getline(fin,s);
    vector<Particle> p(num);
    for(int i=0;i<num;i++){
        fin>>p[i];
        if(i%100000==0){
            cout<<i<<endl;
        }
    }
    return p;
}

class Basal_Area{
public:
    int n;
    int num;                        //sampling numbers
    double **p;                     //Store the area in each lattices;
    Basal_Area(int nn,int m=10000000);
    void output();
    ~Basal_Area(){
        for(int i=0;i<n; i++)
            delete[] p[i];
        delete[] p;
    }
};
Basal_Area::Basal_Area(int nn,int m){
    n=nn; num=m;
    double r=double(n/2);
    p = new double*[n];               //row;
    for (int i=0; i<n; ++i)
        p[i]=new double[n];            //col;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            p[i][j]=0;
    for(int i=0;i<num;i++){
        double a=random(0,n);
        double b=random(0,n);
        if((a-r)*(a-r)+(b-r)*(b-r)<=r*r)
             p[(int)a][(int)b]++;
    }
    double avernum=double(num/(n*n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            p[i][j]/=avernum;
			if(p[i][j]>1)
                p[i][j]=1;
        }
    }
}
void Basal_Area::output(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<p[i][j]<<" "<<"\t";
        cout<<endl;
    }
}

class Lattice{
public:
    Vector x; 
    double basal_area;
    Lattice(int a=0,int b=0,int c=0):basal_area(0) {x=Vector(a,b,c);}
    double num_density();
    Vector average_vel();
    Vector average_acceler();
    Vector average_ang_vel();
    //using node list because it don't need too much continuous memory space;
    list<Particle*> p;
};
double Lattice::num_density(){
    if(basal_area>=0.4)
        return p.size()/basal_area;
    else 
        return 0;
}
Vector Lattice::average_vel(){
    list<Particle*>::const_iterator i;
    Vector v(0,0,0);
    for(i=p.begin();i!=p.end();i++)
        v+=(*i)->v;					//this bracket can't omit;
    return v/p.size();
}
Vector Lattice::average_acceler(){
    list<Particle*>::const_iterator i;
    Vector v(0,0,0);
    for(i=p.begin();i!=p.end();i++)
        v+=(*i)->a;
    return v/p.size();
}
Vector Lattice::average_ang_vel(){
    list<Particle*>::const_iterator i;
    Vector v(0,0,0);
    for(i=p.begin();i!=p.end();i++)
        v+=(*i)->w;
    return v/p.size();
}

string intostr(int a){				 //实现十位数以内的转换
    char p[10];
    sprintf(p,"%d",a);
    return p;
}

int get_index(Vector p /*coord*/,Vector n /*divide number*/){
    if(p.x>n.x||p.x<0||p.y>n.y||p.y<0||p.z>n.z||p.z<0)
        cerr<<"Illegal coord!"<<endl;
    if(n.x<=0||n.y<=0||n.z<=0)
        cerr<<"Illegal divide number!"<<endl;
    p-=Vector(1,1,1);
    return (int)(p.x+p.y*n.x+p.z*n.x*n.y);
}

Vector get_coord(int index0 /*index*/ ,Vector n /*divide nmuber*/){
    if(n.x<=0 ||n.y<=0||n.z<=0)
        cerr<<"Illegal divide number!"<<endl;
    if(index0<0||index0>n.x*n.y*n.z-1)
        cerr<<"Illegal index!"<<endl;
    Vector p(0,0,0);
    p.x=index0%(int(n.x));
    index0-=p.x;
    index0/=n.x;
    p.y=index0%(int(n.y));
    p.z=(int)(index0/(n.y));
    return p+Vector(1,1,1);
}

//User-defined function myless(), to sort the class Particle ,by its parameter "id";
bool myless(const Particle &p1,const Particle &p2) { return p1.id<p2.id; }

void particle_relate_force(vector<Particle> &pp,vector<Force> &ff){
    //using myless to sort class Particle;
    sort(pp.begin(),pp.end(),myless);
    //实现类Force中定义的指针p1，p2和类Particle定义的指针数组fp
    for(int i=0;i<ff.size();i++){
        pp[ff[i].id1].fp.push_back (&ff[i]);
        pp[ff[i].id2].fp.push_back(&ff[i]);
        ff[i].p1=&pp[ff[i].id1];
        ff[i].p2=&pp[ff[i].id2];
    }
    cout<<"The particle and the force are related!"<<endl;
}

inline void part(const string s1 ,const string s2){  //Divide the different part of progame;
	cout<<"*********************Part "<<s1<<":"<<s2<<"*********************"<<endl;
}

#endif 

