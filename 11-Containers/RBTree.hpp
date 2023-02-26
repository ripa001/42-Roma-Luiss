# pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include "utils.hpp"
#include "iterator/RBTree_iterator.hpp"
namespace ft {

	template < class T, class Compare = std::less< T >, class Alloc = std::allocator<T> >
	class RBTree {
		public:
			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef Compare														value_compare;
        	typedef ft::treeRBIterator< T >									    iterator;
        	typedef ft::treeRBIterator< const T >								const_iterator;
        	typedef ft::reverse_iterator< iterator >				            reverse_iterator;
        	typedef ft::reverse_iterator< const_iterator >			            const_reverse_iterator;
			typedef typename allocator_type::pointer				            pointer;
        	typedef typename allocator_type::const_pointer			            const_pointer;
        	typedef typename allocator_type::reference				            reference;
        	typedef typename allocator_type::const_reference		            const_reference;
        	typedef std::size_t										            size_type;
        	typedef node< value_type >                                          treeNode;
        	typedef fakeNode< value_type >                                          fakeNodeI;
        	typedef typename Alloc::template rebind< treeNode >::other	        node_allocator;
        	typedef typename Alloc::template rebind< fakeNodeI >::other	        node_allocator_fake;

		private:
			treeNode		*_NIL;
			treeNode		*_root;
			size_type		_height;
			Compare			_comp;
			node_allocator	_node_alloc;
			node_allocator_fake	_node_alloc_fake;
			allocator_type	_alloc;

		public:
			explicit RBTree(const value_compare &comp, const allocator_type &alloc) : _NIL(nilNode()), _height(0), _comp(comp), _alloc(alloc) {
				_NIL->color = BLACK;
				_root = _NIL;
			}
			
 			RBTree( RBTree const &t ) : _NIL(nilNode()), _root(_NIL), _comp(t._comp), _alloc(t._alloc) { insert(t.begin(), t.end()); };

			RBTree& operator=(const RBTree &t) {
				if (this != &t) {
					clear(_root);
					insert(t.begin(), t.end());
					_comp = t._comp;
					_alloc = t._alloc;
				}
				return *this;
			}

			void        delNilNode(treeNode *node)
        	{              
        	    _node_alloc.deallocate(node, 1); 
        	    _height--; 
        	}
			~RBTree(void) {
				clear(_root);
				delNilNode(_NIL);
			};


			treeNode	*nilNode() {
				treeNode    *nilnode = _node_alloc.allocate(1);

            	nilnode->left  = _NIL;
            	nilnode->right = _NIL;
            	nilnode->parent = 0;
            	nilnode->color = BLACK;
            	nilnode->leaf = 0;
				return (nilnode);
			}


			bool		empty( void ) const { return (_height == 0); };
			size_type   size( void ) const { return (_height); };
	    	size_type	max_size() const { return (_node_alloc_fake.max_size()); };

			treeNode*	search(treeNode* to_find, const value_type& val) const
        	{
        	    while (to_find != _NIL) 
        	    {
        	        if (_comp(val, to_find->value))
						to_find = to_find->left;
        	        else if (_comp(to_find->value, val))
						to_find = to_find->right;
        	        else
						return (to_find);
        	    }
        	    return 0;
        	}

			void        clear(treeNode *root) {
        		if (root && root->leaf)
        	    {
        	        clear(root->left);
        	        clear(root->right);
        	        delNode(root);
        	    }
        	    _root = _NIL;            
        	}
        	iterator	insert(iterator position, const value_type& value) { return insert(value).first; (void)position; };

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last) { while (first != last) insert(*first++); }

