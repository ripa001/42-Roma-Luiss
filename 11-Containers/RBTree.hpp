# pragma once

#include <string>
#include <iostream>
#include <cmath>	
#include "utils.hpp"


namespace ft {
	enum        nodeColor {        RED, BLACK      };

	template < typename T >
	struct node {
	    typedef T           value_type;
	    value_type          value;
		node                *parent, *left, *right;
		bool                color;
	    int                 leaf;

	    node( void )    :   value(0), parent (0), left(0), 
	                        right(0), color( RED )                                              {};
	    node( T const& value, node *parent, int leaf )   :      value(value),
	                                                            parent (parent), left(0), right(0),
	                                                            color( RED ), leaf(leaf)        {};
	    node( node const& t )   :   value(t.value),
	                                parent (t.parent), left(t.left), right(t.right),
	                                color( t.color ), leaf(t.leaf)                              {};
	    node&     operator = ( node const& t )
	    {
	        this->value = t.value;
	        this->parent = t.parent;
	        this->left = t.left;
	        this->right = t.right;
	        this->color = t.color;
	        this->leaf = t.leaf;
	        return *this;
	    }
	    ~node () {};
	};

	template < class T, class Compare = std::less< T >, class Alloc = std::allocator<T> >
	class RBTree {
		public:
			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef Compare														value_compare;
			typedef typename allocator_type::pointer				            pointer;
        	typedef typename allocator_type::const_pointer			            const_pointer;
        	typedef typename allocator_type::reference				            reference;
        	typedef typename allocator_type::const_reference		            const_reference;
        	typedef treeIterator< T >									        iterator;
        	typedef treeIterator< const T >								        const_iterator;
        	typedef ft::reverse_iterator< iterator >				            reverse_iterator;
        	typedef ft::reverse_iterator< const_iterator >			            const_reverse_iterator;
        	typedef std::size_t										            size_type;
        	typedef node< value_type >                                          treeNode;
        	typedef typename Alloc::template rebind< treeNode >::other	        node_allocator;

		private:
			treeNode		*_NIL;
			treeNode		*_root;
			size_type		_height;
			Compare			_comp;
			node_allocator	_node_alloc;
			allocator_type	_alloc;

		public:
			explicit RBTree(const value_compare &comp, const allocator_type &alloc) : _NIL(nilNode()), _height(0), _comp(comp), _alloc(alloc) {
				_NIL->color = BLACK;
				_root = _NIL;
			}
 			RBTree( RBTree const &t ) : _NIL(nilNode()), _root(_NIL), _comp(t._comp), _alloc(t._alloc) { insert(t.begin(), t.end()); };

			RBTree& operator=(const RBTree &t) {
				if (this != &t) {
					clear();
					insert(t.begin(), t.end());
					_comp = t._comp;
					_alloc = t._alloc;
				}
				return *this
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

			void        clear(treeNode *root) {
        		if (root && root->leaf)
        	    {
        	        clear(root->left);
        	        clear(root->right);
        	        delNode(root);
        	    }
        	    _root = _NIL;            
        	}

			ft::pair<iterator, bool> insert(value_type const &value) {
				if (_root == NIL) {
					_root = newNode(value, _NIL, 2);
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
						ft::make_pair(iterator(curr), false)
				}
				curr = newNode(value, parent, 1);
				if (_comp(value, parent->value))             parent->left = curr;
            	else                                         parent->right = curr;
				curr->left->parent = curr;
				curr->right->parent = curr;
				// TODO Balancing
            	rebalanceTreeinsert(curr);
            	return ft::make_pair(iterator(curr), true);
			}


			void 				erase(treeNode *node)
			{
					treeNode    *to_del = node;
					treeNode    *to_fix;
					int originColor = node->color;
					if (node->left == NIL)
					{
						to_fix = node->right;
						transplantNode(node, node->right);
					}
					else if (node->right == NIL)
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
						rebalanceTree4erase(to_fix);
					delNode(node);
			};
			void 					erase(iterator first, iterator last)                    {       while (first != last)   erase(*first++);	        };

		
		private:

        	treeNode                    *newNode( value_type const& value, treeNode *parent, int leaf ) {
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

        	void        delNode(treeNode *node) {              
        	    _alloc.destroy(&(node->value));  
        	    _node_alloc.deallocate(node, 1); 
        	    _height--;
        	}

        	void        delnilNode(treeNode *node) {
        	    _node_alloc.deallocate(node, 1); 
        	    _height--; 
        	}

			// min, max
        	treeNode    *min(treeNode* node) const      {       while (node->left != _NIL)       {   node = node->left;      }    return node;        };
        	treeNode    *max(treeNode* node) const      {       while (node && node->leaf)      {   node = node->right;     }    return node;        };
	
			treeNode grandparent(treeNode *n) {
				return n->parent->parent;
			}

			treeNode uncle(treeNode *n) {
				if (n->parent == grandparent(n)->left)
					return grandparent(n)->right;
				else
					return grandparent(n)->left;
			}

			void rebalanceTreeInsert(treeNode *node) {
				insertCase1(node)
			}
			
			void insertCase1(treeNode *n) {
			    if (n == _root || n->parent == NULL)
			        n->color = BLACK;
			    else
			        insertCase2(n);
			}

			void insertCase2(treeNode *n) {
				if (n->parent->color == BLACK)
					return; /* Tree is still valid */
				else
					insertCase3(n);
			}

			void insertCase3(treeNode *n) {
				if (uncle(n) != NULL && uncle(n)->color == RED) {
					n->parent->color = BLACK;
					uncle(n)->color = BLACK;
					grandparent(n)->color = RED;
					insertCase1(grandparent(n));
				}
				else
					insertCase4(n);
			}

			void insertCase4(treeNode *n) {
				if (n == n->parent->right && n->parent == grandparent(n)->left) {
					leftRotate(n->parent);
					n = n->left;
				} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
					rightRotate(n->parent);
					n = n->right;
				}
				insertCase5(n);
			}

			void insertCase5(treeNode *n) {
				n->parent->color = BLACK;
				grandparent(n)->color = RED;
				if (n == n->parent->left && n->parent == grandparent(n)->left) {
					rightRotate(grandparent(n));
				} else {
					/* Here, n == n->parent->right && n->parent == grandparent(n)->right */
					leftRotate(grandparent(n));
				}
			}

			void    leftRotate(treeNode    *node) {
        	    treeNode    *tmp = node->right;
        	    node->right = tmp->left;
        	    if (tmp->left != NIL)
        	        tmp->left->parent = node;
        	    tmp->parent = node->parent;
        	    if (node->parent == NIL)
        	        _root = tmp;
        	    else if (node == node->parent->left)
        	        node = tmp;
        	    else
        	        node->parent->right = tmp;
        	    tmp->left = node;
        	    node->parent = tmp;
        	}

        	void    rightRotate(treeNode *node) {
        	    treeNode    *tmp = node->left;
        	    node->left = tmp->right;
        	    if (tmp->right != NIL)
        	        tmp->right->parent = node;
        	    tmp->parent = node->parent;
        	    if (node->parent == NIL)
        	        _root = tmp;
        	    else if (node == node->parent->right)
        	        node = tmp;
        	    else
        	        node->parent->left = tmp;
        	    tmp->right = node;
        	    node->parent = tmp;
        	}

			void	transplantNode(treeNode *a, treeNode *b)
			{
				if (a->parent == NIL)       _root = b;
				else if (a == a->parent->left)  a->parent->left = b;
				else                            a->parent->right = b;
				b->parent = a->parent;
			};

	};

}; 
