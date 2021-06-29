#include<bits/stdc++.h>
#include"LexicalAnalysis.h"
using namespace std;

vector<pair<int,string> > wordList;
string line,error;
int cur=0;

map<string,vector<vector<string> > >table={
  {"E",{{"T","E'"},{"T","E'"},{},{},{},{},{},{}}}, 
  {"E'",{{},{},{"e"},{"A","T","E'"},{"A","T","E'"},{},{},{"e"}}},
  {"T",{{"F","T'"},{"F","T'"},{},{},{},{},{},{}}},
  {"T'",{{},{},{"e"},{"e"},{"e"},{"M","F","T'"},{"M","F","T'"},{"e"}}},
  {"F",{{"i"},{"(","E",")"},{},{},{},{},{},{}}},
  {"A",{{},{},{},{"+"},{"-"},{},{},{}}},
  {"M",{{},{},{},{},{},{"*"},{"/"},{}}}
};

map<char,int> terminal={{'i',0},{'(',1},{')',2},{'+',3},{'-',4},{'*',5},{'/',6},{'$',7}};

int main(int argc,char **argv){
    if(argc==2)freopen(argv[1],"r",stdin);
    while(getline(cin,line)){
        line+="$";
        wordList=getWord(line);
        cur=0;
        error="";
        vector<string> stk={"E"};
        while(!stk.empty()){
            if(!error.empty())break;
            if(stk.back()==wordList[cur].second || (stk.back()=="i" && wordList[cur].first==1)){
                cur++;
                stk.pop_back();
            }else{
                int charId=0;
                if(wordList[cur].first!=1)charId=terminal[wordList[cur].second[0]];
                vector<string> value=table[stk.back()][charId];
                if(value.empty()){
                    error="error at "+stk.back()+", word position: "+to_string(cur++);
                    stk.pop_back();
                }else{
                    stk.pop_back();
                    for(int i=(int)value.size()-1;i>=0;--i){
                        if(value[i]=="e")continue;
                        stk.push_back(value[i]);
                    }
                }
            }
        }
        if(error.empty())cout<<"valid"<<endl;
        else cout<<"invalid"<<' '<<error<<endl;
    }
    return 0;
}
