#include "iterator.hpp"

namespace ft {

	enum	nodeColor { RED, BLACK };

	template <class Pair>
	struct fakeNode {
		fakeNode					*parent;
		fakeNode 				*left;
		fakeNode 				*right;
		Pair					data;
		int						color;
	};

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
	    node&     operator= ( node const& t )
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
	
	template< typename U >
	class treeRBIterator
	{
		public:
			typedef U								value_type;
			typedef U*								pointer;
			typedef const U*						const_pointer;
			typedef U&								reference;
			typedef const U&                        const_reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef node< value_type >              treeNode;
			typedef node< const value_type >        const_treeNode;
			typedef treeRBIterator< U >               iterator;
			typedef treeRBIterator< const U >         const_iterator;

			treeRBIterator( void ) :  _node(NULL)                         {};
			treeRBIterator( treeNode * current ) : _node(current)         {};
			treeRBIterator( treeRBIterator const& t ) : _node(t.base())     {};
			treeRBIterator&		operator= ( treeRBIterator const& t )    {       _node = t.base(); return *this;         };

			operator           const_iterator() const                  {       return const_iterator(reinterpret_cast<const_treeNode *>(_node));    }

			treeNode            *base( void )   const                   {       return _node;                           };

			reference		operator* () 							    {       return _node->value;                    };
			const_reference	operator* () const						    {       return _node->value;                    };
			pointer			operator->()							    {       return &_node->value;                   };
			const_pointer	operator->() const						    {       return &_node->value;                   };

			treeRBIterator&		operator++ ()
			{
				if (!_node->leaf)
					return *this;
				if (_node && _node->right && _node->right->leaf)
				{
					// std::cout << "quisakhdskjdas" << std::endl;
					_node = _node->right;
					while (_node && _node->left && _node->left->leaf) _node = _node->left;
				}
				else
				{

					// std::cout << "cdsjncds" << std::endl;
					// if (!_node->parent->leaf)
					// 	return *this;
					treeNode	*curr = _node;
					_node = _node->parent;
					while (_node && _node->leaf && _node->right == curr)
					{
						curr = _node;
						_node = _node->parent;
					};
				}
				// std::cout << "sasdsa" << std::endl;
				return *this;
			}
			
			treeRBIterator&		operator-- ()
			{
				// std::cout << this << "ksajndksjan";
				if (!_node->leaf)
				{
					while (_node->parent && _node->parent->leaf)
						_node = _node->parent;
					while (_node->right && _node->right->leaf)
						_node = _node->right;
					return *this;
				}
				else if (_node->left && _node->left->leaf)
				{
					_node = _node->left;
					while (_node->right && _node->right->leaf) _node = _node->right;
				}
				else
				{
					treeNode	*curr = _node;
					_node = _node->parent;
					while (_node && _node->leaf && _node->left == curr)
					{
						curr = _node;
						_node = _node->parent;
					};
				}
				return *this;
			}
			treeRBIterator		operator++ ( int )							    {   treeRBIterator ptr(*this); operator++(); return ptr;  }
			treeRBIterator		operator-- ( int )							    {   treeRBIterator ptr(*this); operator--(); return ptr;  }

			bool		operator== ( treeRBIterator const& t ) 		            {	return  _node == t._node;	};
			bool		operator!= ( treeRBIterator const& t )		            {	return  _node != t._node;	};
			bool		operator> ( treeRBIterator const& t ) 		            {	return  _node > t._node;	};
			bool		operator<= ( treeRBIterator const& t ) 		            {	return  _node <= t._node;	};
			bool		operator< ( treeRBIterator const& t ) 		            {	return  _node < t._node;	};
			bool 	    operator>= ( treeRBIterator const& t ) 		            {	return  _node >= t._node;	};
			
			private:
				treeNode*			    _node;
	};

}