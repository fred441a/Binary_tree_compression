#include <string>
#include <map>
#include <stdio.h>
#include <iostream>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


void CountWords (std::map<std::string, int> &PtrMap,char* FileChunk){
		static char wordBuffer[428];
		static int wordIndex;
		int i = 0;
		while(FileChunk[i]){
				if(FileChunk[i] < 0){
						PtrMap[std::string(wordBuffer)] ++;
						std::cout << wordBuffer << ":" << PtrMap[std::string(wordBuffer)] << "\n";
						break;
				}
				if(FileChunk[i] == ' '){
						wordBuffer[wordIndex] = 0;
						wordIndex = 0;
						PtrMap[std::string(wordBuffer)] ++;
						std::cout << wordBuffer << ":" << PtrMap[std::string(wordBuffer)] << "\n";
				}else{
						wordBuffer[wordIndex] = FileChunk[i];
						wordIndex++;
				}
				i++;
		}

}


void Compress(char* path){
		//open file
		FILE *InputFile = std::fopen(path,"r+");
		//create buffer to read file into
		char buffer[100];
		// read the first 100 characters of file into buffer
		size_t sizeLeft = fread(buffer,sizeof(*buffer),ARRAY_SIZE(buffer),InputFile);
		//if the file is over 100 characters (it probably is) keep reading until theres is less then 100 left
		std::map<std::string, int> WordCount;
		while(sizeLeft == 100){
				CountWords(WordCount, buffer);
				sizeLeft = fread(buffer,sizeof(*buffer),ARRAY_SIZE(buffer),InputFile);
		}
		CountWords(WordCount,buffer);
}


/*
std::string *SortWords(std::map<std::string,int>){
}
*/

void Uncompress(std::string path){

}

int main(int argc, char *argv[]){

	if(argc > 2){

		if( std::string(argv[1])  == "-C"){
				Compress(argv[2]);
				return 0;
		}
		if( std::string(argv[1]) == "-U"){
				Uncompress(std::string(argv[2]));
				return 0;
		}

	}

	std::cout << "this is the help page!";

	return 0;
}

