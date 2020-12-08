
#include "iterator_adapter/iterator_adapter.h"

#include <gtest/gtest.h>

#include <numeric>
#include <random>
#include <algorithm>
#include <vector>
#include <list>

TEST(iterator_adapter, vector_distance)
{
    std::vector<int> vec(64);
    auto distanceVec = std::distance(vec.cbegin(), vec.cend());

    eld::iterator_adapter<int, std::random_access_iterator_tag> iterBegin{vec.begin()},
            iterEnd{vec.end()};

    // does not compile
//    auto distance = std::distance(eld::make_iter_adapter((int*) nullptr),
//                                  eld::make_iter_adapter((int*) nullptr));


    auto distance = std::distance(eld::make_iter_adapter(vec.begin()),
                                  eld::make_iter_adapter(vec.end()));

    ASSERT_EQ(distance, distanceVec);
}

//TEST(iterator_adapter, vector_distance_const)
//{
//    std::vector<int> vec(64);
//    auto distanceVec = std::distance(vec.cbegin(), vec.cend());
//
//    eld::const_iterator_adapter<int, std::random_access_iterator_tag> iterBegin{vec.cbegin()},
//            iterEnd{vec.cend()};
//
//    // does not compile
////    auto distance = std::distance(eld::make_iter_adapter((int*) nullptr),
////                                  eld::make_iter_adapter((int*) nullptr));
//
//    auto distance = std::distance(iterBegin, iterEnd);
//
//    ASSERT_EQ(distance, distanceVec);
//}

TEST(iterator_adapter, vector_sorting)
{
    std::vector<int> vec(64);
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});

    std::sort(eld::make_iter_adapter(vec.begin()), eld::make_iter_adapter(vec.end()));

    ASSERT_TRUE(std::is_sorted(vec.cbegin(), vec.cend()));
}

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}