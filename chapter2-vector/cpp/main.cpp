#include <iostream>
#include "vector_dsa.h"
#include "vector_dsa_ordered.h"
#include "fibonacci/fib.h"

int main() {

    int a[5] = {3, 2, 1, 4, 1};
    VectorDsa<double > dvecDsa(3,3,1);
    cout << dvecDsa << endl;

    VectorDsa<int> ivecDsa(a,5);
    cout << ivecDsa << endl;
    cout << ivecDsa.find(2, 3, 0) << endl;
    ivecDsa.deduplicate();
    cout << ivecDsa <<endl;

    ivecDsa.traverse(Increase<int>());
    cout << ivecDsa << endl;
    increase(ivecDsa);
    cout << ivecDsa << endl;
//    ivecDsa.bubbleSort();
    ivecDsa.mergeSort();
    cout << ivecDsa << "sort" << endl;

    int b[6] = {1,3,4,5,5,6};
    VectorDsaOrdered<int> ivec_ord(b, 6);
    int num_bin = ivec_ord.binsearch(0, 6, 2);
    int num_bin_improve = ivec_ord.binsearch_improve(0, 6, 2);
    int num_bin_return_rule = ivec_ord.binsearch_return_rule(0, 6, 2);
    int num_fib = ivec_ord.fibsearch(0, 6, 2);
    ivec_ord.search(2); cout << endl;
    if(num_bin > -1){
        cout << num_bin << " num_binRank: " << ivec_ord[num_bin] << endl;
    }
    if(num_bin_improve > -1){
        cout << num_bin_improve << " num_bin_improveRank: " << ivec_ord[num_bin_improve] << endl;
    }
    if(num_bin_return_rule > -1){
        cout << num_bin_return_rule << " num_bin_return_ruleRank: " << ivec_ord[num_bin_return_rule] << endl;
    }
    if(num_fib > -1){
        cout << num_fib << " num_fibRank: " << ivec_ord[num_fib] << endl;
    }

    Fib fib(10);
    cout <<"fib: " << fib << "fib.get() : " << fib.get() << endl;
    fib.prev();
    cout <<"fib: " << fib << "fib.get() : " << fib.get() << endl;

    return 0;
}