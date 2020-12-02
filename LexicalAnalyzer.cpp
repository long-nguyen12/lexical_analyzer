#include <iostream>
#include <fstream>
#include <array>
#include <stdlib.h>
#include <string>
#include <ctype.h>

namespace valueIs
{
    bool keyword(const std::string& buffer)
    {
        const std::array<std::string,32> keywords = {"auto","break","case","char","const","continue","default",
                                "do","double","else","enum","extern","float","for","goto",
                                "if","int","long","register","return","short","signed",
                                "sizeof","static","struct","switch","typedef","union",
                                "unsigned","void","volatile","while"};
        unsigned int len = keywords.size();
        for(unsigned int i = 0; i < len; i++)
            if(buffer == keywords[i])
                return true;
        return false;
    }

    bool validDelimiter(const char& ch)
    {
        return ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}';
    }

    bool validIdentifier(const std::string& str)
    {
        return !(str.size() == 0 || str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' ||
                 str[0] == '8' || str[0] == '9' || validDelimiter(str[0]));
    }
    bool validInteger(const std::string& str)
    {
       unsigned int len = str.size();
       if (len == 0)
          return false;
       for(unsigned int i = 0; i < len; i++)
       {
          if((str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9') || (str[i] == '-' && i > 0))
             return false;
       }
       return true;
    }
    bool realNumber(const std::string& str)
    {
       int len = str.size();
       bool hasDecimal = false;
       if (len == 0)
          return false;
       for (int i = 0; i < len; i++)
       {
          if ((str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.') || (str[i] == '-' && i > 0))
             return false;
          if (str[i] == '.')
             hasDecimal = true;
       }
       return hasDecimal;
    }

    bool arithmeticOperator(const char& ch)
    {
        const std::string operators = "+-*/%=";
        unsigned int len = operators.size();
        for(unsigned int i = 0; i < len; i++)
            if(ch == operators[i])
                return true;
        return false;
    }
}

int main(){
	char ch;
	std::string buffer;
	std::ifstream ifile("program.txt");

	if(!ifile.is_open())
    {
		std::cout << "error while opening the file\n";
		exit(0);
	}

	while(ifile.get(ch))
    {
		if(valueIs::arithmeticOperator(ch))
            std::cout << ch << " is operator\n";
   		if(isalnum(ch) || ch == '.')
   			buffer += ch;
   		if((ch == ' ' || ch == '\n') && (buffer.size() > 0))
   		{
            if(valueIs::keyword(buffer))
                std::cout << buffer << " is keyword\n";
            else if(valueIs::validInteger(buffer))
                std::cout << buffer << " is integer\n";
            else if(valueIs::realNumber(buffer))
                std::cout << buffer << " is real number\n";
            else if(valueIs::validIdentifier(buffer))
                std::cout << buffer << " is valid identifier\n";
            else
                std::cout << buffer << " is invalid identifier\n";
            buffer = "";
   		}
	}

	ifile.close();
	return 0;
}
