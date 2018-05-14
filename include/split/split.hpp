#ifndef SPLIT_SPLIT_HPP_INCLUDED
#define SPLIT_SPLIT_HPP_INCLUDED

#include <iterator>
#include <string>

namespace split {

    struct Slice {
        constexpr Slice(char const* s, char const* e) :
            start{s}
        ,   end{e}
        { }

        friend auto to_string(Slice const& slice) -> std::string;

        auto operator==(Slice const& other) const -> bool;
        auto operator!=(Slice const& other) const -> bool;

        constexpr auto size() const -> size_t {
            return end - start;
        }

        char const* start;
        char const* end;
    };

    auto to_string(Slice const& slice) -> std::string;

    auto operator==(char const* lhs, Slice const& rhs) -> bool;
    auto operator!=(char const* lhs, Slice const& rhs) -> bool;
    auto operator==(Slice const& lhs, char const* rhs) -> bool;
    auto operator!=(Slice const& lhs, char const* rhs) -> bool;

    constexpr Slice NONE = { "", "" };

    struct SplitIterator {
        using value_type = Slice;
        using reference = value_type const&;
        using pointer = value_type const*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        SplitIterator(Slice range, Slice needle = NONE);
        auto operator++() -> SplitIterator&;
        auto operator++(int) -> SplitIterator;
        auto operator*() const -> reference;
        auto operator->() const -> pointer;

        friend auto operator==(SplitIterator const& lhs,
                               SplitIterator const& rhs) -> bool;

        friend auto operator!=(SplitIterator const& lhs,
                               SplitIterator const& rhs) -> bool;
    private:
        Slice current_;
        Slice needle_;
        char const* end_;
    };

    struct SplitResult {
        using iterator = SplitIterator;
        using const_iterator = iterator;
        using value_type = typename iterator::value_type;

        SplitResult(SplitIterator first, SplitIterator last);
        auto begin() const -> SplitIterator;
        auto end() const -> SplitIterator;
        auto size() const -> size_t;

    private:
        SplitIterator first_;
        SplitIterator last_;
    };

    auto split(std::string const& haystack, std::string const& needle)
        -> SplitResult;

    auto split(char const* haystack, char const* needle)
        -> SplitResult;

    auto split(char const* first, char const* last,
               char const* needle_f, char const* needle_l) 
        -> SplitResult;
}
#endif //SPLIT_SPLIT_HPP_INCLUDED
