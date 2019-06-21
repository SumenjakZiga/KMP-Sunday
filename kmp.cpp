#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//KMP
void KMPnext(string, int*, int);
void iskanjeKMP(string, int, string, int);

//Sunday
void tabelaZnakov(int*, string, int);
void iskanjeSunday(string, int, string, int);

int main(int agrv, char* argc[]){
	ifstream ifs(argc[3]);
	//ifstream ifs("vhod.txt");
	string text ( (istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>() ) ); //prebrana datoteka
	string pat=argc[2];
	//string pat="Lorem ipsum";
	
	/*for(int x=0; x<pat.length(); x++){
		cout<<next[x];
	}*/
	int neke=((int)*(argc[1]))-48;
	switch(neke){
		case 0:
			iskanjeKMP(text, text.length(), pat, pat.length());
			break;
		case 1:
			//string text="abcabcabcabbabcababcabc";
			//string pat="abcabc";
			iskanjeSunday(text, text.length(), pat, pat.length());
			break;
	}	
	
	return 0;
}

void KMPnext(string pat, int* next, int len){
	next[0]=0;
	//next[1]=0;
	for(int x=1, j=0; x<len; x++){
		if(pat[x]==pat[j]){
			next[x]=(++j)-1;
		}else
		{
			j=0;
			next[x]=j;
		}
	}
}

void iskanjeKMP(string text, int velText, string pat, int velPat){
	int next[pat.length()];
	KMPnext(pat, next, pat.length());
	
	for(int x=0, j=0; x<velText; x++){
		//cout<<"x: "<<x<<endl<<"j: "<<j<<endl<<text[x]<<pat[j]<<endl;
		if(text[x]==pat[j]){
			j++;
			if(j==velPat){
				cout<<x-j+1<<"\t";
				j=0;
			}
		}else{
			//cout<<"Presjakujem\n"<<"x pred: "<<x<<endl;
			x-=next[j];
			//cout<<"treuten next: "<<next[j]<<"trenuten x: "<<x<<endl;
			j=0;
		}
	}
}

void tabelaZnakov(int znaki[], string pat, int velPat){
	for(int x=0; x<128; x++)znaki[x]=velPat;
	for(int x=0; x<velPat; x++){
		znaki[int(pat[x])]=velPat-x-1;
	}
}

void iskanjeSunday(string txt, int velText, string pat, int velPat){
	int znaki[128];
	tabelaZnakov(znaki, pat, velPat);
	
	/*for(int x=0; x<127; x++){
		cout<<znaki[x];
		cout<<char(x)<<endl;
	}*/
	int z=0;
	for(int x=0, j=velPat-1, i=velPat-1; x<velText; x++){
		cout<<pat[j]<<txt[i]<<endl;
		cout<<j<<"  "<<i<<endl;
		if(pat[j]==txt[i]){
			z++;
			if(j==0){
				cout<<"ujemanje\n";
				j=velPat;
				i=velPat+x+1;
				z=0;
			}
			j--;
			i--;
		}else{
			cout<<"nej"<<endl;
			j=velPat-1;
			i+=znaki[txt[i]]+z;
			z=0;
		}
	}
}
