#include "includes.h"
#include <string>
#include <unordered_map>

using id = unsigned short int;
const id MAX_UNSIGNED_SHORT = std::numeric_limits<id>::max(); // максимальное число id

class LZW{

private:
   
    std::unordered_map<std::string, id> codeDict; //словарь для метода кодирования
    std::unordered_map<id, std::string> decodeDict; //словарь для метода декодирования
    id eof = 26; // end of file 
    id next_code;
    id max_code; 
    
public:
    LZW(){
        max_code = MAX_UNSIGNED_SHORT;
        next_code = eof + 1; 
    }
    ~LZW(){

    }
    int code(){

        std::string str;
        std::string tmpStr;
        this->initDict();
        char letter;

       while(std::cin >> letter){
            tmpStr = str;
            str += letter;

            if (this->codeDict.find(str) == this->codeDict.end()){ // если нет такой строки в словаре 
                this->codeDict.insert(std::make_pair(str, this->next_code)); // то надо ее добавить, а код str без последней буквы вывести в cout 
                ++(this->next_code);
                str = letter;
                std::cout.write((char*)&(this->codeDict.find(tmpStr)->second), sizeof (this->codeDict.find(tmpStr)->second)); //изменяем тип second и отправляем его размер
                tmpStr.clear();

                if (this->next_code == this->max_code){ // проверяем на переполнение типа id слова в словаре
                    this->initDict();
                    str.clear();
                }
            }
        }
        if(!str.empty()){
            std::cout.write((char*)&(this->codeDict.find(str)->second), sizeof this->codeDict.find(str)->second);
        }
       return 0;
    }

    int decode(){
        std::string str;
        std::string tmpStr;
        this->initDict();
        id num = 0; // id последнего слова 
        id tmpNum = 0; // id предпоследнего слова 

       if (!std::cin.read((char *)&tmpNum, sizeof(id))){// если первый символ не считывается то файл пуст
           std::cout << "Empty file." << std::endl;
           return 0;
       }
       std::cout << this->decodeDict.find(tmpNum)->second;// выводим декодированную строку 
        while(std::cin.read((char *)&num, sizeof(id))){ 
            tmpStr = this->decodeDict.find(tmpNum)->second;
            if(this->decodeDict.size() == num ){
               //std::cerr << "if(this->decodeDict.size() == num ){ " << std::endl;
                tmpStr += tmpStr.front();
                this->decodeDict.insert(std::make_pair(this->next_code, tmpStr)); // добавляем tmpStr в словарь с следующим id
                ++(this->next_code);
                str = this->decodeDict.find(num)->second;
                std::cout << str;// выводим декодированную строку 
            }else if((this->decodeDict.size() < num)&&(num != 0)){
                    std::cerr << "ERROR: id does not exist in the dictionary." << std::endl;
                    break;
            }else{
                str = this->decodeDict.find(num)->second;
                std::cout << str;// выводим декодированную строку 
                tmpStr += str.front(); // берем из последней строки первую букву и добавляем ее в конец предпоследнего слова
                this->decodeDict.insert(std::make_pair(this->next_code, tmpStr)); // добавляем tmpStr в словарь с следующим id
                ++(this->next_code);
            }
            if(this->next_code == this->max_code - 1){
                if (!std::cin.read((char *)&tmpNum, sizeof(id))){ // до обнуления таблицы не считывается буквы - файл пуст
                    break;
                }
                this->initDict();
                if (this->decodeDict.find(tmpNum) != this->decodeDict.end()){
                    std::cout << this->decodeDict.find(tmpNum)->second;// выводим декодированную строку 
                    continue;
                }else{
                    std::cerr << "Dictionary initialization error." << std::endl;
                }
            }
            tmpNum = num;
        }
        return 0;
    }
    void initDict(){
        next_code = eof + 1;
        codeDict.clear();
        decodeDict.clear();
        
        for (id ch = 'a'; ch <= 'z'; ch++) {
            std::string str(1,static_cast<char>(ch)); //
            codeDict.insert(std::make_pair(str, ch - 'a'));
            decodeDict.insert(std::make_pair(ch - 'a', str));
        }
        codeDict.insert(std::make_pair("", eof));
        decodeDict.insert(std::make_pair(eof, ""));
        }
};






