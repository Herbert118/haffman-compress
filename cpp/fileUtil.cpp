#include "../h/fileUtil.h"

string FileUtil::read_s(string fin_name){
     string result;
     this->fins.open(fin_name,ios::in);
     char c ;
     fins.get(c);
     while(!fins.eof()){     
     result += c;
     fins.get(c);
     }
     fins.close();

     return result;
}

void FileUtil::write_s(string fout_name,string str){
     this->fous.open(fout_name,ios::out);
     fous.write(str.c_str(),str.size());
     fous.close();
}
long FileUtil::getFsize(string fin_name){
     long fsize = 0;
     this->fins.open(fin_name,ios::binary);
     fins.seekg(0,ios::end);
     fsize = fins.tellg();
     fins.close();
     return fsize;
}
char * FileUtil::read_b(string fin_name,long &fsize){
     this->fins.open(fin_name,ios::binary);
     fins.seekg(0,ios::end);
     fsize = fins.tellg();
     char *buffer = new char[fsize];
     fins.seekg(0,fins.beg);
     fins.read(buffer,fsize);
     fins.close();
     return buffer;
}

void FileUtil::write_b(string fout_name,char * buffer,long size){
     fous.open(fout_name,ios::binary|ios::trunc);
     if(size == 0){
     fous.close();
          return;
     }
     fous.write(buffer,size);
     fous.close();
}

void FileUtil::write_b_a(string fout_name,char*buffer,long size){
     fous.open(fout_name,ios::binary|ios::app);
     fous.write(buffer,size);
     fous.close();
}

char* FileUtil::read_b_a(string fin_name,long start,long size){
     fins.open(fin_name,ios::binary);
     fins.seekg(start);
     char * buffer = new char[size];
     fins.read(buffer,size);
     fins.close();
     return buffer;
}

void FileUtil::write_b_p(string fout_name,char*buffer,long start, long size){
     fstream fs;//I dont't konw why it must be this and have to be put here
     fs.open(fout_name,ios_base::binary|ios_base::out|ios_base::in);
     fs.seekp(start,ios_base::beg);
     fs.write(buffer,size);
     fs.close();
}
