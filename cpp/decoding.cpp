#include "../h/coding.h"

inline char getBit(char bit, char i){
    return (bit>>i)&1;
}

Decoding::Decoding(string in, string out)
{
    this->crpFile = in;
    this->normFile = out;
}
Decoding::~Decoding()
{
}
void Decoding::startDecoding()
{
    const long bufferSize = 1000;
    cout<<"in startDecoding"<<endl;
    FileUtil fu;
	char * buff =  fu.read_b_a(crpFile,0,sizeof(FileHeader));
	FileHeader* headerp =  (FileHeader*)buff;
    rebuildTree(headerp->freq);
    cout<<"fsize "<<headerp->fsize<<endl;
    cout<<"lastNum"<<headerp->lastNum<<endl;
    FileUtil fu2;
    fu2.write_b(normFile,NULL,0);    
    long start;
    char * fileBuffer;
    long wsize;//save the write size
    char * normFileBuf;
    for(start = sizeof(FileHeader);start < headerp->fsize-bufferSize;start+=bufferSize){
        fileBuffer = fu2.read_b_a(crpFile,start, bufferSize);//coding with attention,every symbol is important
        normFileBuf = biToStr(fileBuffer, bufferSize,8,wsize);
        saveCoding(normFileBuf,wsize);
        delete fileBuffer;
        //delete normFileBuf; //normFileBuf will be deleted in biToStr
    }

    if(headerp->fsize%bufferSize!=0){

        fileBuffer = fu2.read_b_a(crpFile, start, bufferSize);
        normFileBuf = biToStr(fileBuffer, headerp->fsize%bufferSize,headerp->lastNum,wsize);
        saveCoding(normFileBuf,wsize);
        delete fileBuffer;
        //delete normFileBuf;
    }

}

void Decoding::rebuildTree(long *freq)
{
    vector<char> chars;
    vector<long> weights;
    cout<<"in rebuildTree"<<endl;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            chars.push_back((char)i-128);
            weights.push_back(freq[i]);
            cout<<i<<":"<<freq[i]<<" ";
        }
    }

    cout<<endl<<"chars.size"<<chars.size()<<endl;

    tree.HuffmanCoding(&weights[0], &chars[0], weights.size()); //not safe
    cout<<"end rebuild"<<endl;
}


char *Decoding::biToStr(char *bi, long size,int lastNum,long& convertSize)
{   
    int i;
    //cout<<endl;
    //cout<<"in biToStr"<<endl;
    tree.clearResult();
    for(i = 0; i<size-1;i++){
        for(int j = 7; j>=0;j--){
            tree.oneMore(getBit(bi[i],j));
            //cout<<(int)getBit(bi[i],j);
        }
    }

    i = size-1;
    for(int j = lastNum-1;j>=0;j--){
        tree.oneMore(getBit(bi[i],j));
        //cout<<(int)getBit(bi[i],j);
    }     
    //cout<<endl;
    vector<char> *result = tree.getResult();
    convertSize = result->size();
    return &(*result)[0];
}
void Decoding::saveCoding(char * normBuff,long writeSize)
{
    FileUtil fu;
    fu.write_b_a(normFile,normBuff,writeSize);
}