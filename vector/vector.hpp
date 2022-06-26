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

#ifndef _VECTOR
#define _VECTOR

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class   vector
    {


        public :
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

        private :

            allocator_type      myAlloc;
            value_type*         container;
            size_type           vector_size;
            size_type           vector_capacity;

            size_type _getvector_capacity_bit(size_type n)
            {
                int i = 0;
                if (n == 0)
                    return (0);
                if (n == 1)
                    return (1);
                while (1)
                {
                    if ((n > pow(2, i) && n <= pow(2, i + 1)))
                        return (pow(2, i + 1));
                    i++;
                }
            }

        public :

//**********************************************             MEMBER FUNCTIONS               **********************************************


            explicit vector (const allocator_type& alloc = allocator_type()) : myAlloc(alloc), container(NULL), vector_size(0), vector_capacity(0){};

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : vector_size(n), myAlloc(alloc), vector_capacity(n)
            {
                container = myAlloc.allocate(vector_size);
                // check for the memory with exceptions
                for (size_type i = 0; i < vector_size; i++)
                {
                    myAlloc.construct(&container[i], val);
                }
            }

            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
                   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL) : vector_capacity(0), vector_size(0), container(NULL), myAlloc(alloc)
            {
                (void)f;
                reserve(last - first);
                for (; first != last; first++)
                    myAlloc.construct(&container[vector_size++], *first);
            }

            vector (const vector& x) {*this = x;};

            ~vector()
            {
                if (vector_capacity > 0)
                {
                    myAlloc.deallocate(container, vector_capacity);
                }
            }

            vector& operator=(const vector& x)
            {
                if (vector_size)
                    myAlloc.deallocate(container, vector_size);
                this->vector_size = x.vector_size;
                this->vector_capacity = x.vector_capacity;
                this->myAlloc = myAlloc.allocate(this->vector_capacity);
                container = myAlloc.allocate(vector_capacity);
                for(int i = 0; i < vector_size; i++)
                    myAlloc.constuct(&container[i], x.container[i]);
                return (*this);
            }

//**********************************************             ITERATORS                      **********************************************

            iterator    begin() {return (iterator(&container[0]));}
            iterator    begin() const {return (iterator(&container[0]));}
            iterator    end() {return (iterator(&container[vector_size]));}
            iterator    end() const {return (iterator(&container[vector_size]));}

            reverse_iterator    rbegin() {return (reverse_iterator(end));}
            reverse_iterator    rbegin() const {return (const_reverse_iterator(end));}
            reverse_iterator    rend() {return (reverse_iterator(begin()));}
            reverse_iterator    rend() const {return (const_reverse_iterator(begin()));}

//**********************************************             CAPACITY                       **********************************************


            size_type      size() const {return vector_size;}

            size_type      max_size() const {return myAlloc.max_size();}

            void        resize (size_type n, value_type val = value_type())
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

            void        reserve (size_type n)
            {
                if (n > vector_capacity)
                {
                    vector   help;

                    help = *this;
                    if (vector_capacity)
                        myAlloc.deallocate(container, vector_capacity);
                    vector_capacity = n;
                    vector_size = help.size();
                    container = myAlloc.allocate(vector_capacity);
                    for(size_type i = 0; i < vector_size; i++)
                        myAlloc.construct(&container[i], help.container[i]);
                }
            }

            size_type   capacity() const { return (vector_capacity);};

            bool        empty() const { return (vector_size == 0 ? true : false);};

//**********************************************             ELEMENT ACCESS                 **********************************************

            class out_of_range : public std::exception
            {
                public:
                  virtual const char* what() const throw()
                  {
                      return ("vector::_M_range_check");
                  };
            };

            reference operator[](size_type n) { return container[n];}

            const_reference operator[] (size_type n) const { return container[n];}

            reference at (size_type n)
            {
                if (n >= vector_size)
                    throw out_of_range();
                return container[n];
            }

            const_reference at (size_type n) const
            {
                if (n >= vector_size)
                    throw out_of_range();
                return container[n];
            }

            reference front() { return (container[0]);}

            const_reference front() const { return (container[0]);}

            reference back() { return (container[vector_size - 1]);}

            const_reference back() const { return (container[vector_size - 1]);}

//**********************************************             MODIFIERS                      **********************************************

            void assign (size_type n, const value_type& val)
            {
                if (vector_capacity)
                {
                    clear();
                    myAlloc.deallocate(container, vector_capacity);
                }
                vector_capacity = n;
                vector_size = n;
                container = myAlloc.allocate(vector_capacity);
                for(size_type i = 0; i < vector_size; i++)
                    myAlloc.construct(&container[i], val);
            }

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
            {
                (void)f;
                size_type   n = last - first;

                if (n > vector_capacity)
                {
                    myAlloc.deallocate(container, vector_capacity);
                    container = myAlloc.allocate(n);
                    vector_capacity = n;
                }
                for(size_type i = 0; i < n; ++i)
                    myAlloc.construct(&container[i], *first++);
                vector_size = n;
            }

            void        push_back (const value_type& val)
            {
                if (vector_capacity > vector_size)
                {
                    container[vector_size] = val;
                    vector_size++;
                }
                else
                    resize(vector_size + 1, val);
            }

            void        pop_back() { myAlloc.destroy(&container[vector_size--]);}

            iterator insert (iterator position, const value_type& val)
            {
                size_type i = 0;
                size_type o = position - begin();

                if (vector_size == 0)
                    push_back(val);
                else
                {
                    if (vector_size + 1 > vector_capacity)
                        reserve(vector_capacity * 2);
                    while (vector_size - i + 1 > 0)
                    {
                        if (vector_size - i == o)
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
                return (container + o);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                size_type o = position - this->begin();
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
                    if (vector_size - i == o)
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
                        myAlloc.construct(&container[vector_size - i + n - 1] , container[vector_size - i - 1]);
                    i++;
                }
                vector_size += n;
            }

            void        clear()
            {
                for(size_type i = 0; i < vector_size; i++)
                    myAlloc.destroy(container + i);
                vector_size = 0;
            }

            void        swap (vector& x)
            {
                vector help;

                help = *this;
                *this = x;
                x = help;
            }


//**********************************************             ALLOCATE                       **********************************************

            allocator_type get_allocator() const { return (myAlloc);}
    };
}

#endif