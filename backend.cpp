#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "field.c"

using namespace std;
static float pi=3.1415926535897932384626;
static float mu=1.25663706e-6;
static float epsilon=8.8541878128e-12;
static float pi4e0=4*pi*epsilon;


void qp(string __){
    cout<<__<<endl;
}
void qp(float  __){
    cout<<__<<endl;
}

double norm(double* x, double* y)
{
    uint8_t dim=sizeof(x)/3;
    double __=0;
    for(uint8_t i;i<dim;i++)
    {
        __+=sqrt(pow(x[i],2)+pow(y[i],2));
        
    }
    return __;

}

double dot_product(float* A, float* B){
    uint8_t vl=sizeof(A)/4;
    double val=0;
    for(uint8_t i=0;i<vl;){
        val+=A[0]*B[0];
    }
    return val;
}

//field function begins


//field function begins

int main()
{
    string current_line;
    fstream ioc;
    ioc.open("points.csv");
    unsigned long n_of_points=0;
    while(getline(ioc,current_line))
    {
       n_of_points++;

    }
    double points[n_of_points][3];
    double normals[n_of_points][3];
   
    ioc.close();
    fstream iop;
   
    iop.open("points.csv");
    unsigned long current_point=0;

    while(getline(iop,current_line))
    {
        uint16_t commas[2]={0,0};
        uint16_t len=current_line.length();
        uint8_t comma_count=0;
        for(uint16_t i=0; i<len; i++)
        {
            if(current_line[i]==',')
            {
                commas[comma_count]=i;
                comma_count++;
            }
            if(comma_count==2){
                break;
            }

        }
        points[current_point][0]=stof(current_line.substr(0,commas[0]));
        points[current_point][1]=stof(current_line.substr(commas[0]+1,commas[1]));
        points[current_point][2]=stof(current_line.substr(commas[1]+1,len));
        


    }
    iop.close();
    fstream ion;
    ion.open("normals.csv");

    current_point=0;
  while(getline(ion,current_line))
    {
        uint16_t commas[2]={0,0};
        uint16_t len=current_line.length();
        uint8_t comma_count=0;
        for(uint16_t i=0; i<len; i++)
        {
            if(current_line[i]==',')
            {
                commas[comma_count]=i;
                comma_count++;
            }
            if(comma_count==2){
                break;
            }

        }
        normals[current_point][0]=stof(current_line.substr(0,commas[0]));
        normals[current_point][1]=stof(current_line.substr(commas[0]+1,commas[1]));
        normals[current_point][2]=stof(current_line.substr(commas[1]+1,len));
       


    }
    ion.close();
//field data:
double r_val;

for (unsigned long i=0; i<n_of_points;i++)
{

double __=fieldX(points[i][0],points[i][1],points[i][2])*normals[i][0]+fieldY(points[i][0],points[i][1],points[i][2])*normals[i][1]+fieldZ(points[i][0],points[i][1],points[i][2])*normals[i][2];

if (isnan(__)==false)
{
r_val+=__;


}



}
fstream io;
io.open("out.txt");
io<<r_val;
io.close();
   return 0;

}