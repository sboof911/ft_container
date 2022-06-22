#pragma once

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
//#include "Vector.hpp"
//#include "stack.hpp"
#include "pair.hpp"
#include <stack>
#include <iterator>
#include <string>
#include "iterator_traits.hpp"
#define PRINTLN(x) std::cout << x <<std::endl;
namespace ft{
    template <class K, class T,class Compare, class Alloc >
    class BST {
         public :
            typedef ft::pair<const K, T>                                  value_type;
            typedef Alloc 						                    allocator_type;
            typedef Compare                                         key_compare;
            typedef allocator_traits<allocator<BST> >         	    __alloc_traits;
            typedef allocator_traits<Alloc>                 	    alloc_traits;
            typedef typename __alloc_traits::difference_type		difference_type;
            typedef typename alloc_traits::pointer                  pointer;
            typedef typename alloc_traits::const_pointer            const_pointer;
            typedef typename alloc_traits::size_type                size_type;
            typedef typename __alloc_traits::pointer                P;
            typedef ft::mapiter<P, value_type>			        iterator;
            typedef ft::mapiter<P, const value_type>			  const_iterator;

        public:
            value_type *m_pair;
            BST *left, *right, *parent;
            allocator_type allocc;
            Compare     c;
        public :

            BST(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): m_pair(NULL), left(NULL), right(NULL), parent(NULL), allocc(alloc), c(comp) {
                  m_pair = allocc.allocate(1);
              }
            BST(K first,T second, const key_compare& comp= key_compare(),
                const allocator_type& alloc= allocator_type()) 
                : m_pair(NULL), left(NULL), right(NULL), parent(NULL), allocc(alloc), c(comp)
            {
                m_pair = allocc.allocate(1);
                allocc.construct(m_pair, first, second);
            }

            BST(const value_type &pair, const key_compare& comp= key_compare(),
                const allocator_type& alloc= allocator_type())
                : m_pair(NULL), left(NULL), right(NULL), parent(NULL), allocc(alloc), c(comp)
            {
                m_pair = allocc.allocate(1);
                allocc.construct(m_pair, pair);
            }

            BST(BST& other): m_pair(NULL), left(NULL), right(NULL), parent(NULL), allocc(other.allocc), c(other.c)
            {
                BST* tmp;
                tmp = treecopy(&other);
                allocc.construct(m_pair,*tmp->m_pair);
                left = tmp->left;
                right = tmp->right;
                delete tmp;
            }
            
            ~BST()
            {
                allocc.deallocate(m_pair, 1);
            }

            BST& operator= (const BST& x)
            {  
                BST* tmp;
                clear(right);
                clear(left);
                //right = treecopy(x.right);
                // allocc.construct(m_pair,*tmp->m_pair);
                // left = tmp->left;
                // right = tmp->right;
                // parent = tmp->parent;
                delete this;
                return (*tmp);
            }
            BST *find(K key, BST* tmp)
            {
                BST *root = tmp;
				if (tmp == NULL)
					return NULL;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                root = root->right;
                while (root)
                {
                    if (root->m_pair->first == key)
                        return (root);
                    if (key < root->m_pair->first)
                        root = root->left;
                    else
                        root = root->right;
				}
                return (NULL);
            }

            BST *find(K key, BST* tmp) const
            {
                BST *root = tmp;
				if (tmp == NULL)
					return NULL;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                root = root->right;
                while (root)
                {
                    if (root->m_pair->first == key)
                        return (root);
                    if (key < root->m_pair->first)
                        root = root->left;
                    else
                        root = root->right;
				}
                return (NULL);
            }



            BST* leftRotate(BST* x) 
            {
                
                BST* y = x->left;
                x->left = y->right;
                if (y->right != nullptr) {
                    y->right->parent = x;
                }
                x->parent = y->parent;
                // if (x->parent == nullptr) {
                //     ;
                // } else if (x == x->parent->right) {
                //     x->parent->right = y;
                // } else {
                //     x->parent->left = y;
                // }
                y->right = x;
                x->parent = y;
                return (y);
            }


            BST* rightRotate(BST* x)
            {
                BST *y = x->right;
                x->right = y->left;
                if (y->left != nullptr)
                {
                    y->left->parent = x;
                }
                y->parent = x->parent;
                // if (x->parent == nullptr)
                // {
                //     ;
                // } else if (x == x->parent->left)
                // {
                //     x->parent->left = y;
                // } else {
                //     x->parent->right = y;
                // }
                y->left = x;
                x->parent = y;

                // update the balance factor
                return (y);
            }



