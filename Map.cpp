#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <random>
#include <chrono>
#include <iterator>
#include <cassert>
# include "Map.hpp"


class MyMovable {
    public:
        int val;
        bool was_moved = false;
        MyMovable()
        {
        };


        MyMovable(int i) : val{i} { }
        // WARNING if you can't compile with the following line uncommented, you
        // may not be move constructing when you insert
        //MyMovable(const MyMovable&) = delete;
       //MyMovable(MyMovable&& other) {
         //   other.was_moved = true;
        //} 
        bool operator==(const MyMovable& other) const {
            return this->val < other.val;
        }
};

void move_insert() {
    cs540::Map<int, MyMovable> my_map;
    MyMovable mv{1};
    my_map.insert({1, std::move(mv)});
    assert(mv.was_moved);
}



 cs540::Map<int, int> cubes(int low, int high)
	 {
    cs540::Map<int, int> cb;
    for (int i = low; i < high; ++i) {
        cb.insert({i, i*i*i});
    }
    return cb;
    }

    void stress(int stress_size) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<unsigned int> dist(0, 10000);

    cs540::Map<int, int> m;

    for(int i = 0; i < stress_size; ++i) {
        auto g = dist(gen);
        m.insert({g, g});
    }

    int num_erases = gen() % m.size();
    for(int i = 0; i < num_erases; ++i) {
        //select a random element
        int choice = gen() % m.size();
        auto iter = std::begin(m);
        for (int j = 0; j < choice; ++j) {
            ++iter;
        }
    m.erase(iter);
    }
}


// unrealistic examples
void access_by_key() {
    cs540::Map<int, long> m;
    m.insert({10, 10});
    m.insert({3, 3});
    m.insert({20, 20});
    m.insert({15, 15});

    m.at(10);
    bool thrown = false;
    try {
        m.at(10000);
    } catch (std::out_of_range) {
        thrown = true;
    }
    assert(thrown); // the .at should have thrown an exception

    const auto& m_ref = m;
    m_ref.at(10); // const .at

    auto iter = m.find(3);
    assert((*iter).second == 3);

    auto iter2 = m.find(100000); // not in map, should give iterator to end()
    assert(iter2 == std::end(m));

    m[30] = 30; // should default construct

    m.remove(10);
    assert(m.find(10) == std::end(m)); // 10 shouldn't be in the map anymore
}



void count_words() {
cs540::Map<std::string, int> words_count;

    // just a big list of words
    auto words = {"this", "is", "a", "string", "with", "words", "some",
        "words", "in", "the", "string", "repeat", "the", "more", "they",
        "repeat", "the", "more", "they", "should", "count", "they", "more",
        "they", "count", "the", "more", "they", "will", "have", "their",
        "count", "increased"};
        
    for (auto& word : words) {
        // this works because int can be default constructed, and the 
        // default of int (by doing int{} ) is 0.
		   words_count[word] += 1; // add 1 to the count
    }
 
    // print the frequency of each word
    std::cout << "word frequency:\n";
    for (auto& count : words_count) { // uses .begin() and .end()
        std::cout << count.first << ": " << count.second +1<< '\n';
    }
    
    std::cout << "word frequency reversed order:\n";
    auto riter = words_count.rbegin();
    for (; riter != words_count.rend(); ++riter) {
        std::cout << (*riter).first << ": " << (*riter).second +1<< '\n';
    }   
	std::cout << (*riter).first << ": " << (*riter).second +1<< '\n'; 
	
}




using namespace cs540;
using namespace std;
int main()
{
	//test cases
	
	//=================count words tested ===============================/
	 count_words();
	 
    //====================access by key test ====================================//
	  access_by_key();
   //===========================Stress test ==========================================//
 	    stress(10000);

	//============================cube test ====================================================//
	auto cube = cubes(-5, 10); // move construct returned value
    std::cout << cube.at(-2) << '\n'; // -8
    std::cout << cube.at(5) << '\n';  // 125
	
	
	 const int n = 30;
      try {
        std::cout << cube.at(n) << '\n'; // 30 is not in the Map
    } catch (std::out_of_range) {
        std::cout << n << " not in cubes range\n";
    }
     //=================Range Insert test=============================================//
    
  	  	  std::vector<std::pair<string, int>> v = {{"hi", 2}, {"bye", 4}, {"hi", 1}, {"bye", 5}};
          std::vector<std::pair<int, int>> u = {{1, 2}, {3, 4}, {1, 1}, {110, 5}};
           auto i = v.begin();
           auto j = v.end();

           cs540::Map<string, int> y;   
            y.insert(i, j);
  //=======================range insert tested==========================//
    
     // constructors and assignment examples:
    // initializer_list example
    cs540::Map<int, double> int_double_map {{1, 1.0}, {3, 5.67}, {13, 6.9}};

    // must support copy construction
    cs540::Map<int, double> copy_example{int_double_map};

    // must support move construction
    cs540::Map<int, double> move_example {std::move(int_double_map)};

    cs540::Map<int, double> assign_example;
    // must support copy assignment
    assign_example = copy_example;
    // must support move assignment
    assign_example = std::move(move_example);

    // moved-from object must still support assignment
    move_example = copy_example;

     //=======================================================================//
     
  //not using move insert  
   // move_insert();
        
return 0;
}



