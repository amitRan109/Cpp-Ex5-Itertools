#include "doctest.h"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

using namespace itertools;
using namespace std;

template <typename T>
bool equals(T a, T b){ return a == b;}
struct lessThan3 {
    bool operator()(int i) const { return i < 3; }
};


TEST_CASE("range"){ //25
    CHECK_NOTHROW(range(5,9));
    CHECK_NOTHROW(range(0,50));
    CHECK_NOTHROW(range(10,800));
    CHECK_NOTHROW(range(80,80));
    CHECK_NOTHROW(range(0,0));

    CHECK_NOTHROW(range(-50,0));
    CHECK_NOTHROW(range(-100,50));
    CHECK_NOTHROW(range(-100,-10));
    CHECK_NOTHROW(range(-200,-100));
    CHECK_NOTHROW(range(-200,200));

    for (int i: range(0,15))
        CHECK(i>-1);



}
TEST_CASE("accumulate"){ //25
    //range - 5
    for (int i: accumulate(range(1,3)))
        CHECK(i>0);
    auto lam =[](int x, int y){return x*y;}; 
    accumulate a =accumulate(range(1,4),lam);
    accumulate<range,decltype(lam)>::iterator it = a.begin();
    CHECK(equals(*it,1));
    CHECK(equals(*(++it),2));
    CHECK(equals(*(++it),6)); 
    
    //vector -5
    vector<string> v1 = {"amit","ran"};
    accumulate a1 =accumulate(v1);
    accumulate<vector<string>>::iterator it1 = a1.begin();
    CHECK(equals(*it1,string("amit")));
    CHECK(equals(*(++it1),string("amitran")));

    vector<double> v2 = {1.5,2.5,3.5};
    accumulate a2 =accumulate(v2);
    accumulate<vector<double>>::iterator it2 = a2.begin();
    CHECK(equals(*it2,1.5));
    CHECK(equals(*(++it2),4.0));
    CHECK(equals(*(++it2),7.5));


    //list -15
    list <int> l3 = {100,4,5,1};
    auto lam3 = [](int x, int y){return x/y;};
    accumulate a3 =accumulate(l3,lam3);
    accumulate<list<int>,decltype(lam3)>::iterator it3 = a3.begin();
    CHECK(equals(*it3,100));
    CHECK(equals(*(++it3),25));
    CHECK(equals(*(++it3),5));
    CHECK(equals(*(++it3),5));
    CHECK(equals(*(++it3),5)); // out of range

    list <int> l4 = {80,50,20,6,1};
    auto lam4 = [](int x, int y){return x%y;};
    accumulate a4 =accumulate(l4,lam4);
    accumulate<list <int>,decltype(lam4)>::iterator it4 = a4.begin();
    CHECK(equals(*it4,80));
    CHECK(equals(*(++it4),30));
    CHECK(equals(*(++it4),10));
    CHECK(equals(*(++it4),4));
    CHECK(equals(*(++it4),0));


    list <int> l5 = {8,23,52,8,4};
    auto lam5 = [](int x, int y){return x;};
    accumulate a5 =accumulate(l5,lam5);
    accumulate<list <int>,decltype(lam5)>::iterator it5 = a5.begin();
    CHECK(equals(*it5,8));
    CHECK(equals(*(++it5),8));
    CHECK(equals(*(++it5),8));
    CHECK(equals(*(++it5),8));
    CHECK(equals(*(++it5),8));
    
}
TEST_CASE("filterfalse"){ //25
    //5
    vector <int> v1 = {30,2,67,1,82,0,-5,-40,100,85};
    for (auto i: filterfalse(lessThan3{}, v1))
        CHECK(i >= 3);
    //5
    vector <int> v2 = {30,2,67,1,83,99,79,0,-40};
    auto lam2 = [](int x){return x%2==0;};
    for (auto i: filterfalse(lam2, v2))
        CHECK(i%2!=0);
    //5
    vector <int> v3 = {-30,-2,67,-1,82,0,49,56,-5,-40};
    auto lam3 = [](int x){return x<0;};
    for (auto i: filterfalse(lam3, v3))
        CHECK(i>=0);
    
    //5
    vector <int> v4 = {1,2,4,30,7,10,5,13,9,12,15};
    auto lam4 = [](int x){return x%3==1;};
    for (auto i: filterfalse(lam4, v4))
        CHECK(i%3!=1);
    
    //5
    vector <int> v5 = {30,2,67,1,82,0,-5,3,-50};
    auto lam5 = [](int x){return x/2>5;};
    for (auto i: filterfalse(lam5, v5))
        CHECK(i/2<=5);
    
    
}
TEST_CASE("compress"){ //25   
    //11
    vector<bool> v1 = {true,true,true,true,true,true,true,true,true,true};
    int count1=0;
    for (auto i: compress(range(1,11),v1)) {
        CHECK(i);
        count1++;
    } 
    CHECK(equals(count1, 10));

    //6
    vector <int> v2 = {3,45,67,99,80,-9,50,61};
    vector<bool> v3 = {false,false,true,true,true,false,true,true};
    int count2=0;
    for (auto i: compress(v2,v3)) {
        CHECK(i>=50);
        count2++;
    } 
    CHECK(equals(count2, 5));

    //10
    vector <int> v4 = {0,-3,-20,-5,45,67,-10,-88,-9,50,-61,0,-500};
    vector<bool> v5 = 
        {true,true,true,true,false,false,true,true,true,false,true,true,true};
    int count3=0;
    for (auto i: compress(v4,v5)) {
        CHECK(i<=0);
        count3++;
    } 
    CHECK(equals(count3, 10));

}