			ft::pair<iterator, bool> insert(value_type const &value) {
				if (_root == _NIL) {
					_root = newNode(value, _NIL, 2);
					_NIL->parent = _root;
					_root->color = BLACK;
					return ft::make_pair(iterator(_root), true);
				}
				treeNode	*parent = _NIL;
				treeNode	*curr = _root;
				while (curr != _NIL)
				{
					parent = curr;
					if (_comp(value, curr->value))
						curr = curr->left;
					else if(_comp(curr->value, value))
						curr = curr->right;
					else
						return (ft::make_pair(iterator(curr), false));
				}
				curr = newNode(value, parent, 1);
				if (_comp(value, parent->value))             parent->left = curr;
            	else                                         parent->right = curr;
				curr->left->parent = curr;
				curr->right->parent = curr;
            	rebalanceTreeInsert(curr);
            	return ft::make_pair(iterator(curr), true);
			}

			
			size_type	erase(value_type const &val)
        	{
        	    treeNode	*to_del = search(_root, val);
			    if (!to_del)
        	        return 0;
			    erase(to_del);
			    return 1;
        	}

			void 				erase(treeNode *node)
        	{
                treeNode    *to_del = node;
                treeNode    *to_fix;
                int originColor = node->color;
                if (node->left == _NIL)
                {
                    to_fix = node->right;
                    transplantNode(node, node->right);
                }
                else if (node->right == _NIL)
                {
                    to_fix = node->left;
                    transplantNode(node, node->left);
                }
                else
                {
                    to_del = min(node->right); //min
                    originColor = to_del->color;
                    to_fix = to_del->right;
                    if (to_del->parent == node) to_fix->parent = to_del; // to check
                    else
                    {
                        transplantNode(to_del, to_del->right);
                        to_del->right = node->right;
                        to_del->right->parent = to_del;
                    }
                    transplantNode(node, to_del);
                    to_del->left = node->left;
                    to_del->left->parent = to_del;
                    to_del->color = node->color;
                }
                if (originColor == BLACK)
                    rebalanceTreeErase(to_fix);
                delNode(node);
        };
			void	erase(iterator first, iterator last) { while (first != last) erase(*first++); }

			iterator				begin( void )
        	{
        	    if (_root == _NIL)		return iterator(_NIL);
        	    treeNode* first = _root;
        	    while (first && first->left != _NIL) { first = first->left; }
        	    return iterator(first);
        	}

        	const_iterator			begin( void ) const
        	{
        	    if (_root == _NIL || !_root)  return iterator(_NIL);
        	    treeNode* first = _root;
        	    while (first && first->left != _NIL) first = first->left;
        	    return iterator(first);
        	}

        	iterator				end() { return iterator(max(_root)); }
        	const_iterator			end() const { return iterator(max(_root)); }
        	reverse_iterator		rbegin() { return reverse_iterator(end()); }
        	const_reverse_iterator	rbegin() const { return reverse_iterator(end()); }
        	reverse_iterator		rend() { return reverse_iterator(begin()); }
        	const_reverse_iterator	rend() const { return reverse_iterator(begin()); }
			// void 					erase(iterator first, iterator last) { while (first != last)   erase(*first++);	        };
			void	swap( RBTree &t) {
				ft::swap(_root, t._root);
				ft::swap(_NIL, t._NIL);
				ft::swap(_height, t._height);
				ft::swap(_alloc, t._alloc);
				ft::swap(_node_alloc, t._node_alloc);
				ft::swap(_comp, t._comp);
			};

			iterator	find(const value_type &val ) const{
				treeNode	*curr = search(_root, val);
				if (curr)
					return iterator(curr);
				return iterator(max(_root));
			};

			iterator	lower_bound( value_type const &val ) const {
				treeNode	*curr = _root;
				treeNode	*prev = _NIL;
				while (curr != _NIL)
				{
					if (_comp(curr->value, val))
						curr = curr->right;
					else
					{
						prev = curr;
						curr = curr->left;
					}
				}
				return iterator(prev);
			};

			treeNode* upper_bound (const value_type& value) const {
        	    treeNode*	node = _root;
        	    treeNode*	upper = _NIL;
	
        	    while (node != _NIL)
        	    {
        	        if (_comp(value, node->value))
        	            {       upper = node; node = node->left;        }
        	        else        node = node->right;
        	    }
        	    return upper;
        	};
			
