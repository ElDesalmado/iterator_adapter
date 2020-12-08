#pragma once

#include <iterator>

namespace eld
{
    namespace detail
    {
        template<typename IterR, typename IterL>
        using iter_same_value_type = std::is_same<
                typename std::iterator_traits<IterR>::value_type,
                typename std::iterator_traits<IterL>::value_type>;

        template<typename IterR, typename IterL>
        using iter_same_category = std::is_same<
                typename std::iterator_traits<IterR>::iterator_category,
                typename std::iterator_traits<IterL>::iterator_category>;

        template<typename Iter>
        using iterator_value_type_t = typename std::iterator_traits<Iter>::value_type;

        template<typename Iter>
        using iterator_category_t = typename std::iterator_traits<Iter>::iterator_category;

        // TODO: implement using these classes?
        template<typename T, typename C>
        struct iter_adapter_base
        {
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = C;
        };

        template<typename T, typename C>
        struct iter_adapter_base<const T, C>
        {
            using difference_type = std::ptrdiff_t;
            using value_type = const T;
            using pointer = const T *;
            using reference = const T &;
            using iterator_category = C;
        };

    }

    template<typename, typename>
    struct iterator_adapter;

    template<typename T>
    class iterator_adapter<T, std::random_access_iterator_tag>
    {
        using this_type = iterator_adapter<T, std::random_access_iterator_tag>;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        template<typename RandomIter, typename = typename
        std::enable_if<
                detail::iter_same_value_type<this_type, RandomIter>() &&
                detail::iter_same_value_type<this_type, RandomIter>()
        >::type>
        constexpr explicit iterator_adapter(RandomIter iter)
                : ptr_(&*iter)
        {}

        constexpr iterator_adapter(const iterator_adapter &other)
                : ptr_(other.ptr_)
        {}

        iterator_adapter(iterator_adapter &&other) noexcept
                : ptr_(other.ptr_)
        {
                    other.ptr_ = nullptr;
        }

        iterator_adapter &operator=(const iterator_adapter &other)
        {
            ptr_ = other.ptr_;
            return *this;
        }

        iterator_adapter &operator=(iterator_adapter &&other) noexcept
        {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
            return *this;
        }

        // Iterator
        value_type &operator*()
        {
            return *ptr_;
        }

        iterator_adapter &operator++()
        {
            ptr_ = std::next(ptr_);
            return *this;
        }

        // InputIterator
        friend bool operator==(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return lhs.ptr_ == rhs.ptr_;
        }

        friend bool operator!=(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return !(lhs == rhs);
        }

        value_type &operator->()
        {
            return *ptr_;
        }

        const value_type &operator->() const
        {
            return *ptr_;
        }

        iterator_adapter operator++(int)
        {
            const auto tmp = *this;
            ++*this;
            return tmp;
        }

        // ForwardIterator
        constexpr iterator_adapter()
                : ptr_(nullptr)
        {}

        // BidirectionalIterator
        iterator_adapter &operator--()
        {
            ptr_ = std::prev(ptr_);
            return *this;
        }

        iterator_adapter operator--(int) &
        {
            const auto tmp = *this;
            --*this;
            return tmp;
        }

        // RandomAccessIterator
        iterator_adapter &operator+=(difference_type rhs)
        {
            ptr_ = std::next(ptr_, rhs);
            return *this;
        }

        friend iterator_adapter operator+(const iterator_adapter &lhs, difference_type rhs)
        {
            auto tmp = lhs;
            tmp += rhs;
            return tmp;
        }

        friend iterator_adapter operator+(difference_type lhs, const iterator_adapter &rhs)
        {
            return rhs + lhs;
        }

        iterator_adapter &operator-=(difference_type rhs)
        {
            ptr_ = std::prev(ptr_, rhs);
            return *this;
        }

        friend iterator_adapter operator-(const iterator_adapter &lhs, difference_type rhs)
        {
            auto tmp = lhs;
            tmp -= rhs;
            return tmp;
        }

        friend iterator_adapter operator-(difference_type lhs, const iterator_adapter &rhs)
        {
            return rhs - lhs;
        }

        friend difference_type operator-(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return std::distance(rhs.ptr_, lhs.ptr_);
        }

        reference operator[](size_t i) const
        {
            return *(*this + i);
        }

        friend bool operator<(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return lhs.ptr_ < rhs.ptr_;
        }

        friend bool operator<=(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return lhs.ptr_ <= rhs.ptr_;
        }

        friend bool operator>(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return lhs.ptr_ > rhs.ptr_;
        }

