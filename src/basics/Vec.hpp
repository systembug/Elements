//
// Created by systembug on 21. 9. 19..
//

#ifndef ELEMENTS_VEC_HPP
#define ELEMENTS_VEC_HPP

#include "StaticMem.hpp"
#include "DynamicMem.hpp"

namespace elements::basics {
    template <class T, std::size_t N = 0> requires std::is_fundamental_v<T>
    class Vec {
        typedef T*			                            pointer;
        typedef const T*                                const_pointer;
        typedef T&                   	                reference;
        typedef const T&             	                const_reference;
        typedef T*          		                    iterator;
        typedef const T*			                    const_iterator;
        typedef std::size_t                    	        size_type;
        typedef std::ptrdiff_t                   	    difference_type;
        typedef std::reverse_iterator<iterator>	        reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    public:
        constexpr Vec()
            : m_mem()
        {}
        constexpr Vec(std::initializer_list<T> list)
           : m_mem(list)
        {}
        ~Vec() = default;
        constexpr Vec(const Vec& vec)
            : m_mem(vec.m_mem)
        {}
        constexpr Vec(Vec&& vec) noexcept
            : m_mem(std::move(vec.m_mem))
        {}
        constexpr Vec& operator=(const Vec& vec)
        {
            if (this != &vec) {
                m_mem = vec.m_mem;
            }

            return *this;
        }
        constexpr Vec& operator=(Vec&& vec) noexcept
        {
            if (this != &vec) {
                m_mem = std::move(vec.m_mem);
            }

            return *this;
        }
        constexpr Vec& operator=(Vec<T>&& vec) noexcept
        {
            if (this != &vec) {
                m_mem = std::move(vec.m_mem);
            }

            return *this;
        }

    public:
        constexpr size_type size() const noexcept { return m_mem.size(); }
        constexpr size_type max_size() const noexcept { return m_mem.size(); }
        constexpr pointer data() noexcept { return m_mem.data(); }
        constexpr const_pointer data() const noexcept { return m_mem.data(); }
        constexpr iterator begin() noexcept { return iterator(data()); }
        constexpr const_iterator begin() const noexcept { return iterator(data()); }
        constexpr iterator end() noexcept { return iterator(data() + size()); }
        constexpr const_iterator end() const noexcept { return const_iterator(data() + size()); }
        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        constexpr const_reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
        constexpr reverse_iterator rend() noexcept { return reverse_iterator(rbegin()); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(rbegin()); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }
        constexpr const_iterator cend() const noexcept { return const_iterator(data() + size()); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
        constexpr reference at(std::size_t idx) { return m_mem.at(idx); }
        constexpr void swap(Vec& vec) noexcept { std::swap_ranges(begin(), end(), vec.begin()); }
        constexpr bool empty() const noexcept { return size() == 0; }
        constexpr reference front() noexcept { return *begin(); }
        constexpr const_reference front() const noexcept { return *begin(); }
        constexpr reference back() noexcept { return *end(); }
        constexpr const_reference back() const noexcept { return *end(); }

    public:
        constexpr reference operator[] (size_type idx) noexcept { return m_mem[idx]; }
        constexpr const_reference operator[] (size_type idx) const noexcept { return m_mem[idx]; }

    public:
        StaticMem<T, N> m_mem;
    };

    template <class T> requires std::is_fundamental_v<T>
    class Vec<T, 0> {
        typedef T*			                            pointer;
        typedef const T*                                const_pointer;
        typedef T&                   	                reference;
        typedef const T&             	                const_reference;
        typedef T*          		                    iterator;
        typedef const T*			                    const_iterator;
        typedef std::size_t                    	        size_type;
        typedef std::ptrdiff_t                   	    difference_type;
        typedef std::reverse_iterator<iterator>	        reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    public:
        constexpr Vec() = default;
        constexpr Vec(std::initializer_list<T> list)
            : m_mem(list)
        {}
        constexpr Vec(size_type size)
            : m_mem(size)
        {}
        constexpr Vec(size_type size, T&& alloc)
            : m_mem(size, std::forward<T>(alloc))
        {}
        ~Vec() = default;
        constexpr Vec(const Vec& vec)
            : m_mem(vec.m_mem)
        {}
        constexpr Vec(Vec&& vec) noexcept
            : m_mem(std::move(vec.m_mem))
        {}
        constexpr Vec& operator=(const Vec& vec)
        {
            if (this != &vec) {
                m_mem = vec.m_mem;
            }

            return *this;
        }
        constexpr Vec& operator=(Vec&& vec) noexcept
        {
            if (this != &vec) {
                m_mem = std::move(vec.m_mem);
            }

            return *this;
        }

