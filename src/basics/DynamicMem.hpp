//
// Created by systembug on 21. 10. 21..
//

#ifndef ELEMENTS_DYNAMICMEM_HPP
#define ELEMENTS_DYNAMICMEM_HPP

#include <vector>
#include "3rdparty/highway/hwy/highway.h"
#include "DynamicMemAlloc.hpp"

namespace elements::basics {
#if (HWY_NAMESPACE != HWY_SCALAR)
    template <class T>
    using DynArr = std::vector<T, DynamicMemAlloc<T>>;
#else
    template <class T>
    using DynArr = std::vector<T>;
#endif

    template <class T>
    class DynamicMem {
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
        constexpr DynamicMem() = default;

        template <class U>
        constexpr DynamicMem(std::size_t size, U&& alloc)
            : m_mem(size, std::forward<U>(alloc))
        {}
        constexpr DynamicMem(std::initializer_list<T> list)
            : m_mem(list)
        {}
        virtual ~DynamicMem() = default;
        constexpr DynamicMem(const DynamicMem& mem)
            : m_mem(mem.m_mem)
        {}
        constexpr DynamicMem(DynamicMem&& mem) noexcept
            : m_mem(std::move(mem.m_mem))
        {}
        constexpr DynamicMem& operator=(const DynamicMem<T>& mem)
        {
            if (this != &mem) {
                m_mem = mem.m_mem;
            }

            return *this;
        }
        constexpr DynamicMem& operator=(DynamicMem<T>&& mem) noexcept
        {
            if (this != &mem) {
                m_mem = std::move(mem.m_mem);
            }

            return *this;
        }

    public:
        inline DynArr<T>& base() const { return m_mem; }
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
        constexpr void swap(DynamicMem& vec) noexcept { std::swap_ranges(begin(), end(), vec.begin()); }
        constexpr bool empty() const noexcept { return size() == 0; }
        constexpr reference front() noexcept { return *begin(); }
        constexpr const_reference front() const noexcept { return *begin(); }
        constexpr reference back() noexcept { return *end(); }
        constexpr const_reference back() const noexcept { return *end(); }

    public:
        constexpr reference operator[] (size_type idx) noexcept { return m_mem[idx]; }
        constexpr const_reference operator[] (size_type idx) const noexcept { return m_mem[idx]; }

    private:
        DynArr<T> m_mem;
    };

    template <class T>
    inline auto operator<=>(const DynamicMem<T>& lhs, const DynamicMem<T>& rhs) {
        return lhs.data() <=> rhs.data();
    }
}


#endif //ELEMENTS_DYNAMICMEM_HPP
