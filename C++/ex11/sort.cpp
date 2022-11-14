#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <deque>

//Based on Merge-sort algolithm

namespace PL4 {
    /*
    template <class Ran>
    void sort(Ran begin, Ran end){
        auto diff = end - begin;
        if (diff <= 1) { return; }
        Ran middle = begin + diff / 2;
        PL4::sort(begin, middle);
        PL4::sort(middle, end);
        std::inplace_merge(begin, middle, end);
    }
    */
    template <class BiDirIt>
    void sort(BiDirIt begin, BiDirIt end){
        BiDirIt i,j;
        i = begin;
        while(i < end){
            j = i;
            while(j > begin && *(j-1)>*j){
                auto temp = *j;
                *j = *(j-1);
                *(j-1) = temp;
                j--;
            }
            i++;
        }
    }
}

int main(){
    int org1[] = {3, 5, 1, 6, 2, 7, 4};
    int org2[] = {7, 4, 6, 1, 3, 5, 2};

    //Test on vector<int>
    std::cout << "Test on vector<int>" << std::endl;
    std::vector<int> v(org1, org1 + sizeof(org1)/sizeof(int));
    std::cout << "Original: ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    PL4::sort(v.begin(), v.end());
    std::cout << "\nSorted: ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

    //Test on deque<int>
    std::cout << "\n\nTest on deque<int>" << std::endl;
    std::deque<int> d(org2, org2 + sizeof(org2)/sizeof(int));
    std::cout << "Original: ";
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    PL4::sort(d.begin(), d.end());
    std::cout << "\nSorted: ";
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
