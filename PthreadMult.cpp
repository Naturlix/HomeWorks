#include <iostream>
#include <cmath>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void* ret(void* args);
 
struct arg_type{
	int** id1;
	int** id2;
	int** id3;
	int i;
	int j;
	int m;
};



int main(int argc, char* argv[])
{
// Читаем аргументы и создаем 3 матрица NxM MxK и NxK -результирующую
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int k = atoi(argv[3]);

	int** Arr1;
	int** Arr2;
	int** Arr3;
	
        Arr1 = new int* [n];
	Arr2 = new int* [m];
	Arr3 = new int* [n];
      
        int i,j;
        for(i=0;i<n;++i) 
        	Arr1[i]=new int [m];
        	
        for(i=0;i<m;++i) 
        	Arr2[i]=new int [k];
        	
	for(i=0;i<n;++i) 
		Arr3[i]=new int [k];
		
	arg_type* args = new arg_type [n*k];
	pthread_t* thread=new pthread_t [n*k];

//Заполняем масивы
	for(i=0;i<n;i++)
                for(int j=0;j<m;++j)
                        Arr1[i][j]=rand() % 10;

	for(i=0;i<m;i++)
                for(int j=0;j<k;++j)
			Arr2[i][j]=rand() % 10;

	for(i=0;i<n;i++)
                for(int j=0;j<k;++j)
                        Arr3[i][j]=0;
//Выводим первые 2 масива

	cout << "Первая матрица:\n";
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                        cout<<Arr1[i][j]<<' ';
                cout<<endl;
        }

	cout << "Вторая матрица:\n";
        for(i=0;i<m;++i)
        {
                for(j=0;j<k;j++)
                        cout<<Arr2[i][j]<<' ';
                cout<<endl;
        }

//Подсчет элементов 3 матрицы:

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < k; j++)
		{
			args[i*n+j].id1 = Arr1;
			args[i*n+j].id2 = Arr2;
			args[i*n+j].id3 = Arr3;
			args[i*n+j].i = i;
			args[i*n+j].j = j;
			args[i*n+j].m = m;

			pthread_create (&thread[ i*n+j ], NULL, ret, (void*) &args[i*n+j]);
		}
    	}
    	
    	for (i = 0; i < n; i++)
		for (j = 0; j < k; j++)
    			pthread_join   (thread[ i*n+j ], NULL);

//Выводим результат

	cout << "Результат:\n";
        for(i=0;i<n;i++)
        {
                for(j=0;j<k;j++)
                        cout<<Arr3[i][j]<<' ';
                cout<<endl;
        }
        
        return 0;
}
 
void * ret(void* args)
{
	arg_type* arg= (arg_type*) args;
	int i=arg->i;
	int j=arg->j;
	int m=arg->m;
	int** mass1=arg->id1;
	int** mass2=arg->id2;
	int** mass3=arg->id3;
	
	int k = 0;
	for (k = 0; k < m; k++) 
		mass3[i][j] += mass1[i][k] * mass2[k][j];
}
