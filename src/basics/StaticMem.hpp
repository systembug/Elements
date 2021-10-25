//
// Created by systembug on 21. 10. 21..
//

#ifndef ELEMENTS_STATICMEM_HPP
#define ELEMENTS_STATICMEM_HPP

#include <array>

namespace elements::basics {
    template <class T, std::size_t N, std::size_t ...Ns>
    static constexpr std::array<T, N> makeArrayImpl(std::initializer_list<T> list, std::index_sequence<Ns...>)
    {
        return std::array<T, N>{*(std::begin(list) + Ns)...};
    }

    template <class T, std::size_t N>
    static constexpr std::array<T, N> makeArray(std::initializer_list<T> list) {
        if (list.size() > N)
            throw std::out_of_range("The size of initializer list exceeds the original Vec size.");
        return makeArrayImpl<T, N>(list, std::make_index_sequence<N>());
    }

    template <class T, std::size_t N>
    class StaticMem : public std::array<T, N> {
    public:
        constexpr StaticMem() = default;
        constexpr StaticMem(std::initializer_list<T> list)
            : std::array<T, N>(makeArray<T, N>(list))
        {}
        virtual ~StaticMem() = default;
        constexpr StaticMem(const StaticMem& mem)
            : std::array<T, N>(mem)
        {}
        // Not recommended
        constexpr StaticMem(StaticMem&& mem) noexcept
            : std::array<T, N>(std::move(mem))
        {
            std::fill(std::begin(mem), std::end(mem), 0);
        }
        constexpr StaticMem& operator=(const StaticMem<T, N>& mem)
        {
            if (this != &mem) {
                std::array<T, N>::operator=(mem);
            }

            return *this;
        }
        // Not recommended
        constexpr StaticMem& operator=(StaticMem<T, N>&& mem) noexcept
        {
            if (this != &mem) {
                std::array<T, N>::operator=(std::move(mem));
                std::fill(std::begin(mem), std::end(mem), 0);
            }

            return *this;
        }
    };
}

#endif //ELEMENTS_STATICMEM_HPP
