#include"tools.h"
using namespace std;

int main(int argc, char **argv){

    char buf[SIZE];
    int fd = stoi(argv[0]);
    read(fd,buf,SIZE);
    close(fd);
    stringvec input = parse_input(buf);

    int price = calculate_result(input[0],input[2]);

    write_to_fifo(price,input[1]);


    
}