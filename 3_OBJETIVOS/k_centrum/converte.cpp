

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
	int n, p = 3;
	cin>>n;
	double k[2] = {2.0, 3.0};
	int ind = rand()%2;
	double kk = 1.0/k[ind];
	cout<<n<<" "<<p<<endl;
	for (int i=0; i<k[ind]; i++){
		cout<<kk<<" ";
	}
	for (int i=k[ind]; i<p; i++){
		cout<<"0.0 ";
	}
	cout<<endl;
	int i,j,p1,p2,p3;
	while (cin>>i){
		cin>>j;
		cin>>p1;
		cin>>p2;
		cin>>p3;
		cout<<i<<" "<<j<<" "<<p1<<" "<<p2<<" "<<p3<<endl;
	}
	return 0;
}