#include "includes.h"
#include "lzw.h"

void Menu(){
    std::cout << "write 0 for exit" << std::endl; 
    std::cout << "write 1 for use in_file and out_file for code" << std::endl; 
    std::cout << "write 2 for use in_file and out_file for decode" << std::endl;
}

int main (){

    std::ofstream out;
    std::ofstream in;

    LZW zip;
    Menu();

    unsigned short int act = 5;
    std::string tmpfn1;
    std::string fn1;
    std::string fn2;
    std::string tmp;

    while (act != 0){
        std::cin >> act; 
        switch (act){
        case 1:{ //code infile -> outfile проверить файлом или  // открываются два файла на вывод возможно с удалением всего что внутри !!!!
            std::cout << "Enter the file name to compress." << std::endl;
            std::cin >> fn1;

            std::ofstream out(fn1 + ".z",std::ios::binary);
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

            std::ifstream in(fn1);//std::ios_base::in|std::ios_base::binary
            std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
            std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

            zip.code();

            std::cin.rdbuf(cinbuf);   //reset to standard input again
            std::cout.rdbuf(coutbuf); //reset to standard output again
            break;
        }
        case 2:{ //decode infile -> outfile
            std::cout << "Enter the file name to decompress." << std::endl;
            std::cin >> fn1;

            if (fn1.back() != 'z' || fn1[fn1.length() - 2] != '.'){
                std::cout << "Bad file " << std::endl;
                return 0;
            }

            fn2 = fn1;
            fn2.erase(fn2.length() - 2, fn2.length() - 1);
           
            std::ofstream out(fn2 + ".txt");
            std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

            std::ifstream in(fn1,std::ios_base::binary);
            std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
            std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

            zip.decode();

            std::cin.rdbuf(cinbuf);   //reset to standard input again
            std::cout.rdbuf(coutbuf); //reset to standard output again
            break;
        }
        default:
            return 0;
            break;
        }
        Menu();
    }
    return 0;
}




