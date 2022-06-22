/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:54:38 by amaach            #+#    #+#             */
/*   Updated: 2022/06/22 00:54:38 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
namespace ft
{
    template <class T, class Container = std::vector<T> > 
    class stack
    {
        public :
            typedef Container                                container_type;
            typedef typename container_type::value_type      value_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;

        protected :
            container_type c;
        
        public :
            explicit stack (const container_type& ctnr = container_type()) :  c(ctnr)
            {
            }

            ~stack()
            {
            }

            bool empty() const
            {
                return (c.empty());
            }

            size_type size() const
            {
                return (c.size());
            }

            value_type& top()
            {
                return (c.back());
            }
        
            const value_type& top() const
            {
                return (c.back());
            }

            void push (const value_type& val)
            {
                c.push_back(val);
            }

            void pop()
            {
                c.pop_back();
            }

            bool operator== (const ft::stack<T,Container>& rhs)
            {
                return (this->c == rhs.c);
            }

            bool operator!= (const ft::stack<T,Container>& rhs)
            {
                return (this->c != rhs.c);
            }

            bool operator<= (const ft::stack<T,Container>& rhs)
            {
                return (this->c <= rhs.c);
            }

            bool operator>= (const ft::stack<T,Container>& rhs)
            {
                return (this->c >= rhs.c);
            }

            bool operator< (const ft::stack<T,Container>& rhs)
            {
                return (this->c < rhs.c);
            }

            bool operator> (const ft::stack<T,Container>& rhs)
            {
                return (this->c > rhs.c);
            }
    };
}
