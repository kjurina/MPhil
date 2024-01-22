#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iterator>

int main(void)
{
  std::ifstream file("PMs.txt", std::ifstream::in);

  std::vector<std::string> firstNames;
  std::vector<std::string> surnames;

  while(file)
  {
    std::string name;
    file >> name;
    if(!file)
    {
      break;
    }
    firstNames.push_back(name);
    file >> name;
    surnames.push_back(name);
  }
  
  std::vector<std::string>::iterator georgeIt = std::find(firstNames.begin(), firstNames.end(), "George");

  if( georgeIt != firstNames.end() )
  {
    size_t georgePosn = std::distance(firstNames.begin(), georgeIt);

    std::cout << "The " << georgePosn << " Prime Minister was George " << surnames[georgePosn] << std::endl;
  }

  std::vector<std::string>::iterator richardIt = std::find(firstNames.begin(), firstNames.end(), "Richard");

  if( richardIt != firstNames.end() )
  {
    size_t richardPosn = std::distance(firstNames.begin(), richardIt);

    std::cout << "The " << richardPosn << " Prime Minister was Richard " << surnames[richardPosn] << std::endl;
  }
  else
  {
    std::cout << "There have been no PMs called Richard" << std::endl;
  }
  
  size_t numCharles = std::count(firstNames.begin(), firstNames.end(), "Charles");
  std::cout << "There were " << numCharles << " PMs called Charles" << std::endl;

  std::vector<std::string>::iterator adjIter = firstNames.begin();

  while( adjIter != firstNames.end() )
  {
    adjIter = std::adjacent_find(adjIter+1, firstNames.end());
    if( adjIter != firstNames.end() )
    {
      size_t adjPosn = std::distance(firstNames.begin(), adjIter);
      std::cout << "PMs " << adjPosn << "(" << *adjIter << " " << surnames[adjPosn] << ") and "
		<< adjPosn+1 << "(" << *adjIter << " " << surnames[adjPosn+1] << ")" << std::endl;
    }
    
  }
  
}
