
#include "../h/tree.h"


	string * HuffmanTree:: getHCodes(){
		return HCodes;
	}
	
	void HuffmanTree:: HuffmanCoding(long weights[],char chars[], int n)
	{
		//weights stores n char weight, and put the result in  HCodes
		if (n <= 1)
			return;
		int m = 2 * n - 1;
		this->root = m;
		this->state = root;

		HTBase = new HTNode[m + 1];
		HTNode *p = HTBase + 1;
		int i = 1;
		int s1 = 0;
		int s2 = 0;
		cout<<"in hufcoding"<<endl;
		for (; i <= n; ++i, ++p)
		{
			p->weight = weights[i - 1];
			p->theChar = chars[i-1];
			//cout<<" "<<i<<":"<<(int)chars[i-1]<<" ";
			p->parent = p->lchild = p->rchild = 0;
		}

		for (; i < m; ++i, ++p)
		{
			p->weight = p->parent = p->lchild = p->rchild = 0;
			p->theChar = '\0';
		}

		for (i = n + 1; i <= m; ++i)
		{
			Seclect(HTBase, i - 1, s1, s2);
			HTBase[s1].parent = i;
			HTBase[s2].parent = i;
			HTBase[i].lchild = s1;
			HTBase[i].rchild = s2;
			HTBase[i].weight = HTBase[s1].weight + HTBase[s2].weight;
		}
		
		//get the code
		HCodes = new string[n];
		string cd;
		int length;
		int chil;
		int pare;
	
		for (i = 1; i <= n; i++)
		{
			length = n - 1;
			cd.assign(length, '2');
			for (chil = i, pare = HTBase[i].parent; pare != 0; chil = pare, pare = HTBase[pare].parent)
			{
				if (HTBase[pare].lchild == chil)
				{
					//cd.replace(length - 1, length - 1, "0");
					cd.at(length - 1) = '0';
					length--;
				}
				else
				{
					//cd.replace(length - 1, length - 1, "1");
					cd.at(length - 1) = '1';
					length--;
				}
			}
			HCodes[i-1] = regex_replace(cd, regex("2+"), "");
		}

	
		cout<<endl;
		cout<<"hcodes"<<endl;
		for(int i = 0;i<n;i++){
			//cout<<(int)chars[i]<<":"<<HCodes[i]<<" ";
		}
		cout<<endl;
		cout<<"endHufcode"<<endl;
	}

	void  HuffmanTree::Seclect(HTNode *HTBase, int scope, int &s1, int &s2)
	{
		int i = 1;
		HTNode *p;
		long w, w1 = __LONG_MAX__, w2 = __LONG_MAX__;
		for (; i <= scope; i++)
		{
			if (HTBase[i].parent != 0)
			{
				continue;
			}

			w = HTBase[i].weight;
			if (w < w2)
			{
				if (w < w1)
				{
					w1 = w;
					s1 = i;
				}
				else
				{
					w2 = w;
					s2 = i;
				}
			}
		}
	}
	
	void HuffmanTree::oneMore(char biChar){
		if(biChar == 0){
			state = HTBase[state].lchild;
		}
		else{
			state = HTBase[state].rchild;
		}
			if(HTBase[state].lchild == 0 ){//get one
				char a = HTBase[state].theChar;
				result.push_back(a);
				//cout<<state<<":"<<(int)HTBase[state].theChar<<" ";
				state = root;
			} 
	}
	
	vector<char>* HuffmanTree::getResult(){
		return &result;
	}
	void HuffmanTree:: clearResult(){
		result.clear();
	}
	int HuffmanTree::getState(){
		return state;
	}