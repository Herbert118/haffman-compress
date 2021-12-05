#include "../h/tree.h"
#include "../h/coding.h"
void test1(){

	string *HCodes;
	long weights[] = {1, 2, 3, 4};
	char chars[] = "abcd";
	int num = 4;
	HuffmanTree tree;
	tree.HuffmanCoding(weights,chars,4);
	for(int i = 0;i<num;i++){
		cout<< chars[i]<<" : "<<tree.getHCodes()[i+1]<<endl;
	}
	
}


void test2(){
	Encoding ec("g.png","g.hcrps");
	ec.startEncoding();
}

void test3(){
	Decoding d("g.hcrps","o.png");
	d.startDecoding();
}
void test4(){
	test2();
	cout<<endl<<sizeof(FileHeader);
	FileUtil fu;
	char * buff =  fu.read_b_a("test1.hcrps",0,sizeof(FileHeader));
	FileHeader* headp =  (FileHeader*)buff;
	cout<<endl<<headp->fsize;
}

inline char getBit(char bit,char i){
	return (bit>>i)&1;
}
void test5(){
	char a =-99;
	cout<<(int) a;
}

void showHelp(){
	cout<<"Usage\n"<<"haffCp [-c/-d] [file] [-o] [target]\n";
	cout<<"-c compress\n";
	cout<<"-f decompress\n";
}
int main(int argc, char* argv[])
{
	int o;
	string srcFile = "";
	string objFile = "";
	int compress = 0;
	int decompress = 0;

	if(argc > 5){
		cerr<< "Too many Argument"<<endl;
		return 0;
	}
	
	for(int i = 0;i < argc;i++){
		string a = argv[i];
		if(a.at(0) == '-'){// well may be switch is better , but I don't want to change now
			for(int j = 1; j<a.size();j++){
				//cout<<a.at(j);

				if(a.at(j) == 'h'){
					showHelp();
					return 0;				
				}
				if(i == argc-1){
					break;
				}
				if(a.at(j) =='c'){
					compress = 1;
					srcFile = argv[i+1];
				}
				else if(a.at(j) == 'd'){
					decompress = 1;
					srcFile = argv[i+1];
				}
				else if(a.at(j) == 'o'){
					objFile = argv[i+1];
				}
			}
		}

	}

	if(compress==1&&decompress==1){
		cerr<<"error: Conflict arguments"<<endl;
		return 1;
	}
	if(compress ==0&& decompress==0){
		cerr<<"error: Invalid arguments: no source file"<<endl;
		return 2;
	}
	if(objFile.empty()){
		cerr<<"error: Invalid argements: no object file"<<endl;
		return 3;
	}
	fstream fs;
	fs.open(srcFile);
	if(objFile.empty()){
		if(!fs.good()){
			cerr<<"source file not exist";
			return 4;
		}
	}

	if(compress){
		Encoding ec(srcFile, objFile);
		ec.startEncoding();
	}
	else{
		Decoding dc(srcFile,objFile);
		dc.startDecoding();
	}
}

