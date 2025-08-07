#ifndef ENTITIES_HPP
#define ENTITIES_HPP

//#define current_class reinterpret_cast<uint64_t>( this )
//
//#define declare_member(type, name, offset) type name() { return vm->read<type>( current_class + offset ); } 
//#define declare_member_bit(Bit, Name, Offset) bool Name( ) { return bool( vm->read<char>( current_class + Offset) & (1 << Bit)); }
//
//#define apply_member(type, name, offset) void name( type val ) { vm->write<type>( current_class + offset, val); }
//#define apply_member_bit(Bit, Name, Offset) void Name( bool Value ) { vm->write<char>( vm->read<char>( current_class + Offset) | (1 << Bit), Value); }

namespace sdk {

	struct fname {
		std::uint32_t idx;
	};

	template< class type >
	class tarray {
	public:

		tarray( ) : data( ), count( ), max_count( ) { }
		tarray( type* data, std::uint32_t count, std::uint32_t max_count ) :
			data( data ), count( count ), max_count( max_count ) { }

		FORCEINLINE type get( std::uintptr_t idx ) const
		{	
			return vm->read< type >(
				std::bit_cast< std::uintptr_t >( this->data ) + ( idx * sizeof( type ) ) 
			);
		}

		FORCEINLINE std::vector<type> get_itter( )
		{
			if ( this->count > this->max_count )
				return {};

			std::vector<type> buffer( this->count );

			vm->read_array( 
				std::bit_cast<std::uintptr_t>( this->data ), 
				buffer.data( ), 
				sizeof( type ) * this->count
			);

			return buffer;
		}

		ALWAYS_INLINE std::uintptr_t get_addr( )
		{
			return reinterpret_cast<std::uintptr_t>( this->data );
		}

		ALWAYS_INLINE std::uint32_t size( ) const
		{
			return this->count;
		};

		ALWAYS_INLINE std::uint32_t max_size( ) const
		{
			return this->max_count;
		};

		ALWAYS_INLINE bool is_valid_index( std::int32_t index ) const
		{
			return this->index >= 0 && index < count;
		};

		ALWAYS_INLINE bool is_valid( ) const
		{
			return this->data != nullptr;
		};

		type* data;
		std::uint32_t count;
		std::uint32_t max_count;

	};



}

#endif // !gaurd