/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:54:38 by amaach            #+#    #+#             */
/*   Updated: 2022/06/28 18:00:27 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;

    protected:
        container_type _container;

    public:
        explicit stack(const container_type &container = container_type()) : _container(container) {}
        stack const &operator= (stack const &x)  {
         _container = x._container;
            
        }
        void push(const T &value) { _container.push_back(value); }

        void pop() { _container.pop_back(); }

        value_type &top() { return _container.back(); }

        const value_type &top() const { return _container.back(); }

        bool empty() const { return _container.empty(); }

        size_type size() const { return _container.size(); }

        template <class stack_type, class container_type>
        friend bool operator==(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container == rhs._container;
        }
        template <class stack_type, class container_type>
        friend bool operator!=(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container != rhs._container;
        }
        template <class stack_type, class container_type>
        friend bool operator>(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container > rhs._container;
        }
        template <class stack_type, class container_type>
        friend bool operator<(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container < rhs._container;
        }
        template <class stack_type, class container_type>
        friend bool operator>=(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container >= rhs._container;
        }
        template <class stack_type, class container_type>
        friend bool operator<=(const stack<stack_type, container_type> &lhs, const stack<stack_type, container_type> &rhs)
        {
            return lhs._container <= rhs._container;
        }
    };
}