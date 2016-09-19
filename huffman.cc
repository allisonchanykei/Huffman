#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <string>
#include <bitset>
#include <cmath>
using namespace std;

struct node{
	int freq;
	char c;
	node* left;
	node* right;
};

class cmp{
public:
	bool operator()(const node* l1, const node* l2) const
	{
		return l1->freq > l2->freq;
	}
};

node* NewNode(int freq, char c = ' ', node* left = 0, node* right = 0){
	node* np = new node;
	np->freq = freq;
	np->c=c;
	np->left = left;
	np->right = right;
	return np;
}

vector<node*> counting(string input){
    vector<node*> count;
    int letters[27]= {0};

    for (unsigned int x = 0; x < input.length(); x++) { //see which letter is in the string
		int c = tolower(input[x]) - 'a';
		letters[c]++;
    }

    for (int x = 0; x < 26; x++) { //number of times of the letter appeared
        if (letters[x]) {
            char c = x + 'a';          
            count.push_back(NewNode (letters[x],c));
        }
    }
    
	for (unsigned int x = 0; x < input.length(); x++) { //count space
		if (input[x]==' '){
			letters[26]++;
			cout<<input[x]<<endl;
		}
    }
	count.push_back(NewNode(letters[26],' '));
	return count;
}

void prewalk(node* nd){
	if (nd == 0) return;
	cout<<nd->freq<<endl;
	if (nd->left)
		prewalk(nd->left);
	if (nd->right)
		prewalk(nd->right);
}

void code(node* nd, map <char,string> &m){ //assign codes to letters
	static string s="";
	if (nd->right){
		s=s+"1";
		code(nd->right,m);
		s.pop_back();
	}
	if (nd->left){
		s=s+"0";
		code(nd->left,m);
		s.pop_back();
	}
	if (nd->left==0 and nd->right==0){
		cout<<s<<" "<<nd->c<<endl;
		m.insert(pair<char,string>(nd->c,s));
	}
}

void lfree(node* root){
	if (root == 0) return;
	if (root->left)
		lfree(root->left);
	if (root->right)
		lfree(root->right);
	delete root;
	root = 0;
}

string bitstr(map <char,string> m,string input){ //return the input in a binary string
	cout<<input<<" "<<input.length()<<endl;
	string bitstring="";
	for (unsigned int x = 0; x < input.length(); x++) {
		char i =tolower(input[x]);
		string ext = m.find(i)->second;
		bitstring = bitstring + ext;
	}
	while (bitstring.length()%8!=0){
		bitstring = bitstring + "0";
	}
	return bitstring;
}

string btc(string s){ //turn binary string into characters
	string c;
	while (s.length()!=0){
		int decimal = bitset<8>(s).to_ulong();
		c=c+char(decimal);
		s.erase(s.begin(),s.begin()+8);
	}
	return c;
}
int main(){
	ofstream outf,outmap;
	ifstream inf;
	priority_queue<node*,vector<node*>, cmp> q ;
	//cout<<"Enter a string: ";
    string input;
    //input="mississippi river";
    getline(cin, input);
    //inf.open("text.txt",ios::in);
    //getline(inf, input);
    vector<node*> count=counting(input);
    map <char,string> m;
	for (unsigned int x=0;x<count.size();x++){
		cout<<count[x]->c<<" "<<count[x]->freq<<endl;
		q.push(count[x]);
	}
	cout<<endl;
	while (q.size()>1){ //adding the first 2 items in the queue until there is one item left
		int sum=0;
		node* nd=NewNode(sum);
		for (int x=0;x<2;x++){
			sum = sum + q.top()->freq;
			if (x==0) nd->left=q.top(); //assigning the node* to the left node
			if (x==1) nd->right=q.top();//assigning the node* to the right node
			cout<<q.top()->c<<" "<<q.top()->freq<<endl;
			q.pop();
		}
		nd->freq=sum;
		prewalk(nd);
		q.push(nd);
	}
	cout<<q.top()->c<<" "<<q.top()->freq<<endl;
	prewalk (q.top());
	code(q.top(),m);
	lfree(q.top());
	
	string bitstring=bitstr(m,input);
	cout<<bitstring<<endl;
	string cc=btc(bitstring);
	outf.open ("compressed.txt", ios::out);
	outf<<cc<<endl;
	outf.close();
	outmap.open("mymap.txt",ios::out);
	outmap<<input.length()<<endl;
	for (auto pos = m.begin(); pos != m.end(); ++pos) {
        outmap<<pos->first << " "<<pos->second << endl;
    }
	outmap.close();
	return 0;
}