			allocator_type	get_allocator( void ) { return (_alloc); };
			treeNode    	*get_root() const { return (_root); };


		private:

        	treeNode	*newNode( value_type const& value, treeNode *parent, int leaf ) {
        	    treeNode    *newnode = _node_alloc.allocate(1);
        	    _alloc.construct(&(newnode->value), value);
        	    newnode->left  = _NIL;
        	    newnode->right = _NIL;
        	    newnode->parent = parent;
        	    newnode->color = RED;
        	    newnode->leaf = leaf;
        	    _height++;
				return newnode;
        	};

        	void	delNode(treeNode *node) {
        	    _alloc.destroy(&(node->value));  
        	    _node_alloc.deallocate(node, 1); 
        	    _height--;
        	}

			// min, max
        	treeNode    *min(treeNode* node) const      {       while (node->left != _NIL)       {   node = node->left;      }    return node;        };
        	treeNode    *max(treeNode* node) const      {       while (node && node->leaf)      {   node = node->right;     }    return node;        };
	
			treeNode *grandparent(treeNode *n) {
				return n->parent->parent;
			}

			treeNode *uncle(treeNode *n) {
				if (n->parent == grandparent(n)->left)
					return grandparent(n)->right;
				else
					return grandparent(n)->left;
			}

			void	rebalanceTreeInsert(treeNode *node) {
				insertCase1(node);
			}
			
			void	insertCase1(treeNode *n) {
			    if (n == _root || n->parent == NULL)
			        n->color = BLACK;
			    else
			        insertCase2(n);
			}

			void	insertCase2(treeNode *n) {
				if (n->parent->color == BLACK)
					return; /* Tree is still valid */
				else
					insertCase3(n);
			}

			void	insertCase3(treeNode *n) {
				if (uncle(n) != NULL && uncle(n)->color == RED) {
					n->parent->color = BLACK;
					uncle(n)->color = BLACK;
					grandparent(n)->color = RED;
					insertCase1(grandparent(n));
				}
				else
					insertCase4(n);
			}

