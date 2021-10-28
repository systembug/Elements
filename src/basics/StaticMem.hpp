//
// Created by systembug on 21. 10. 21..
//

#ifndef ELEMENTS_STATICMEM_HPP
#define ELEMENTS_STATICMEM_HPP

#include <array>
#include "3rdparty/highway/hwy/highway.h"
#define MAX_SIZE 16384

namespace elements::basics {
    template <class T, std::size_t N> requires (N <= MAX_SIZE)
    using StaticArr = std::array<T, N>;

    template <class T, std::size_t N, std::size_t ...Ns>
    static constexpr StaticArr<T, N> makeArrayImpl(std::initializer_list<T> list, std::index_sequence<Ns...>)
    {
        return std::array<T, N>{*(std::begin(list) + Ns)...};
    }

    template <class T, std::size_t N>
    static constexpr StaticArr<T, N> makeArray(std::initializer_list<T> list) {
        if (list.size() > N)
            throw std::out_of_range("The size of initializer list exceeds the original Vec size.");
        return makeArrayImpl<T, N>(list, std::make_index_sequence<N>());
    }

    template <class T, std::size_t N>
    class StaticMem {
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
        constexpr StaticMem() = default;
        constexpr StaticMem(std::initializer_list<T> list)
            : m_mem(makeArray<T, N>(list))
        {}
        virtual ~StaticMem() = default;
        constexpr StaticMem(const StaticMem& mem)
            : m_mem(mem.m_mem)
        {}
        // Not recommended
        constexpr StaticMem(StaticMem&& mem) noexcept
            : m_mem(std::move(mem.m_mem))
        {
            std::fill(std::begin(mem.m_mem), std::end(mem.m_mem), 0);
        }
        constexpr StaticMem& operator=(const StaticMem<T, N>& mem)
        {
            if (this != &mem) {
                m_mem = mem.m_mem;
            }

            return *this;
        }
        // Not recommended
        constexpr StaticMem& operator=(StaticMem<T, N>&& mem) noexcept
        {
            if (this != &mem) {
                m_mem = std::move(mem.m_mem);
                std::fill(std::begin(mem.m_mem), std::end(mem.m_mem), 0);
            }

            return *this;
        }

        public:
            inline StaticArr<T, N>& base() const { return m_mem; }
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
            constexpr void swap(StaticMem<T, N>& vec) noexcept { std::swap_ranges(begin(), end(), vec.begin()); }
            constexpr bool empty() const noexcept { return size() == 0; }
            constexpr reference front() noexcept { return *begin(); }
            constexpr const_reference front() const noexcept { return *begin(); }
            constexpr reference back() noexcept { return *end(); }
            constexpr const_reference back() const noexcept { return *end(); }

        public:
            constexpr reference operator[] (size_type idx) noexcept { return m_mem[idx]; }
            constexpr const_reference operator[] (size_type idx) const noexcept { return m_mem[idx]; }

        private:
        #if (HWY_NAMESPACE != HWY_SCALAR)
            // HWY_ALIGN StaticArr<T, N> m_mem;
            StaticArr<T, N> m_mem;
        #else
            StaticArr<T, N> m_mem;
        #endif
    };
}

#endif //ELEMENTS_STATICMEM_HPP
