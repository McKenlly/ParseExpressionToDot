#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <map>

#define MINUS 2
#define PLUS  2
#define MULTIPLICATION 3
#define DIVISION 3
#define SCOPE 1
std::set<char> SIGN = {'+', '-', '*', '/'};

int getPriority(const char &);
char* Parser(std::string&);
int main() {
//    std::cout << "Please, enter your correct arithmetic expression" << std::endl;
    std::string str;
    std::cin >> str;
    char *newStr = Parser(str);

    std::map<int, std::pair<char, bool> > map_;

    std::cout << "digraph G {" << std::endl;
   // std::cout << "\tnode[shape=plaintext];" << std::endl;
    for (int i = 0; i < str.size(); i++) {
        if (isalpha(newStr[i]) || SIGN.find(newStr[i]) != SIGN.end()) {
            std::cout << "\tNode" << i << "[label=\"" << newStr[i] << "\"];" << std::endl;
            map_[i].first = newStr[i];
            map_[i].second = false;
        }
    }

    free(newStr);
    std::vector<std::map<int, std::pair<char, bool> >::iterator> vecIt;

    while (map_.size() > 2) {
        for (auto i = map_.begin(); i != map_.end(); i++) {
            if (SIGN.find(i->second.first) == SIGN.end() || i->second.second == true) { continue;}
            auto it = i;
            int count = 0;
            int tokens = 0;
            do {
                it--;
                if (SIGN.find(it->second.first) == SIGN.end()) {
                    tokens++;
                }
                count++;
                vecIt.push_back(it);
            } while (it != map_.begin() && count < 2);
            if (count == 2) {
                i->second.second = true;
                std::cout << "\tNode" << i->first << " -> Node" << vecIt[0]->first <</* "[dir=none];" <<*/ std::endl;
                std::cout << "\tNode" << i->first << " -> Node" << vecIt[1]->first <</* "[dir=none];" <<*/ std::endl;
                map_.erase(vecIt[0]);
                map_.erase(vecIt[1]);
                vecIt.clear();
                break;
            }
        }
    }
    std::cout <<"}" << std::endl;

}

char* Parser(std::string& str) {
    std::stack<char> opers;
    size_t point = 0;
    char *outstring = (char *)malloc(sizeof(char)*(str.size()+1));
    for (auto curr_char : str)           
    {
      if(curr_char == ')') {
        while (!opers.empty()) {                                    
            if (opers.top() == '(') {
                opers.pop();
                break;
            }
            outstring[point++] = opers.top();
            opers.pop();
        }
      }
      
      if(curr_char >= 'a' && curr_char <= 'z')        
          outstring[point++] = curr_char;        
      
      if(curr_char == '(')                         
	        opers.push(curr_char);

      if(SIGN.find(curr_char) != SIGN.end()) {
        if(opers.empty())                     
            opers.push(curr_char);
        else                                 
        if(getPriority(opers.top()) < getPriority(curr_char))      
            opers.push(curr_char);      
        else                              
        {
          while((!opers.empty())&&(getPriority(opers.top()) >= getPriority(curr_char))) {
              outstring[point++] = opers.top();
              opers.pop();
          }
          opers.push(curr_char);           
        } 
      }
    }
    while (!opers.empty())               
        {
            outstring[point++] = opers.top();
            opers.pop();
        }    
    outstring[point]='\0';
//    std::cout << outstring << std::endl;
    return outstring;
}

int getPriority(const char &ch){
    switch(ch) {
        case '-': return MINUS;
        case '+': return PLUS;
        case '*': return MULTIPLICATION;
        case '/': return DIVISION;
        case ')':
        case '(': return SCOPE;
        default:  {
            std::cerr<< "Uncorrect expression\n";
            exit(1);
        }
    }
}