			void	insertCase4(treeNode *n) {
				if (n == n->parent->right && n->parent == grandparent(n)->left) {
					leftRotate(n->parent);
					n = n->left;
				} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
					rightRotate(n->parent);
					n = n->right;
				}
				insertCase5(n);
			}

			void	insertCase5(treeNode *n) {
				n->parent->color = BLACK;
				grandparent(n)->color = RED;
				if (n == n->parent->left && n->parent == grandparent(n)->left) {
					rightRotate(grandparent(n));
				} else {
					/* Here, n == n->parent->right && n->parent == grandparent(n)->right */
					leftRotate(grandparent(n));
				}
			}

			void	leftRotate(treeNode *node)
			{
				treeNode    *tmp = node->right;
				node->right = tmp->left;
				if (tmp->left != _NIL)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == _NIL)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
			}

			void	rightRotate(treeNode *node)
			{
				treeNode    *tmp = node->left;
				node->left = tmp->right;
				if (tmp->right != _NIL)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == _NIL)
					_root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;
			}
			void	transplantNode(treeNode *a, treeNode *b)
			{
				if (a->parent == _NIL)       _root = b;
				else if (a == a->parent->left)  a->parent->left = b;
				else                            a->parent->right = b;
				b->parent = a->parent;
			};

			 void    rebalanceTreeErase(treeNode *node)
			{
				while (node != _root && node->color == BLACK)
				{
					if( node == node->parent->left)
					{
						treeNode *sibling = node->parent->right;
						if (sibling->color == RED)
						{
							recolorNode(sibling); //b
							node->parent->color = RED; 
							leftRotate(node->parent);
							sibling = node->parent->right;
						}
						if (sibling->left->color == BLACK && sibling->right->color == BLACK)
						{
							sibling->color = RED;
							node = node->parent;
						}
						else
						{
							if (sibling->right->color == BLACK)
							{
								sibling->left->color = BLACK;
								sibling->color = RED;
								rightRotate(sibling);
								sibling = node->parent->right;
							}
							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->right->color = BLACK;
							leftRotate(node->parent);
							node = _root;
						}
					}
					else
					{
						treeNode *sibling = node->parent->left;
						if (sibling->color == RED)
						{
							recolorNode(sibling);
							node->parent->color = RED;
							rightRotate(node->parent);
							sibling = node->parent->left;
						}
						if (sibling->right->color == BLACK && sibling->left->color == BLACK)
						{
							sibling->color = RED;
							node = node->parent;
						}
						else 
						{
							if (sibling->left->color == BLACK)
							{
								sibling->right->color = BLACK;
								sibling->color = RED;
								leftRotate(sibling);
								sibling = node->parent->left;
							}
							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->left->color = BLACK;
							rightRotate(node->parent);
							node = _root;
						}
					}
				}
				node->color = BLACK;
			};
		    void	recolorNode(treeNode *node) { node->color == RED ? node->color = BLACK : node->color = RED; };        


			// void	rebalanceTreeErase(treeNode *node) {
			// 	eraseCase1(node);
			// }

			// treeNode *sibling(treeNode *n) {
			//     if (n == n->parent->left)
			//         return n->parent->right;
			//     else
			//         return n->parent->left;
			// }

			// void	eraseCase1(treeNode *n) {
			//     if (n == _root || n->parent == NULL)
			//         return;
			//     else
			//         eraseCase2(n);
			// }

			// void	eraseCase2(treeNode *n) {
    		// 	if (sibling(n)->color == RED) {
    		// 	    n->parent->color = RED;
    		// 	    sibling(n)->color = BLACK;
    		// 	    if (n == n->parent->left)
    		// 	        leftRotate(n->parent);
    		// 	    else
    		// 	        rightRotate(n->parent);
    		// 	}
    		// 	eraseCase3(n);
			// }

			// void	eraseCase3(treeNode *n) {
    		// 	if (n->parent->color == BLACK &&
    		// 	    sibling(n)->color == BLACK &&
    		// 	    sibling(n)->left->color == BLACK &&
    		// 	    sibling(n)->right->color == BLACK)
    		// 	{
    		// 	    sibling(n)->color = RED;
    		// 	    eraseCase1(n->parent);
    		// 	}
    		// 	else
    		// 	    eraseCase4(n);
			// }

			// void	eraseCase4(treeNode *n) {
			//     if (n->parent->color == RED &&
			//         sibling(n)->color == BLACK &&
			//         sibling(n)->left->color == BLACK &&
			//         sibling(n)->right->color == BLACK)
			//     {
			//         sibling(n)->color = RED;
			//         n->parent->color = BLACK;
			//     }
			//     else
			//         eraseCase5(n);
			// }

			// void	eraseCase5(treeNode *n) {
			//     if (n == n->parent->left && sibling(n)->color == BLACK &&
			//         sibling(n)->left->color == RED && sibling(n)->right->color == BLACK) {
			//         sibling(n)->color = RED;
			//         sibling(n)->left->color = BLACK;
			//         rightRotate(sibling(n));
			//     }
			//     else if (n == n->parent->right && sibling(n)->color == BLACK &&
			//              sibling(n)->right->color == RED && sibling(n)->left->color == BLACK) {
			//         sibling(n)->color = RED;
			//         sibling(n)->right->color = BLACK;
			//         leftRotate(sibling(n));
			//     }
			//     eraseCase6(n);
			// }

			// void eraseCase6(treeNode *n) {
			//     sibling(n)->color = n->parent->color;
			//     n->parent->color = BLACK;
			//     if (n == n->parent->left) {
			//         /* Here, sibling(n)->right->color == RED */
			//         sibling(n)->right->color = BLACK;
			//         leftRotate(n->parent);
			//     }
			//     else {
			//         /* Here, sibling(n)->left->color == RED */
			//         sibling(n)->left->color = BLACK;
			//         rightRotate(n->parent);
			//     }
			// }
	};

}; 
