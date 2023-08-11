#include <iostream>
#include "vector"
#include <ctime>
using namespace std;

uint64_t mod(uint64_t a, uint64_t b){
    return ((a % b) + b)%b;
}



uint64_t mod_bin_exp(uint64_t x,uint64_t y, uint64_t n){
    if (y == 0){
        return 1;
    } else if (y % 2 == 0){
        return mod((mod_bin_exp(x,y/2,n)* mod_bin_exp(x,y/2,n)),n);
    } else {
        return mod(mod((mod_bin_exp(x,y/2,n)* mod_bin_exp(x,y/2,n)),n)*x,n);
    }
}



bool funcion(vector<uint64_t> &v, uint64_t i, uint64_t m,uint64_t r, uint64_t acumulado,vector<vector<uint64_t>> &memo){
    if (i == v.size()){
        return acumulado % m == r;
    }
    if(memo[i][acumulado] == -1) {
       memo[i][acumulado] = funcion(v,i+1,m,r,mod(acumulado+v[i],m) ,memo)|| funcion(v,i+1,m,r,mod(acumulado*v[i],m),memo)
               || funcion(v,i+1,m,r, mod(acumulado-v[i],m),memo) || funcion(v,i+1,m,r, mod_bin_exp(acumulado,v[i],m),memo);
    }
    return memo[i][acumulado];
}


int main (){
    uint64_t c; cin >> c;
    vector<bool> respuestas;
    while (c--) {
        uint64_t n, r, m;
        cin >> n >> r >> m;
        vector<uint64_t> elementos;
        for (int i = 0; i < n; ++i) {
            uint64_t e;
            cin >> e;
            elementos.push_back(e);
        }
        vector<vector<uint64_t>> memo;
        for (int i = 0; i < n; ++i) {
            vector<uint64_t> fila;
            for (int j = 0; j < m; ++j) {
                fila.push_back(-1);
            }
            memo.push_back(fila);
        }
        respuestas.push_back(funcion(elementos,1,m,r,elementos[0],memo));
    }
    for (int i = 0; i < respuestas.size(); ++i) {
        cout << respuestas[i] << endl;
    }
    return 0;

}
