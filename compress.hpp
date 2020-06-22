#include <iostream>
using namespace std;
namespace itertools{
    
template <typename cont_a,typename cont_b>
class compress {
    public:
    cont_a a;
    cont_b b;

public:
    compress (cont_a _a, cont_b _b)
    :a(_a),b(_b){}

    class iterator{
        typename cont_a::iterator it_a;
        typename cont_b::iterator it_b;
        typename cont_a::iterator end;
        

    public:
        iterator(typename cont_a::iterator a,
            typename cont_b::iterator b,
            typename cont_a::iterator end) 
        :it_a(a),it_b(b),end(end) {
             while(it_a != end && !(*it_b)){
                ++it_a;
                ++it_b;
            }
        }

        iterator &operator++() {
            ++it_a; ++it_b;
            while(it_a != end && !(*it_b)){
                it_a++;it_b++;
            }
            return *this;
        }

        const iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator &other) const {
            return it_a == other.it_a;
        }

        bool operator!=(const iterator &other) const {
            return it_a != other.it_a;
        }

        decltype(*(a.begin())) operator*() {
            return *it_a;
        }

    };

    iterator begin() {
        return iterator(a.begin(),b.begin(),a.end());
    }

    iterator end() {
        return iterator(a.end(),b.begin(),a.end());
    }
};
}