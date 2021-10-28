//
// Created by systembug on 21. 10. 27..
//

#ifndef ELEMENTS_DYNAMICMEMALLOC_HPP
#define ELEMENTS_DYNAMICMEMALLOC_HPP

#include <memory>
#include "hwy/aligned_allocator.h"

namespace elements::basics {
    template <class T>
    struct DynamicMemAlloc {
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

        template <class U>
        struct rebind {
            typedef DynamicMemAlloc<U> other;
        };

        DynamicMemAlloc() = default;
        ~DynamicMemAlloc() = default;

        pointer allocate(size_type n, const void* hint = 0)
        {
            void* ptr = hwy::AllocateAlignedBytes(sizeof(size_type) * n, nullptr, nullptr);
            if (ptr == nullptr)
                throw std::bad_alloc();
            return reinterpret_cast<pointer>(ptr);
        }

        void deallocate(pointer p, size_type /* unused */)
        {
            return hwy::FreeAlignedBytes(reinterpret_cast<void*>(p), nullptr, nullptr);
        }

        size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

        template <class U, class... Args>
        void construct(U* p, Args&&... args) {
            new(p) U(std::forward<Args>(args)...);
        }

        template <class U>
        void destroy(U* p) {
            p->~U();
        }
    };
}

#endif //ELEMENTS_DYNAMICMEMALLOC_HPP
