#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

typedef map <string,char> Cmap;

string bintodec(int d){
    string binary = bitset<8>(d).to_string(); //to binary
	return binary;
}
string bitstring (string s){
	string bs;
	for (unsigned int x=0;x<s.length();x++){
		bs=bs+bintodec(int(s[x]));
	}
	return bs;
}
string message (string s, Cmap m,unsigned long size){
	string mes="";
	while (!s.empty() and mes.length()<size){
		int x=0;
		string fs="";
		while (m.find(fs)==m.end()){
			fs= fs + s[x];
			x++;
		}
		mes = mes+m.find(fs)->second;
		s.erase(s.begin(),s.begin()+x);
	}
	return mes;
}
int main(){
	ifstream inf,inmap;
	Cmap m;
	inf.open("compressed.txt", ios::in);
	string s,bs,word;
	while (inf>>s){
		bs=bs+bitstring(s);
	}
	cout<<bs<<endl;
	inf.close();
	
	inmap.open("mymap.txt", ios::in);
	string strsize;
	getline(inmap,strsize);
	long intsize = atoi(strsize.c_str());
	while (getline(inmap,word)){
		char c = word[0];
		word.erase(word.begin(),word.begin()+2);
		string bnum = word;
		m.insert(pair<string,char>(bnum,c));
	}
	inmap.close();
    string d = message(bs,m,intsize);
    cout<<d<<endl;
	return 0;
}
