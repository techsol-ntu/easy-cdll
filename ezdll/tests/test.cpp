#include <cstdio>
#include <iostream>
#include "ezdll.hpp"
using namespace std;

void f(long *dims, void *python_data) {
    Parameters params(dims, python_data);
    freopen("test_output.txt", "w", stdout);
    cout << "a" << endl;
    for (int i = 0, k = params.api_data_dims[0][0]; i < k; i++) {
        cout << params.a[i] << (i==k-1?'\n':' ');
    }
    cout << "b" << endl;
    for (int i = 0, _ = params.api_data_dims[1][0]; i < _; i++) {
        for (int j = 0, __ = params.api_data_dims[1][1]; j < __; j++) {
            cout << params.b[i][j] << (j==__-1?'\n':' ');
        }
    }
    cout << "c" << endl;
    for (int i = 0, _ = params.api_data_dims[2][0]; i < _; i++) {
        for (int j = 0, __ = params.api_data_dims[2][1]; j < __; j++) {
            for (int k = 0, ___ = params.api_data_dims[2][2]; k < ___; k++) {
                cout << params.c[i][j][k] << (k==___-1?'\n':' ');
            }
        }
    }
    cout << endl;
    return;
}

extern "C" {
    struct OutputStruct *api(long *dims, void *python_data) {
        f(dims, python_data);
        struct OutputStruct *outputs = new OutputStruct;
        outputs->objective = 1.23456789;
        return outputs;
    }
}