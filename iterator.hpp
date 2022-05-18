/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:09:33 by amaach            #+#    #+#             */
/*   Updated: 2022/05/18 20:50:08 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_
#define ITERATOR_


#include <stddef.h>


template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class T>
class myIterator
{
    public :
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef typename iterator_traits<T>::value_type value_type,
        typedef typename iterator_traits<T>::difference_type difference_type,
        typedef typename iterator_traits<T>::pointer pointer,
        typedef typename iterator_traits<T>::reference reference>
        
    
    private:
        pointer  MyIter;

    public:
        myIterator(){};
        myIterator(value_type it) : MyIter(&it);
        myIterator(const value_type& it){ *this = it;};
        ~myIterator(){};
        
};


#endif