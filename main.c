#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#define PI 3.14159265

using namespace std;



double distanceBetweenTwoPoints(double px1,double py1,double px2,double py2)
{
    double d = sqrt( pow((px2-px1),2) + pow((py2-py1),2) );
    return d;
}

double prependicularDistance(double px, double py,
                             double vx1, double vy1, double vx2, double vy2)
{


    double d = (
                    (  fabs( ((vy2-vy1)*px) - ((vx2-vx1)*py) + (vx2*vy1)- (vy2*vx1) )  )
                            /
                    (  sqrt( (  pow((vy2-vy1),2)  ) + (   pow(vx2-vx1,2)  )  )   )
                );
    return d;
}

double AngelsOfVectors(double wx1, double wy1, double wx2, double wy2,
                       double vx1, double vy1, double vx2, double vy2)
{
    double W = sqrt( pow((wx2 - wx1),2) + pow((wy2 - wy1),2) );
    double V = sqrt( pow((vx2 - vx1),2) + pow((vy2 - vy1),2) );
    double temp = ( ((wx2 - wx1)*(vx2 - vx1)) + ((wy2 - wy1)*(vy2 - vy1)) ) / (W*V) ;
    double teta = acos( temp )*(180.0/PI);
    return fabs( teta );
}

double hausdorffDistance(double px, double py, double vx1, double vy1, double vx2, double vy2)
{
    double d = 0;
    if ( AngelsOfVectors( vx1,vy1,px,py,vx1,vy1,vx2,vy2 ) < 90 && AngelsOfVectors( vx2,vy2,px,py,vx2,vy2,vx1,vy1 ) < 90 )
    {
        //cout << 1;
        d = prependicularDistance( px,py,vx1,vy1,vx2,vy2 );
    }
    else if (AngelsOfVectors( vx1,vy1,px,py,vx1,vy1,vx2,vy2 ) >= 90)
    {
        //cout << 2;
        d = distanceBetweenTwoPoints( px,py,vx1,vy1 );
    }
    else if ( AngelsOfVectors( vx2,vy2,px,py,vx2,vy2,vx1,vy1 ) >= 90 )
    {
        //cout << 3;
        d = distanceBetweenTwoPoints( px,py,vx2,vy2 );
    }
    return d;
}


void Agrawal(double x[], double y[],int n, double epsilon)
{

    cout << x[0] << " " << y[0] << "\n";

    bool a = true;

    for (int i = 0; i < n; i++ )
    {
        a = true;
        for (int j = i+1; j < n; j++ )
        {
            for (int k = i; k < j; k++)
            {
                if ( hausdorffDistance(x[k],y[k],x[i],y[i],x[j],y[j]) < epsilon ) {

                } else {
                    i = j-1;
                    if ( i != 0)
                        cout << x[i] << " " << y[i] << "\n";
                    a = false;
                    i--;
                    break;
                }
            }
            if (!a)
                break;
        }
    }
    cout << x[n-1] << " " << y[n-1] << "\n";
}


void NewAlgAgrawal(double x[], double y[],int n)
{
    double min_x = *std::min_element(x,x+n);
    double max_x = *std::max_element(x,x+n);

    double min_y = *std::min_element(y,y+n);
    double max_y = *std::max_element(y,y+n);

    int arr_length = ( (double)(max_x - min_x ) / 0.1 ) + 5;
    double new_x[arr_length];
    double new_y[arr_length];

    int k = 0;
    for ( int i = 0; i < n-1; i++ )
    {
        for ( double j = x[i]; j <= x[i+1]; j += 0.1 )
        {
            new_x[k] = j;
            new_y[k] = ( (double)( y[i+1]-y[i] ) / ( x[i+1]-x[i] ) )*( j - x[i] )+y[i];
            k++;
        }
    }

    new_x[arr_length-1] = x[n-1];
    new_y[arr_length-1] = y[n-1];


    //for ( int i = 0; i < arr_length; i++)
        //cout << "new_x[" << i << "] = " << new_x[i] << "   " << "new_y[" << i << "] = " << new_y[i] << "\n";

    Agrawal(new_x,new_y,arr_length,1);

}

int main()
{
    //cout << "\n" <<hausdorffDistance(7,3,1,1,5,1) << endl;

    //cout << "\n" <<hausdorffDistance(5,1,1,1,7,3) << endl;


    //cout << "\n" <<hausdorffDistance(4,7,1,5,7,6) << endl;
    //cout << "\n" <<hausdorffDistance(4,6.1,1,5,7,6) << endl;




    //double x[] = {1,5,7};

    //double y[] = {1,1,3};


    //double x[] = {1,4,7,10,15,16,20};

    //double y[] = {5,7,6,10,1,2,3};


    double x[] = {1,4,7,10,15,16,20};

    double y[] = {5,6.1,6,10,1,2,3};


    //Agrawal(x,y,7,1);

    NewAlgAgrawal(x,y,7);




    //cout << AngelsOfVectors(5,1,7,3,5,1,1,1) << "\n";

    //cout << AngelsOfVectors(4,1,2,3,4,1,7,1) << "\n";

    //cout << AngelsOfVectors(7,1,10,3,7,1,4,1);

    return 0;
}
