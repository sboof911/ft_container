/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:44:22 by amaach            #+#    #+#             */
/*   Updated: 2022/06/29 03:02:44 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{
   template <typename T>
    class reverse_iterator 
    {
    public:
        typedef T                                                iterator_type;
        typedef typename iterator_traits<T>::iterator_category   iterator_category;
        typedef typename iterator_traits<T>::value_type          value_type;
        typedef typename iterator_traits<T>::difference_type     difference_type;
        typedef typename iterator_traits<T>::pointer             pointer;
        typedef typename iterator_traits<T>::reference           reference;

    private:
        iterator_type _Iter;

    public:
        reverse_iterator() : _Iter() {}
        explicit reverse_iterator(iterator_type it) : _Iter(it) {}
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &rev_it) : _Iter(rev_it.base()) {}

        iterator_type base() const { return _Iter; }

        reference operator*() const
        {
            iterator_type tmp = _Iter;
            return *(--tmp);
        }
        reverse_iterator &operator++()
        {
            --_Iter;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --_Iter;
            return tmp;
        }
        reverse_iterator &operator--()
        {
            ++_Iter;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            ++_Iter;
            return tmp;
        }
        bool operator==(const reverse_iterator &obj) const
        {
            return _Iter == obj._Iter;
        }
        bool operator!=(const reverse_iterator &obj) const
        {
            return _Iter != obj._Iter;
        }
        pointer operator->() const
        {
            iterator_type tmp(_Iter);
            --tmp;
            return tmp.operator->();
        }
        reference operator[](difference_type n) const
        {
            return *(_Iter - n - 1);
        }
        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_Iter - n);
        }

        reverse_iterator operator-(difference_type n) const
        {
            reverse_iterator tmp(_Iter + n);
            return (tmp);
        }

        reverse_iterator &operator+=(difference_type n)
        {
            _Iter -= n;
            return *this;
        }
        reverse_iterator &operator-=(difference_type n)
        {
            _Iter += n;
            return *this;
        }
    };
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() != rhs.base();
    }
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() > rhs.base();
    }
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() >= rhs.base();
    }
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() < rhs.base();
    }
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() <= rhs.base();
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &rev_it)
    {
        return rev_it + n;
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }
}

#endif