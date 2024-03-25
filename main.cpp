#include "game.h"
#include <iostream>

int main() {
    int size = 0;
    int mins_count = 0;

    std::cout << "Input your matrix size: " ;
    std::cin >> size;

    do {
        std::cout << "Input mins count: ";
        std::cin >> mins_count;
    } while(mins_count <= 0 || mins_count >= (size * size) / 2);

    Game ob(size, mins_count);
    
    int** temp = new int*[size];
    for(int i = 0; i < size; ++i) {
        temp[i] = new int[size];
    }
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            temp[i][j] = 0;   
        }
    }
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            std::cout << temp[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    int indexI = 0;
    int indexJ = 0;
    //ob.print();
    do{
        
        std::cout << std::endl;
        std::cout << "input your indexes: ";
        do {
            std::cin >> indexI >> indexJ ;
        }while((indexI >= size || indexI < 0) || (indexJ >= size || indexJ < 0));
        ob.check(indexI, indexJ, temp);
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                std::cout << temp[i][j] << ' ';
            }
            std::cout << std::endl; 
        }
    }while(ob.get_mins_count() != ob.get_open() && ob.check(indexI, indexJ, temp));

    for(int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;    
    return 0;
}