#include"tools.h"

using namespace std;

int main(int argc, char **argv){

    char buf[SIZE];
    int fd = stoi(argv[0]);
    read(fd,buf,SIZE);
    close(fd);
    stringvec input = parse_input(buf);
    stringvec dir_vec = read_directory(input[0]);

    for (int i = 0; i < dir_vec.size(); i++){
        create_process(input[0] + "/" + dir_vec[i],input[1]+ to_string(i)+ "-",input[2],"./city.out");
    }
    
    int price = get_maxOrmin_between_childs(input[2],dir_vec,input[1]);
    write_to_fifo(price,input[1]);

    return 0;
}