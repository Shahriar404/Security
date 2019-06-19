#include <iostream>
#include<bits/stdc++.h>
using namespace std;
string input;
int minn,maxx;
char out[100];
void pass(int in,bool low,bool up, bool num, int len) // current index ,flag for lowercase , uppercase, numeric, length
{
    if(in>=len)
    {
        if(low && up && num) //all flag is on
        {
            for(int i=0;i<len;i++)
                cout<<out[i];

           cout <<endl;
        }
        return ;

    }

    for(int i=0;i<input.size();i++)//loop over input string
    {
       char c=input[i];
       if(c>='0' && c<='9')
       {
           out[in]=c;
           pass(in+1,low,up,1,len);//turn on the numeric flag
       }
       else
       {
           out[in]=c;
           pass(in+1,1,up,num,len);//on lowercase flag
           out[in]=toupper(c) ;// for same character combination with uppercase
           pass(in+1,low,1,num,len);//on uppercase flag
       }

    }


}
int main()
{

    freopen("out.txt","w",stdout);



   /*input
    abc123(characters in password)
    3 5 (min length - max length)
    */

  cin>>input>>minn>>maxx;

  for(int i=minn;i<=maxx;i++)
  {
      pass(0,0,0,0,i);// pass length min to max
  }

}
