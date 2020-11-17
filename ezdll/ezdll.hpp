#ifndef _EZDLL_HPP_
#define _EZDLL_HPP_

#include <vector>

class Parameters {

private:

    void *python_data_ptr;

    template<typename T>
    T _fix_type_(T ref) { return (T)python_data_ptr; }

    template<typename T, typename K>
    T _fill_data_1d(T container, K element, std::vector<int> &dims) {
        int size = dims.size()?dims[dims.size()-1]:1;
        T buf = new K[size];
        for (int i = 0; i < size; i++) {
            buf[i] = *_fix_type_(&buf[i]);
            python_data_ptr += sizeof(K);
        }
        return buf;
    }

    template<typename T, typename K>
    T _fill_data_2d(T container, K element, std::vector<int> &dims) {
        int size = dims[dims.size()-2];
        T buf = new K[size];
        for (int i = 0; i < size; i++) {
            K _; buf[i] = _fill_data_1d(*container, *_, dims);
        }
        return buf;
    }

    template<typename T, typename K>
    T _fill_data_3d(T container, K element, std::vector<int> &dims) {
        int size = dims[dims.size()-3];
        T buf = new K[size];
        for (int i = 0; i < size; i++) {
            K _; buf[i] = _fill_data_2d(*container, *_, dims);
        }
        return buf;
    }

public:

    Parameters(long *dims, void *python_data) {
        python_data_ptr = python_data;
        while (*dims >= 0) {
            std::vector<int> d;
            while (*dims > 0) {
                d.push_back(*dims);
                dims++;
            }
            api_data_dims.push_back(d);
            dims++;
        }
        a = _fill_data_1d(a, *a, api_data_dims[0]);
        b = _fill_data_1d(b, *b, api_data_dims[1]);
        c = _fill_data_2d(c, *c, api_data_dims[2]);
    }
    std::vector< std::vector<int> > api_data_dims;
    long *a;
    long *b;
    long **c;
};

struct OutputStruct {
    double objective;
    double sol[1024][1024];
    double others[1024];
};

#endif