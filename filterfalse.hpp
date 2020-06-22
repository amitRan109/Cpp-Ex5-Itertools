#include <iostream>
using namespace std;
namespace itertools{
    
template <typename container,typename lambda>
class filterfalse {
    public:
    container cont;
    lambda check;

public:
     filterfalse (lambda l,container new_container)
    :cont(new_container),check(l) {}

    class iterator{
        typename container::iterator it_start;
        typename container::iterator it_end;
        lambda check;

    public:
        iterator(typename container::iterator start,
        typename container::iterator end,lambda _f) 
        :it_start(start),it_end(end),check(_f) {
            while(it_start != it_end && check(*it_start)){
                it_start++;
            }
        }

        iterator &operator++() {
            it_start++;
            while(it_start != it_end && check(*it_start)){
                it_start++;
            }
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

        decltype(*(cont.begin())) operator*() {
            return *it_start;
        }

    };

    iterator begin() {
        return iterator(cont.begin(),cont.end(),this->check);
    }

    iterator end() {
        return iterator(cont.end(),cont.end(),this->check);
    }
};
}