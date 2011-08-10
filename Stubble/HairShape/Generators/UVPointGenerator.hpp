#ifndef STUBBLE_UV_POINT_GENERATOR_HPP
#define STUBBLE_UV_POINT_GENERATOR_HPP

#include "Common\CommonTypes.hpp"
#include "HairShape\Generators\RandomGenerator.hpp"
#include "HairShape\Mesh\UVPoint.hpp"
#include "HairShape\Mesh\TriangleConstIterator.hpp"
#include "HairShape\Texture\Texture.hpp"

#include <vector>

namespace Stubble
{

namespace HairShape
{

class UVPointGenerator
{
public:
	///----------------------------------------------------------------------------------------------------
	/// Default constructor. 
	///
	/// \param	aTexture						texture
	/// \param	aTriangleConstIterator			mesh triangle iterator
	/// \param [in,out]	aRandomGenerator		random number generator. 
	///----------------------------------------------------------------------------------------------------
	UVPointGenerator( const Texture &aTexture, TriangleConstIterator & aTriangleConstIterator, RandomGenerator & aRandomNumberGenerator );

	///----------------------------------------------------------------------------------------------------
	/// Finaliser. 
	///----------------------------------------------------------------------------------------------------
	inline ~UVPointGenerator();

	///----------------------------------------------------------------------------------------------------
	/// Generation of next sample. 
	///
	/// \return	Generated sample. 
	///----------------------------------------------------------------------------------------------------
	UVPoint next();

	///----------------------------------------------------------------------------------------------------
	/// Gets a triangle normalized density. 
	///
	/// \param	aID	Identifier for a triangle. 
	///
	/// \return	The triangle normalized density. 
	///----------------------------------------------------------------------------------------------------
	inline Real getTriangleDensity( int aID ) const;

private:

	///----------------------------------------------------------------------------------------------------
	/// Builds the vertices. 
	///----------------------------------------------------------------------------------------------------
	void BuildVertices();
	
	///----------------------------------------------------------------------------------------------------
	/// Sub triangle. 
	///----------------------------------------------------------------------------------------------------
	struct SubTriangle
	{
		///----------------------------------------------------------------------------------------------------
		/// Sets sub triangle properties . 
		///
		/// \param	aVertex1ID			Identifier for a vertex 1. 
		/// \param	aVertex2ID			Identifier for a vertex 2. 
		/// \param	aVertex3ID			Identifier for a vertex 3. 
		/// \param	aCDFValue			a cdf value. 
		/// \param	aTriangleSimpleID	Simple identifier for triangle or current recursion depth. 
		///----------------------------------------------------------------------------------------------------
		void set( unsigned __int16 aVertex1ID, unsigned __int16 aVertex2ID, 
			unsigned __int16 aVertex3ID, Real aCDFValue, unsigned int aTriangleSimpleID )
		{
			mVertex1ID = aVertex1ID;
			mVertex2ID = aVertex2ID;
			mVertex3ID = aVertex3ID;
			mCDFValue = aCDFValue;
			mTriangleSimpleID = aTriangleSimpleID;
		}

		///----------------------------------------------------------------------------------------------------
		/// Default constructor. 
		///----------------------------------------------------------------------------------------------------
		SubTriangle()
		{
		}

		unsigned int mTriangleSimpleID; ///< Simple identifier for the triangle or current recursion depth
		unsigned __int16 mVertex1ID; ///< Identifier for the vertex 1
		unsigned __int16 mVertex2ID; ///< Identifier for the vertex 2
		unsigned __int16 mVertex3ID; ///< Identifier for the vertex 3
		Real mCDFValue; ///< The cdf value
	};

	///----------------------------------------------------------------------------------------------------
	/// Triangle
	///----------------------------------------------------------------------------------------------------

	///----------------------------------------------------------------------------------------------------
	/// Vertex (Barycentric coordinates). 
	///----------------------------------------------------------------------------------------------------

	struct Vertex
	{
		Real mU; ///< The u coordinate
		Real mV; ///< The v coordinate
	};

	///----------------------------------------------------------------------------------------------------
	/// Defines an alias representing the sub triangles .
	///----------------------------------------------------------------------------------------------------
	typedef std::vector< SubTriangle > SubTriangles;

	///----------------------------------------------------------------------------------------------------
	/// Defines an alias representing array of reals .
	///----------------------------------------------------------------------------------------------------
	typedef std::vector< Real > RealArray;

	///----------------------------------------------------------------------------------------------------
	/// Defines an alias representing array of vertices .
	///----------------------------------------------------------------------------------------------------
	typedef std::vector< Vertex > VerticesArray;

	///< Depth of the maximum division of one triangle
	static const unsigned int MAX_DIVISION_DEPTH = 8;

	///< Size of the maximum triangle uv (2^MAX_DISION_DEPTH)
	static const unsigned int MAX_TRIANGLE_UV_SIZE = 1 << MAX_DIVISION_DEPTH;
	
	///< Number of subtriangles = 4^MAX_DIVISION_DEPTH
	static const unsigned int NUM_TRIANGLES = 1 << ( MAX_DIVISION_DEPTH << 1 );
	
	///< Size of the stack = number of subtriangles + MAX_DIVISION_DEPTH = 4^MAX_DIVISION_DEPTH + MAX_DIVISION_DEPTH
	static const unsigned int STACK_SIZE = NUM_TRIANGLES + MAX_DIVISION_DEPTH;

	///< Index of first vertex in triangle
	static const unsigned int FIRST_VERTEX_INDEX = 0;
	
	///< Index of second vertex in triangle (2^MAX_DIVISION_DEPTH)
	static const unsigned int SECOND_VERTEX_INDEX = 1 << MAX_DIVISION_DEPTH;
	
	///< Index of third vertex in triangle (2^MAX_DIVISION_DEPTH + 2)*(2^MAX_DIVISION_DEPTH + 1)/2 - 1
	static const unsigned int THIRD_VERTEX_INDEX = 
		( ( ( SECOND_VERTEX_INDEX + 1 ) * ( SECOND_VERTEX_INDEX + 2 ) ) >> 1 ) - 1;
	
	///< Number of vertices in divided triangle
	static const unsigned int VERTICES_COUNT = THIRD_VERTEX_INDEX + 1;
	
	SubTriangles mSubTriangles;	///< The sub triangles cdf
	
	VerticesArray mVertices; ///< The vertices
	
	RandomGenerator & mRandomNumberGenerator; ///< The random number generator

	RealArray mTrianglesPDF;  ///< The triangles pdf
};

// inline functions implementation

inline UVPointGenerator::~UVPointGenerator()
{
}

///----------------------------------------------------------------------------------------------------
/// Gets a triangle density. 
///
/// \param	aID	Identifier for a triangle. 
///
/// \return	The triangle density. 
///----------------------------------------------------------------------------------------------------
inline Real UVPointGenerator::getTriangleDensity( int aID ) const
{
	return mTrianglesPDF[ aID ];
}

} // namespace HairShape

} // namespace Stubble

#endif // STUBBLE_UV_POINT_GENERATOR_HPP