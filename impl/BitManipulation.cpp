#include <bits/stdc++.h>
using namespace std;

#define multTwo(S) (S<<1)
#define divTwo(S) (S>>1)
#define isOn(S, j) (S & (1<<j))                 // or (S>>j) & 1
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define LSOne(S) (S & -(S))                     // note this returns the value of LSOne
#define setAll(S, n) (S = (1<<n)-1)

#define numOnBits(S) (__builtin_popcount(S))
#define numLeadingZero(S) (__builtin_clz(S))    // note this is undefined behaviour if S is 0
#define numTrailingZero(S) (__builtin_ctz(S))   // note this is undefined behaviour if S is 0
#define indexLSOne(S) (__builtin_ffs(S))        // note this returns 1 + index of LSOne
#define parity(S) (__builtin_parity(S))         // returns 1 if odd number of 1s in S else 0 if even number of 1s in S
//refer to https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html for more builtin functions

#define modulo(S, N) ((S) & (N-1))              // returns S%N where N is a power of 2
#define isPowerOfTwo(S) (S && !(S & (S-1)))     // if S is power of 2, S & S-1 will be 0, also need to check S is not 0
#define isDivisiblePowerOfTwo(S, j) (!(S & ((1<<j)-1)))
#define nearestPowerOfTwo(S) (1<<lround(log2(S)))
#define turnOffLastOne(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveOnes(S) ((S) & (S+1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1))

// these are supported via bit std lib since C++20
#define onlyOneBit(S) (has_single_bit(S))       // checks if S is power of 2 also
#define roundUpPowerOfTwo(S) (bit_ceil(S))
#define roundDownPowerOfTwo(S) (bit_floor(S))
#define countTrailingOnes(S) (countr_one(S))
#define countLeadingOnes(S) (countl_one(S))
#define countTrailingZeroes(S) (countr_zero(S))
#define countLeadingZeroes(S) (countl_zero(S))
#define rotateLeft(S, j) (rotl(S, j))           // shift j can be negative
#define rotateRight(S, j) (rotr(S, j))          // shift j can be negative

void printSet(int vS) {                         // in binary representation
  printf("S = %2d = ", vS);
  stack<int> st;
  while (vS)
    st.push(vS%2), vS /= 2;
  while (!st.empty())                         // to reverse the print order
    printf("%d", st.top()), st.pop();
  printf("\n");
}

void subsetMask(int mask){                   // get all proper subsets of a bitmask
  for(int subset=mask; subset; subset=(mask & (subset-1))){
    cout << subset << "\n";
  }
}

int countSetBits(int vS){                    // counts number of set bits (like popcount) by repeatedly clearing last set bit
  int count = 0;
  while(n){
    n &= n-1;
    count++;
  }
  return count;
}

int countSetBitsUpto(int n){                 // counts number of set bits of all integers up to n inclusive
  int count = 0;
  while(n>0){
    int x = bit_width(n) - 1;
    count += x<<(x-1);
    n -= (1<<x);
    count += n+1;
  }
  return count;
}
// the idea here is from 1 to 2^x -1 there are x*2^(x-1) set bits
