#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

main(){
	int fifo_server,fifo_client,frk;
	char *bufsend=(char*)malloc(200*sizeof(char));
	char *bufrecive=(char*)malloc(200*sizeof(char));

if(frk=fork()){ while(1){

	fifo_client=open("fifo_client",O_RDWR);
	if(fifo_client < 0){
		printf("Error in opening file");
		exit(-1);
	}

	strcpy(bufrecive,"");
 	read(fifo_client,bufrecive,200*sizeof(char));
 	puts(bufrecive);

	close(fifo_client);}

}else{ while(1){

	fifo_server=open("fifo_server",O_RDWR);
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}

	strcpy(bufsend,"");	
	gets(bufsend);
	write(fifo_server,bufsend,200*sizeof(char));
	
	close(fifo_server);}
	}
}
