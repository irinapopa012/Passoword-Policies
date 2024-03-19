#include <iostream>
#include <string.h>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

class Policy
{
protected:
    bool isChecked;
public:
    virtual void check( const string &p) =0;
    bool getCheck() const
    {
        return isChecked;
    }
};
class LengthPolicy:public Policy
{ private:
    uint16_t minLength;
    uint16_t maxLength;
public:
    LengthPolicy(uint16_t min)
    {
        minLength=min;
        maxLength=255;
    }
    LengthPolicy(uint16_t min, uint16_t max) {
        minLength=min;
        maxLength=max;
    }
    void check(const string &p)
    {
        if(p.size()>=minLength && p.size()<=maxLength)
            isChecked=true;
        else isChecked=false;
    }
};
class ClassPolicy:public Policy
{private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t a)
    {
        minClassCount=a;
    }
    void check(const string &p)
    {int ok4=0;
        int ok1=0;
        int ok2=0;
        int ok3=0;
        int s=0;
        for(int i=0; i<p.size(); i++) {
            if (islower(p[i]))
                ok1=1;
            if (isupper(p[i]))
                ok2=1;
            if (isdigit(p[i]))
                ok3=1;

            if(!isalnum(p[i]))
                ok4=1;}
        if(ok1!=0)
            s++;
        if(ok2!=0)
            s++;
        if(ok3!=0)
            s++;
        if(ok4!=0)
            s++;

        if(s>=minClassCount)
            isChecked=true;
        else isChecked= false;
    }

};
class IncludePolicy:public Policy
{
private:
    char characterType;
public:
    IncludePolicy(char a)
    {
        characterType=a;

    }
    void check(const string &p)
    { int ok=0;
        if(characterType=='a')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(islower(p[i]))
                    ok=1;
            }
        }
        if(characterType=='A')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(isupper(p[i]))
                    ok=1;

            }

        }
        if(characterType=='0')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(isdigit(p[i]))
                    ok=1;
            }
        }
        if(characterType=='$')
        {
            for(int i=0; i<p.size(); i++)
                if(!isalnum(p[i]))
                    ok=1;
        }
        if(ok==1)
            isChecked=true;
        else isChecked=false;
    }

};

class NotIncludePolicy:public Policy
{
private:
    char characterType;
public:
    NotIncludePolicy(char a)
    {
        characterType=a;

    }
    void check(const string &p)
    { int ok=0;
        if(characterType=='a')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(islower(p[i]))
                    ok=1;
            }
        }
        if(characterType=='A')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(isupper(p[i]))
                    ok=1;

            }

        }
        if(characterType=='0')
        {
            for(int i=0; i<p.size(); i++)
            {
                if(isdigit(p[i]))
                    ok=1;
            }
        }
        if(characterType=='$')
        {
            for(int i=0; i<p.size(); i++)
                if(!isalnum(p[i]))
                    ok=1;
        }
        if(ok==0)
            isChecked=true;
        else isChecked=false;
    }


};
class RepetitionPolicy: public Policy
{
private:
    uint16_t maxCount;
public:  RepetitionPolicy(uint16_t a)
    { maxCount=a;

    }
    void check(const string &p) {
        int k = 1;
        int max = 0;
        for (int i = 1; i < p.size(); i++) {
            if (p[i - 1] == p[i]) {
                k++;
                if (k > max)
                    max = k;
            } else k = 1;

        }
        if(max<=maxCount)
            isChecked=true;
        else isChecked= false;

    }


};
class ConsecutivePolicy: public Policy
{
private:
    uint16_t maxCount;
public:  ConsecutivePolicy(uint16_t a)
    { maxCount=a;

    }
    void check(const string &p) {
        int k=1;
        int max=0;
        for(int i=1; i<p.size(); i++)
        {
            if(p[i-1]==p[i]-1)
            {k++;
                if(k>max)
                    max=k;

            }
            else k=1;
        }
        if(max<=maxCount)
            isChecked=true;
        else isChecked=false;
    }


};
string checkPassword (string p, vector<Policy*> v )
{ int ok=0;
    for(int i=0; i<v.size(); i++)
    {
        v[i]->check(p);
        if(v[i]->getCheck()) ok++;
    }
    if(ok==v.size())
        return "OK";
    else return "NOK";
}
int main()
{
    int n;
    string cerinta;
    int nr1, nr2;
    char c;
    cin>>n;
    string parole;
    vector<Policy*> cerintele;
    for(int i=0; i<n; i++)
    {
        cin>>cerinta;
        if(cerinta=="length") {
            cin >> nr1;
            if (getchar() == ' ') {
                cin >> nr2;
                cerintele.push_back(new LengthPolicy(nr1, nr2));
            } else cerintele.push_back(new LengthPolicy(nr1));
        }
        if(cerinta=="include")
        { cin>>c;
            cerintele.push_back(new IncludePolicy(c));}
        if(cerinta=="repetition")
        {cin>>nr1;
            cerintele.push_back(new RepetitionPolicy(nr1));}
        if(cerinta=="consecutive") {
            cin >> nr1;
            cerintele.push_back(new ConsecutivePolicy(nr1));

        }
        if(cerinta=="class")
        {
            cin>>nr1;
            cerintele.push_back(new ClassPolicy(nr1));
        }
        if(cerinta=="ninclude")
        {
            cin>>c;
            cerintele.push_back(new NotIncludePolicy(c));
        }


    }
    while(cin>>parole)
    {
        cout<<checkPassword(parole, cerintele)<<endl;
    }
    return 0;

}








