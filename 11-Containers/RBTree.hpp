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
            	// rebalanceTree4insert(curr);
            	return ft::make_pair(iterator(curr), true);
			}
		
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
	
	};
}; 
