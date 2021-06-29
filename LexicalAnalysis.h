#include<bits/stdc++.h>
using namespace std;

const string delimiterList=",;()[]{}$";
const string opcharList="!+-*/%=<>&|";
const set<string> keywordList={"","if","while","break","continue","return","int","const","void","else"};
const set<string> operatorList={"","!","+","-","*","/","%","=","==","!=","<",">","<=",">=","&&","||"};
const vector<string> wordType={"","ID","NUM","OPERATOR","DELIMITER"};

string dec(string s){
    int base=10,x=0;
    if(s[0]=='0'){
        if(s[1]=='x' || s[1]=='X'){
            base=16;
            s.erase(0,2);
        }else base=8;
    }
    for(int i=0;i<(int)s.length();++i){
        x=x*base+s[i]-'0';
    }
    return to_string(x);
}

bool isDelimiter(char ch){
    return (int)delimiterList.find(ch)!=-1;
}

bool isOpchar(char ch){
    return (int)opcharList.find(ch)!=-1;
}


vector<pair<int,string> > getWord(string s){
    vector<pair<int,string> >wordList;
    int len=s.length(),p=0;
    while(p<len){
        if(isspace(s[p]))p++;
        if(isalpha(s[p])){
            string token="";
            while(isalnum(s[p]) || s[p]=='_')token+=s[p++];
            if(keywordList.find(token)!=keywordList.end()){
                wordList.push_back(make_pair(0,token));
            }else wordList.push_back(make_pair(1,token));
        }
        if(isdigit(s[p])){
            string token="";
            while(isxdigit(s[p]) || s[p]=='x' || s[p]=='X')token+=s[p++];
            wordList.push_back(make_pair(2,dec(token)));
        }
        if(isDelimiter(s[p])){
            string token="";
            int cnt=0;
            while(isDelimiter(s[p]) && cnt==0)token+=s[p++],cnt++;
            wordList.push_back(make_pair(4,token));
        }
        if(isOpchar(s[p])){
            string token="";
            int cnt=0;
            while(isOpchar(s[p]) && cnt==0)token+=s[p++],cnt++;
            wordList.push_back(make_pair(3,token));
        }
    }
    return wordList;
}
