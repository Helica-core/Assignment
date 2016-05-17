#include<iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
///////////////////////////////
map <int ,string > ch_dic;
string t;
int coun;
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
        t = word;
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

void separate(char text[],char word[][12],char wordlist[][12])
{
    int c=0;
	int i,j=0;
	int number=0;
	char temp[20];
	//printf("%s\n",text);
	for(;text[number]!='\0';number++)
        ;
	i=number-1;
	//printf("字数：%d\n",number/2);

	while(i>=0)
   {

	 if(i>=9)
	  {

		for(j=9;j>1;j=j-1)
		{
	     	mycopy(text,temp,j,i);
			if(ch_word_query(temp)==1)                  //wfind为查找字符串是否存在于哈希表中
			  {
  	             //printf("%s 匹配成功\n",temp);
  				 strcpy(word[c++],temp);
  				 strcpy(wordlist[coun++],temp);
  			     i=i-j-1;
				  break;
  			  }
		}
		if(j<=1&&text[i]<0)
		{
		   mycopy(text,temp,j,i);
	       strcpy(word[c++],temp);
	       strcpy(wordlist[coun++],temp);
           i=i-2;
        }
        else if(j<=1&&text[i]>=0)
        {
		   mycopy(text,temp,0,i);
	       strcpy(word[c++],temp);
	       strcpy(wordlist[coun++],temp);
           i=i-1;
        }
        else;
	  }
	  else{
  		       for(j=i;j>1;j=j-1)
	    	{
		     	mycopy(text,temp,j,i);
		     	  if(ch_word_query(temp)==1)
          			  {
		            	 //printf("%s 匹配成功\n",temp);
  				         strcpy(word[c++],temp);
						   strcpy(wordlist[coun++],temp);
  			             i=i-j-1;
				         break;
	                  }
		    }

        		if(j<=1&&text[i]<0)
	        	{
		             mycopy(text,temp,j,i);
	                 strcpy(word[c++],temp);
	                 strcpy(wordlist[coun++],temp);
                      i=i-2;
                }
                 else if(j<=1&&text[i]>=0)
                {
		              mycopy(text,temp,0,i);
	                  strcpy(word[c++],temp);
	                  strcpy(wordlist[coun++],temp);
                       i=i-1;
               }
                    else;

    	   }
   }

	c=c-1;
	coun=coun-1;
	while(c>=0)
	{
        if(c!=0)
        {
            printf("%s/",wordlist[c]);
	        --c;
        }
        else
        {
            printf("%s/",word[c]);
	        --c;
        }
	}
}
void for_each( int (&int_ref)[10] )
{
    for( int i=0; i<10; ++i )
        std::cout << int_ref[i] << std::endl;
}

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
