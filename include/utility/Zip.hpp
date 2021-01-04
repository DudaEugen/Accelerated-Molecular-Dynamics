#pragma once
#ifndef TAHD_ZIP_H
#define TAHD_ZIP_H

#include <tuple>

namespace utils::zip
{
    /* This is a class for iterating over multiple objects of the same length.
    Class for "range based for" loop*/
    template<class... Args>
    class Zip
    {
        using tuple_t = std::tuple<Args&...>;
        using tuple_size = std::tuple_size<tuple_t>;
        using tuple_iterator_t = std::tuple<decltype(std::declval<Args>().begin())...>;
        using dereference_iterator_tuple_t = std::tuple<decltype(*std::declval<Args>().begin())&...>;

        tuple_t elements;

    public:
        class Iterator;

    private:
        template <std::size_t... Is>
        Iterator begin_impl(std::index_sequence<Is...>) 
        {
            return Iterator(std::get<Is>(elements).begin()...);
        }
        template <std::size_t... Is>
        Iterator end_impl(std::index_sequence<Is...> ) 
        {
            return Iterator(std::get<Is>(elements).end()...);
        }
    public:
        Zip(Args&... args) 
            : elements{ args... }
        {
        }

        Iterator begin()
        {
            return begin_impl(std::make_index_sequence<tuple_size::value>{});
        }
        Iterator end()
        {
            return end_impl(std::make_index_sequence<tuple_size::value>{});
        }
        
        class Iterator
        {
            tuple_iterator_t iterators;

            Iterator(decltype(std::declval<Args>().begin())... args)
                : iterators{ std::tuple{args...} }
            {
            }

            template<std::size_t... Is>
            dereference_iterator_tuple_t dereference_impl(std::index_sequence<Is...> ) 
            {
                dereference_iterator_tuple_t result(*(std::get<Is>(iterators))...);
                return result;
            }

            template<class... Ts> 
            void empty(Ts... t) {}

            template<std::size_t... Is>
            void increment_impl(std::index_sequence<Is...> ) 
            {
                empty(++(std::get<Is>(iterators))...);
            }
        public:
            Iterator& operator++() noexcept
            {
                increment_impl(std::make_index_sequence<tuple_size::value>{});
                return *this;
            }
            
            auto operator*()
            {
                return dereference_impl(std::make_index_sequence<tuple_size::value>{});
            }
            
            bool operator!=(Iterator& it) const noexcept
            {
                return std::get<0>(iterators) != std::get<0>(it.iterators);
            }

            friend class Zip<Args...>;
        };
    };
}

#endif  //TAHD_ZIP_H
