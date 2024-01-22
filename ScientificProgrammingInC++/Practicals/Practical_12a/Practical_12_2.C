#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>

int main(void)
{
  std::string file;
  std::cout << "Enter filename: ";
  std::cin >> file;
  
  std::ifstream myFile(file.c_str(), std::ifstream::in);
  std::string text;

  while(myFile)
  {
    std::string line;
    std::getline(myFile, line);
    text += line;
  }
  
  std::vector<unsigned int> charCount(27,0);

  for(std::string::const_iterator charIt = text.begin() ; charIt != text.end() ; ++charIt )
  {
    if( *charIt > 96 && *charIt <= 122)
    {
      charCount[(*charIt)-96]++;
    }
    else if( *charIt > 64 && *charIt <= 90)
    {
      charCount[(*charIt)-64]++;
    }
  }
  
  size_t totalChars = std::accumulate(charCount.begin(), charCount.end(), 0);

  for(unsigned int i=1 ; i <= 26 ; i++)
  {
    float freq = charCount[i] / (float)totalChars;
    std::cout.precision(3);
    std::cout << (char)(i + 64) << ": " << freq*100 << "%" << std::endl;
  }
  
}
