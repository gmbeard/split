#include "split/split.hpp"

#include "catch.hpp"

TEST_CASE("Split", "[split]") {

    constexpr char PHRASE[] = "1, 2, 3, 4";
    constexpr char DELIM[] = ",";

    SECTION("Should have correct number of slices") {

        auto first = split::SplitIterator(
            {std::begin(PHRASE), std::end(PHRASE)-1},
            {std::begin(DELIM), std::end(DELIM)-1}
        );

        auto last = split::SplitIterator(
            {std::end(PHRASE)-1, std::end(PHRASE)-1});

        size_t n = 0;
        while (first != last) {
            n += 1;
            ++first; ++last;
        }

        REQUIRE(4 == n);
    }

    SECTION("Slices should have correct values") {

        auto first = split::SplitIterator(
            {std::begin(PHRASE), std::end(PHRASE)-1},
            {std::begin(DELIM), std::end(DELIM)-1}
        );

        auto last = split::SplitIterator(
            {std::end(PHRASE)-1, std::end(PHRASE)-1});

        std::vector<std::string> values;

        while (first != last) {
            values.emplace_back(first->start, first->end);
            first++; last++;
        }

        REQUIRE(values[0] == "1");
        REQUIRE(values[1] == " 2");
        REQUIRE(values[2] == " 3");
        REQUIRE(values[3] == " 4");
    }

    SECTION("Split function should be enumerable") {
        using std::begin;
        using std::end;

//        auto r = split::split(begin(PHRASE), end(PHRASE)-1,
//                              begin(DELIM), end(DELIM)-1);

        auto r = split::split(PHRASE, DELIM);
        std::vector<std::string> values;

        for (auto const& s : r) {
            values.push_back(split::to_string(s));
        }

        REQUIRE(4 == values.size());
        REQUIRE(values[0] == "1");
        REQUIRE(values[1] == " 2");
        REQUIRE(values[2] == " 3");
        REQUIRE(values[3] == " 4");
    }
}