            int height(BST *t)
            {
                int h = 0;
                if (t != NULL)
                {
                    int l_height = height(t->left);
                    int r_height = height(t->right);
                    int max_height = std::max(l_height, r_height);
                    h = max_height + 1;
                }
                return h;
            }
            int difference(BST *t)
            {
                if (t != NULL)
                {
                    int l_height = height(t->left);
                    int r_height = height(t->right);
                    int b_factor = l_height - r_height;
                    return b_factor;
                }
                return 0;
            }

            BST* rebalance(BST* node) 
            {
                BST*    tmp;
                int bal_factor = difference(node);

                if (bal_factor > 1) {
                    if (difference(node->right) > 0)
                    {
                        // tmp = node->right
                        node = leftRotate(node);
                    }
                    else 
                    {
                        node->left = rightRotate(node->left);
                        node = leftRotate(node);
                    }
                } else if (bal_factor < -1) {
                    if (difference(node->left) > 0)
                    {
                        node->right = leftRotate(node->right);
                        node = rightRotate(node);
                    }
                    else
                    {
                        node = rightRotate(node);
                    }
                }
                return node;
            }

            BST* updateBalance(BST* node)
            {
                if (difference(node) < -1 || difference(node) > 1) {
                    node = rebalance(node);
                
                    return node;
                }

                if (node->left != nullptr) {
                    if (difference(node->left) != 0) {
                        node->left = updateBalance(node->left);
                    }
                }
                if (node->right != nullptr) {
                    if (difference(node->right) != 0) {
                        node->left = updateBalance(node->right);
                    }
                }
                return node;
            }

            BST*   insert(BST* root, const value_type &pair)
            {
                if (find(pair.first, root)!= NULL)
                    return (NULL);
                if (!root) {
                    return new BST(pair, c, allocc);
                }
                if (c(root->m_pair->first, pair.first)){
                    root->right = insert(root->right, pair);
                    root->right = rebalance(root->right);
                    root->right->parent = root;
                }
                else {
                    root->left = insert(root->left, pair);
                    root->left = rebalance(root->left);
                    root->left->parent = root;
                }
                return root;
            }

            BST*   insert(BST* root, K first,T second)
            {
                if (find(first, root) != NULL)
                    return (NULL);
                if (!root) {
                    return new BST(first, second, c, allocc);
                }
                if (root->m_pair->first < first){
                    root->right = insert(root->right, first, second);
                    root->right = rebalance(root->right);
                    root->right->parent = root;
                }
                else {
                    root->left = insert(root->left, first, second);
                    root->left = rebalance(root->left);
                    root->left->parent = root;
                }
            
                return root;
            }
            void inorder(BST *t)//inorder traversal
            {
                if (t == NULL)
                return;
                inorder(t->left);
                inorder(t->right);
            }

            BST*    maxkey(BST* root)
            {
                BST *current = root;

                
                if (current)
                while (current->parent  != NULL)
                {
                    current = current->parent;
                }
                current = current->right;
                while (current && current->right != NULL)
                {
                    current = current->right;
                }
                return current;
            }

            BST*    minkey(BST* root)
            {
                BST *current = root;
                
                if (!current) return  NULL;
                while (current->parent != NULL)
                {
                    current = current->parent;
                }
                current = current->right;
                while (current && current->left != NULL)
                {
                    current = current->left;
                }
                return current;
            }
            BST*    minkey(BST* root) const 
            {
                BST *current = root;
                
                if (!current) return  NULL;
                while (current->parent != NULL)
                {
                    current = current->parent;
                }
                current = current->right;
                while (current && current->left != NULL)
                {
                    current = current->left;
                }
                return current;
            }

            BST*    mink(BST* root)
            {
                BST *current = root;

                while (current && current->left != NULL)
                {
                    current = current->left;
                }
                return current;
            }

