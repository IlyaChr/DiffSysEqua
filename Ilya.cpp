#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*Неявный модифицированный Метод Эйлера (O(h^2)) */

void makeRungeKutta(double* Y, double x1 , double x2,int k,int qua);
bool EpsCheck(double* P_TEMP , double* P , int qua,double eps);
double fun(double x, double* Y, int number );

const double EPS = 0.0000001; // точность решения метода итераций
const int QUA= 4;            //кол-во уравнений


/*Note
для работы программы нужно изменить QUA (кол-во уравнений)
задать начальные условия до вызова основного метода
изменить функцию fun

*/

int main()
{

    double x1 = 0.0;
    double x2 = 9.0;
    int k  = 5000;

    double* Y = new double[QUA];

    Y[0] = 1.0;
    Y[1] = 0.0;
    Y[2] = 3.0;
    Y[3] = 0.0;

    makeRungeKutta(Y,x1,x2,k,QUA);

    delete[] Y;
    return 0;
}



/**
    Y - решение с граничными условиями
    x1 , x2 - граница решения
    k - количество точек
    **/

    void makeRungeKutta(double* Y, double x1 , double x2,int k,int qua){


    ofstream write;
    write.open("data.txt");


    double h = abs(x2-x1)/k;

    double X = x1;

    double* P = new double[qua];

    double* P_TEMP = new double[qua];



    for (int i=0; i<k ; i++){


        cout  <<setw(10) <<  X  << setw(20)<< Y[0] <<endl;
        write << setw(10) <<  X  << setw(20) << Y[0] <<endl;

        X+=h;


        for (int j=0; j<qua ; j++){
        P[j] = Y[j] + h * fun(X, Y,j);
        }

        /*
        Метод простой итерации
        */
            do{

            for (int j=0; j<qua ; j++){
            P_TEMP[j] = P[j];
            }

            for (int j=0; j<qua ; j++){
            P[j] = Y[j] +  h * ( fun(X, Y,j) + fun(X + h , P,j))/2.0;
            }


            }while( !EpsCheck(P_TEMP , P , qua , EPS ) );


        for (int j=0; j<qua ; j++){
        Y[j] = P[j];
        }

    }

    write.close();

    delete[] P;
    delete[] P_TEMP;

    }




	double fun(double x, double* Y, int number ){


	    switch(number)
	    {
	        case 0:
            return Y[1];

            case 1 :
            return Y[2];

            case 2:
            return Y[3];

            case 3 :
            return
            3*(2*pow(sin(x),2)+cos(x))+16*pow(sin(x),2)-sin(x)*(-4*pow(sin(x),2) + 4* pow(cos(x),2) - cos(x))/2 +
    2*(sin(x)-16*cos(x)*sin(x))+4*cos(x)*sin(x)-sin(x)-16*pow(cos(x),2)+cos(x) -2*Y[3] + (Y[2]*sin(x))/2 - Y[1] - 3*Y[0];


            default:
            exit(EXIT_FAILURE);

	    }

	}



	bool EpsCheck(double* P_TEMP , double* P , int qua,double eps){

	double Temp = 0.0;

	bool flag = false;

        for (int i = 0 ; i<qua ; i++ ){

            Temp += abs(P_TEMP[i]-P[i])/qua;

        }

	if (Temp <= eps) flag = true;


	return flag;

	}

