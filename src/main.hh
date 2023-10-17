#include <vector>
#include <string>
class dog{
    public:
        dog(){
        }
        dog(std::string a, std::string b, int c){
            name = a;
            breed = b;
            age = c;
        }
        std::string name;
        std::string breed;
        int age;
        std::vector<char> chars;
};