            void  swap(BST* root, BST* key)
            {
                // BST* cc1 = root->right;
                // BST* cc2 = root->left;
                // BST* tmp = root->parent;
                // if (tmp != NULL)
                // {
                //     if (tmp->left == root)
                //         tmp->left = key;
                //     else
                //         tmp->right = key;
                // }
                // if (key->parent != NULL)
                // {
                //     if (key->parent->left == key)
                //         key->parent->left = root;
                //     else
                //         key->parent->right = root;
                // }
                // cout << root->m_pair->first << " " << root->m_pair->second << endl;
                // allocc.construct(root->m_pair, *key->m_pair);
                // cout << root->m_pair->first << " " << root->m_pair->second << endl;
                // //root->m_pair = key->m_pair;
                // root->parent =key->parent;
                // root->right = key->right;
                // root->left = key->left;
                // key->parent = tmp;
                // key->right = cc1;
                // key->left = cc2;
                value_type *tmp = root->m_pair;
                root->m_pair = key->m_pair;
                key->m_pair = tmp;
                allocc.construct(key->m_pair, *root->m_pair);
            }
            BST*    deleteNode(BST* root, K key)
            {
                BST     *temp;
                value_type     *tmp;
                if (root == NULL)
                    return root;

                if (key < root->m_pair->first)
                {
                    root->left = deleteNode(root->left, key);
                    if (root->left != NULL)
                        root->left->parent = root;
                }
                else if (key > root->m_pair->first)
                {
                    root->right = deleteNode(root->right, key);
                    if (root->right != NULL)
                        root->right->parent = root;
                }
                else 
                {
                    if (root->left == NULL)
                    {
                        temp = root->right;
                        delete root;
                        return temp;
                    } else if (root->right == NULL) 
                    {
                        temp = root->left;
                        delete (root);
                        return temp;
                    }
                    temp = mink(root->right);
                    swap(root , temp);

                    root->right = deleteNode(root->right, temp->m_pair->first);
                }
                return root;
            }

            BST *getnextnode(BST *key)
            {
                BST *tmp = NULL;

                if (key == NULL)
                    return NULL;
                BST *root = key;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                root = root->right;
                while (root != NULL) 
                {
                    if (c(key->m_pair->first,  root->m_pair->first))
                    {
                        tmp = root;
                        root = root->left;
                    }
                    else
                        root = root->right;
                }
                return (tmp);
            }

            BST *getnextnode(K kk, BST *key) const
            {
                BST *tmp = NULL;

                if (key == NULL)
                    return NULL;
                BST *root = key;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                root = root->right;
                while (root != NULL) 
                {
                    if (c(kk ,root->m_pair->first))
                    {
                        tmp = root;
                        root = root->left;
                    }
                    else
                        root = root->right;
                }
                return (tmp);
            }

            BST *getprevnode(BST *key) const
            {
                BST *tmp = NULL;

                BST *root = key;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
               root = root->right;
                while (root != NULL) 
                {
                    if (root->m_pair->first < key->m_pair->first)
                    {
                        tmp = root;
                        root = root->right;
                    }
                    else
                    root = root->left;
                }
                return (tmp);
            }

            BST *getprevnode(K kk, BST *key) const
            {
                BST *tmp = NULL;

                BST *root = key;
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                root = root->right;
                while (root != NULL) 
                {
                    if (c(root->m_pair->first , kk))
                    {
                        tmp = root;
                        root = root->right;
                    }
                    else
                    root = root->left;
                }
                return (tmp);
            }

            BST *treecopy(const BST *key)
            {
                if (key == NULL)
                    return (NULL);
                BST *tmp = new BST(*key->m_pair, key->c, key->allocc);
                if (key->right)
                {
                    tmp->right = treecopy(key->right);
                    tmp->right->parent = tmp;
                }
                if (key->left)
                {
                    tmp->left = treecopy(key->left);
                    tmp->left->parent = tmp;
                }
                return (tmp);
            }

            size_type size(BST* key)
            {
                size_type i = 0;

                if (key != NULL && key->m_pair != NULL)
                    i++;
                if (key->right != NULL)
                    i += size(key->right);
                if (key->left != NULL)
                    i += size(key->left);
                return i;
            }

            void clear(BST * root)
            {
                if (root == NULL)
                    return ;
                if (root->left != NULL)
                    clear(root->left);
                if (root->right != NULL)
                    clear(root->right);
                    delete root;
            }
            iterator begin(BST* root)
            {
                return (minkey(root));
            }
            iterator end(BST* root)
            {
                while (root->parent != NULL)
                {
                    root = root->parent;
                }
                return (root);
            }
    };



