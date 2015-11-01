#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PRINT(A, str) cout<<str<<A<<endl;

using namespace std;
int main(int argc, char *argv[]){
	int *p;
	char pathname[] = "/home/squee/FTOK/main.cpp";
	int shmid;
	int trig=1;
	int N,i;

	//Чтение аргумента
	if(argc!=2){
		printf("Put da N.\n");
		exit(1);
	}
	N=atoi(argv[1]);

	//Создание ключа
	key_t key = ftok(pathname, 0);
	if (key < 0){
		cout<<"Error, cant generate key"<<endl;
		cout<<strerror(errno)<<endl;
		exit(-1);
	}
	PRINT(key, "Key ")


	//Создание идентификатора или подключение к уже существующему
	if((shmid = shmget(key, sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
		if(errno != EEXIST){
			printf("Can\'t create shared memory\n");
			cout<<strerror(errno)<<endl;
			exit(-1);
    		}else{
        		if((shmid = shmget(key, sizeof(int), 0) )< 0){
            			printf("Can\'t find shared memory\n");
            			cout << strerror(errno)<<endl;
            			exit(-1);
			}
    			trig = 0;
    		}

    	}
	PRINT(shmid, "shmid ")

	//Создание ссылки на выделенный сегмент 
	if((p = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
		printf("Can't attach shared memory\n");
		cout<<strerror(errno)<<endl;
		exit(-1);
	}
	PRINT(p, "P ")

	//если идентификатор был только что создан, то устанавливает значение переменной в SM равым 1, иначе инкрементирует его N раз
	if (trig){
		(*p)=1;
    	}else{
		for(i=0;i<N;i++) (*p)++;
    	}
    	PRINT(*p, "[P] ")


	if(shmdt(p) < 0){
		printf("Can't detach shared memory\n");
		cout<<strerror(errno)<<endl;
		exit(-1);
    	}



    return 0;
}
