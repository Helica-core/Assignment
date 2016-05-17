#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

map <int ,string > ch_dic;
string t;

unsigned int ch_word_hash(const char *ch_word)
{
    unsigned int seed = 131;
    unsigned int res = 0;

    while(*ch_word)
    {
        res = res*seed + (256+(*ch_word++));
    }
    return (res & 0x7FFFFFFF);
}

void load_dic(const char *dic_name)
{
    FILE *fp = fopen(dic_name,"r");
    char word[64];

    while(feof(fp) == 0)
    {
        fgets(word,64,fp);
        int len = strlen(word);
        if(word[len-1] == '\n') word[len-1] = '\0';

        unsigned int ch_hash = ch_word_hash(word);

        cout << word <<" hash:"<<ch_hash<< endl;

        if(ch_dic.count(ch_hash))
        {
            cout << "gg,there have collusion" << endl;
        }
        else
        {
            ch_dic.insert(pair<int,string>(ch_hash,word));
        }
        t = word;
    }

}

bool ch_word_query(const char *ch_word)
{
    if(ch_dic.count(ch_word_hash(ch_word)))
        return true;
    return false;
}

int main()
{
    load_dic("input.txt");

    if(ch_word_query(t.c_str()))
        cout << "excited!" << endl;
    else cout << "I am angry" << endl;

}
