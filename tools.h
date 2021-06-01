#ifndef TOOLS_H
#define TOOLS_H
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
#include<sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <utility> 
#include <stdexcept>
#include <sstream> 
#include <limits> 


using namespace std;

#define MAX 1
#define MIN 0
#define SIZE 512

typedef std::vector<std::string> stringvec;
stringvec read_csv(std::string filename);
int return_date(char* date_str);
std::vector<int> parse_command(std::string command);
stringvec read_directory(const std::string& name);
int read_from_fifo(string fifo_path);
void write_to_fifo(int price, string fifo_path);
int return_max(vector<int> vec);
int return_min(vector<int> vec);
int get_maxOrmin_between_childs(string command,stringvec dir_vec,string pipe_name);
stringvec parse_input(char buf[SIZE]);
void create_process(string province_name,string pipe_name,string command, const char* argv);
int get_max(stringvec csv_file, int product_id, int start_date, int end_date);
int get_min(stringvec csv_file, int product_id, int start_date, int end_date);
int calculate_result(string shop_name,string command);
vector<int> parse_line(string line);

#endif