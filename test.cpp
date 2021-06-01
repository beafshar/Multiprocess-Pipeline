

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<sys/types.h>
#include<dirent.h>
#include<vector>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h> 

#include <fcntl.h>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <limits> 

using namespace std;
int read_from_fifo(string fifo_path){

    int fifo;
    if (fifo = open(&fifo_path[0], O_RDWR) < 0){
        printf("error in opening read fifo ");
        cout <<fifo_path<<endl;
        exit(1);
    }
    
    // char price_c[SIZE] = {0};
    string price_s;
    cout<<"read fifo: "<<fifo<<endl;
    if(read(fifo, &price_s, 512) < 0){
        printf("error in reading fifo ");
        cout <<fifo_path<<endl;
        exit(1);
    }
    close(fifo);
    unlink(&fifo_path[0]);
    int price = stoi(price_s);
    // cout <<"reaaad shop "<< price<< " pipe name " << fifo_path <<endl;
    return price;
    
}


int main(){
    read_from_fifo("./pipes/f-0-0-0-0-");
return 0;

}