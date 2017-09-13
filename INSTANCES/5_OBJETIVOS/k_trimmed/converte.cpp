#include <iostream>
#include <vector> 
#include <string>
#include <climits>
#include <stack>   
#include <utility>      // std::pair
#include <cmath>
#include <list>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
using namespace std;

int main(){
	/* initialize random seed: */
  	srand (time(NULL));
	int n, p = 5;
	cin>>n;
	double k[2] = {1,2};
	//k = 1  ===> 0 0.3 0.3 0.3 0
	//k = 2  ===> 0 0 1 0 0
	int ind = rand()%2;
	cout<<n<<" "<<p<<endl;
	for (int i=0; i<k[ind]; i++) cout<<"0 ";
	for (int i=k[ind]; i<p-k[ind]; i++) cout<<(1.0/(p-(2.0*k[ind])))<<" ";
	for (int i=p-k[ind]; i<p; i++) cout<<"0 ";
		cout<<endl;
	int i,j,p1,p2,p3, p4, p5;
	while (cin>>i){
		cin>>j;
		cin>>p1;
		cin>>p2;
		cin>>p3;
		cin>>p4;
		cin>>p5;
		cout<<i<<" "<<j<<" "<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<endl;
	}
	return 0;
}