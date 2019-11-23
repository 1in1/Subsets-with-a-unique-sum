#include <iostream>
#include <chrono>
typedef unsigned long long big;
#define MAXSUM 295425
using namespace std;

int main()
{
  auto start = chrono::high_resolution_clock::now();
  int* table[51];
  for(int i=0; i<51; i++) {
    table[i] = new int[MAXSUM+1];
    for(int j=0; j<=MAXSUM; j++)
      table[i][j] = 0;
  }
  table[0][0] = 1;
  int size;
  for(int k=1; k<=100; k++){  //for each element we could add
    if(k>50){
      size = 50;
    } else {
      size = k;
    }

    for(int i=size; i>=1; --i) {  //loop over subset size
      for(int j=MAXSUM; j>=k*k; --j) {
        if(table[i-1][j-k*k] > 0){ //if the value we are coming from is reachable
          if(table[i][j] == 0) { //if we haven't already seen this value
            table[i][j] = table[i-1][j-k*k]; //mark as seen or seen twice as appropriate
          } else { //otherwise mark as seen twice
            table[i][j] = 2;
          }
        }
      }
    }

  }
  big total = 0;
  for(int i = 1; i<=MAXSUM; i++) {
    if(table[50][i] == 1)
      total += i;
  }
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout<<total<<endl;
  cout << "Done. Took "<<duration.count()/1000<< " milliseconds total.";

}
