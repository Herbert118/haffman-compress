#include "tree.h"
#include "fileUtil.h"

typedef struct FileHeader{
char info[6];
long freq[256];
long fsize;
int lastNum;
}FileHeader;

class Encoding{
    private:
        string targetFile;
        string inputFile;
        string * hcodes;
        vector<char> chars;
        string tmpStr;
    public:
    Encoding(string,string);
    ~Encoding();
    void startEncoding();
    void calFreq(char*,long,long*);
    void buildTreeAndGetCodes(long *);
    string strToBiStr(char *,long);
    void saveCoding(string);
    void writeFileHeader(FileHeader*);
};

class Decoding{
    private:
    string crpFile;
    string normFile;
    HuffmanTree  tree;
    public:
    Decoding(string, string);
    ~Decoding();
    void startDecoding();
    FileHeader readFileHeader();
    void rebuildTree(long*freq);
    char* biToStr(char*biStr,long size,int lastNum,long &);
    void saveCoding(char*,long);

};
