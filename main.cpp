#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

class word {
		// kan klare op til 268435456 forskellige ord (4 byte - 4bit for at signalere størrelse)
		// not the most mememory effecient i know, but std::vec<bool> is mega broken
		bool data[4*8];
		size_t bitSize;
		uint8_t arr[4] = {0,0,0,0};

		public:
		word(int number){
				std::fill_n(data,4*8,0);
				int i = 0;
				while(number > 0){
						data[i] = number % 2;
						i++;
						std::cout << number % 2;
						number /= 2;
						
				}
				bitSize = i;
				std::cout << "\n";
		}

		word(bool *number, size_t size){
				*data = number;
				bitSize = size*8;
		}

		size_t size(){
				size_t size = std::ceil(bitSize/8.0);
				if(size == 0){
						return 1;
				}
				return size;
		}

		uint8_t* dataArr(){
				if(bitSize==0){
						return arr;

				}
				for(int i = 0 ; i < this->size() ; i++){
						for(int j = 0; j <=8;j++){
								if(data[j+i*8]){
										arr[i] += std::pow(2,j);
								}
						}
				}
				for(int i = 0; i <this->size();i++){
						std::cout << (int)arr[i] <<" : ";
				}
				std::cout << this->size() << "\n";
				return arr;
		}
};

void Compress(char* path, char* output){
		word test(125);
		test.dataArr();
		//open file
		std::ifstream InputFile (path);
		//Count words so most used words can be proitized.
		std::map<std::string, int> WordMap;
		for(std::string sentence; std::getline(InputFile,sentence);){
				std::stringstream sentenceStream(sentence);
				for(std::string word; std::getline(sentenceStream,word,' ');){
						WordMap[word]++;
				}
				WordMap["\n"]++;
		}
		InputFile.clear();
		InputFile.seekg(0);


		//sort into vector with most used word first.
		//slow temporary sort
		const int AmountOfWords = WordMap.size();
		std::string WordList[AmountOfWords];
		for(int i = 0; i < AmountOfWords; i++){
				std::string Biggest;
				for(auto const&word: WordMap){
						if(Biggest == ""){
								Biggest = word.first;
						}
						if(WordMap[Biggest]<word.second){
								Biggest = word.first;
						}
				}
				WordList[i] = Biggest;
				WordMap.erase(Biggest);
		}

		for(int i = 0; i < AmountOfWords; i++){
				std::cout << WordList[i]<<"\n";
		}
		//print dictionary array
		std::ofstream OutputFile(output);
		for(int i = 0; i < AmountOfWords; i ++){
				for(int j = 0; true; j++){
						OutputFile.put(WordList[i][j]);
						if(WordList[i][j] == 0){
								break;
						}
				}
		}
		//add spacer
		uint8_t spacer[2] = {255,255};
		OutputFile.write((char*)spacer,2);
		std::vector<std::string> dictionary(&WordList[0], &WordList[AmountOfWords]);

		//write actual text
		for(std::string sentence; std::getline(InputFile,sentence);){
				std::stringstream sentenceStream(sentence);
				for(std::string word; std::getline(sentenceStream,word,' ');){
						int postistion =  std::distance( dictionary.begin(), std::find(dictionary.begin(),dictionary.end(),word));
						std::cout << postistion << "\n";
						class word WordNumber(postistion);
						OutputFile.write((char*)WordNumber.dataArr(),WordNumber.size());
						OutputFile.flush();
				}
				class word LineChange(WordMap["\n"]);
				OutputFile.write((char*)LineChange.dataArr(),LineChange.size());
				OutputFile.flush();
		}
		OutputFile.close();
		InputFile.close();
		
}

/*
std::string *SortWords(std::map<std::string,int>){
}
*/

void Uncompress(std::string path){

}

int main(int argc, char *argv[]){

	if(argc > 3){

		if( std::string(argv[1])  == "-C"){
				Compress(argv[2],argv[3]);
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