    template <class K, class T,class Compare = less<K>, class Alloc = allocator<ft::pair<const K,T> > >
    class Map{
        public :
            typedef K                                                   key_type;
            typedef T                                                   Mapped_type;
            typedef ft::pair<const key_type, Mapped_type>                   value_type;
            typedef Compare                                             key_compare;
            typedef Alloc                                               allocator_type;
            typedef value_type&                                         reference;
            typedef const value_type&                                   const_reference;

            typedef BST<key_type, Mapped_type, Compare, allocator_type>   __base;

            typedef allocator_traits<allocator_type>         	         alloc_traits;
            typedef typename alloc_traits::pointer                      pointer;
            typedef typename alloc_traits::const_pointer                const_pointer;
            typedef typename alloc_traits::size_type                    size_type;
            typedef typename alloc_traits::difference_type              difference_type;

            typedef typename __base::iterator               	        iterator;
            typedef typename __base::const_iterator                   	    const_iterator;
            typedef ft::reverse_mapiter<iterator>       		        reverse_iterator;
            typedef ft::reverse_mapiter<const_iterator>   		        const_reverse_iterator;

            class value_compare
            { 
				friend class Map;
                protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {}
                public  :
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                result_type operator() (const first_argument_type& x, const second_argument_type& y) const
                {
                    return comp(x.first, y.first);
                }
            };
        private :
            size_type   n;
            __base     tree;

            allocator_type allocc;
            Compare     c;

            void __clear(__base* root)
            {
                if (root == NULL)
                    return ;
                if (root->left != NULL)
                    __clear(root->left);
                if (root->right != NULL)
                    __clear(root->right);
                
                delete root;
            }

        public :

            Map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : n(0), tree(comp, alloc), allocc(alloc),c(comp) {
                   
              }

            template <class InputIterator>
            Map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()): n(0), tree(comp, alloc), allocc(alloc), c(comp)
            {
                insert (first, last);
				n = tree.size(tree.right);
            }

            Map (const Map& x) : tree(x.c, x.allocc)
            {
                *this = x;
            }

			~Map()
            {
                if (n != 0)
                    __clear(tree.right);
            }

			Map& operator= (const Map& x)
            {
                tree.clear(tree.right);
                tree.right = tree.treecopy(x.tree.right);
                if (tree.right != NULL)
                    tree.right->parent = &tree;
                n = x.n;
                return *this;
            }

            bool empty() const
            {
                if (n == 0)
                    return true;
                return false;
            }

            size_type size() const
            {
                return n;
            }

            size_type max_size() const
            {
                return (allocc.max_size());
            }

            iterator begin()
            {
                if (n == 0)
                    return &tree;
                return tree.minkey(tree.right);
            }

            __base* _begin()
            {
                if (n == 0)
                    return (const __base)&tree;
                return *((tree.minkey(tree.right)));
            }

            iterator end()
            {
                return iterator(&tree);
            }

            const_iterator begin() const
            {
                if (n == 0)
                {
                    __base tmp(*tree.m_pair, c, allocc);
                    return const_iterator(&tmp);
                }
                __base tmp(*(tree.minkey(tree.right)->m_pair), c, allocc);
                return const_iterator(&tmp);
            }

            const_iterator end() const
            {
                __base tmp(*tree.m_pair,c, allocc);
                return const_iterator(&tmp);
            }

