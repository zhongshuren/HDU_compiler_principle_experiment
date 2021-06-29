#include<bits/stdc++.h>
#include"LexicalAnalysis.h"
using namespace std;

vector<pair<int,string> > wordList;
string line,error;
int cur=0;

void process(string s){
    if(!error.empty())return;
    if(s=="E"){
        if(wordList[cur].first==1 || wordList[cur].second=="("){
            process("T");
            process("E'");
        }else error="error at E, word position: "+to_string(cur++);
    }else if(s=="E'"){
        if(wordList[cur].second=="+" || wordList[cur].second=="-"){
            process("A");
            process("T");
            process("E'");
        }else if(wordList[cur].second==")" || wordList[cur].second=="$"){
            
        }else error="error at E', word position: "+to_string(cur++);
    }else if(s=="T"){
        if(wordList[cur].first==1 || wordList[cur].second=="("){
            process("F");
            process("T'");
        }else error="error at T, word position: "+to_string(cur++);
    }else if(s=="T'"){
        if(wordList[cur].second=="*" || wordList[cur].second=="/"){
            process("M");
            process("F");
            process("T'");
        }else if(wordList[cur].second==")" || wordList[cur].second=="+" || wordList[cur].second=="-" || wordList[cur].second=="$"){
            
        }else error="error at T', word position: "+to_string(cur++);
    }else if(s=="F"){
        if(wordList[cur].first==1){
            cur++;
        }else if(wordList[cur].second=="("){
            cur++;
            process("E");
            cur++;
        }else error="error at F, word position: "+to_string(cur++);
    }else if(s=="A"){
        if(wordList[cur].second=="+"){
            cur++;
        }else if(wordList[cur].second=="-"){
            cur++;
        }else error="error at A, word position: "+to_string(cur++);
    }else if(s=="M"){
        if(wordList[cur].second=="*"){
            cur++;
        }else if(wordList[cur].second=="/"){
            cur++;
        }else error="error at M, word position: "+to_string(cur++);
    }
}

int main(int argc, char **argv){
    if(argc==2)freopen(argv[1],"r",stdin);
    while(getline(cin,line)){
        line+="$";
        wordList=getWord(line);
        cur=0;
        error="";
        process("E");
        if(error.empty())cout<<"valid"<<endl;
        else cout<<"invalid"<<' '<<error<<endl;
    }
    return 0;
}
