#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;

	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}

bool isValidDelimiter(char ch)
{
   if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
       ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
       ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
       ch == '[' || ch == ']' || ch == '{' || ch == '}')
      return true;
   return false;
}

bool isvalidIdentifier(string str)
{
   if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' ||
       str[0] == '9' || isValidDelimiter(str[0]) == true)
      return false;
   return true;
}

bool isValidInteger(char str[])
{
   int i, len = strlen(str);
   if (len == 0)
      return false;
   for (i = 0; i < len; i++)
   {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
         return false;
   }
   return true;
}
bool isRealNumber(char str[])
{
   int i, len = strlen(str);
   bool hasDecimal = false;
   if (len == 0)
      return false;
   for (i = 0; i < len; i++)
   {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
         return false;
      if (str[i] == '.')
         hasDecimal = true;
   }
   return hasDecimal;
}

int main(){
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("program.txt");
	int i,j=0;

	if(!fin.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}

	while(!fin.eof()){
   		ch = fin.get();

		for(i = 0; i < 6; ++i){
   			if(ch == operators[i])
   				cout<<ch<<" is operator\n";
   		}

   		if(isalnum(ch) || ch == '.'){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
            buffer[j] = '\0';
            j = 0;

            if(isKeyword(buffer) == 1)
                cout<<buffer<<" is keyword\n";
            else if(isValidInteger(buffer) == true)
                cout<<buffer<<" is integer\n";
            else if(isRealNumber(buffer) == true)
                cout<<buffer<<" is real number\n";
            else if(isvalidIdentifier(buffer) == true)
                cout<<buffer<<" is valid identifier\n";
            else
                cout<<buffer<<" is invalid identifier\n";
   		}

	}

	fin.close();

	return 0;
}
