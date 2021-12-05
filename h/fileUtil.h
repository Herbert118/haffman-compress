#include "main.h"
#include <fstream>
class FileUtil
{
    private:
    ifstream fins;   
    ofstream fous;
    public:
    string read_s(string fin_name);
    void write_s(string fout_name,string str);
    char * read_b(string fin_name,long & size);
    long getFsize(string fin_name);
    void write_b(string fout_name,char* buffer,long size);
    void write_b_a(string fout_name,char*buffer,long size);
    char* read_b_a(string fin_name,long start, long size);
    void write_b_p(string fin_name,char*buffer,long start,long size);
};