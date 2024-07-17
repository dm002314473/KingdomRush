#include "MainMenu.h"

void MainMenu::levelReader(int index)
{
    //novi sting "level" + index + ".txt"
    std::ifstream file(/*novi string*/);
    if (!file.is_open())
    {
        std::cerr << "Unable to open waves.txt" << std::endl;
        return;
    }

     std::string line;
    while (std::getline(file, line))
    {
        if(line != "stand position"){

        }
    }

    file.close();
}