/*************************************************************************
 > File Name: temp2.cpp
 > Author: 胡高科
 > Mail: hugaoke@126.com 
 > Version:No.2 
 > Created Time: 2015年12月10日 星期四 21时37分02秒
 ************************************************************************/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<vector>
#include<list>
#include<algorithm>         //The header flie of function sort();
#include<cstdio>            //The header flie of function sprintf();
#include<iomanip>           //header flie of setprecision(),used to control output format;
#include"vector.h"
#include"classfile.h"
using namespace std;

int main(){
    double start = clock();
    //srand((unsigned) time(NULL));
    srand(1);
    part("one","Setting parameter");
    int nn=6;
    int nz=120;
    Structure para={0.6,0.030,0.006}; 
    //unit: cm
    Vector origin_point(-para.D/2,-para.D/2,0);
    Vector n(nn,nn,nz);      
    //n represent the number of lattices in x,y,z directoin;
    Vector delta(para.D/nn,para.D/nn,para.high/nz);
    cout<<"The division length of each lattice is :"<<delta<<endl;
    cout<<"The division number in each direction is:"<<n<<endl;
    //delta represent the le ngth of lattice in x,y,z direction;
    
    part("two","Input data");
	Basal_Area area(nn);
    area.output();
    vector<Lattice> coord;
    for(int i=0;i<nn*nn*nz;i++){
        Vector tt=get_coord (i,n);
        coord.push_back(Lattice(tt.x,tt.y,tt.z));
        coord[i].basal_area=area.p[int(tt.x)-1][int(tt.y)-1];
    }
    string address="/home/hugaoke/data/test/";
    string name1="flow_500kD030d006pp000pb000pw000_n_PosVelOmg_00100000.dat";
    string file_name1=address+name1;
    vector<Particle> p=Particle::filein(file_name1);
    cout<<"Data of postion is readly!"<<endl;
    string name2="flow_500kD030d006pp000pb000pw000_n_f_00100000.dat";
    string file_name2=address+name2;
    vector<Force> f=Force::filein(name2);
    cout<<"Data of force is readly!"<<endl;
    particle_relate_force(p,f);
    
    for(int i=0;i<p.size();i++){
        if(p[i].x.z>=0){             //don't care the particle out the funnel;
            Vector a =p[i].lattice(delta,origin_point);
            int index=get_index(a,n);
            coord[index].p.push_back(&p[i]);
        }  
    }
    cout<<"The particle and the lattice are related!"<<endl;
    
    part("three","Calculation");    
    ofstream fout("num_density.txt");
    for(int i=0;i<coord.size();i++){
        fout<<setprecision(5)<<coord[i].num_density()<<" "<<"\t";
        if(i%nn==nn-1)              fout<<endl;
        if(i%(nn*nn)==nn*nn-1)      fout<<endl;
    }

    double finish = clock();
    cout<<"This progame spend:"<<(finish-start)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}

   /* cout<<"f="<<f[f.size()-1]<<endl;
    cout<<"p2="<<f[f.size()-1] .p2->x<<endl;
    cout<<"p1="<<*f[f.size()-1].p1<<endl;
    cout<<p[478852].lattice(delta,para)<<endl;
    list<Particle*>::const_iterator i;
    for( i=coord[1][3][34].p.begin();i!=coord[1][3][34].p.end();i++)
        cout<<(*i)->id<<" ";        //this bracket can't omit;
    int k=499969;
    cout<<setprecision(5);
    cout<<p[k].x<<endl;
    cout<<(p[k].x.x-para.behind)/delta.x<<endl;
    cout<<p[ k].lattice(delta,para)-Vector(1,1,1)<<endl;*/
