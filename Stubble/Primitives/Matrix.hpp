#ifndef STUBBLE_MATRIX_HPP
#define STUBBLE_MATRIX_HPP

namespace Stubble
{

///----------------------------------------------------------------------------------------------------
/// Representation of Matrix. 
///----------------------------------------------------------------------------------------------------
template < typename Type >
class Matrix
{ 
public:

	///----------------------------------------------------------------------------------------------------
	/// Const array indexer operator. 
	///
	/// \param	aIndex	Zero-based index of a. 
	///
	/// \return	The indexed value. 
	///----------------------------------------------------------------------------------------------------
	inline Type operator[] ( unsigned __int32 aIndex ) const;

	///----------------------------------------------------------------------------------------------------
	/// Array indexer operator. 
	///
	/// \param	aIndex	Zero-based index of a. 
	///
	/// \return	The indexed value. 
	///----------------------------------------------------------------------------------------------------
	inline Type & operator[] ( unsigned __int32 aIndex );

	///-------------------------------------------------------------------------------------------------
	/// Multiplication operator. 
	///
	/// \param	aMat	The matrix. 
	///
	/// \return	The result of the operation. 
	///-------------------------------------------------------------------------------------------------
	inline Matrix< Type > operator* ( const Matrix< Type > & aMat ) const;

	Type m[ 16 ];   ///< The matrix data
};

template < typename Type >
inline Type Matrix< Type >::operator[] ( unsigned __int32 aIndex ) const
{
	return m[ aIndex ];
}

template < typename Type >
inline Type & Matrix< Type >::operator[] ( unsigned __int32 aIndex )
{
	return m[ aIndex ];
}

template < typename Type >
inline Matrix< Type > Matrix< Type >::operator* ( const Matrix< Type > & aMat ) const
{
	Matrix< Type > tmp;
	// First column
	tmp.m[ 0 ] = m[ 0 ] * aMat.m[ 0 ] + m[ 1 ] * aMat.m[ 4 ] + m[ 2 ] * aMat.m[ 8 ] + m[ 3 ] * aMat.m[ 12 ];
	tmp.m[ 0 ] = m[ 0 ] * aMat.m[ 1 ] + m[ 1 ] * aMat.m[ 5 ] + m[ 2 ] * aMat.m[ 9 ] + m[ 3 ] * aMat.m[ 13 ];
	tmp.m[ 0 ] = m[ 0 ] * aMat.m[ 2 ] + m[ 1 ] * aMat.m[ 6 ] + m[ 2 ] * aMat.m[ 10 ] + m[ 3 ] * aMat.m[ 14 ];
	tmp.m[ 0 ] = m[ 0 ] * aMat.m[ 3 ] + m[ 1 ] * aMat.m[ 7 ] + m[ 2 ] * aMat.m[ 11 ] + m[ 3 ] * aMat.m[ 15 ];
	// Second column
	tmp.m[ 0 ] = m[ 4 ] * aMat.m[ 0 ] + m[ 5 ] * aMat.m[ 4 ] + m[ 6 ] * aMat.m[ 8 ] + m[ 7 ] * aMat.m[ 12 ];
	tmp.m[ 0 ] = m[ 4 ] * aMat.m[ 1 ] + m[ 5 ] * aMat.m[ 5 ] + m[ 6 ] * aMat.m[ 9 ] + m[ 7 ] * aMat.m[ 13 ];
	tmp.m[ 0 ] = m[ 4 ] * aMat.m[ 2 ] + m[ 5 ] * aMat.m[ 6 ] + m[ 6 ] * aMat.m[ 10 ] + m[ 7 ] * aMat.m[ 14 ];
	tmp.m[ 0 ] = m[ 4 ] * aMat.m[ 3 ] + m[ 5 ] * aMat.m[ 7 ] + m[ 6 ] * aMat.m[ 11 ] + m[ 7 ] * aMat.m[ 15 ];
	// Third column
	tmp.m[ 0 ] = m[ 8 ] * aMat.m[ 0 ] + m[ 9 ] * aMat.m[ 4 ] + m[ 10 ] * aMat.m[ 8 ] + m[ 11 ] * aMat.m[ 12 ];
	tmp.m[ 0 ] = m[ 8 ] * aMat.m[ 1 ] + m[ 9 ] * aMat.m[ 5 ] + m[ 10 ] * aMat.m[ 9 ] + m[ 11 ] * aMat.m[ 13 ];
	tmp.m[ 0 ] = m[ 8 ] * aMat.m[ 2 ] + m[ 9 ] * aMat.m[ 6 ] + m[ 10 ] * aMat.m[ 10 ] + m[ 11 ] * aMat.m[ 14 ];
	tmp.m[ 0 ] = m[ 8 ] * aMat.m[ 3 ] + m[ 9 ] * aMat.m[ 7 ] + m[ 10 ] * aMat.m[ 11 ] + m[ 11 ] * aMat.m[ 15 ];
	// Fourth column
	tmp.m[ 0 ] = m[ 12 ] * aMat.m[ 0 ] + m[ 11 ] * aMat.m[ 4 ] + m[ 14 ] * aMat.m[ 8 ] + m[ 15 ] * aMat.m[ 12 ];
	tmp.m[ 0 ] = m[ 12 ] * aMat.m[ 1 ] + m[ 11 ] * aMat.m[ 5 ] + m[ 14 ] * aMat.m[ 9 ] + m[ 15 ] * aMat.m[ 13 ];
	tmp.m[ 0 ] = m[ 12 ] * aMat.m[ 2 ] + m[ 11 ] * aMat.m[ 6 ] + m[ 14 ] * aMat.m[ 10 ] + m[ 15 ] * aMat.m[ 14 ];
	tmp.m[ 0 ] = m[ 12 ] * aMat.m[ 3 ] + m[ 11 ] * aMat.m[ 7 ] + m[ 14 ] * aMat.m[ 11 ] + m[ 15 ] * aMat.m[ 15 ];
	return tmp;
}

} //namespace Stubble

#endif //STUBBLE_MATRIX_HPP