        template <std::size_t N>
        constexpr Vec& operator=(Vec<T, N>&& vec) noexcept
        {
            if (this != &vec) {
                m_mem = std::move(vec.m_mem);
            }

            return *this;
        }

    public:
        inline const DynamicMem<T>& base() const { return m_mem; }
        constexpr size_type size() const noexcept { return m_mem.size(); }
        constexpr size_type max_size() const noexcept { return m_mem.capacity(); }
        constexpr pointer data() noexcept { return m_mem.data(); }
        constexpr const_pointer data() const noexcept { return m_mem.data(); }
        constexpr iterator begin() noexcept { return iterator(data()); }
        constexpr const_iterator begin() const noexcept { return iterator(data()); }
        constexpr iterator end() noexcept { return iterator(data() + size()); }
        constexpr const_iterator end() const noexcept { return const_iterator(data() + size()); }
        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        constexpr const_reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
        constexpr reverse_iterator rend() noexcept { return reverse_iterator(rbegin()); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(rbegin()); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }
        constexpr const_iterator cend() const noexcept { return const_iterator(data() + size()); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
        constexpr reference at(std::size_t idx) { return m_mem.at(idx); }
        constexpr void swap(Vec& vec) noexcept { std::swap_ranges(begin(), end(), vec.begin()); }
        constexpr bool empty() const noexcept { return size() == 0; }
        constexpr reference front() noexcept { return *begin(); }
        constexpr const_reference front() const noexcept { return *begin(); }
        constexpr reference back() noexcept { return *end(); }
        constexpr const_reference back() const noexcept { return *end(); }

    public:
        constexpr reference operator[] (size_type idx) noexcept { return m_mem[idx]; }
        constexpr const_reference operator[] (size_type idx) const noexcept { return m_mem[idx]; }

    public:
        DynamicMem<T> m_mem;
    };

    template <class T, std::size_t N>
    constexpr inline bool operator==(const Vec<T, N>& lhs, const Vec<T, N>& rhs) {
        return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
    }

    template <class T, std::size_t N>
    constexpr inline bool operator==(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
    }

    template <class T, std::size_t N>
    constexpr inline auto operator<=>(const Vec<T, N>& lhs, const Vec<T, N>& rhs) {
        return lhs.data() <=> rhs.data();
    }

    template <class T>
    inline auto operator<=>(const Vec<T>& lhs, const Vec<T>& rhs) {
        return lhs.base() <=> rhs.base();
    }

    template <class T, std::size_t N>
    inline auto operator!=(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        return !(lhs.data() == rhs.base().data());
    }

    template <class T, std::size_t N>
    inline auto operator>(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        return !std::lexicographical_compare(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
    }

    template <class T, std::size_t N>
    inline auto operator>=(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        if (operator==(lhs, rhs)) return true;
        return operator>(lhs, rhs);
    }

    template <class T, std::size_t N>
    inline auto operator<(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        return std::lexicographical_compare(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
    }

    template <class T, std::size_t N>
    inline auto operator<=(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        if (operator==(lhs, rhs)) return true;
        return operator<(lhs, rhs);
    }
}

namespace std {
    template <std::size_t Idx, class T, std::size_t N>
        constexpr T& get(elements::basics::Vec<T, N>& vec) noexcept {
        static_assert(Idx < N, "Index is within bounds");
        return vec[Idx];
    }

    template <std::size_t Idx, class T, std::size_t N>
    constexpr const T& get(const elements::basics::Vec<T, N>& vec) noexcept {
        static_assert(Idx < N, "Index is within bounds");
        return vec[Idx];
    }

    template <std::size_t Idx, class T, std::size_t N>
    constexpr const T&& get(const elements::basics::Vec<T, N>&& vec) noexcept {
        static_assert(Idx < N, "Index is within bounds");
        return std::move(vec[Idx]);
    }
}

// TODO: apply to proxy pattern
// TODO: apply to SIMD
template <class T, std::size_t N>
static constexpr elements::basics::Vec<T, N> operator+(const elements::basics::Vec<T, N>& lhs, const elements::basics::Vec<T, N>& rhs)
{
    elements::basics::Vec<T, N> result;
#ifdef __SIMD_ENABLED__
    constexpr if (std::is_same_v<T, int8_t>) {

    }
    else {

    }
#else
    for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] + rhs[i];
#endif
    return result;
}

#endif //ELEMENTS_VEC_HPP
