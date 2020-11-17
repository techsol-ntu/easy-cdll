#include <iostream>
#include "ezdll.hpp"
using namespace std;

void f(long *dims, void *python_data) {
    Parameters params(dims, python_data);
    cout << "a" << endl;
    for (int i = 0, k = params.api_data_dims[0][0]; i < k; i++) {
        cout << params.a[i] << (i==k-1?'\n':' ');
    }
    cout << "b" << endl;
    for (int i = 0, k = params.api_data_dims[1][0]; i < k; i++) {
        cout << params.b[i] << (i==k-1?'\n':' ');
    }
    cout << "c" << endl;
    for (int i = 0, k = params.api_data_dims[2][0]; i < k; i++) {
        for (int j = 0, l = params.api_data_dims[2][1]; j < l; j++) {
            cout << params.c[i][j] << (j==l-1?'\n':' ');
        }
    }
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