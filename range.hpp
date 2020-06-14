#pragma once
namespace itertools {
    class range {
        int start;
        int finish;
    public:
        range(int a, int b) : start(a), finish(b) {}

        class iterator {
            int current;
        public:
            iterator(int current_to_be = 0) : current(current_to_be) {}

            iterator &operator++() {
                current = current + 1;
                return *this;
            }

            const iterator operator++(int) {
                iterator temp = *this;
                ++current;
                return temp;
            }

            bool operator==(const iterator &it) const {
                return current == it.current;
            }

            bool operator!=(const iterator &it) const {
                return current != it.current;
            }

            int operator*(){
                return current;
            }

        };

        iterator begin() {
            return iterator(start);
        }

        iterator end() {
            return iterator(finish);
        }

    };
}