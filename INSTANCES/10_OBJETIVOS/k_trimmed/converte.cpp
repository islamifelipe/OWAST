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
	int n, p = 10;
	cin>>n;
	double k[3] = {2,3,4};
	//k = 2  ===> 0 0 0.166 0.166 0.166 0.166 0.166 0.166 0 0 
	//k = 3  ===> 0 0 0 0.25 0.25 0.25 0.25 0 0 0 
	//k = 4  ===> 0 0 0 0 0.5 0.5 0 0 0 0 
	int ind = rand()%3;
	cout<<n<<" "<<p<<endl;
	for (int i=0; i<k[ind]; i++) cout<<"0 ";
	for (int i=k[ind]; i<p-k[ind]; i++) cout<<(1.0/(p-(2.0*k[ind])))<<" ";
	for (int i=p-k[ind]; i<p; i++) cout<<"0 ";
	
	cout<<endl;
	int i,j,p1,p2,p3, p4, p5, p6, p7, p8, p9, p10;
	while (cin>>i){
		cin>>j;
		cin>>p1;
		cin>>p2;
		cin>>p3;
		cin>>p4;
		cin>>p5;
		cin>>p6;
		cin>>p7;
		cin>>p8;
		cin>>p9;
		cin>>p10;
		cout<<i<<" "<<j<<" "<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<" "<<p7<<" "<<p8<<" "<<p9<<" "<<p10<<endl;
	}
	return 0;
}