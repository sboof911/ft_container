/* **********************************************             *** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:16:18 by amaach            #+#    #+#             */
/*   Updated: 2022/05/17 20:04:27 by amaach           ###   ########.fr       */
/*                                                                            */
/* **********************************************             *** */

#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                                   value_type;
            typedef Alloc                                               allocator_type;
            typedef value_type                                          &reference;
            typedef const value_type                                    &const_reference;
            typedef std::ptrdiff_t                                      difference_type;

            typedef typename ft::iterator<value_type>                   iterator;
            typedef typename ft::iterator<const value_type>             const_iterator;
            typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>       const_reverse_iterator;

            typedef typename allocator_type::size_type                  size_type;
            typedef typename allocator_type::pointer                    pointer;
            typedef typename allocator_type::const_pointer              const_pointer;

        private:
            size_type       vector_capacity;
            size_type       vector_size;
            pointer         container;
            allocator_type  myAlloc;

        public:
            class outofbounds : public std::exception
            {
                public:
                    const char *what() const throw(){ return ("index outofbounds");}
            };

//**********************************************             MEMBER FUNCTIONS               **********************************************

            explicit vector(const allocator_type &alloc = allocator_type()) : vector_capacity(0), vector_size(0), container(NULL), myAlloc(alloc) {}

            explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : vector_capacity(0), vector_size(0), container(NULL), myAlloc(alloc)
            {
                if (n == 0)
                    container = NULL;
                else
                    container = myAlloc.allocate(n);
                for (size_type i = 0; i < n; ++i)
                    myAlloc.construct(&container[i], val);
                vector_size = n;
                vector_capacity = n;
            }

            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
                   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL) : vector_capacity(0), vector_size(0), container(NULL), myAlloc(alloc)
            {
                (void)f;
                reserve(last - first);
                for (; first != last; first++)
                    myAlloc.construct(&container[vector_size++] , *first);
            }

            vector(const vector &x) : container(NULL), myAlloc(x.myAlloc){ *this = x;}

            ~vector()
            {
                for (size_type i = 0; i < vector_size; i++)
                    myAlloc.destroy(&container[i]);
                myAlloc.deallocate(container, vector_capacity);
            }

            vector &operator=(const vector &x)
            {
                size_type i;
                if (vector_size != 0)
                    myAlloc.deallocate(container, vector_size);
                vector_size = x.vector_size;
                vector_capacity = x.vector_capacity;
                container = myAlloc.allocate(vector_capacity);
                for (i = 0; i < vector_size; i++)
                    myAlloc.construct(&container[i], x.container[i]);
                return (*this);
            }

//**********************************************             ITERATORS                      **********************************************

            iterator                    begin() {return (iterator(&container[0]));}
            const_iterator              begin() const {return (iterator(&container[0]));}
            iterator                    end() {return (iterator(&container[vector_size]));}
            const_iterator              end() const {return (iterator(&container[vector_size]));}

            reverse_iterator            rbegin() {return (reverse_iterator(end()));}
            const_reverse_iterator      rbegin() const {return (const_reverse_iterator(end()));}
            reverse_iterator            rend() {return (reverse_iterator(begin()));}
            const_reverse_iterator      rend() const {return (const_reverse_iterator(begin()));}

//**********************************************             CAPACITY                       **********************************************

            size_type size() const{ return (vector_size);}

            size_type max_size() const{ return (myAlloc.max_size());}

            size_type capacity() const{ return (vector_capacity);}

            bool empty() const
            {
                if (vector_size == 0)
                    return (1);
                else
                    return 0;
            }

            void    reserve (size_type n)
            {
                if (n > vector_capacity)
                {
                    pointer tmp = container;
                    container = myAlloc.allocate(n);
                    if (tmp != NULL)
                    {
                        for (size_type i = 0; i < vector_size; i++)
                            myAlloc.construct(container + i, tmp[i]);
                        myAlloc.deallocate(tmp, vector_capacity);
                    }
                    vector_capacity = n;
                }
            }
            void resize(size_type n, value_type val = value_type())
            {
                size_type i;
                pointer tmp;
                tmp = container;
                if (n < vector_size)
                {
                    for (i = n; i < vector_size; i++)
                        myAlloc.destroy(&container[i]);
                    vector_size = n;
                }
                else if (n > vector_capacity)
                {
                    if (n > (vector_capacity * 2))
                        reserve(n);
                    else
                        reserve(vector_capacity * 2);
                    for (i = vector_size; i < n; i++)
                        push_back(val);
                }
                else if (n > vector_size)
                    for (i = vector_size; i < n; i++)
                        push_back(val);
            }

//**********************************************             ELEMENT ACCESS                 **********************************************

            reference operator[](size_type n) { return container[n];}

            const_reference operator[] (size_type n) const { return container[n];}

            reference at (size_type n)
            {
                if (n >= vector_size)
                    throw std::out_of_range("vector");
                return container[n];
            }

            const_reference at (size_type n) const
            {
                if (n >= vector_size)
                    throw std::out_of_range("vector");
                return container[n];
            }

            reference front() { return (container[0]);}

            const_reference front() const { return (container[0]);}

            reference back() { return (container[vector_size - 1]);}

            const_reference back() const { return (container[vector_size - 1]);}

