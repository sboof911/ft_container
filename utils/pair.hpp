/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 02:03:49 by amaach            #+#    #+#             */
/*   Updated: 2022/06/29 05:16:41 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP


namespace ft
{
    template <class T1, class T2>
    class pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

    public:
        first_type first;
        second_type second;
        
        pair():first(), second()  {}

        template <class U, class V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

        pair (const first_type& a, const second_type& b) : first(a), second(b) {}
        
        template <class U, class V>
        pair &operator=(const pair<U, V> &pr)
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return lhs.first == rhs.first && lhs.second == rhs.second;}

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return !(lhs == rhs);}

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);}

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return !(rhs < lhs);}

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return rhs < lhs;}

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs){ return !(lhs < rhs);}
}

#endif