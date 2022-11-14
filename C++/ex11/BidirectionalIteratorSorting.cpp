#include <iterator>
#include <iostream>
#include <list>
#include <deque>

//Based on Insertion sort algolithm
namespace PL4 {
    template <class BiDirIt>
    void sort(BiDirIt begin, BiDirIt end){
        BiDirIt i,j;
        i = begin;
        i++;
        while(i != end){
            j = i;
            j--;
            auto Aj_1 = *j;
            j++;
            while(j != begin && Aj_1 > *j){
                //swap the j-th and the j-1 elements
                auto Aj = *j;
                *j = Aj_1;
                j--;
                *j = Aj;
                
                j--;
                Aj_1 = *j;
                j++;
            }
            i++;
        }
    }
}

int main(){
    //Test on vector<int>
    std::cout << "Test on list<int>" << std::endl;
    std::list<int> ls;
    ls.push_back(3); ls.push_back(5); ls.push_back(1);
    ls.push_back(6); ls.push_back(4);
    std::cout << "Original: ";
    std::copy(ls.begin(), ls.end(), std::ostream_iterator<int>(std::cout, " "));
    PL4::sort(ls.begin(), ls.end());
    std::cout << "\nSorted: ";
    std::copy(ls.begin(), ls.end(), std::ostream_iterator<int>(std::cout, " "));

    //Test on deque<int>
    std::cout << "\n\nTest on deque<int>" << std::endl;
    std::deque<int> d;
    d.push_front(3); d.push_front(5); d.push_front(1);
    d.push_front(6); d.push_front(4);
    std::cout << "Original: ";
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    PL4::sort(d.begin(), d.end());
    std::cout << "\nSorted: ";
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    
    std::cout  << std::endl;
    return 0;
}