//**********************************************             MODIFIERS                      **********************************************

            void clear()
            {
                for (size_type i = 0; i < vector_size; i++)
                    myAlloc.destroy(&container[i]);
                vector_size = 0;
            }

            void swap(vector &x)
            {
                pointer tmp = container;
                size_type   tmp_size = vector_size;
                size_type   tmp_capacity = vector_capacity;

                container = x.container;
                vector_size = x.vector_size;
                vector_capacity = x.vector_capacity;

                x.container = tmp;
                x.vector_size = tmp_size;
                x.vector_capacity = tmp_capacity;
            }

            void push_back(const value_type &val)
            {
                if (vector_size == 0)
                    reserve(1);
                else if (vector_size == vector_capacity)
                    reserve(vector_capacity * 2);
                myAlloc.construct(container + vector_size, val);
                vector_size++;
            }

            void pop_back(){myAlloc.destroy(&container[vector_size--]);}

            void assign(size_type n, const T &x)
            {
                if (n > vector_capacity)
                {
                    myAlloc.deallocate(container, vector_capacity);
                    container = myAlloc.allocate(n);
                    vector_capacity = n;
                }
                for (size_type i = 0; i < n; ++i)
                    myAlloc.construct(&container[i] , x);
                vector_size = n;
            }

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
            {
                (void)f;
                size_type n = last - first;

                if (n > vector_capacity)
                {
                    myAlloc.deallocate(container, vector_capacity);
                    container = myAlloc.allocate(n);
                    vector_capacity = n;
                }
                for (size_type i = 0; i < n; ++i)
                    myAlloc.construct(&container[i] , *first++);
                vector_size = n;
            }

            iterator erase(iterator pos)
            {
                for (size_type i = pos - container; i < vector_size - 1; ++i)
                    container[i] = container[i + 1];
                vector_size--;
                return pos;
            }

            iterator erase(iterator first, iterator last)
            {
                size_type n = last - first;

                for (size_type i = first - container; i < vector_size - n; ++i)
                    myAlloc.construct(&container[i] , container[i + n]);
                vector_size -= n;
                return first;
            }

            iterator insert (iterator position, const value_type& val)
            {
                size_type i = 0;
                size_type pos = position - begin();

                if (vector_size == 0)
                    push_back(val);
                else
                {
                    if (vector_size + 1 > vector_capacity)
                        reserve(vector_capacity * 2);
                    while (vector_size - i + 1 > 0)
                    {
                        if (vector_size - i == pos)
                        {
                            myAlloc.construct(&container[vector_size - i] , val);
                            break;
                        }
                        else
                            myAlloc.construct(&container[vector_size - i] , container[vector_size - i - 1]);
                        i++;
                    }
                    vector_size++;
                }
                return (container + pos);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                size_type pos = position - this->begin();
                size_type i = 0;
                size_type k = n;
                if (vector_size + n > vector_capacity)
                {
                    if (vector_size + n < vector_size * 2)
                        reserve(!(vector_size )? 1 : (vector_size * 2));
                    else
                        reserve(!(vector_size + n)? 1 : (vector_size + n ));

                }
                while (vector_size - i + n > 0)
                {
                    if (vector_size - i == pos)
                    {
                        while (k--)
                            myAlloc.construct(&container[vector_size - i + k] , val);
                        break;
                    }
                    else
                        myAlloc.construct(&container[vector_size - i + n - 1] , container[vector_size - i - 1]);
                    i++;
                }
                vector_size += n;
            }

            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
            {
                (void)f;
                size_type n = std::distance(first, last);
                size_type i = 0;
                size_type pos = position - begin();
                if (vector_capacity < vector_size + n && n <= vector_size)
                    reserve(vector_capacity * 2);
                else if (vector_size + n > vector_capacity)
                    reserve(vector_capacity + n);
                while (vector_size + n - i > 0)
                {
                    if (vector_size - i == pos)
                    {
                        pos = n;
                        try
                        {
                            while (pos--)
                               myAlloc.construct(&container[vector_size - i + pos], *(--last));
                        }
                        catch (...)
                        {
                            for (size_type i = size(); i != 0; i--)
                            {

                                std::cout << "i =  " << i << std::endl;
                                myAlloc.destroy(&container[i - 1]);
                            }
                            vector_capacity = 0;
                            throw 3;
                        }
                        break;
                    }
                    else
                        myAlloc.construct(&container[vector_size - i + n - 1] ,  container[vector_size - i - 1]);
                    i++;
                }
                vector_size += n;
            }

//**********************************************             ALLOCATE                       **********************************************

            allocator_type get_allocator() const { return (myAlloc);}

    };

//**********************************************      NO MEMBER FUNCTIONS OVERLOAD          **********************************************

    template <class M, class allocc>
    void swap(vector<M, allocc> &x, vector<M, allocc> &y) { x.swap(y);}

    template <class M, class alocc>
    bool operator==(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
                return (false);
        }
        return (true);
    }

    template <class M, class alocc>
    bool operator!=(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs){ return (!(lhs == rhs));}

    template <class M, class alocc>
    bool operator<(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs)
    {
        if (lhs.size() < rhs.size())
            return (true);
        else if (lhs.size() > rhs.size())
            return (false);
        size_t i;
        for (i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] < rhs[i])
                return (true);
            else if (lhs[i] > rhs[i])
                return (false);
        }
        return (false);
    }

    template <class M, class alocc>
    bool operator>(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs){ return (rhs < lhs);}

    template <class M, class alocc>
    bool operator<=(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs){ return (!(lhs > rhs));}

    template <class M, class alocc>
    bool operator>=(const ft::vector<M, alocc> &lhs, const ft::vector<M, alocc> &rhs){ return (!(rhs > lhs));}
}

//**********************************************         RELATIONAL OPERATORS               **********************************************

template <typename T>
std::ostream &operator<<(std::ostream &os, const ft::vector<T> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
        os << v[i] << " ";
    return os;
}

#endif