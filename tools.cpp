#include"tools.h"

using namespace std;

void create_process(string province_name,string pipe_name,string command, const char* argv){
        int fd[2]; // 0 for read, 1 for write
        
        if (pipe(fd) < 0 ){
            printf("error occured in opening province pipe.\n");
        }

        int pid = fork();

        if (pid < 0){
            printf("error occured in creating province fork.\n");
        }
        if (pid == 0){
            //child
            close(fd[1]);
            string fd_char = to_string(fd[0]);
            char *pchar = &fd_char[0];
            char*  arg[] = {pchar,NULL};
            execv(argv,arg);
            
        }
        else{
            //parrent
            close(fd[0]);
            string buf = "#" + province_name + "#" + pipe_name + "#" + command + "#";
            char x[SIZE];
            strcpy(x,&buf[0]);
            char * myfifo = &pipe_name[0]; 
            mkfifo(myfifo, 0666); 
            write(fd[1],&x, SIZE);

        }  
}
stringvec parse_input(char buf[SIZE]){
    char dir_name_c[SIZE],pipe_name_c[SIZE],command_c[SIZE];

    sscanf(buf,"#%[^#]#%[^#]#%[^#]#",dir_name_c,pipe_name_c,command_c);
    string dir_name(dir_name_c);
    string pipe_name(pipe_name_c);
    string command(command_c);

    stringvec vec;
    vec.push_back(dir_name);
    vec.push_back(pipe_name);
    vec.push_back(command);

    return vec;
}

int get_maxOrmin_between_childs(string command,stringvec dir_vec,string pipe_name){
    vector<int> vec = parse_command(command);
    int price;

    vector<int> prices;

    for (int i = 0; i < dir_vec.size(); i++){
        price = read_from_fifo(pipe_name + to_string(i)+ "-");
        prices.push_back(price); 
    }

    if (vec[0] == MAX) price = return_max(prices);
    else price = return_min(prices);
    return price;
}

stringvec read_csv(string filename){

    stringvec result;
    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    std::string line;

    while(getline(myFile, line)){
        stringstream ss(line);
        result.push_back(line);  
    }
    myFile.close();

    return result;
}

int return_max(vector<int> vec){
    int price = -1;
    for (int i = 0; i < vec.size(); i++){
        price = max(price,vec[i]);
    }
    return price;
}

int return_min(vector<int> vec){
    int price = std::numeric_limits<int>::max();
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] != -1){
            price = min(price,vec[i]);
        }
    }
    
    return (price == std::numeric_limits<int>::max())? -1:price;
}

int read_from_fifo(string fifo_path){

    int fifo;
    const char *pchar = fifo_path.c_str();
    if ((fifo = open(pchar, O_RDONLY)) < 0){
        printf("error in opening read fifo ");
        exit(1);
    }
    
    char price_c[SIZE];

    int flag;
    if((flag = read(fifo, price_c, SIZE) )< 0){
        printf("error in reading fifo ");
        exit(1);
    }

    close(fifo);
    unlink(pchar);
    int price = stoi(price_c);
    return price;
}


void write_to_fifo(int price_i, string fifo_path){
    int fifo;
    const char *fifochar = fifo_path.c_str();
    if ((fifo = open(fifochar,O_WRONLY)) < 0){
        printf("error in opening write fifo\n");
        exit(1);
    }
    string s = to_string(price_i);
    const char *pchar = s.c_str();
    char kh[100];
    strcpy(kh, pchar);

    int flag;
    if ((flag = write(fifo, kh, SIZE)) < 0){
        printf("error in writing to pipe\n");
        exit(1);
    }
    close(fifo);
}

int return_date(char* date_str){
    char years_c[SIZE],months_c[SIZE],days_c[SIZE];
    sscanf(date_str,"%[^/]/%[^/]/%[^/]",years_c,months_c,days_c);

    int years = stoi(years_c) * 10000;
    int months = stoi(months_c) * 100;
    int days = stoi(days_c);
    int date = days + months + years;
    return date;
}

vector<int> parse_command(string command_s){
    vector<int> vec;
    char command[SIZE];
    strcpy(command,&command_s[0]);
    char type[SIZE],id_c[SIZE],start_c[SIZE],end_c[SIZE];
    int id,date_start,date_end;

    sscanf(command,"%[^ ] %[^ ] %[^ ] %[^ ]",type,id_c,start_c,end_c);

    string id_s(id_c);
    string start_s(start_c);
    string end_s(end_c);

    if (strcmp(type,"MAX") == 0)
        vec.push_back(MAX);
    else if (strcmp(type,"MIN") == 0)
        vec.push_back(MIN);

    id = stoi(id_s);
    vec.push_back(id);

    date_start = return_date(&start_s[0]);
    vec.push_back(date_start);

    date_end = return_date(&end_s[0]);
    vec.push_back(date_end);

    return vec;
}
stringvec read_directory(const std::string& name){
    stringvec v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        if (strcmp(dp->d_name,".") != 0 & strcmp(dp->d_name,"..") != 0)
            v.push_back(dp->d_name);
    }
    closedir(dirp);
    return v;
}

int get_max(stringvec vec, int product_id, int start_date, int end_date){

    int price_max = -1000;
    int price;
    vector<int> vec_line;
    for (int i = 1; i < vec.size(); i++){
        vec_line = parse_line(vec[i]);
        if (vec_line[1] == product_id && vec_line[0] >= start_date && vec_line[0] <= end_date){
            price = vec_line[2];
            price_max = max(price_max,price);
        }

    }
    return price_max == -1000? -1:price_max;
}

vector<int> parse_line(string line){
    char date_c[SIZE],id_c[SIZE],price_c[SIZE];
    sscanf(&line[0],"%[^,],%[^,],%[^,]",date_c,id_c,price_c);

    vector<int> vec;
    vec.push_back(return_date(date_c));
    vec.push_back(stoi(id_c));
    vec.push_back(stoi(price_c));
    return vec;
}

int get_min(stringvec vec, int product_id, int start_date, int end_date){

    int price_min = std::numeric_limits<int>::max();
    int price;
    vector<int> vec_line;
    for (int i = 1; i < vec.size(); i++){
        vec_line = parse_line(vec[i]);

        if ((vec_line[1] == product_id) && (vec_line[0] >= start_date) && (vec_line[0] <= end_date)){
            price = vec_line[2];
            price_min = min(price_min,price);

        }
    }

    return (price_min == std::numeric_limits<int>::max())? -1:price_min;
}


int calculate_result(string shop_name,string command){
    int price = -1;
    stringvec shop = read_csv(shop_name);
    vector<int> command_vec = parse_command(command);

    if(command_vec[0] == MAX){
        price = get_max(shop,command_vec[1],command_vec[2],command_vec[3]);
    }
    else if (command_vec[0] == MIN){
        price = get_min(shop,command_vec[1],command_vec[2],command_vec[3]);
    }

    return price;  
}