#include<bits/stdc++.h>
using namespace std;

typedef vector< pair<int,int> > vectorPair;
int pNo=381; //random number

class SSSS {
    private:
    char secretString;
    int m,n;
    public:
    SSSS(char s,int m, int n)
    {
        secretString=s;
        this->m=m;
        this->n=n;
    }

    vectorPair encrypt() {
        int num=int(secretString);     //ASCII val of secretString
        int a=num;
        int b=1;
        vectorPair keysArr;
        for(int i=1;i<=4;i++)
        {
            keysArr.push_back({i,(a+b*i)%pNo});  //store 4 keys
        }
        int x=rand()%4,y=rand()%4; // to find keys 
        while(x==y)
        {
            x=rand()%4,y=rand()%4; // edge case when x==y
        }
        vectorPair result; 
        result.push_back(keysArr[x]);
        result.push_back(keysArr[y]);
        return result;
    }

    char decrypt(vectorPair &keys) {
    
        int x0=keys[0].first;
        int y0=keys[0].second;
        int x1=keys[1].first;
        int y1=keys[1].second;

        // Lagrange basis polynomial (https://e...content-available-to-author-only...a.org/wiki/Shamir%27s_Secret_Sharing)
        int ans= (y0*x1/(x0-x1)) + (y1*x0/(x1-x0));

        ans=-1*ans;
        if(ans<0)
            return char(pNo+ans);
        return char(ans%pNo);
    }

};

int main()
{
    char secretString[32];
    cin>>secretString;
    int i=0;
    bool verified=true;
    for(int i=0;i<strlen(secretString);i++)
    {
        SSSS algo(secretString[i],4,2);
        vectorPair result=algo.encrypt();
        char ans=algo.decrypt(result);
        if(ans!=secretString[i])
            {
                verified=false;
                break;
            }
    }
    if(verified)
        cout<<"Working"<<endl;
    else
    {
        cout<<"Not working"<<endl;
    }
    return 0;
}