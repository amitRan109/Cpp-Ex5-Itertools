#include <iostream>
using namespace std;
namespace itertools{
class add {
public:
    template <typename T>
    T operator()(T x, T y) const {
        return x+y;
    }
};     
template <typename container,typename lambda = add>
class accumulate {
    public:
    container cont;
    lambda f;
    typedef typename container::value_type value_type;

public:
    accumulate (container new_container,lambda l=add())
    :cont(new_container),f(l){}

    class iterator{
        typename container::iterator it_start;
        typename container::iterator it_end;
        typename container::value_type sum;
        lambda f;

    public:
        iterator(typename container::iterator start,typename container::iterator end,lambda _f) 
        :it_start(start),it_end(end),f(_f) {
            if (start != end) sum = *start;
        }

        iterator &operator++() {
            ++it_start;
            if (it_start != it_end)
                sum = f(sum,*it_start);
            return *this; 
        }

        const iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator &other) const {
            return it_start == other.it_start;
        }

        bool operator!=(const iterator &other) const {
            return it_start != other.it_start;
        }

        auto operator*() {
            return sum;
        }

    };

    iterator begin() {
        return iterator(cont.begin(),cont.end(),this->f);
    }

    iterator end() {
        return iterator(cont.end(),cont.end(),this->f);
    }
};
}