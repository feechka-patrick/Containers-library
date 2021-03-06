#pragma once

#include <iostream>
#include <iterator> // std::random_access_iterator_tag

namespace ft{
	template<class Iter>
	class reverse_iterator
	{
		public:
			typedef Iter										iterator_type;
			typedef typename Iter::value_type					value_type;
			typedef typename Iter::difference_type				difference_type;
			typedef typename Iter::pointer						pointer;
			typedef typename Iter::reference					reference;
			typedef typename Iter::iterator_category			iterator_category;
			
			// -- CONSTRUCTORS

			reverse_iterator();

			explicit reverse_iterator( iterator_type x ) : it(x) {}

			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : it(other.base()) {}

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ){
				it = other.base();
				return *this;
			}

			//~reverse_iterator() {}

			// -- MEMBER FUNCTIONS

			iterator_type base() const { return it; }

			reference operator*() const { return *it; }
			pointer operator->() const { return it.operator->(); }

			value_type operator[]( difference_type n ) const {
				reverse_iterator tmp(it);
				tmp += n;
				return *(tmp.base());
			}


			// -- advances or decrements the iterator

			reverse_iterator& operator++() {
				 --it;
				 return *this; 
			}
			reverse_iterator& operator--() {
				 ++it;
				 return *this; 
			}
			reverse_iterator operator++( int ) {
				iterator_type old_it = it;
				it--;
				return reverse_iterator(old_it);
			}
			reverse_iterator operator--( int ) {
				iterator_type old_it = it;
				it++;
				return reverse_iterator(old_it);
			}

			reverse_iterator operator+( difference_type n ) const { 
				return reverse_iterator(it - n); 
			}

			reverse_iterator operator-( difference_type n ) const { 
				return reverse_iterator(it + n); 
			}
			
			reverse_iterator& operator+=( difference_type n ){
				it = it - n;
				return *this;
			}

			reverse_iterator& operator-=( difference_type n ){
				it = it + n;
				return *this;
			}

		private:
			iterator_type it;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() == lhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() != lhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() < lhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() <= lhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() > lhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ){
						return rhs.base() >= lhs.base();
	}

	template< class Iter >
	reverse_iterator<Iter>
		operator+( typename reverse_iterator<Iter>::difference_type n,
               const reverse_iterator<Iter>& it ){
				   return reverse_iterator<Iter>(it.base() - n);
	}

	template< class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
		operator-( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs ){
					return rhs.base() - lhs.base();
	}
}