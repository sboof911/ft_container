/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:44:22 by amaach            #+#    #+#             */
/*   Updated: 2022/05/25 00:25:32 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>

namespace ft{
    
   template <class T>
    class reverse_iterator 
    {
    public:                     // CHECK https://www.cplusplus.com/reference/iterator/reverse_iterator/   
        typedef T value_type;   // I need to change a lot of things here
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

    private:
        pointer _ptr;
    public:
        reverse_iterator() : _ptr(NULL) {}
        reverse_iterator(pointer ptr) : _ptr(ptr) {}
        ~reverse_iterator(){}
        reverse_iterator(const reverse_iterator& copy) { *this = copy;}
  
        reverse_iterator &operator=(const reverse_iterator &obj)
        {
            this->_ptr = obj._ptr;
            return (*this);
        }

        reverse_iterator &operator++()
        {
            this->_ptr--;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            this->_ptr--;
            return tmp;
        }

        reverse_iterator &operator--()
        {
            _ptr++;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            _ptr++;
            return tmp;
        }

        difference_type operator-(const reverse_iterator &obj) const { return (this->_ptr + obj._ptr);}
   
        reference operator*() { return *this->_ptr;}
      
        pointer operator->() const { return this->_ptr; }

        reverse_iterator operator+(difference_type n) const { return this->_ptr - n;}
    
        reverse_iterator operator-(difference_type n) const { return this->_ptr + n;}

        reference operator[](int n) const { return this->_ptr[n];}

        reverse_iterator &operator+=(int n)
        {
            this->_ptr -= n;
            return *this;
        }

        reverse_iterator &operator-=(int n)
        {
            this->_ptr += n;
            return *this;
        }
        
        operator reverse_iterator<const value_type> () const { return reverse_iterator<const value_type>(&this->_ptr) ; }

    };
}

#endif