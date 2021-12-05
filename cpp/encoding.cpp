#include "../h/coding.h"

  
    Encoding::Encoding(string fileName,string target){
        this->inputFile = fileName;
        this->targetFile = target;
    }

    Encoding::~Encoding(){

    }

    void Encoding::startEncoding()
    {
        const long bufferSize = 1000;
        long fileSize;
        FileUtil fileUtil;
        fileSize = fileUtil.getFsize(inputFile);
        fileUtil.read_b(inputFile,fileSize);
        cout<<"fileSize"<<fileSize;

        long *freqArr = new long[256];
        for(int i = 0;i<256;i++){
            freqArr[i] = 0;
        }

        long start;
        char*fileBuffer;
        for(start = 0; start < fileSize-bufferSize; start+=bufferSize){        
        fileBuffer  = fileUtil.read_b_a(inputFile,start,bufferSize);           //memory is not ok
        calFreq(fileBuffer,bufferSize,freqArr);
            delete fileBuffer;
        }
        
        if(fileSize%bufferSize!=0){
            fileBuffer  = fileUtil.read_b_a(inputFile,start,bufferSize);           //memory is not ok
            calFreq(fileBuffer,fileSize%bufferSize,freqArr);
            delete fileBuffer;
        }

        buildTreeAndGetCodes(freqArr);        


        FileHeader header = {'h','c','r','p','s'};
        copy(freqArr,freqArr+256,header.freq);
        FileUtil fu2;
        fu2.write_b(targetFile,(char *)&header,sizeof(FileHeader));//occupy the space first

        long bitNum = 0;
        tmpStr = "";
        for(start = 0;start<fileSize-bufferSize; start+=bufferSize){
            fileBuffer = fileUtil.read_b_a(inputFile,start,bufferSize);
            string str = strToBiStr(fileBuffer,bufferSize);
            bitNum += str.size()-str.size()%8; 
            saveCoding(str);
            delete fileBuffer;
        }

        if(fileSize%bufferSize!=0){
            fileBuffer  = fileUtil.read_b_a(inputFile,start,fileSize%bufferSize);           //memory is not ok
            string str = strToBiStr(fileBuffer,fileSize%bufferSize);
            cout<<str<<endl;
            saveCoding(str);
            char last = stoi(tmpStr+string("").assign(8-tmpStr.size(),'0'),0,2);
            fileUtil.write_b_a(targetFile,&last,1);//write the last bit
            bitNum+=str.size();
            delete fileBuffer;
        }
        
        delete freqArr;

        int lastNum = tmpStr.size();
        long size_b = lastNum==0?bitNum/8:bitNum/8+1;
        (&header)->fsize = size_b;
        (&header)->lastNum = lastNum;
        cout<<"biStr size  "<<bitNum<<endl;
        cout<<"header fsize"<<header.fsize<<endl;
        cout<<"lastNum"<<header.lastNum<<endl;
        writeFileHeader(&header);

    }

    void Encoding:: calFreq(char * buff,long size,long freq[])
    {
        for(int i = 0;i<size;i++){
           freq[(int)buff[i]+128]++; //127 is offset//no 127 because of the trunc//no there is no stupid trunc//no it is 128 you numb
        }
        //cout<<endl;
    }

    void Encoding::buildTreeAndGetCodes(long * freq)
    { //memory is ok ,i think
        HuffmanTree tree;
        vector<long> weights; 
        for(int i = 0; i< 256; i++){
            if(freq[i]!= 0){
                this->chars.push_back(i-128);
                weights.push_back(freq[i]);
            }
        }
        for(int i = 0; i<chars.size();i++){
            cout<<(int)chars.at(i)<<" : "<<weights.at(i)<<"  ";
        }
        tree.HuffmanCoding(&weights[0],&chars[0],weights.size());//not safe
        this->hcodes = tree.getHCodes();
    }
    string Encoding::strToBiStr(char * buffStr,long size){
        //cout<<endl<<"in strToBiStr"<<endl;
        //cout<<"chars"<<chars.size()<<endl;
        //cout<<"size"<<size<<endl;
        string result = tmpStr;
        string convertArr[256];
        
        for(int i = 0; i<chars.size();i++){
            convertArr[(int)chars.at(i)+128] = hcodes[i];//to be faster, get the char, get the code 
            //cout<<(int)chars.at(i)+127<<" ";
        }  
        
        for(long i = 0; i<size;i++){
            result += convertArr[(int)buffStr[i]+128];
            //get the char , get the code
            //cout<< convertArr[(int)buffStr[i]]<<" ";
            //TODO:change to unsigned char
        }
        //cout<<"strToBiStrEnd"<<endl;
        //cout<<result.substr(0,15)<<endl;
        return result;   
    }
    
    void Encoding::writeFileHeader(FileHeader *headPtr){
        FileUtil f;
        f.write_b_p(this->targetFile,(char*)headPtr,0,sizeof(FileHeader));
    }
    void Encoding::saveCoding(string biStr){
        FileUtil fu;        
        const char * biStr_a =  biStr.c_str();
        
        int lastNum = biStr.size()%8;
        long size_w = biStr.size()/8;       
        char * buffer = new char[size_w];
        int i;
        for(i = 0;i<size_w;i++){
            buffer[i] = stoi(biStr.substr(i*8,8),0,2);
            //cout<<biStr.substr(i*8,8)<<endl;
        }
        string temp;
        tmpStr = biStr.substr(i*8,lastNum);
        //cout<<tmpStr<<endl;
        fu.write_b_a(this->targetFile,buffer,size_w);
    }

    
