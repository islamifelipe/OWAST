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
	double alfa[6] = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};
	int ind = rand()%6;
	cout<<n<<" "<<p<<endl;
	cout<<alfa[ind]<<" 0 0 0 0 0 0 0 0 "<<1.0 - alfa[ind]<<endl;
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