#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;

const int MAX = 100;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<pii, int> piii;

ll a[MAX+1];

/************** GENERATING TOPOLOGICAL SEQUENCES *****************/
ll d[MAX+1];            // d[i] = no of topological sequences of index i
int cc[MAX+1][MAX+1];   // no. of columns in given plane,row
int pp, n;              // no. of planes and n
piii x[MAX+1]; int k;   // the sequence of positions and its depth
vector<pii> poss;
int s;
ll c[MAX+1];

bool possible(int x, int y, int z) {
  if(x>1 && cc[x-1][y] < z) return 0;
  if(y>1 && cc[x][y-1] < z) return 0;
  return 1;
}
void include(int p, int y, int z) {
  k++;
  cc[p][y] = z;
  x[k] = make_pair(pii(p,y), z);
}
void exclude(int p, int y, int z) {
  cc[p][y]--;
  k--;
}

bool exist(pii e){
  for(int j=0;j<poss.size();j++){// j=i+1 changed to j=1
    if(poss[j]==e)
      return true;
  }
  return false;
}

void printconfig() { for(int i=1; i<=k; i++) printf("(%d,%d,%d)  ", x[i].first.first, x[i].first.second, x[i].second); printf("%d\n", k); }

int update_poss(int x,int y){

  int c2 = cc[x][y]+1;
  s=0;

  if(possible(x, y, c2)){
    poss.push_back(pii(x,y));
    s++;
  }

  c2 = cc[x+1][y]+1;

  if((possible(x+1, y, c2)) & !(exist(pii(x+1,y)))){
    poss.push_back(pii(x+1,y));
    s++;
  }

  c2 = cc[x][y+1]+1;

  if((possible(x, y+1, c2)) & !(exist(pii(x,y+1)))){
    poss.push_back(pii(x,y+1));
    s++;
  }

  return s;
}

void bm(int from,int to,int add){
  for(int i=from;i<to+add;i++){
    if( k== n){
      d[k+1]++;
      return;
    }

    d[k+1]++;

    int c2 = cc[poss[i].first][poss[i].second]+1;
    include(poss[i].first,poss[i].second, c2);
    add=update_poss(poss[i].first,poss[i].second);
    bm(i+1,to+add,0);
    exclude(poss[i].first,poss[i].second, c2);
    while(add!=0){
        poss.pop_back();
        add--;
    }
  }
}

void generate_topological_sequences(int nn) {
  memset(cc, 0, sizeof(cc));
  memset(d, 0, sizeof(d));
  d[0] = 1;
  d[1]=1;
  k=1; x[1] = make_pair(pii(1,1),1);
  poss.push_back(pii(1,1));
  poss.push_back(pii(1,2));
  poss.push_back(pii(2,1));
  cc[1][1] = 1;
  s=0;
  n = nn;
  bm(0,3,0);
}

int main() {
  printf("Enter N: ");
  int N; scanf("%d", &N);
  clock_t begin = clock();
  generate_topological_sequences(N);

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  printf("\nc[i] = no. of 2D partitions of i\n");
  for(int i=0; i<=N; i++) printf("c[%d] = %lld\n", i, d[i]);
  printf("\nTime taken:%.3f", elapsed_secs);
}
