#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <windows.h>
#include <string>
#include <cmath>

using namespace std;
///////////////////////////////
map <int ,string > ch_dic;

struct Idf_word{
    string word;
    double idf;
    Idf_word(string _w,double _i) :word(_w),idf(_i){}
    bool operator < (const Idf_word &rhs) const
    {
        return idf < rhs.idf;
    }
};

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

        //cout << word <<" hash:"<<ch_hash<< endl;

        if(ch_dic.count(ch_hash))
        {
           // cout << "gg,there have collusion" << endl;

        }
        else
        {
           ch_dic.insert(pair<int,string>(ch_hash,word));

        }
    }

}

bool ch_word_query(const char *ch_word)
{
    if(ch_dic.count(ch_word_hash(ch_word)))
        return true;
    return false;
}
///////////////////////////////////////////////////

void mycopy(char a[],char b[],int c,int d)
{

    int i=0;
    while(c>=0)
    {
        b[i++]=a[d-c];
        c--;
    }
    b[i]='\0';
}

void separate(const char *file_name,vector <string> &save_word)
{
    char text[1024][1024];
    char wordlist[4096][12],word[4096][12];

    int t=0;
    int coun = 0;
	FILE *txt=fopen(file_name,"r");
	char new_file[128];
	strcpy(new_file,string(string(file_name)+".new.txt").c_str());

    //FILE *pNEW_FILE=fopen(new_file,"w");

    while((fscanf(txt,"%s",text[t++]))!=EOF)
        ;

	for(int cnt_line=0;cnt_line<t;cnt_line++)
    {
        int c=0;
        int i,j,t=0;
        int number=0;
        char temp[20];

        for(;text[cnt_line][number]!='\0';number++)
            ;
        i=number-1;

        while(i>=0)
        {

            if(i>=9)
            {
                for(j=9;j>1;j=j-1)
                {
                    mycopy(text[cnt_line],temp,j,i);
                    if(ch_word_query(temp)==1)                  //wfind为查找字符串是否存在于哈希表中
                    {
                        //printf("%s 匹配成功\n",temp);
                        strcpy(word[c++],temp);
                        strcpy(wordlist[coun++],temp);
                        i=i-j-1;
                        break;
                    }
                }
                if(j<=1&&text[cnt_line][i]<0)
                {
                   mycopy(text[cnt_line],temp,j,i);
                   strcpy(word[c++],temp);
                   strcpy(wordlist[coun++],temp);
                   i=i-2;
                }
                else if(j<=1&&text[cnt_line][i]>=0)
                {
                   mycopy(text[cnt_line],temp,0,i);
                   strcpy(word[c++],temp);
                   strcpy(wordlist[coun++],temp);
                   i=i-1;
                }
                else;

            }
            else
            {
                for(j=i;j>1;j=j-1)
                {
                    mycopy(text[cnt_line],temp,j,i);
                    if(ch_word_query(temp)==1)
                    {
                        //printf("%s 匹配成功\n",temp);
                        strcpy(word[c++],temp);
                        strcpy(wordlist[coun++],temp);
                        i=i-j-1;
                        break;
                    }
                }
                if(j<=1&&text[cnt_line][i]<0)
                {
                    mycopy(text[cnt_line],temp,j,i);
                    strcpy(word[c++],temp);
                    strcpy(wordlist[coun++],temp);
                    i=i-2;
                }
                else if(j<=1&&text[cnt_line][i]>=0)
                {
                    mycopy(text[cnt_line],temp,0,i);
                    strcpy(word[c++],temp);
                    strcpy(wordlist[coun++],temp);
                    i=i-1;
                }
            }
        }

    	c=c-1;
        coun=coun-1;
        while(c>=0)
        {
            if(c!=0)
            {
                //printf("%s/",wordlist[c]);
                //fprintf(pNEW_FILE,"%s/",wordlist[c]);
                save_word.push_back(wordlist[c]);
                //cout << wordlist[c] << endl;
                --c;
            }
            else
            {
                //fprintf(pNEW_FILE,"%s",word[c]);
                //cout << wordlist[c] << endl;
                --c;
            }
        }
        //fprintf(pNEW_FILE,"\n");
    }

}

void for_each( int (&int_ref)[10] )
{
    for( int i=0; i<10; ++i )
        std::cout << int_ref[i] << std::endl;
}

bool word_search(vector <string> &v,string word)
{
    vector <string>::iterator it;
    for(it = v.begin();it != v.end();it++) if(*it == word)
    {
        return true;
    }
    return false;
}

void get_filename(const char *dir ,vector <string> &file_list)
{
    cout << "travel :" << dir << endl;

    WIN32_FIND_DATA wfd;
    HANDLE hFind;

    hFind = FindFirstFile(dir,&wfd);

    do{
        cout << wfd.cFileName << endl;
        file_list.push_back(wfd.cFileName);
    }while(FindNextFile(hFind,&wfd));

    FindClose(hFind);
}

void travel_folder(vector <string>* v_word)
{
    vector <string> folder_name;
    vector <string> file_list;
    vector <string>::iterator it,it2;
    string addr = "/*";

    get_filename("C:/data_ch/*",folder_name);
    int cnt = 0;

    for(it = folder_name.begin();it!=folder_name.end();it++,cnt++) if(*it != "." && *it != "..")
    {
        file_list.clear();
        string dir = "C:/data_ch/" + *it + addr;
        cout << "path:" << dir << endl;
        get_filename(dir.c_str(),file_list);
        int num_doc = 0;

        for(it2 = file_list.begin();it2!=file_list.end();it2++) if(*it2!="."&&*it2!="..")
        {
            v_word[cnt].clear();
            cout << "analysis:" << "C:/data_ch/"+*it+"/"+*it2 << endl;
            separate(("C:/data_ch/"+*it+"/"+*it2).c_str(),v_word[num_doc++]);
        }

        map<string,double> idf;
        map<string,int> cnt_word[1024];
        vector <Idf_word> final_idf;

        for(int i=0;i<num_doc;i++)
        {
            for(it2 = v_word[i].begin();it2!=v_word[i].end();it2++) if(!idf.count(*it2) && it2->size()>2)
            {
                idf.insert(pair<string,double>(*it2,1));
                for(int j=0;j<num_doc;j++) if(word_search(v_word[j],*it2))
                {
                        idf[*it2]+=1;
                }
                idf[*it2] = log((double)num_doc/idf[*it2])/log(2);
                //cout << *it2<<": "<<idf[*it2] << endl;
                final_idf.push_back(Idf_word(*it2,idf[*it2]));
            }
        }
        sort(final_idf.begin(),final_idf.end());
        for(int i=0;i<final_idf.size();i++)
        {
            cout << final_idf[i].word << ":" << final_idf[i].idf << endl;
        }
        system("PAUSE");
    }
}

int main()
{
    freopen("log.txt","w",stdout);
    load_dic("dic.txt");
    vector <string> word_list[4096];
    //string path = "C:\Users\韩泽方\Desktop\大二下\数字内容安全\实验四\体育领域\体育分类测试文档";
    travel_folder(word_list);
    //separate("./test/news209792295.txt",word_list[1]);
    system("PAUSE");
}

/*
int main()
{
	int x=0;
	int t=0;
  	char text[100][1000];
  	char text2[10000];
	char word[10000][12];
	char wordlist[10000][12];
	FILE *txt=fopen("news209792295.txt","r");
	load_dic("词典.txt");
    while((fscanf(txt,"%s",text[t++]))!=EOF)
    ;


    while(x<t)
	{
	  separate(text[x],word,wordlist);
      ++x;
	}

    //separate(text2,word);

}
*/
