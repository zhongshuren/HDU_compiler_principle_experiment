#include<bits/stdc++.h>
using namespace std;

const string delimiterList=",;()[]{}";
const string opcharList="!+-*/%=<>&|";
const set<string> keywordList={"","if","while","break","continue","return","int","const","void","else"};
const set<string> operatorList={"","!","+","-","*","/","%","=","==","!=","<",">","<=",">=","&&","||"};
const vector<string> wordType={"","ID","NUM","OPERATOR","DELIMITER"};

string line,error;
bool isAnnotation=0;
vector<pair<int,string> >wordList;

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

void addWord(int type,string value){
    if(isAnnotation)return;
    //if(type>2)return;
    wordList.push_back(make_pair(type,value));
}

int main(int argc, char **argv){
    if(argc==2)freopen(argv[1],"r",stdin);
    int lineIndex=1;
    vector<string> lineList;
    while(getline(cin,line)){
        lineList.push_back(line);
        int len=line.length(),p=0;
        while(p<len){
            if(isspace(line[p]))p++;
            if(isalpha(line[p])){
                string token="";
                while(isalnum(line[p]) || line[p]=='_')token+=line[p++];
                if(keywordList.find(token)!=keywordList.end()){
                    addWord(0,token);
                }else addWord(1,token);
            }
            if(isdigit(line[p])){
                string token="";
                bool isx=0;
                while(isxdigit(line[p]) || line[p]=='x' || line[p]=='X'){
                    token+=line[p];
                    if(line[p]=='x' || line[p]=='X'){
                        if(token=="0x" || token=="0X")isx=1;
                    }
                    if(isalpha(line[p]) && !isx){
                        error="Error: invalid number at line "+to_string(lineIndex)+": "+token;
                    }
                    p++;
                }
                addWord(2,dec(token));
            }
            if(ispunct(line[p])){
                if((int)delimiterList.find(line[p])!=-1 && (int)opcharList.find(line[p])!=-1){
                    error="Error: undefined character at line "+to_string(lineIndex)+": "+line[p];
                }
                string token="";
                int last=p;
                while(ispunct(line[p]))token+=line[p++];
                if(token.substr(0,2)=="//")break;
                if(token.substr(0,2)=="/*"){
                    isAnnotation=1;
                    break;
                }
                if(token.substr(0,2)=="*/"){
                    if(isAnnotation==0){
                        error="Error: absence of /* at line "+to_string(lineIndex)+": ";
                    }
                    isAnnotation=0;
                    p=last+2;
                    continue;
                }
                if(operatorList.find(token)!=operatorList.end()){
                    addWord(3,token);
                }else if((int)delimiterList.find(token)!=-1){
                    addWord(4,token);
                }else{
                    error="Error: undefined operator at line "+to_string(lineIndex)+": "+token;
                }
            }
        }
        lineIndex++;
    }
    for(int i=0;i<(int)lineList.size();++i){
        cout<<lineList[i]<<endl;
    }
    if(isAnnotation==1){
        error="Error: absence of */ at line "+to_string(lineIndex)+": ";
    }
    if(error.empty()){
        cout<<"Words: "<<endl;
        for(int i=0;i<(int)wordList.size();++i){
            if(wordList[i].first==0)cout<<"<"<<wordList[i].second<<">";
            else if(wordList[i].first<=4)cout<<"<"<<wordType[wordList[i].first]<<","<<wordList[i].second<<">";
            if(i<(int)wordList.size()-1)cout<<", ";
        }
    }else cout<<error<<endl;
    return 0;
}
