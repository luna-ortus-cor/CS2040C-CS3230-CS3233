#include <iostream>
#include <vector>

using namespace std;

int add(vector<vector<char>> v, int i, int j){
    int extra = 0;
    if(v[i+1][j+1] == 'o') {
        extra++;
    }
    if(v[i+1][j] == 'o') {
        extra++;
    }
    if(v[i+1][j-1] == 'o') {
        extra++;
    }
    if(v[i][j+1] == 'o') {
        extra++;
    }
    if(v[i][j-1] == 'o') {
        extra++;
    }
    if(v[i-1][j+1] == 'o') {
        extra++;
    }
    if(v[i-1][j] == 'o') {
        extra++;
    }
    if(v[i-1][j-1] == 'o') {
        extra++;
    }

    return extra;
}

int main(){
    int r, s;
    cin >> r >> s;
    vector<vector<char>> v;
    v.resize(r+5, vector<char>(s+5, '.'));
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= s; j++){
            cin >> v[i][j];
        }
    }

    int handshake = 0;
    for(int i = 0;i <= r; i++){
        for(int j = 0; j <= s; j++){
            if(v[i][j] == 'o' && v[i+1][j] == 'o') {
                handshake++;
            }
            if(v[i][j] == 'o' && v[i][j+1] == 'o') {
                handshake++;
            }
            if(v[i][j] == 'o' && v[i+1][j+1] == 'o') {
                handshake++;
            }
            if(v[i][j] == 'o' && v[i-1][j+1] == 'o') {
                handshake++;
            }
        }
    }

    int extra = 0;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= s; j++){
            if(v[i][j] == '.'){
                extra = max(extra, add(v, i, j));
            }
        }
    }

    cout << handshake + extra << endl;
    return 0;
}
