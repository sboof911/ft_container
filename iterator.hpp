/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:09:33 by amaach            #+#    #+#             */
/*   Updated: 2022/05/24 18:33:57 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>

namespace ft{
    
   template <class T>
    class iterator 
    {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;

    private:
        pointer _ptr;
    public:
        iterator() : _ptr(NULL) {}
        iterator(pointer ptr) : _ptr(ptr) {}
        ~iterator(){}
        iterator(const iterator& copy) { *this = copy;}

        iterator &operator=(const iterator &obj)
        {
            this->_ptr = obj._ptr;
            return (*this);
        }

        iterator &operator++()
        {
            this->_ptr++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            this->_ptr++;
            return tmp;
        }

        iterator &operator--()
        {
            _ptr--;
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            _ptr--;
            return tmp;
        }

        template <class U>
        bool operator==(const iterator<U> &obj) const { return (this->_ptr == obj._ptr);}

        template <class U>
        bool operator!=(const iterator<U> &obj) const { return (this->_ptr != obj._ptr);}

        template <class U>
        bool operator<=(const iterator<U> &obj) const { return (this->_ptr <= obj._ptr);}

        template <class U>
        bool operator<(const iterator<U> &obj) const { return (this->_ptr < obj._ptr);}

        template <class U>
        bool operator>(const iterator<U> &obj) const { return (this->_ptr > obj._ptr);}

        template <class U>
        bool operator>=(const iterator<U> &obj) const { return (this->_ptr >= obj._ptr);}
        
        difference_type operator-(const iterator &obj) const { return (this->_ptr - obj._ptr);}
   
        reference operator*() { return *this->_ptr;}
      
        pointer operator->() const { return this->_ptr;}

        iterator operator+(difference_type n) const { return this->_ptr + n;}
    
        iterator operator-(difference_type n) const { return this->_ptr - n;}

        reference operator[](int n) const { return this->_ptr[n];}

        iterator &operator+=(int n)
        {
            this->_ptr += n;
            return *this;
        }

        iterator &operator-=(int n)
        {
            this->_ptr -= n;
            return *this;
        }
    };
}

#endif