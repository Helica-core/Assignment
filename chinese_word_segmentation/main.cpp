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
int TOTAL_WORD_NUM = 0;

struct Idf_word{
    string word;
    double idf;
    double w;
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

void separate(const char *file_name,map<string,int> &save_word)
{
    char text[1024][100];
    char wordlist[4096][12],word[4096][12];
    cout << file_name << endl;
    int t=0;
    int coun = 0;
	FILE *txt=fopen(file_name,"r");
	char new_file[128];
	strcpy(new_file,string(string(file_name)+".new.txt").c_str());

    FILE *pNEW_FILE=fopen(new_file,"w");

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
        TOTAL_WORD_NUM += c;
        while(c>=0)
        {
            fprintf(pNEW_FILE,"%s/",word[c]);
            c--;
            /*
            if(c!=0)
            {

                //printf("%s/",wordlist[c]);
                fprintf(pNEW_FILE,"%s/",wordlist[c]);
                if(!save_word.count(wordlist[c]) )
                    save_word.insert(pair<string,int>(wordlist[c],1));
                else
                    save_word[wordlist[c]] ++;
                --c;
            }
            else
            {
                fprintf(pNEW_FILE,"%s",word[c]);
                //cout << wordlist[c] << endl;
                --c;
            }
            */
        }
        fprintf(pNEW_FILE,"\n");
    }

}

void for_each( int (&int_ref)[10] )
{
    for( int i=0; i<10; ++i )
        std::cout << int_ref[i] << std::endl;
}

bool word_search(map <string,int> &v,string word)
{
    map <string,int>::iterator it;
    for(it = v.begin();it != v.end();it++) if(it->first == word)
    {
        return true;
    }
    return false;
}

void get_filename(const char *dir ,vector <string> &file_list)
{
    //cout << "travel :" << dir << endl;

    WIN32_FIND_DATA wfd;
    HANDLE hFind;

    hFind = FindFirstFile(dir,&wfd);

    do{
        //cout << wfd.cFileName << endl;
        file_list.push_back(wfd.cFileName);
    }while(FindNextFile(hFind,&wfd));

    FindClose(hFind);
}

void travel_folder(map <string,int>* v_word)
{
    vector <string> folder_name;
    vector <string> file_list;
    vector <string>::iterator it,it2;
    map <string,int>::iterator it_m;
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


        //system("PAUSE");
        map<string,double> idf;
        map<string,int> cnt_word[1024];
        vector <Idf_word> final_idf;

        for(int i=0;i<num_doc;i++)
        {
            int tot_word_num = v_word[i].size();
            //cout << endl;
            //cout << "name:" << file_list[i+2] << "\twords:" << tot_word_num << endl;
            //cout << "-----------------------------------------------" <<endl;

            for(it_m = v_word[i].begin();it_m!=v_word[i].end();it_m++) if(it_m->first.size()>2)
            {
                if(!idf.count(it_m->first))
                {
                    idf.insert(pair<string,double>(it_m->first,1));
                    for(int j=0;j<num_doc;j++) if(word_search(v_word[j],it_m->first))
                    {
                        idf[it_m->first]+=1;
                    }
                    idf[it_m->first] = log((double)num_doc/idf[it_m->first])/log(2);
                }
                double tf = (double)it_m->second / tot_word_num;
                //final_idf.push_back(Idf_word(it_m->first,idf[it_m->first]));
                //cout << "word:" << it_m->first << "\tweight:" << tf*idf[it_m->first];
                //cout << "\tidf:" << idf[it_m->first] << "\ttf:" << tf << endl;
            }

        }

//        sort(final_idf.begin(),final_idf.end());
//        for(int i=0;i<final_idf.size();i++)
//        {
//            cout << final_idf[i].word << ":" << final_idf[i].idf << endl;
//        }
    }
}

int main()
{
    //freopen("log.txt","w",stdout);
    load_dic("dic.txt");

    map <string,int> word_list[4096];

    travel_folder(word_list);

    cout << "Done!" << endl;
    cout << "totla num:" <<TOTAL_WORD_NUM <<endl;
    //system("PAUSE");
}
