/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 02:03:49 by amaach            #+#    #+#             */
/*   Updated: 2022/06/22 02:03:53 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <utility>

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair(){}
        pair (const first_type& a, const second_type& b) : first(a), second(b){}
        template<class U, class V> 
        pair (const pair<U,V>& pr): first(pr.first), second(pr.second){}
        pair& operator= (const pair& pr)  {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }

    template <class T1,class T2>
    ft::pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( ft::pair<T1,T2>(x,y) );
    }



    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };


    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return (false);
            else if (*first1 < *first2)
                return (true);
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template<class value_type>
    bool equal(value_type const &a, value_type const &b) {
        return (a == b);
    }

    template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

    template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};

}