#ifndef TREE_H
#define TREE_H
#pragma once
#include "main.h"
#include <string>
#include <regex>
using namespace std;
class HTNode
{
public:
	long weight;
	int parent, lchild, rchild;
	char theChar;
};


class HuffmanTree
{
private:
	HTNode* HTBase;
	string * HCodes;
	vector<char> result;
	int state;
	int root;
public:

	string * getHCodes();
	
	void HuffmanCoding(long weights[], char chars[],int n);
	void  Seclect(HTNode *HTBase, int scope, int &s1, int &s2);

	void oneMore(char);
	vector<char>* getResult();
	int getState();
	void clearResult();
};
#endif