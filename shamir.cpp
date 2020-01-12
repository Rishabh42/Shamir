#include<bits/stdc++.h>
using namespace std;
typedef vector< pair<int,int> > vectorPair; // list of pairs [(1,2),(3,4),(5,6)]
						// vectorPair[0].first -> 1 , vectorPair[0].second -> 2
int pNo=269; // pNo number
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
        int num=int(secretString);     //ASCII val of secretString string
        int a0=num;
        int a1=rand()%pNo;    // to stay within range
        vectorPair keysArr;
        for(int i=1;i<=4;i++)
        {
            keysArr.push_back({i,(a0+a1*i)%pNo});  //store 4 keys
        }
        // Finding two random indices to return keys
        int x=rand()%4,y=rand()%4; // 0-3 
        while(x==y)
        {
            x=rand()%4,y=rand()%4; // edge case when x==y
        }
        vectorPair result; // List of pairs , result 
        result.push_back(keysArr[x]);
        result.push_back(keysArr[y]);
        return result; // list of tuples. [(1,2),(3,4)]
    }
    char decrypt(vectorPair &keys) {
        // Constent term for so turns by solving manually , turns out to be.
        // -1*(y0*x1/(x0-x1) + y1*x0/(x1-x0))
        int x0=keys[0].first;
        int y0=keys[0].second;
        int x1=keys[1].first;
        int y1=keys[1].second;
        // Lagrange basis polynomial
        int ans= (y0*x1/(x0-x1)) + (y1*x0/(x1-x0));
        ans=-1*ans;
        if(ans<0)
            return char(pNo+ans);
        return char(ans%pNo);
    }

};

int main()
{
    // I have found that no byte datatype exists in C++. I am using char that is almost equivalent.
    // Source: https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
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

// https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing
// IDEon
