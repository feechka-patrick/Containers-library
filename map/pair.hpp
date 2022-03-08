#pragma once

namespace ft{
	template < class T1, typename T2 >
	struct pair {

		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair( void ) : first(), second() {}

		pair( const first_type &x, const second_type &y ) : first( x ), second( y ) {}

		template < class U1, class U2 >
		pair( const pair<U1, U2> &p ) : first( p.first ), second( p.second ) {}

		pair	&operator = ( const pair &src ) {
			if ( this != &src ) {
				first = src.first;
				second = src.second;
			}
			return *this;
		}
    };

    template < class T1, class T2 >
	ft::pair<T1, T2>	make_pair( T1 t, T2 u ) {
		return ft::pair<T1, T2>( t, u );
	}

	template < class T1, class T2 >
	bool	operator == ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool	operator != ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !(lhs == rhs);
	}

	template < class T1, class T2 >
	bool	operator < ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return lhs.first < rhs.first || ( !( rhs.first < lhs.first ) && lhs.second < rhs.second );
	}

	template < class T1, class T2 >
	bool	operator <= ( const pair<T2, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !( rhs < lhs );
	}

	template < class T1, class T2 >
	bool	operator > ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return rhs < lhs;
	}

	template < class T1, class T2 >
	bool	operator >= ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !( lhs < rhs );
	}
}