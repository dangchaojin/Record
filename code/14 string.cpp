#include <iostream>
#include <string>
#include <sstream>

int main()
{
	//按特定字符分割1:
    std::stringstream strStream("112,119,,,110");
    std::string tempStr("");
    while (getline(strStream, tempStr, ',')) {
        std::cout << tempStr << std::endl;
    }
	
	
	//按特定字符分割2:
    std::string str("dasd,sda ,da.   sad");
    std::regex re(",");
    std::vector<std::string> ss = std::vector<std::string>{std::sregex_token_iterator(str.begin(), str.end(), re, -1),
                                                 std::sregex_token_iterator()};

	//按特定字符分割3:(需要使用string.h)											 
    char str[] = "hello world look";
    char *p;
    p = strtok(str, " ");
    while (p) {
        std::cout << p << std::endl;
        p = strtok(NULL, " ");
    }
	
	std::string str("dasfafasdd asd as asd c");
	std::string delim(" ");
	std::vector<std::string> res;
	if("" == str){
		return 0;
	}
	char *strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());
	
	char *d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		std::string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
	delete strs;
	delete d;
	
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