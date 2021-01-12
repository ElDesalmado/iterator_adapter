#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#include "iterator_adapter/iterator_adapter.h"

#include <gtest/gtest.h>

#include <numeric>
#include <random>
#include <algorithm>
#include <vector>
#include <list>

using RandomByteIterator = eld::iterator_adapter<uint8_t,
        std::random_access_iterator_tag>;
using RandomByteConstIterator = eld::const_iterator_adapter<uint8_t,
        std::random_access_iterator_tag>;

void sort(RandomByteIterator begin, RandomByteIterator end)
{
    std::sort(begin, end);
}

std::ptrdiff_t distance(RandomByteConstIterator cbegin, RandomByteConstIterator cend)
{
    return std::distance(cbegin, cend);
}

TEST(iterator_adapter, vector_distance)
{
std::vector<int> vec(64);
auto distanceVec = std::distance(vec.cbegin(), vec.cend());

// does not compile
//    auto distance = std::distance(eld::make_iter_adapter((int*) nullptr),
//                                  eld::make_iter_adapter((int*) nullptr));

auto distance = std::distance(eld::make_const_iter_adapter(vec.cbegin()),
                              eld::make_const_iter_adapter(vec.cend()));

ASSERT_EQ(distance, distanceVec);
}

TEST(iterator_adapter, vector_distance_wrapped)
{
std::vector<int> vec(64);
auto distanceVec = std::distance(vec.cbegin(), vec.cend());

const auto& constRefVec = vec;
auto dist = distance(constRefVec.cbegin(), constRefVec.cend());

ASSERT_EQ(dist, distanceVec);
}

TEST(iterator_adapter, vector_sorting)
{
std::vector<int> vec(64);
std::iota(vec.begin(), vec.end(), 0);
std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});

std::sort(eld::make_iter_adapter(vec.begin()), eld::make_iter_adapter(vec.end()));

ASSERT_TRUE(std::is_sorted(vec.cbegin(), vec.cend()));
}

TEST(iterator_adapter, vector_sorting_wrapped)
{
std::vector<int> vec(64);
std::iota(vec.begin(), vec.end(), 0);
std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});

sort(vec.begin(), vec.end());

ASSERT_TRUE(std::is_sorted(vec.cbegin(), vec.cend()));
}

int main(int argc, char **argv)
{
    static_assert(std::is_same<int,
            typename std::iterator_traits<
                    std::vector<int>::iterator
            >::value_type>(), "");

    typename std::iterator_traits<
            std::vector<int>::const_iterator
    >::value_type UNUSED(a) = 6;
    typename std::iterator_traits<
            std::vector<int>::iterator
    >::value_type UNUSED(b) = 6;

    static_assert(!std::is_same<const int,
            typename std::iterator_traits<
                    std::vector<int>::const_iterator
            >::value_type>(), "");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}