        friend bool operator>=(const iterator_adapter &lhs, const iterator_adapter &rhs)
        {
            return lhs.ptr_ >= rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    template<typename, typename>
    struct const_iterator_adapter;

    template<typename T>
    class const_iterator_adapter<T, std::random_access_iterator_tag>
    {
        using this_type = iterator_adapter<T, std::random_access_iterator_tag>;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;
        using reference = const T &;
        using iterator_category = std::random_access_iterator_tag;

        template<typename RandomIter, typename = typename
        std::enable_if<
                detail::iter_same_value_type<this_type, RandomIter>() &&
                detail::iter_same_value_type<this_type, RandomIter>()
        >::type>
        constexpr explicit const_iterator_adapter(RandomIter iter)
                : ptr_(&*iter)
        {}

        constexpr const_iterator_adapter(const const_iterator_adapter &other)
                : ptr_(other.ptr_)
        {}

        const_iterator_adapter(const_iterator_adapter &&other) noexcept
                : ptr_(other.ptr_)
        {
              other.ptr_ = nullptr;
        }

        const_iterator_adapter &operator=(const const_iterator_adapter &other)
        {
            ptr_ = other.ptr_;
            return *this;
        }

        const_iterator_adapter &operator=(const_iterator_adapter &&other) noexcept
        {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
            return *this;
        }

        // Iterator
        value_type &operator*()
        {
            return *ptr_;
        }

        const_iterator_adapter &operator++()
        {
            ptr_ = std::next(ptr_);
            return *this;
        }

        // InputIterator
        friend bool operator==(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return lhs.ptr_ == rhs.ptr_;
        }

        friend bool operator!=(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return !(lhs == rhs);
        }

        value_type &operator->()
        {
            return *ptr_;
        }

        const value_type &operator->() const
        {
            return *ptr_;
        }

        const_iterator_adapter operator++(int)
        {
            const auto tmp = *this;
            ++*this;
            return tmp;
        }

        // ForwardIterator
        constexpr const_iterator_adapter()
                : ptr_(nullptr)
        {}

        // BidirectionalIterator
        const_iterator_adapter &operator--()
        {
            ptr_ = std::prev(ptr_);
            return *this;
        }

        const_iterator_adapter operator--(int) &
        {
            const auto tmp = *this;
            --*this;
            return tmp;
        }

        // RandomAccessIterator
        const_iterator_adapter &operator+=(difference_type rhs)
        {
            ptr_ = std::next(ptr_, rhs);
            return *this;
        }

        friend const_iterator_adapter operator+(const const_iterator_adapter &lhs, difference_type rhs)
        {
            auto tmp = lhs;
            tmp += rhs;
            return tmp;
        }

        friend const_iterator_adapter operator+(difference_type lhs, const const_iterator_adapter &rhs)
        {
            return rhs + lhs;
        }

        const_iterator_adapter &operator-=(difference_type rhs)
        {
            ptr_ = std::prev(ptr_, rhs);
            return *this;
        }

        friend const_iterator_adapter operator-(const const_iterator_adapter &lhs, difference_type rhs)
        {
            auto tmp = lhs;
            tmp -= rhs;
            return tmp;
        }

        friend const_iterator_adapter operator-(difference_type lhs, const const_iterator_adapter &rhs)
        {
            return rhs - lhs;
        }

        friend difference_type operator-(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return std::distance(rhs.ptr_, lhs.ptr_);
        }

        reference operator[](size_t i) const
        {
            return *(*this + i);
        }

        friend bool operator<(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return lhs.ptr_ < rhs.ptr_;
        }

        friend bool operator<=(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return lhs.ptr_ <= rhs.ptr_;
        }

        friend bool operator>(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return lhs.ptr_ > rhs.ptr_;
        }

        friend bool operator>=(const const_iterator_adapter &lhs, const const_iterator_adapter &rhs)
        {
            return lhs.ptr_ >= rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    template<typename Iter>
    iterator_adapter<detail::iterator_value_type_t<Iter>, detail::iterator_category_t<Iter>>
    constexpr make_iter_adapter(Iter iter)
    {
        return iterator_adapter<detail::iterator_value_type_t<Iter>, detail::iterator_category_t<Iter>>(iter);
    }

}

struct random_iter_sample
{
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int *;
    using reference = int &;
    using iterator_category = std::random_access_iterator_tag;
};

static_assert(std::is_same<typename std::iterator_traits<random_iter_sample>::iterator_category,
        std::random_access_iterator_tag>::value, "");

namespace scoped
{
    struct random_iter_sample
    {
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int *;
        using reference = int &;
        using iterator_category = std::random_access_iterator_tag;
    };

}
