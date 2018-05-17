#include "split/split.hpp"
#include <algorithm>
#include <cassert>
#include <string>

using namespace split;

auto Slice::operator==(Slice const& other) const -> bool {
    if (size() != other.size()) {
        return false;
    }

    auto r = start;
    auto l = other.start;

    while (r != end) {
        if (*r++ != *l++) {
            return false;
        }
    }

    return true;
}

auto Slice::operator!=(Slice const& other) const -> bool {
    return !(*this == other);
}

auto split::to_string(Slice const& slice) -> std::string {
    assert(slice.start <= slice.end);
    return { slice.start, slice.end };
}

SplitIterator::SplitIterator(Slice range, Slice needle) :
    current_{NONE}
,   needle_{needle}
,   end_{range.end}
{
    assert(range.start <= range.end);
    assert(needle.start <= needle.end);

    auto pos = std::search(range.start,
                           range.end,
                           needle_.start,
                           needle_.end);
    current_ = {
        range.start,
        pos
    };
}

auto SplitIterator::operator++() -> SplitIterator& {
    auto dist = std::distance(current_.end, end_);
    auto needle_size = std::distance(needle_.start, needle_.end);

    if (dist <= needle_size || current_.end == end_) {
        current_ = { end_, end_ };
        return *this;
    }

    assert((current_.end + needle_size) < end_);

    current_.start = current_.end + needle_size;
    current_.end = 
        std::search(current_.start, end_,
                    needle_.start, needle_.end);
    return *this;
}

auto SplitIterator::operator++(int) -> SplitIterator {
    auto tmp = *this;
    operator++();
    return tmp;
}

auto SplitIterator::operator*() const -> SplitIterator::reference {
    return current_;
}

auto SplitIterator::operator->() const -> SplitIterator::pointer {
    return std::addressof(current_);
}

SplitResult::SplitResult(SplitIterator first,
                         SplitIterator last) :
    first_{first}
,   last_{last}
{ }

auto SplitResult::begin() const -> SplitIterator {
    return first_;
}

auto SplitResult::end() const -> SplitIterator {
    return last_;
}

auto SplitResult::size() const -> size_t {
    return std::distance(first_, last_);
}

auto split::operator==(SplitIterator const& lhs,
                       SplitIterator const& rhs) -> bool
{
    return lhs.current_.end == rhs.current_.end
        && lhs.current_.start == rhs.current_.start;
}

auto split::operator!=(SplitIterator const& lhs,
                       SplitIterator const& rhs) -> bool
{
    return !(lhs == rhs);
}

auto split::split(std::string& h, std::string& n)
    -> SplitResult
{
    return split(h.c_str(), n.c_str());
}

auto split::split(char const* haystack, char const* needle)
    -> SplitResult
{
    auto haystack_end = haystack + std::strlen(haystack);
    auto needle_end = needle + std::strlen(needle);

    return split(haystack, haystack_end,
                 needle, needle_end);
}

auto split::split(char const* first, char const* last,
                  char const* needle_f, char const* needle_l) 
    -> SplitResult 
{
    return {
        { { first, last }, { needle_f, needle_l } },
        { { last, last } }
    };
}

auto split::operator==(char const* lhs, 
                       Slice const& rhs) -> bool 
{
    return Slice { lhs, lhs + std::strlen(lhs) } == rhs;

}

auto split::operator!=(char const* lhs,
                       Slice const& rhs) -> bool
{
    return !(lhs == rhs);
}

auto split::operator==(Slice const& lhs,
                       char const* rhs) -> bool
{
    return rhs == lhs;
}

auto split::operator!=(Slice const& lhs,
                       char const* rhs) -> bool
{
    return rhs != lhs;
}
