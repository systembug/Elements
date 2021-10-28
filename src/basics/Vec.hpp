//
// Created by systembug on 21. 9. 19..
//

#ifndef ELEMENTS_VEC_HPP
#define ELEMENTS_VEC_HPP

#include "StaticMem.hpp"
#include "DynamicMem.hpp"

#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "src/basics/Vec.hpp"
#include "hwy/highway.h"
#include "hwy/foreach_target.h"

HWY_BEFORE_NAMESPACE();
namespace elements::basics {
namespace HWY_NAMESPACE {
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
        constexpr Vec operator-() noexcept
        {
            return Vec();
        }

    public:
        inline StaticMem<T, N>& base() const { return m_mem; }
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
        typedef T                                       value_type;
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
        constexpr Vec(size_type size, value_type alloc)
            : m_mem(size, alloc)
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
        constexpr Vec operator-() noexcept
        {
            return Vec();
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

    template <class T>
    constexpr inline bool operator==(const Vec<T>& lhs, const Vec<T>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
    }

    template <class T, std::size_t N>
    constexpr inline bool operator==(const Vec<T, N>& lhs, const Vec<T>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
    }

    template <class T, std::size_t N>
    constexpr inline bool operator==(const Vec<T>& lhs, const Vec<T, N>& rhs) {
        return operator==(rhs, lhs);
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
}

HWY_AFTER_NAMESPACE();

HWY_BEFORE_NAMESPACE();
namespace elements::basics {
namespace HWY_NAMESPACE {
    static constexpr void test() {
        int a = 0;
    }
    template <class T, std::size_t N>
    static constexpr Vec<T, N> addStaticStatic(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
        Vec<T, N> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Add(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T>
    static constexpr Vec<T> addDynDyn(const Vec<T>& lhs, const Vec<T>& rhs) {
        Vec<T> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Add(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T, std::size_t N>
    static constexpr Vec<T, N> addStaticDyn(const Vec<T, N>& lhs, const Vec<T>& rhs)
    {
        Vec<T, N> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Add(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T, std::size_t N>
    static constexpr Vec<T, N> subStaticStatic(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
        Vec<T, N> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Sub(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T>
    static constexpr Vec<T> subDynDyn(const Vec<T>& lhs, const Vec<T>& rhs) {
        Vec<T> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Sub(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T, std::size_t N>
    static constexpr Vec<T, N> subStaticDyn(const Vec<T, N>& lhs, const Vec<T>& rhs)
    {
        Vec<T, N> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Sub(x, y), data, result.data() + i);
        }
        return result;
    }

    template <class T, std::size_t N>
    static constexpr Vec<T, N> subDynStatic(const Vec<T>& lhs, const Vec<T, N>& rhs)
    {
        Vec<T, N> result(lhs.size(), 0);
        const hwy::HWY_NAMESPACE::ScalableTag<T> data;
        for (auto i = 0; i < lhs.size(); i += hwy::HWY_NAMESPACE::Lanes(data)) {
            const auto x = hwy::HWY_NAMESPACE::Load(data, lhs.data() + i);
            const auto y = hwy::HWY_NAMESPACE::Load(data, rhs.data() + i);
            hwy::HWY_NAMESPACE::Store<T>(hwy::HWY_NAMESPACE::Sub(x, y), data, result.data() + i);
        }

        return result;
    }
    // NOLINTNEXTLINE(google-readability-namespace-comments)
}
}

HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace elements::basics {
    HWY_EXPORT(test);
    HWY_EXPORT(addStaticStatic);
    HWY_EXPORT(addDynDyn);
    HWY_EXPORT(addStaticDyn);
    HWY_EXPORT(subStaticStatic);
    HWY_EXPORT(subDynDyn);
    HWY_EXPORT(subStaticDyn);
    HWY_EXPORT(subDynStatic);

    // TODO: apply to proxy pattern
    template <class T, std::size_t N>
    static constexpr Vec<T, N> operator+(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
#if (HWY_NAMESPACE != HWY_SCALAR)
        return HWY_DYNAMIC_DISPATCH(addStaticStatic)(lhs, rhs);
#else
        Vec<T, N> result;
        for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] + rhs[i];
        return result;
#endif
    }

    // TODO: apply to proxy pattern
    template <class T>
    static constexpr Vec<T> operator+(const Vec<T>& lhs, const Vec<T>& rhs)
    {
#if (HWY_NAMESPACE != HWY_SCALAR)
        return HWY_DYNAMIC_DISPATCH(addDynDyn)(lhs, rhs);
#else
        Vec<T> result(lhs.size(), 0);
        for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] + rhs[i];
        return result;
#endif
}

// TODO: apply to proxy pattern
template <class T, std::size_t N>
static constexpr Vec<T, N> operator+(const Vec<T, N>& lhs, const Vec<T>& rhs)
{

#if (HWY_NAMESPACE != HWY_SCALAR)
    return HWY_DYNAMIC_DISPATCH(addStaticDyn)(lhs, rhs);
#else
    Vec<T, N> result;
    std::fill(std::begin(result), std::end(result), 0);
    for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] + rhs[i];
    return result;
#endif
}

// TODO: apply to proxy pattern
template <class T, std::size_t N>
static constexpr Vec<T, N> operator-(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
{
#if (HWY_NAMESPACE != HWY_SCALAR)
     return HWY_DYNAMIC_DISPATCH(subStaticStatic)(lhs, rhs);
#else
     Vec<T, N> result;
     for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] - rhs[i];
     return result;
#endif
}

// TODO: apply to proxy pattern
template <class T>
static constexpr Vec<T> operator-(const Vec<T>& lhs, const Vec<T>& rhs)
{
#if (HWY_NAMESPACE != HWY_SCALAR)
    return HWY_DYNAMIC_DISPATCH(subDynDyn)(lhs, rhs);
#else
    Vec<T> result(lhs.size(), 0);
    for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] - rhs[i];
    return result;
#endif
}

// TODO: apply to proxy pattern
template <class T, std::size_t N>
static constexpr Vec<T, N> operator-(const Vec<T, N>& lhs, const Vec<T>& rhs)
{
#if (HWY_NAMESPACE != HWY_SCALAR)
    return HWY_DYNAMIC_DISPATCH(subStaticDyn)(lhs, rhs);
#else
    Vec<T, N> result;
    std::fill(std::begin(result), std::end(result), 0);
    for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] - rhs[i];
    return result;
#endif
}

// TODO: apply to proxy pattern
template <class T, std::size_t N>
static constexpr Vec<T, N> operator-(const Vec<T>& lhs, const Vec<T, N>& rhs)
{
#if (HWY_NAMESPACE != HWY_SCALAR)
    return HWY_DYNAMIC_DISPATCH(subDynStatic)(lhs, rhs);
#else
    Vec<T, N> result;
    std::fill(std::begin(result), std::end(result), 0);
    for (auto i = 0; i < lhs.size(); ++i) result[i] = lhs[i] - rhs[i];
    return result;
#endif
}

template <class T, std::size_t N>
static constexpr Vec<T, N> operator+(const Vec<T>& lhs, const Vec<T, N>& rhs)
{
    return operator+(rhs, lhs);
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

#endif
#endif //ELEMENTS_VEC_HPP
