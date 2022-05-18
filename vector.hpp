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

template < class T, class Alloc = std::allocator<T> >
class   vector
{


    public :
        typedef T                                        value_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

    protected :
        allocator_type      myAlloc;
        value_type*         arg;
        size_type           vector_size;
        size_type           vector_capacity;

    private :
        size_type _get_capacity_bit(size_type n)
        {
            int i = 0;
            if (n == 0)
                return (0);
            while (1)
            {
                if ((n >= pow(2, i) && n < pow(2, i + 1)))
                    return (pow(2, i + 1));
                i++;
            }
        };

    public :

//**********************************************             MEMBER FUNCTIONS               **********************************************


        vector (const allocator_type& alloc = allocator_type()) : myAlloc(alloc), arg(NULL), vector_size(0), vector_capacity(0){};
        vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : vector_size(n), myAlloc(alloc), vector_capacity(n)
        {
            arg = myAlloc.allocate(vector_size);
            // check for the memory with exceptions
            for (size_type i = 0; i < vector_size; i++)
            {
                myAlloc.construct(&arg[i], val);
            }
        };
        vector (const vector& x) {*this = x;};
        ~vector()
        {
            if (vector_capacity > 0)
            {
                myAlloc.deallocate(arg, vector_capacity);
            }
        }
        vector& operator=(const vector& x)
        {
            if (vector_capacity)
            {    
                clear();
                myAlloc.deallocate(arg, vector_capacity);
            }
            this->myAlloc = x.myAlloc;
            this->vector_size = x.vector_size;
            this->vector_capacity = x.vector_capacity;
            arg = myAlloc.allocate(vector_capacity);
            for(int i = 0; i < vector_size; i++)
                this->arg[i] = x.arg[i];
            return (*this);
        };

//**********************************************             ITERATORS                      **********************************************



//**********************************************             CAPACITY                       **********************************************

                                                
        size_type      size() const {return vector_size;};
        size_type      max_size() const {};
        void        resize (size_type n, value_type val = value_type())
        {
            if (vector_capacity >= n)
            {
                if (n >= vector_size)
                {
                    for (size_type i = vector_size; i < n; i++)
                    {
                        myAlloc.construct(&arg[i], val);
                        vector_size = i;
                    }
                }
                else
                {
                    for (size_type i = vector_size; i > n; i--)
                    {
                        myAlloc.destroy(&arg[i]);
                        vector_size = i;
                    }
                }
            }
            else
            {
                int     SizePreVec = 0;
                vector_size = n;
                vector_capacity = _get_capacity_bit(n);
                if (arg)
                {
                    vector*   help;

                    help = this;
                    clear();
                    myAlloc.deallocate(arg, vector_capacity);
                    for (size_type i = 0; i < help->size(); i++)
                        myAlloc.construct(&arg[i], help->arg[i]);
                    SizePreVec = help->size();
                }
                arg = myAlloc.allocate(vector_capacity);
                for(size_type i = SizePreVec; i < n; i++)
                    myAlloc.construct(&arg[i], val);
            }
        };
        void        reserve (size_type n)
        {
            if (n > vector_capacity)
            {
                vector*   help;

                help = this;
                if (vector_capacity)
                {
                    clear();
                    myAlloc.deallocate(arg, vector_capacity);
                }
                vector_capacity = n;
                vector_size = help->size();
                arg = myAlloc.allocate(vector_capacity);
                for(size_type i = 0; i < vector_size; i++)
                    myAlloc.construct(&arg[i], help->arg[i]);
            }
        };
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

        reference operator[](size_t index)
        {
                return arg[index];
        };
        const_reference operator[] (size_type n) const
        {
                return arg[index];
        };
        reference at (size_type n)
        {
            if (n >= vector_size)
                throw out_of_range();
            return arg[n];
        };
        const_reference at (size_type n) const
        {
            if (n >= vector_size)
                throw out_of_range();
            return arg[n];
        };
        reference front()
        {
            return (arg[0]);
        };
        const_reference front() const
        {
            return (arg[0]);
        };
        reference back()
        {
            return (arg[vector_size - 1]);
        };
        const_reference back() const
        {
            return (arg[vector_size - 1]);
        };


//**********************************************             MODIFIERS                      **********************************************
        void assign (size_type n, const value_type& val)
        {
            if (vector_capacity)
            {
                clear();
                myAlloc.deallocate(arg, vector_capacity);
            }
            vector_capacity = n;
            vector_size = n;
            arg = myAlloc.allocate(vector_capacity);
            for(size_type i = 0; i < vector_size; i++)
                myAlloc.construct(&arg[i], val);
        };
        void        push_back (const value_type& val)
        {
            if (vector_capacity > vector_size)
            {
                arg[vector_size] = val;
                vector_size++;
            }
            else
                resize(vector_size + 1, val);
        };
        void        pop_back()
        {
            vector  help;

            help = *this;
            if (vector_capacity)
            {
                clear();
                myAlloc.deallocate(arg, vector_capacity);
            }
            vector_capacity = help.vector_capacity;
            vector_size = help.vector_size--;
            arg = myAlloc.allocate(vector_capacity);
            for(size_type i = 0; i < vector_size; i++)
                arg[i] = help.arg[i];
        };
        void        clear()
        {
            for(size_type i = 0; i < vector_size; i++)
                myAlloc.destroy(arg + i);
            vector_size = 0;
        };
        void        swap (vector& x)
        {
            vector help;

            help = *this;
            *this = x;
            x = help;
        };


//**********************************************             ALLOCATE                       **********************************************

        allocator_type get_allocator() const
        {
            return (myAlloc);
        };
};

#endif