            reverse_iterator rbegin()
            {
                if (n == 0)
                {
                    return reverse_iterator(end());
                }
                return reverse_iterator(--end());
            }

            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }

            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

            Mapped_type& operator[] (const key_type& k)
            {
                __base *tmp = tree.find(key_type(k), tree.right);
                if (tmp == NULL)
                {
                    tree.right = tree.insert(tree.right, k, Mapped_type());
                    tree.right->parent = &tree;

                    n++;
                    tmp = tree.find(key_type(k), tree.right);
                }
                return (tmp->m_pair->second);
            }

            ft::pair<iterator,bool> 
            insert (const value_type& val)
            {
                __base *tmp = tree.insert(tree.right, val);
                if ((tmp) == NULL)
                {
                    return (ft::pair<iterator,bool>(end(), false));
                }
                tree.right = tmp;
                tree.right->parent = &tree;
                n++;
                iterator it(tree.find(val.first, tree.right));
                return (ft::pair<iterator,bool>(it, true));
            }

            iterator insert (iterator position, const value_type& val)
            {
                __base *tmp =tree.insert(tree.find(position->first,tree.right), value_type(val));
                tree.right->parent = &tree;
                //tmp = tmp->updateBalance(tmp);
                tree.right = tmp;
                n++;
                return (tree.find(val.first,tree.right));
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {

                while (first != last)
                {
                    insert (*first);
                    first++;
                }
            }

            void erase (iterator position)
            {
                tree.right = tree.deleteNode(tree.right, position->first);
                if (tree.right != NULL)
                    tree.right->parent = &tree;
                n--;
            }

            size_type erase (const key_type& k)
            {
                if (!tree.find(k, tree.right))
                    return 0;
                tree.right =tree.deleteNode(tree.right,k);
                if (tree.right != NULL)
                    tree.right->parent = &tree;
                n--;
                return 1;
            }

            void erase (iterator first, iterator last)
            {
                iterator tmp;
                while(first != last)
                {
                    tmp = first;
                    first++;
                    erase(tmp);
                }
            }
            
            void clear()
            {
                if (n != 0)
                    __clear(tree.right);
                n = 0;
            }

            void swap (Map& x)
            {
                Map tmp;

                tmp = x;
                x = *this;
                *this = tmp;
            }

            key_compare key_comp() const
            {
                return c;
            }

            value_compare value_comp() const
            {
                return (value_compare(c));
            }
            iterator find (const key_type& k)
            {
                __base *tmp = tree.find(key_type(k), tree.right);
                if (tmp == NULL)
                    return (&tree);
                return (tmp);
            }
            const_iterator find (const key_type& k) const
            {
                __base *tmp = tree.find(key_type(k), tree.right);
                if (tmp == NULL)
                    return (end());
                return (tmp);
            }

            size_type count (const key_type& k) const
            {
                __base *tmp = tree.find(key_type(k), tree.right);
                if (tmp == NULL)
                    return (0);
                return (1);
            }


            iterator lower_bound (const key_type& k)
            {
                if (tree.find(key_type(k), tree.right) != NULL)
                    return (tree.find(key_type(k), tree.right));
                __base *tmp = tree.getprevnode(key_type(k), tree.right);
                if (tmp == NULL)
                    return (end());
                else
                    return (tmp);
            }

            const_iterator lower_bound (const key_type& k) const
            {
                if (tree.find(key_type(k), tree.right) != NULL)
                    return (tree.find(key_type(k), tree.right));
                __base *tmp = tree.getprevnode(key_type(k), tree.right);
                if (tmp == NULL)
                    return (end());
                else
                    return (tmp);
            }

            iterator upper_bound(const key_type& k)
            {
                __base *tmp = tree.getnextnode(key_type(k), tree.right);
                if (tmp == NULL)
                    return (end());
                else
                    return (tmp);
            }

            const_iterator upper_bound (const key_type& k) const
            {
                __base *tmp = tree.getnextnode(key_type(k), tree.right);
                if (tmp == NULL)
                    return (end());
                else
                    return (tmp);
            }

            ft::pair<iterator,iterator>             equal_range (const key_type& k)
            {
                return(ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
            }

            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return(ft::pair<const_iterator,const_iterator>(this->lower_bound(k), this->upper_bound(k)));
            }
            
            allocator_type get_allocator() const
            {
                return (allocc);
            }
    };
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename ft::Map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin();
        typename ft::Map<Key, T, Compare, Alloc>::const_iterator it2 = lhs.begin();
        while (it != rhs.   end())
        {
            if (*it != *it2)
                return (false);
            ++it2;
            ++it;
        }
        return (true);
    }
    template <class Key, class T, class Compare, class Alloc>
	void swap(ft::Map<Key, T, Compare, Alloc> &x, ft::Map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	};
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() > rhs.size())
            return (true);
        typename ft::Map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin();
       typename ft::Map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
        while (it != lhs.end() && it2 != rhs.end())
        {
            if (*it > *it2)
                return (true);
            ++it2;
            ++it;
        }
        return (false);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs > rhs) && (lhs != rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const Map<Key, T, Compare, Alloc> &lhs, const Map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs > rhs));
    }

}