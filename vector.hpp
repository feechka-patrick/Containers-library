#pragma once

#include <iostream>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			//	-- member types

			typedef T 										value_type;
			typedef Allocator 								allocator_type;
			typedef std::size_t 							size_type;
			typedef std::ptrdiff_t 							difference_type;
			typedef value_type& 							reference;
			typedef const value_type& 						const_reference;
			typedef typename Allocator::pointer 			pointer;
			typedef typename Allocator::const_pointer 		const_pointer;
			//typedef 										iterator;
			//typedef 										const_iterator;
			//typedef std::reverse_iterator<iterator> 		reverse_iterator;
			//typedef std::reverse_iterator<const_iterator> 	const_reverse_iterator;


			//	-- CONSTRUCTORS

			//vector();

			explicit vector(const allocator_type &alloc = allocator_type())
				: alloc(alloc), array(0), vsize(0), csize(0) {}

			explicit vector(size_type count,
							const value_type &value = value_type(),
							const allocator_type &alloc = allocator_type())
							: alloc(alloc), csize(0), vsize(0) 
			{
				try
				{
					array = alloc.allocate(count);
				}
				catch(const std::exception& e)
				{
					this->~vector();
					throw vector::MemoryException();
				}
				csize = count;
				vsize = count;
				for (size_type i = 0; i < vsize; ++i) {
					alloc.construct(array + i, value);
				}
			}

			template <class InputIt>
			vector(InputIt first, InputIt last,
				const allocator_type &alloc = allocator_type());

			vector( const vector& other ) : vsize(0), csize(0), alloc(other.alloc) 
			{
				try
				{
					array = alloc.allocate(other.csize);
				}
				catch(const std::exception& e)
				{
					this->~vector();
					throw vector::MemoryException();
				}
				csize = other.csize;
				vsize = other.vsize;
				for (size_type i = 0; i < vsize; ++i) {
					alloc.construct(array + i, other[i]);
				}
			}


			//	-- DESTRUCTOR

			~vector()
			{
				for (size_type i = 0; i < vsize; i++){
					alloc.destroy(array + i);
				}
				if (csize != 0) alloc.deallocate(array, csize);
				array = 0;
				vsize = 0;
				csize = 0;
			}

			// -- OPERATOR=

			vector& operator= (const vector& other)
			{
				this->~vector();
				array = alloc.allocate(other.csize);
				csize = other.csize;
				vsize = other.vsize;
				for (size_type i = 0; i < vsize ; ++i) {
					alloc.construct(array + i, other[i]);
				}
			}


			// -- MEMBER FUNCTIONS

			void assign( size_type count, const T& value );

			template< class InputIt >
			void assign( InputIt first, InputIt last );

			allocator_type get_allocator() const { return alloc; }

			reference at( size_type pos )
			{
				if (!(pos < this->size()))
					throw vector::RangeException();
				return array[pos];
			}

			const_reference at( size_type pos ) const
			{
				if (!(pos < this->size()))
					throw vector::RangeException();
				return array[pos];	
			}
			
			reference operator[]( size_type pos ) { return array[pos]; }

			const_reference operator[]( size_type pos ) const { return array[pos]; }

			reference front() { return *array; }

			const_reference front() const { return *array; }

			reference back() { return *(array + vsize - 1); }

			const_reference back() const { return *(array + vsize - 1); }

			T* data() { return array; }

			const T* data() const { return array; }

			/* ...... */

			// -- ITERATORS

			// iterator begin();

			// const_iterator begin() const;

			// iterator end();

			// const_iterator end() const;

			// reverse_iterator rbegin();

			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();

			// const_reverse_iterator rend() const;


			// -- CAPACITY

			bool empty() const { return vsize == 0 ? true : false; }

			size_type size() const { return vsize; }

			size_type max_size() const { return alloc.max_size(); }

			void reserve( size_type new_cap )
			{
				if (new_cap > this->max_size())
					throw vector::LengthException();
				if (new_cap <= csize) return;

				//new array
				pointer newarray;
				try
				{
					newarray = alloc.allocate(new_cap);
				}
				catch(const std::exception& e)
				{
					throw vector::MemoryException();
				}
				csize = new_cap;
				for (size_type i = 0; i < vsize; ++i) 
					alloc.construct(newarray + i, array[i]);
				
				//free
				for (size_type i = 0; i < vsize; i++){
					alloc.destroy(array + i);
				}
				if (csize != 0) alloc.deallocate(array, csize);

				array = newarray;
			}

			size_type capacity() const { return csize; }


			// -- MODIFIERS

			void clear()
			{
				for (size_type i = 0; i < vsize; i++){
					alloc.destroy(array + i);
				}
				vsize = 0;
			}


			// -- EXCEPTIONS

			class MemoryException : public std::exception {
				const char* what() const throw() {
					return "ft::bad_alloc";
				}
			};

			class LengthException : public std::exception {
				const char* what() const throw() {
					return "ft::length_error";
				}
			};
			
			class RangeException : public std::exception {
				const char* what() const throw() {
					return "ft::out_of_range";
				}
			};

		private:
			allocator_type		alloc; // allocator
			pointer				array; // pointer to first element
			size_type			vsize; // vector size
			size_type			csize; // size alocated memory		
	};
}
