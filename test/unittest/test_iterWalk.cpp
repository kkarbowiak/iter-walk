#include "iterWalk.h"

#include <catch.hpp>

#include <vector>


TEST_CASE("walk", "[iter][walk]")
{
    using veci = std::vector<int>;

    SECTION("empty")
    {
        veci vi;
        auto w = iter::walker<veci::const_iterator, veci::size_type>(vi.begin(), vi.end());
        auto b = w.begin();
        auto e = w.end();

        REQUIRE(!(b != e));
    }

    SECTION("one")
    {
        veci vi = {5};
        auto w = iter::walker<veci::const_iterator, veci::size_type>(vi.begin(), vi.end());
        auto b = w.begin();
        auto e = w.end();
        auto i = *b;

        REQUIRE(b != e);
        REQUIRE(i.is_first());
        REQUIRE(i.is_last());
        REQUIRE(i.get_index() == 0);
        REQUIRE(*i == 5);
    }

    SECTION("more")
    {
        veci vi = {3, 5, 7, 8};
        auto w = iter::walker<veci::const_iterator, veci::size_type>(vi.begin(), vi.end());
        auto b = w.begin();

        {
            auto i = *b;
            REQUIRE(i.is_first());
            REQUIRE(!i.is_last());
            REQUIRE(i.get_index() == 0);
            REQUIRE(*i == 3);
        }

        ++b;
        {
            auto i = *b;
            REQUIRE(!i.is_first());
            REQUIRE(!i.is_last());
            REQUIRE(i.get_index() == 1);
            REQUIRE(*i == 5);
        }

        ++b;
        {
            auto i = *b;
            REQUIRE(!i.is_first());
            REQUIRE(!i.is_last());
            REQUIRE(i.get_index() == 2);
            REQUIRE(*i == 7);
        }

        ++b;
        {
            auto i = *b;
            REQUIRE(!i.is_first());
            REQUIRE(i.is_last());
            REQUIRE(i.get_index() == 3);
            REQUIRE(*i == 8);
        }
    }
}
