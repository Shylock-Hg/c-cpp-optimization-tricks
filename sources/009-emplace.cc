// The emplace API provided by container to put in.
// The API provided as below usually:
// emplace_front, emplace_back, emplace, emplace_after, emplace_hint

#include <cassert>

#include <iostream>
#include <vector>
#include <utility>

int main(int argc, char * argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "009 emplace" << std::endl;

    std::vector<std::pair<int, int>> t;

    // t.push_back(2, 3);  //!< error
    // copy
    t.push_back(std::pair<int, int> (2, 3));

    // Construct the std::pair<int, int> just in the memory of vector itself.
    // So need the constructor of item.
    // Not copy or move but just construct directly!
    t.emplace_back(2, 3);
    // Copy contructor
    t.emplace_back(std::pair<int, int> (2, 3));

    assert(3 == t.size());

    return 0;
}
