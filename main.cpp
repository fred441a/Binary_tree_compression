#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class word {
  // kan klare op til 268435456 forskellige ord (4 byte - 4bit for at signalere
  // størrelse) not the most mememory effecient i know, but std::vec<bool> is
  // mega broken
  bool data[4 * 8];
  size_t bitSize;
  uint8_t arr[4] = {0, 0, 0, 0};

public:
  word(uint32_t number) {
    std::fill_n(data, 4 * 8, 0);
    int i = 0;
    while (number > 0) {
      if (i == 7 || i == 15 || i == 23) {
        data[i] = 1;
        i++;
      } else {
        data[i] = number % 2;
        i++;
        number /= 2;
      }
    }
    bitSize = i;
  }

  word(uint8_t *number, size_t size) {
    std::fill_n(data, 4 * 8, 0);
    for (int i = 0; i < size; i++) {
      int tempNum = number[i];
      int j = 0;
      while (tempNum > 0) {
        data[i * 8 + j] = tempNum % 2;
        j++;
        tempNum /= 2;
      }
    }

    bitSize = size * 8;
  }

  size_t size() {
    size_t size = std::ceil(bitSize / 8.0);
    if (size == 0) {
      return 1;
    }
    return size;
  }

  uint32_t number() {
    uint32_t ReNumber = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        if (data[i * 8 + j]) {
          ReNumber += std::pow(2, i * 7 + j);
          std::cout << "1";
        } else {
          std::cout << "0";
        }
      }
    }
    std::cout << "\n";
    return ReNumber;
  }

  uint8_t *dataArr() {
    if (bitSize == 0) {
      return arr;
    }
    for (int i = 0; i < this->size(); i++) {
      for (int j = 0; j < 8; j++) {
        if (data[j + i * 8]) {
          arr[i] += std::pow(2, j);
        }
      }
    }
    for (int i = 0; i < this->size(); i++) {
    }
    return arr;
  }
};

void Compress(char *path, char *output) {
  // open file
  std::ifstream InputFile(path);
  // Count words so most used words can be proitized.
  std::map<std::string, int> WordMap;
  for (std::string sentence; std::getline(InputFile, sentence);) {
    std::stringstream sentenceStream(sentence);
    for (std::string word; std::getline(sentenceStream, word, ' ');) {
      WordMap[word]++;
    }
    WordMap["\n"]++;
  }
  InputFile.clear();
  InputFile.seekg(0);

  // sort into vector with most used word first.
  // slow temporary sort
  const int AmountOfWords = WordMap.size();
  std::string WordList[AmountOfWords];
  for (int i = 0; i < AmountOfWords; i++) {
    std::string Biggest;
    for (auto const &word : WordMap) {
      if (Biggest == "") {
        Biggest = word.first;
      }
      if (WordMap[Biggest] < word.second) {
        Biggest = word.first;
      }
    }
    WordList[i] = Biggest;
    WordMap.erase(Biggest);
  }

  for (int i = 0; i < AmountOfWords; i++) {
  }
  // print dictionary array
  std::ofstream OutputFile(output);
  for (int i = 0; i < AmountOfWords; i++) {
    for (int j = 0; true; j++) {
      OutputFile.put(WordList[i][j]);
      if (WordList[i][j] == 0) {
        break;
      }
    }
  }
  // add spacer
  uint8_t spacer[2] = {255, 255};
  OutputFile.write((char *)spacer, 2);
  std::vector<std::string> dictionary(&WordList[0], &WordList[AmountOfWords]);

  // write actual text
  for (std::string sentence; std::getline(InputFile, sentence);) {
    std::stringstream sentenceStream(sentence);
    for (std::string word; std::getline(sentenceStream, word, ' ');) {
      int postistion =
          std::distance(dictionary.begin(),
                        std::find(dictionary.begin(), dictionary.end(), word));
      class word WordNumber(postistion);
      OutputFile.write((char *)WordNumber.dataArr(), WordNumber.size());
      OutputFile.flush();
    }
    class word LineChange(WordMap["\n"]);
    OutputFile.write((char *)LineChange.dataArr(), LineChange.size());
    OutputFile.flush();
  }
  OutputFile.close();
  InputFile.close();
}

void Uncompress(std::string InputPath, std::string OutputPath) {
		word testWord(531);
  std::ifstream InputFile(InputPath);
  std::vector<std::string> Dictionary;
  // TODO add print on errors
  if (InputFile.is_open()) {
    // create a string with all the words in it
    std::string allWords;
    std::getline(InputFile, allWords, (char)255);
    std::stringstream DictionaryStream(allWords);
    // add all the words to dictionary arr
    for (std::string word; std::getline(DictionaryStream, word, (char)0);) {
      Dictionary.push_back(word);
    }
    /*
    if(InputFile.get() != (char)255){
                    std::cout << "There has been a mistake! \n";
    }
    */
    char byte;
    uint8_t wordBuffer[4] = {0, 0, 0, 0};
    size_t bufferSize = 1;
    while (InputFile.get(byte)) {
			std::cout << "byte: " << +byte <<  " Word: " << Dictionary[byte] << "\n";
      if (byte > (char)127) {
        wordBuffer[bufferSize] = byte;
        bufferSize++;
      } else {
        word bufferWord (wordBuffer, bufferSize);
		std::cout << bufferWord.number() << "  " << Dictionary[bufferWord.number()] << "\n";
        std::fill_n(wordBuffer, 4, 0);
        bufferSize = 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc > 3) {

    if (std::string(argv[1]) == "-C") {
      Compress(argv[2], argv[3]);
      return 0;
    }
    if (std::string(argv[1]) == "-U") {
      Uncompress(std::string(argv[2]), std::string(argv[3]));
      return 0;
    }
  }

  std::cout << "this is the help page!";

  return 0;
}
