

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

// typedef struct 
// {
// 	int i;
// 	int j;
// 	int p1;
// 	int p2;
// 	int p3;
// }tip;

int main(){
	/* initialize random seed: */
  	srand (time(NULL));
	int n, p = 8;
	cin>>n;
	double k[4] = {2.0, 4.0, 6.0, 7.0};
	int ind = rand()%4;
	double kk = 1.0/k[ind];
	cout<<n<<" "<<p<<endl;
	for (int i=0; i<k[ind]; i++){
		cout<<kk<<" ";
	}
	for (int i=k[ind]; i<p; i++){
		cout<<"0.0 ";
	}
	cout<<endl;
	int i,j,p1,p2,p3, p4, p5, p6, p7, p8;
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
		cout<<i<<" "<<j<<" "<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<" "<<p7<<" "<<p8<<endl;
	}
	return 0;
}