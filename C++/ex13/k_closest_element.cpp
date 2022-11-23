#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
 
std::vector<float> compute_k_closest(std::vector<float> input, int k){
    std::vector<float> result;
    std::nth_element(input.begin(), input.begin()+k+1, input.end(), std::greater<float>());
    std::vector<float>::iterator max(std::max_element(input.begin(), input.begin()+k+1));
    std::remove_copy(input.begin(), input.begin()+k+1, back_inserter(result), *max);
    return result;
}
 
int main(){
    std::vector<float> input{11.f, 6.5f, 17.f, 7.f, 5.3f, 3.f, 7.f};
    std::vector<float> output(compute_k_closest(input,5));
    copy(output.begin(), output.end(), std::ostream_iterator<float>(std::cout, " "));

    return 0;
}

