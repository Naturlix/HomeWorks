#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int shmid, N = atoi(argv[1]), i;
        key_t key = ftok(argv[0], 0); // генерируем ключ по имени файла
	int *p;

	//создаем SM
        if((shmid = shmget(key, sizeof(int), 0777 | IPC_CREAT | IPC_EXCL)) < 0)
        {
		//Если не создалось, проверяем, существует ли SM по данному ключу: если существует - подключаемся, инкрементируем. Если ошибка в другом, информируем
        	if(errno == EEXIST)
        	{
			shmid = shmget(key, sizeof(int), 0);
			p = (int*) shmat(shmid, NULL, 0);
			for (i = 0; i < N; i++) (*p)++;

        	}else printf("can't create SM");
	}else{
		//если SM создалось - подключаемся, инициализируем, инкрементируем
		p = (int*) shmat(shmid, NULL, 0);
		(*p) = 0;
		for (i = 0; i < N; i++) (*p)++;
	}
	//Выводим SM переменную
        printf("%d\n", *p);
     
     	//отключаемся от SM
	shmdt(p);
	return 0;
}
