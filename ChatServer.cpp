#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(){
//------creation of FIFO---------------
int file1,file2;

file1 = mkfifo("fifo_server",0666); 
if(file1<0) {
 printf("Unable to create a fifo");
 exit(-1);
 }

file2 = mkfifo("fifo_client",0666);
if(file1<0) {
 printf("Unable to create a fifo");
 exit(-1);
 }
//-------------------------------------


//-------------- open da gates--------------
int fifo_server,fifo_client, fork;

fifo_server = open("fifo_server",O_RDWR);
if(fifo_server<1) {
 printf("Error opening file");
 }

fifo_client = open("fifo_client",O_RDWR);
if(fifo_server<1) {
 printf("Error opening file");
 }
//------------------------------------------

char *buf=(char*)malloc(200*sizeof(char));

while(1){

strcpy(buf,"");

read(fifo_server,buf,200*sizeof(char));
puts(buf);
write(fifo_client,buf,200*sizeof(char));

}
close(fifo_server);
close(fifo_client);

}
