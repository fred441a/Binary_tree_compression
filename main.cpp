#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void Compress(char* path, char* output){
		//open file
		std::ifstream InputFile (path);
		// make map of all words in file, and how often they are used
		std::map<std::string, uint32_t> WordMap;
		uint16_t UID = 1;
		//give each word an id and write it to file.
		std::vector<uint16_t> CompressedText;
		for(std::string sentence; std::getline(InputFile,sentence);){
				std::stringstream sentenceStream(sentence);
				for(std::string word; std::getline(sentenceStream,word,' ');){
						if(WordMap[word] == 0){
							WordMap[word]= UID;
							UID++;
						}
						CompressedText.insert(CompressedText.end(),WordMap[word]);
				}
		}
		std::ofstream OutputFile(output);
		//save wordId's in file
		for(auto const& word: WordMap){
				OutputFile.write((char*)&word.first,word.first.size()-1);
				OutputFile << " ";
				OutputFile.write((char*)&word.second,sizeof(word.second));
		}
		//make seperator
		uint8_t seperator[2] = {255,255};
		OutputFile.write((char*)seperator,2);
		for(int i=0; i < CompressedText.size();i++){
				OutputFile.write((char*)&CompressedText[i],sizeof(UID));
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

