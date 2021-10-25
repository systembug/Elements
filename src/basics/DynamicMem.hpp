//
// Created by systembug on 21. 10. 21..
//

#ifndef ELEMENTS_DYNAMICMEM_HPP
#define ELEMENTS_DYNAMICMEM_HPP

#include <vector>

namespace elements::basics {
    template <class T>
    class DynamicMem : public std::vector<T> {
    public:
        constexpr DynamicMem() = default;
        constexpr DynamicMem(std::size_t size, T&& alloc)
            : std::vector<T>(size, std::forward<T>(alloc))
        {}
        constexpr DynamicMem(std::initializer_list<T> list)
            : std::vector<T>(list)
        {}
        virtual ~DynamicMem() = default;
        constexpr DynamicMem(const DynamicMem& mem)
            : std::vector<T>(mem)
        {}
        constexpr DynamicMem(DynamicMem&& mem) noexcept
            : std::vector<T>(std::move(mem))
        {}
        constexpr DynamicMem& operator=(const DynamicMem<T>& mem)
        {
            if (this != &mem) {
                std::vector<T>::operator=(mem);
            }

            return *this;
        }
        constexpr DynamicMem& operator=(DynamicMem<T>&& mem) noexcept
        {
            if (this != &mem) {
                std::vector<T>::operator=(std::move(mem));
            }

            return *this;
        }
    };
}


#endif //ELEMENTS_DYNAMICMEM_HPP
