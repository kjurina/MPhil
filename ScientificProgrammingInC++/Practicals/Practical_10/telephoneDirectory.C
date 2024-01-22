#include <map>
#include <iostream>

int main(void)
{
    std::map<std::string, std::string> directory;

    while (std::cin.good())
    {
        std::string name, number;
        std::cout << "Name: " << std::flush;
        std::getline(std::cin, name);
        if(name.size() == 0)
        {
            break;
        }
        std::cout << "Number: " << std::flush;
        std::getline(std::cin, number);

        if(directory.find(name) != directory.end())
        {
            std::cout << "Duplicate entry!" << std::endl;
        }
        else
        {
            directory[name] = number;
        }
    }

    std::cout << "Starting look-up" << std::endl;

    while (std::cin.good())
    {
        std::string name;
        std::cout << "Name: " << std::flush;
        std::getline(std::cin, name);
        if(name.size() == 0)
        {
            break;
        }  
        std::map<std::string, std::string>::const_iterator nameIter = directory.find(name);
        
        if (nameIter != directory.end())
        {
            std::cout << (*nameIter).second << std::endl;
        }
    }

    std::cout << "Starting reverse look-up" << std::endl;

    while (std::cin.good())
    {
        std::string number;
        std::cout << "Number: " << std::flush;
        std::getline(std::cin, number);
        if(number.size() == 0)
        {
            break;
        }
        std::map<std::string, std::string>::const_iterator directoryIter = directory.begin();
        const std::map<std::string, std::string>::const_iterator directoryEnd = directory.end();

        
    }
    

    


  return 0;
}
