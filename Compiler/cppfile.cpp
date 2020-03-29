#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct a{
    int val;

};


int main(int argc, char const *argv[])
{   
    /*int b = 10;
    for(int i = 0; i < b; i++){
        b++;
        cout << i << endl;
    } */  

    long long a = 1234567890;
    long long b = 1234567890987654321;
    long long c = 987654321;
    
    long long wynik = 1;
    long long pot = a % c;
    
    while(b > 0){
		long long wybor = b % 2;
        if( wybor == 1){  
			wynik = wynik * pot;
			wynik = wynik % c;
		
        }  
		b = b / 2;
		pot = pot * pot;
		pot = pot % c;
    
    }
    cout << wynik;
    /*vector<string> iterators;
    map<string, int> t;

    //cout << t["s"] << endl << endl;
    struct a* st = (struct a*) malloc(sizeof(struct a));
    if(t["tt"] == 1)
        cout << "tru";
    if(find(iterators.begin(), iterators.end(), "fas") != iterators.end())
        cout << "jest";
    string n = "052";
    string w = "asd";
    cout << to_string(atoll(&n[0])) << endl;
    cout << to_string(atoll(&w[0])) << endl;

*/

    return 0;
}
