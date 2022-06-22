/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:09:33 by amaach            #+#    #+#             */
/*   Updated: 2022/06/01 18:23:24 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{
    
   template <class T>
    class iterator 
    {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
        typedef std::random_access_iterator_tag iterator_category;

    private:
        pointer _Iter;
    public:
        iterator() : _Iter(NULL) {}
        iterator(pointer ptr) : _Iter(ptr) {}
        ~iterator(){}
        iterator(const iterator& copy) { *this = copy;}

        iterator &operator=(const iterator &obj)
        {
            this->_Iter = obj._Iter;
            return (*this);
        }

        iterator &operator++()
        {
            this->_Iter++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            this->_Iter++;
            return tmp;
        }

        iterator &operator--()
        {
            _Iter--;
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            _Iter--;
            return tmp;
        }

        template <class U>
        bool operator==(const iterator<U> &obj) const { return (this->_Iter == obj._Iter);}

        template <class U>
        bool operator!=(const iterator<U> &obj) const { return (this->_Iter != obj._Iter);}

        template <class U>
        bool operator<=(const iterator<U> &obj) const { return (this->_Iter <= obj._Iter);}

        template <class U>
        bool operator<(const iterator<U> &obj) const { return (this->_Iter < obj._Iter);}

        template <class U>
        bool operator>(const iterator<U> &obj) const { return (this->_Iter > obj._Iter);}

        template <class U>
        bool operator>=(const iterator<U> &obj) const { return (this->_Iter >= obj._Iter);}
        
        difference_type operator-(const iterator &obj) const { return (this->_Iter - obj._Iter);}
   
        reference operator*() { return *this->_Iter;}
      
        pointer operator->() const { return this->_Iter;}

        iterator operator+(difference_type n) const { return this->_Iter + n;}
    
        iterator operator-(difference_type n) const { return this->_Iter - n;}

        reference operator[](int n) const { return this->_Iter[n];}

        iterator &operator+=(int n)
        {
            this->_Iter += n;
            return *this;
        }

        iterator &operator-=(int n)
        {
            this->_Iter -= n;
            return *this;
        }
    };
    
    template <typename T>
    iterator<T> operator+(std::ptrdiff_t n, ft::iterator<T> it)
    {
        return it + n;
    }
}

#endif