#include <iostream>
#include <vector>
#include <utility>
typedef unsigned long long big;
#define MAXSUM 295425
#define SEEN 0
#define TWICE 101
using namespace std;

int main()
{
	bool*** table = new bool** [2];
	for (int i = 0; i < 2; i++) {
		table[i] = new bool* [MAXSUM+1];
		for (int j = 0; j <= MAXSUM; j++) {
			table[i][j] = new bool[102];
			for (int k = 0; k < 102; k++)
				table[i][j][k] = false;
		}
	}

	for (int i = 1; i <= 100; i++) {
		table[1][i * i][i] = true;
		table[1][i * i][SEEN] = true;
	}

	for (int i = 2; i <= 4; i++) {

		//need to clean the one we're about to use
		for (int j = 1; j <= MAXSUM; j++) {
			table[i%2][j][SEEN] = false;
		}


		for (int j = 1; j <= MAXSUM; j++) { //can definitely optimise over this loop
			if (table[(i-1)%2][j][SEEN] == true && table[(i-1)%2][j][TWICE] == false) { //there is a unique representation of the prev sum
				for (int l = 100; l >= 1; l--) {


					if (table[(i-1)%2][j][l] == false) { //if not already used (and within range guaranteed by MAXSUM)
						if (table[i%2][l * l + j][SEEN] == true) { //already seen a representation
							  table[i%2][l * l + j][TWICE] = true;
						}
						else { //make it same as previous but with l flagged too
							for (int p = 0; p < 102; p++)
								table[i%2][l * l + j][p] = table[(i - 1) % 2][j][p];
							table[i%2][l * l + j][l] = true;
						}
					} else { //only add ones that are bigger than the largest one already being used in that sum
            break;
          }

				}
			}
		}

	}

	big total = 0;
	for (int i = 1; i <= MAXSUM; i++) {
		if (table[0][i][SEEN] == 1 && table[0][i][TWICE] == 0) {
			total += i;
		}
	}
	cout << total;
}
