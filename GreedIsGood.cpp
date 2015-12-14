#include<iostream>
#include<string.h>
#include<cstdlib>
#include<fstream>
#include<iomanip>


using namespace std;

int main(int argc, char *argv[]){
	ifstream ifo;
	ofstream ofo;
	int i,j,num;
	char temp[20];
	char rtf[20];
	string str, buff, output;
	size_t f;
	char c;
	ifo.open("test.c");
	while(!ifo.eof()){
		str.clear();
		getline(ifo, str);
		for(i=1; i<argc; i++){
			strcpy(temp, "");
			strcpy(temp, argv[i]);
			strcpy(rtf, "");
			for(j=0; j< strlen(temp); j++){
				srand((int)temp[j]);
				num = ((int)'a') + rand() % ((int)'z'-(int)'a');
				c = (char)num;
				rtf[j]=c;
			}
			rtf[j]='\0';
			f=0;
			while(str.find(temp, f) != string::npos){
				buff.clear();
				f = str.find(temp, f);
				if( ( ( (str[f-1] < '0' || str[f-1] > '9') && (str[f-1] < 'A' || str[f-1] > 'Z') && (str[f-1] < 'a' || str[f-1] > 'z') ) ) && 
					( (str[f+strlen(temp)] < '0' || str[f+strlen(temp)] > '9') && (str[f + strlen(temp)] < 'A' || str[f + strlen(temp)] > 'Z') &&
 					(str[f+strlen(temp)] < 'a' || str[f+strlen(temp)] > 'z') ) ){
					buff = str.substr(0, f) + rtf + str.substr(f + strlen(temp));
					swap(str, buff);
				}else{
					f++;
				}
			}
		}
		output += (str + '\n');
	}
	ifo.close();

	ofo.open("test.c");
	ofo << output;
	ofo.close();

	return 0;
}
