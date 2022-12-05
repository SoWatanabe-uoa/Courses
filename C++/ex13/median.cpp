//#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

void printVec(const std::vector<float> &vec)
{
    std::cout << "v= {";
    for (int i : vec)
        std::cout << i << ", ";
    std::cout << "}\n";
}

float compute_median(std::vector<float>& v){
    int mid = v.size()/2;
    printVec(v);
    if(mid%2){
        std::nth_element(v.begin(), v.begin()+mid, v.end());
        int m = v[mid];
        std::nth_element(v.begin(), v.begin() + mid - 1,v.end();
        printVec(v);
        return 0.5f*(v[mid-1]+m);
    }
    else{
        std::nth_element(v.begin(), v.begin()+mid, v.end());
        printVec(v);
        return v[mid];
    }
}

int main(){
    std::vector<float> v{5.f, 10.f, 6.f, 4.f, 3.f, 2.f, 8.f, 7.f, 9.f};
    float median = compute_median(v);
    std::cout << "Median:" << median << std::endl;
    return 0;
}

