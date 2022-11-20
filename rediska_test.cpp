#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <deque>
#include "vector.hpp"
//#include "stack.hpp"
//#include "map.hpp"
//#ifdef ft
using namespace ft;
//#else
//using namespace std;
//#endif

struct classcomp { bool operator() (const char& lhs, const char& rhs) const {return lhs<rhs;}};
bool fncomp (char lhs, char rhs) {return lhs<rhs;}

int main() {
//****************************************VECTOR TESTS****************************************
    //constructors
    {
        vector<int> first;
        vector<int> second(4, 100);
        vector<int> third(second.begin(), second.end());
        vector<int> fourth(third);

        int myints[] = {16, 2, 77, 29};
        vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

        std::cout << "The contents of fifth are:";
        for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    //assignation
    {
        vector<int> foo (3,0);
        vector<int> bar (5,0);

        bar = foo;
        foo = vector<int>();

        std::cout << "Size of foo: " << int(foo.size()) << '\n';
        std::cout << "Size of bar: " << int(bar.size()) << '\n';
    }

    //size
    {
        vector<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<10; i++) myints.push_back(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.insert (myints.end(),10,100);
        std::cout << "2. size: " << myints.size() << '\n';

        myints.pop_back();
        std::cout << "3. size: " << myints.size() << '\n';
    }

    //max size
    {
        vector<int> myvector;
        for (int i=0; i<100; i++) myvector.push_back(i);

        std::cout << "size: " << myvector.size() << "\n";
        std::cout << "capacity: " << myvector.capacity() << "\n";
        std::cout << "max_size: " << myvector.max_size() << "\n";
    }

    //empty
    {
        vector<int> myvector;
        int sum (0);

        for (int i=1;i<=10;i++) myvector.push_back(i);

        while (!myvector.empty())
        {
            sum += myvector.back();
            myvector.pop_back();
        }

        std::cout << "total: " << sum << '\n';
    }

    //capacity
    {
        vector<int> myvector;

        for (int i=0; i<100; i++) myvector.push_back(i);

        std::cout << "size: " << (int) myvector.size() << '\n';
        std::cout << "capacity: " << (int) myvector.capacity() << '\n';
        std::cout << "max_size: " << (int) myvector.max_size() << '\n';
    }

    //clear
    {
        vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

    //at
    {
        vector<int> myvector (10);   // 10 zero-initialized ints

        for (unsigned i=0; i<myvector.size(); i++)
            myvector.at(i)=i;

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector.at(i);
        std::cout << '\n';
    }
    //push back
    {
        vector<int> myvector;

        for (int i = 0; i < 10; i++)
            myvector.push_back(i);
        std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
    }

    //pop back
    {
        vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);
        while (!myvector.empty()) {
            sum+=myvector.back();
            myvector.pop_back();
        }
        std::cout << "The elements of myvector add up to " << sum << '\n';
    }

    //front
    {
        vector<int> myvector;
        myvector.push_back(78);
        myvector.push_back(16);

        myvector.front() -= myvector.back();

        std::cout << "myvector.front() is now " << myvector.front() << '\n';
    }

    //back
    {
        vector<int> myvector;

        myvector.push_back(10);

        while (myvector.back() != 0) {
            myvector.push_back ( myvector.back() -1 );
        }

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size() ; i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }


    //revese
    {
        vector<int>::size_type sz;

        vector<int> foo;
        sz = foo.capacity();
        std::cout << "making foo grow:\n";
        for (int i=0; i<100; ++i) {
            foo.push_back(i);
            if (sz!=foo.capacity()) {
                sz = foo.capacity();
                std::cout << "capacity changed: " << sz << '\n';
            }
        }

        vector<int> bar;
        sz = bar.capacity();
        bar.reserve(100);
        std::cout << "making bar grow:\n";
        for (int i=0; i<100; ++i) {
            bar.push_back(i);
            if (sz!=bar.capacity()) {
                sz = bar.capacity();
                std::cout << "capacity changed: " << sz << '\n';
            }
        }
    }



    //begin - end
    {
        vector<int> myvector;
        for (int i=1; i<=5; i++) myvector.push_back(i);

        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        vector<int>::iterator it = myvector.begin();
        vector<int>::const_iterator cit = myvector.begin();
        if (it == cit)
            std::cout << "coucou" << std::endl;
    }

    //revese begin - end
    {
        vector<int> myvector (5);

        vector<int>::reverse_iterator rit = myvector.rbegin();

        int i=0;
        for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
            *rit = ++i;

        std::cout << "myvector contains:";
        for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    //resize
    {
        vector<int> myvector;

        // set some initial content:
        for (size_t i=1;i<10;i++) myvector.push_back(i);

        myvector.resize(5);
        myvector.resize(8,100);
        myvector.resize(12);

        std::cout << "myvector contains:";
        for (size_t i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

    //assign
    {
        vector<int> first;
        vector<int> second;
        vector<int> third;

        first.assign (7,100);
        vector<int>::iterator it;
        it=first.begin()+1;
        second.assign (it,first.end()-1);
        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);

        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        std::cout << "Size of third: " << int (third.size()) << '\n';
    }

    //erase
    {
        vector<int> myvector;
        for (int i=1; i<=10; i++) myvector.push_back(i);

        myvector.erase (myvector.begin()+5);

        myvector.erase (myvector.begin(),myvector.begin()+3);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }

    //compare
    {
        vector<int> foo (3,100);
        vector<int> bar (2,200);

        if (foo==bar) std::cout << "foo and bar are equal\n";
        if (foo!=bar) std::cout << "foo and bar are not equal\n";
        if (foo< bar) std::cout << "foo is less than bar\n";
        if (foo> bar) std::cout << "foo is greater than bar\n";
        if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
        if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
    }

    //swap
    {
        vector<int> foo (3,100);   // three ints with a value of 100
        vector<int> bar (5,200);   // five ints with a value of 200

        foo.swap(bar);

        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
    }
//
////****************************************MAP TESTS****************************************
//    //constructors
//    {
//        map<char,int> first;
//
//        first['a']=10;
//        first['b']=30;
//        first['c']=50;
//        first['d']=70;
//
//        map<char,int> second (first.begin(),first.end());
//
//        map<char,int> third (second);
//
//        map<char,int,classcomp> fourth;
//
//        bool(*fn_pt)(char,char) = fncomp;
//        map<char,int,bool(*)(char,char)> fifth (fn_pt);
//    }
//
//    //assignation
//    {
//        map<char,int> first;
//        map<char,int> second;
//
//        first['x']=8;
//        first['y']=16;
//        first['z']=32;
//
//        second=first;                // second now contains 3 ints
//        first=map<char,int>();  // and first is now empty
//
//        std::cout << "Size of first: " << first.size() << '\n';
//        std::cout << "Size of second: " << second.size() << '\n';
//    }
//
//    //begin - end
//    {
//        map<char,int> mymap;
//
//        mymap['b'] = 100;
//        mymap['a'] = 200;
//        mymap['c'] = 300;
//
//        // show content:
//        for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    // revese begin - end
//    {
//        map<char,int> mymap;
//
//        mymap['x'] = 100;
//        mymap['y'] = 200;
//        mymap['z'] = 300;
//
//        // show content:
//        map<char,int>::reverse_iterator rit;
//        for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
//            std::cout << rit->first << " => " << rit->second << '\n';
//
//    }
//
//    //empty
//    {
//        map<char,int> mymap;
//
//        mymap['a']=10;
//        mymap['b']=20;
//        mymap['c']=30;
//
//        while (!mymap.empty())
//        {
//            std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
//            mymap.erase(mymap.begin());
//        }
//
//    }
//
//    //size
//    {
//        map<char,int> mymap;
//        mymap['a']=101;
//        mymap['b']=202;
//        mymap['c']=302;
//
//        std::cout << "mymap.size() is " << mymap.size() << '\n';
//    }
//
//    //max size
//    {
//        int i;
//        map<int,int> mymap;
//
//        if (mymap.max_size()>1000)
//        {
//            for (i=0; i<1000; i++) mymap[i]=0;
//            std::cout << "The map contains 1000 elements.\n";
//        }
//        else std::cout << "The map could not hold 1000 elements.\n";
//
//    }
//
//    //operators
//    {
//        map<char,std::string> mymap;
//
//        mymap['a']="an element";
//        mymap['b']="another element";
//        mymap['c']=mymap['b'];
//
//        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
//        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
//        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
//        std::cout << "mymap['d'] is " << mymap['d'] << '\n';
//
//        std::cout << "mymap now contains " << mymap.size() << " elements.\n";
//    }
//
//    //insert
//    {
//        map<char,int> mymap;
//
//        mymap.insert ( pair<char,int>('a',100) );
//        mymap.insert ( pair<char,int>('z',200) );
//
//        pair<map<char,int>::iterator,bool> ret;
//        ret = mymap.insert ( pair<char,int>('z',500) );
//        if (ret.second==false) {
//            std::cout << "element 'z' already existed";
//            std::cout << " with a value of " << ret.first->second << '\n';
//        }
//
//        map<char,int>::iterator it = mymap.begin();
//        mymap.insert (it, pair<char,int>('b',300));
//        mymap.insert (it, pair<char,int>('c',400));
//
//        map<char,int> anothermap;
//        anothermap.insert(mymap.begin(),mymap.find('c'));
//
//        std::cout << "mymap contains:\n";
//        for (it=mymap.begin(); it!=mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//
//        std::cout << "anothermap contains:\n";
//        for (it=anothermap.begin(); it!=anothermap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
//    //erase
//    {
//        std::map<char,int> mymap;
//        std::map<char,int>::iterator it;
//
//        // insert some values:
//        mymap['a']=10;
//        mymap['b']=20;
//        mymap['c']=30;
//        mymap['d']=40;
//        mymap['e']=50;
//        mymap['f']=60;
//
//        it=mymap.find('b');
//        mymap.erase (it);
//
//        mymap.erase ('c');
//
//        it=mymap.find ('e');
//        mymap.erase ( it, mymap.end() );
//
//        // show content:
//        for (it=mymap.begin(); it!=mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//
//    }
//    //swap
//    {
//        map<char,int> foo,bar;
//
//        foo['x']=100;
//        foo['y']=200;
//
//        bar['a']=11;
//        bar['b']=22;
//        bar['c']=33;
//
//        foo.swap(bar);
//
//        std::cout << "foo contains:\n";
//        for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//
//        std::cout << "bar contains:\n";
//        for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    //key_compare
//    {
//        map<char,int> mymap;
//
//        map<char,int>::key_compare mycomp = mymap.key_comp();
//
//        mymap['a']=100;
//        mymap['b']=200;
//        mymap['c']=300;
//
//        std::cout << "mymap contains:\n";
//
//        char highest = mymap.rbegin()->first;
//
//        map<char,int>::iterator it = mymap.begin();
//        do {
//            std::cout << it->first << " => " << it->second << '\n';
//        } while ( mycomp((*it++).first, highest) );
//
//        std::cout << '\n';
//    }
//
//    //value_compare
//    {
//        map<char,int> mymap;
//
//        mymap['x']=1001;
//        mymap['y']=2002;
//        mymap['z']=3003;
//
//        std::cout << "mymap contains:\n";
//
//        pair<char,int> highest = *mymap.rbegin();
//
//        map<char,int>::iterator it = mymap.begin();
//        do {
//            std::cout << it->first << " => " << it->second << '\n';
//        } while ( mymap.value_comp()(*it++, highest) );
//    }
//    //find
//    {
//        map<char,int> mymap;
//        map<char,int>::iterator it;
//
//        mymap['a']=50;
//        mymap['b']=100;
//        mymap['c']=150;
//        mymap['d']=200;
//
//        it = mymap.find('b');
//        if (it != mymap.end())
//            mymap.erase (it);
//
//        // print content:
//        std::cout << "elements in mymap:" << '\n';
//        std::cout << "a => " << mymap.find('a')->second << '\n';
//        std::cout << "c => " << mymap.find('c')->second << '\n';
//        std::cout << "d => " << mymap.find('d')->second << '\n';
//    }
//    //count
//    {
//        map<char,int> mymap;
//        char c;
//
//        mymap ['a']=101;
//        mymap ['c']=202;
//        mymap ['f']=303;
//
//        for (c='a'; c<'h'; c++)
//        {
//            std::cout << c;
//            if (mymap.count(c)>0)
//                std::cout << " is an element of mymap.\n";
//            else
//                std::cout << " is not an element of mymap.\n";
//        }
//
//    }
//    //lower_bound
//    {
//
//        map<char,int> mymap;
//        map<char,int>::iterator itlow,itup;
//
//        mymap['a']=20;
//        mymap['b']=40;
//        mymap['c']=60;
//        mymap['d']=80;
//        mymap['e']=100;
//
//        itlow=mymap.lower_bound ('b');
//        itup=mymap.upper_bound ('d');
//
//        mymap.erase(itlow,itup);
//
//        // print content:
//        for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    //upper_bound
//    {
//        map<char,int> mymap;
//        map<char,int>::iterator itlow,itup;
//
//        mymap['a']=20;
//        mymap['b']=40;
//        mymap['c']=60;
//        mymap['d']=80;
//        mymap['e']=100;
//
//        itlow=mymap.lower_bound ('b');
//        itup=mymap.upper_bound ('d');
//
//        mymap.erase(itlow,itup);
//
//        // print content:
//        for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    //equal bound
//    {
//
//        map<char,int> mymap;
//
//        mymap['a']=10;
//        mymap['b']=20;
//        mymap['c']=30;
//
//        pair<map<char,int>::iterator,map<char,int>::iterator> ret;
//        ret = mymap.equal_range('b');
//
//        std::cout << "lower bound points to: ";
//        std::cout << ret.first->first << " => " << ret.first->second << '\n';
//
//        std::cout << "upper bound points to: ";
//        std::cout << ret.second->first << " => " << ret.second->second << '\n';
//    }
//    //****************************************STACK TESTS****************************************
//    //constructors
//    {
//        vector<int> myvector (2,200);
//        stack<int> first;
//        stack<int,vector<int> > third;
//        stack<int,vector<int> > fourth (myvector);
//        std::cout << "size of first: " << first.size() << '\n';
//        std::cout << "size of third: " << third.size() << '\n';
//        std::cout << "size of fourth: " << fourth.size() << '\n';
//    }
//
//    //empty
//    {
//        stack<int> mystack;
//        int sum (0);
//        for (int i=1;i<=10;i++) mystack.push(i);
//        while (!mystack.empty())
//        {
//            sum += mystack.top();
//            mystack.pop();
//        }
//        std::cout << "total: " << sum << '\n';
//    }
//
//    //size
//    {
//        stack<int> myints;
//        std::cout << "0. size: " << myints.size() << '\n';
//        for (int i=0; i<5; i++) myints.push(i);
//        std::cout << "1. size: " << myints.size() << '\n';
//        myints.pop();
//        std::cout << "2. size: " << myints.size() << '\n';
//    }
//
//    //top
//    {
//        stack<int> mystack;
//        mystack.push(10);
//        mystack.push(20);
//        mystack.top() -= 5;
//        std::cout << "mystack.top() is now " << mystack.top() << '\n';
//    }
//
//    //push
//    {
//        stack<int> mystack;
//        for (int i=0; i<5; ++i) mystack.push(i);
//        std::cout << "Popping out elements...";
//        while (!mystack.empty())
//        {
//            std::cout << ' ' << mystack.top();
//            mystack.pop();
//        }
//        std::cout << '\n';
//    }
//
//    //pop
//    {
//        stack<int> mystack;
//        for (int i=0; i<5; ++i) mystack.push(i);
//        std::cout << "Popping out elements...";
//        while (!mystack.empty())
//        {
//            std::cout << ' ' << mystack.top();
//            mystack.pop();
//        }
//        std::cout << '\n';
//    }
//
    return 0;
}