#include <iostream>
#include <string>
#include <sstream>

int main()
{
	//按特定字符分割
    std::stringstream strStream("112,119,,,110");
    std::string tempStr("");
    while (getline(strStream, tempStr, ',')) {
        std::cout << tempStr << std::endl;
    }
	
	//
	std::string findStr("112,119,,,110");
    if (findStr.find('@') != std::string::npos || findStr.find("%40") != std::string::npos) {
        std::cout << "Find !" << std::endl;
    }
	else{
		std::cout << " Not find !" << std::endl;
	}
	
	return 0;
}