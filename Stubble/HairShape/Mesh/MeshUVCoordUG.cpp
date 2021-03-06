#include "MeshUVCoordUG.hpp"

#include <cassert>

namespace Stubble
{

namespace HairShape
{

MeshUVCoordUG::MeshUVCoordUG():
	mDirtyBit( true ),
	mTriangles( 0 ),
	mTrianglesInGrid( 0 ),
	mGridSize( 0 )
{
	mGrid.mTriangles = 0;
	mGrid.mTrianglesCount = 0;
}

MeshUVCoordUG::~MeshUVCoordUG()
{
	delete [] mTriangles;
	delete [] mTrianglesInGrid;
	for( unsigned int i = 0; i < mGridSize; ++i )
	{
		delete[] mGrid.mTriangles[i];
		delete[] mGrid.mTrianglesCount[i];
	}
	delete[] mGrid.mTriangles;
	delete[] mGrid.mTrianglesCount;
}

void MeshUVCoordUG::build( Triangles & aTriangles )
{
	// Free old memory
	delete [] mTriangles;
	mTriangles = 0;
	delete [] mTrianglesInGrid;
	mTrianglesInGrid = 0;

	for( unsigned int i = 0; i < mGridSize; ++i )
	{
		delete[] mGrid.mTriangles[i];
		delete[] mGrid.mTrianglesCount[i];
	}
	delete[] mGrid.mTriangles;
	delete[] mGrid.mTrianglesCount;

	// Aproximate the size of grid
	mGridSize = static_cast< unsigned __int32 >( ceil( sqrtf( static_cast< float >( aTriangles.size() ) ) ) );

	// Allocate new memory for grid
	mGrid.mTriangles = new Triangle *** [ mGridSize ];
	mGrid.mTrianglesCount = new unsigned __int32 * [ mGridSize ];
	for( unsigned int i = 0; i < mGridSize; ++i )
	{
		mGrid.mTriangles[ i ] = new Triangle**[ mGridSize ];
		mGrid.mTrianglesCount[ i ] = new unsigned __int32[ mGridSize ];
		for( unsigned int j = 0; j < mGridSize; ++j )
		{
			mGrid.mTrianglesCount[ i ][ j ] = 0;
		}
	}

	// Zero counts
	//memset( reinterpret_cast< void * >( mGrid.mTrianglesCount ), 0, mGridSize * mGridSize * 
	//	sizeof ( unsigned __int32 ) );//TODO nemuze to zde neco provest?

	// The total count of triangles in grid
	unsigned __int32 total = 0;
   
	// Prepare triangles array
	mTriangles = new Triangle[ aTriangles.size() ];
	Triangle * trIt = mTriangles;

	// first pass: count how many triangle pointers are needed in each cell
	for ( Triangles::const_iterator it = aTriangles.begin(); it != aTriangles.end(); ++it, ++trIt )
	{
		// Copy triangle
		Real u0 = trIt->mVertices[ 0 ].mUCoordinate = it->getVertex1().getUCoordinate();
		Real v0 = trIt->mVertices[ 0 ].mVCoordinate = it->getVertex1().getVCoordinate();
		Real u1 = trIt->mVertices[ 1 ].mUCoordinate = it->getVertex2().getUCoordinate();
		Real v1 = trIt->mVertices[ 1 ].mVCoordinate = it->getVertex2().getVCoordinate();
		Real u2 = trIt->mVertices[ 2 ].mUCoordinate = it->getVertex3().getUCoordinate();
		Real v2 = trIt->mVertices[ 2 ].mVCoordinate = it->getVertex3().getVCoordinate();

		// Calculate bounding box
		Real uMin = MIN3( u0, u1, u2 );
		Real uMax = MAX3( u0, u1, u2 );
		Real vMin = MIN3( v0, v1, v2 );
		Real vMax = MAX3( v0, v1, v2 );

		// Find max, min bounding box coordinates
		int xMin = static_cast< int >( MAX( 0, floor( uMin * mGridSize ) ) ); 
		if ( xMin >= static_cast< int >( mGridSize ) ) 
		{
			continue;
		}
		int xMax = static_cast< int >( MIN( mGridSize - 1, ceil( uMax * mGridSize ) ) ); 
		if ( xMax < 0 ) 
		{
			continue;
		}
		int yMin = static_cast< int >( MAX( 0, floor( vMin * mGridSize ) ) ); 
		if ( yMin >= static_cast< int >( mGridSize ) )
		{
			continue;
		}
		int yMax = static_cast< int >( MIN( mGridSize - 1, ceil( vMax * mGridSize ) ) ); 
		if ( yMax < 0 ) 
		{
			continue;
		}

		// Increase counts in all cells in range
		for ( int y = yMin; y <= yMax; ++y ) 
		{
			for ( int x = xMin; x <= xMax; ++x ) 
			{
				++mGrid.mTrianglesCount[ y ][ x ];
				++total;
			}
		}
	}
      
	// Allocate and distribute space in a linear buffer
	mTrianglesInGrid = new Triangle * [ total ];
	Triangle ** buf = mTrianglesInGrid;
	for ( unsigned int y = 0; y < mGridSize; ++y ) 
	{
		for ( unsigned int x = 0; x < mGridSize; ++x ) 
		{
			// We want to set cell pointer to end of its triangles buffer
			buf += mGrid.mTrianglesCount[ y ][ x ]; 
			mGrid.mTriangles[ y ][ x ] = buf; 
		}
	}
	
	// second pass: assign triangles (from the end of tiny buffers)
	for ( Triangle * trIt = mTriangles, * end = mTriangles + aTriangles.size(); trIt != end; ++trIt )
	{
		// Copy triangle
		Real u0 = trIt->mVertices[ 0 ].mUCoordinate;
		Real v0 = trIt->mVertices[ 0 ].mVCoordinate;
		Real u1 = trIt->mVertices[ 1 ].mUCoordinate;
		Real v1 = trIt->mVertices[ 1 ].mVCoordinate;
		Real u2 = trIt->mVertices[ 2 ].mUCoordinate;
		Real v2 = trIt->mVertices[ 2 ].mVCoordinate;

		// Calculate bounding box
		Real uMin = MIN3( u0, u1, u2 );
		Real uMax = MAX3( u0, u1, u2 );
		Real vMin = MIN3( v0, v1, v2 );
		Real vMax = MAX3( v0, v1, v2 );

		// Find max, min bounding box coordinates
		int xMin = static_cast< int >( MAX( 0, floor( uMin * mGridSize ) ) ); 
		if ( xMin >= static_cast< int >( mGridSize ) ) 
		{
			continue;
		}
		int xMax = static_cast< int >( MIN( mGridSize - 1, ceil( uMax * mGridSize ) ) ); 
		if ( xMax < 0 ) 
		{
			continue;
		}
		int yMin = static_cast< int >( MAX( 0, floor( vMin * mGridSize ) ) ); 
		if ( yMin >= static_cast< int >( mGridSize ) )
		{
			continue;
		}
		int yMax = static_cast< int >( MIN( mGridSize - 1, ceil( vMax * mGridSize ) ) ); 
		if ( yMax < 0 ) 
		{
			continue;
		}

		// add triangle to all cells in range
		for ( int y = yMin; y <= yMax; ++y ) 
		{
			for ( int x = xMin; x <= xMax; ++x ) 
			{
				*--mGrid.mTriangles[ y ][ x ] = trIt;
			}
		}
	}
	mDirtyBit = false;
}

UVPoint MeshUVCoordUG::getUVPoint( const MeshPoint &aPoint ) const
{
	assert( !mDirtyBit ); // Structure is build and holds current data

	Real u = aPoint.getUCoordinate();
	Real v = aPoint.getVCoordinate();

	// first select grid cell
	int x = static_cast< int >( floor( u * mGridSize ) ); 
	if ( x < 0 || x >= static_cast< int >( mGridSize ) )
	{
		return UVPoint( 0, 0, UVPoint::NOT_TRIANGLE );
	}
	int y = static_cast< int >( floor( v * mGridSize ) ); 
	if ( y < 0 || y >= static_cast< int >( mGridSize ) )
	{
		return UVPoint( 0, 0, UVPoint::NOT_TRIANGLE );
	}

	// For every triangle in cell
	for ( Triangle ** trIt = mGrid.mTriangles[ y ][ x ], ** end = trIt + mGrid.mTrianglesCount[ y ][ x ]; 
		trIt != end; ++trIt )
	{
		// Select u,v coordinates of triangle points
		Real u0 = ( *trIt )->mVertices[ 0 ].mUCoordinate;
		Real v0 = ( *trIt )->mVertices[ 0 ].mVCoordinate;
		Real u1 = ( *trIt )->mVertices[ 1 ].mUCoordinate;
		Real v1 = ( *trIt )->mVertices[ 1 ].mVCoordinate;
		Real u2 = ( *trIt )->mVertices[ 2 ].mUCoordinate;
		Real v2 = ( *trIt )->mVertices[ 2 ].mVCoordinate;

		// Calculate determinant
		Real det = ( u0 - u2 ) * ( v1 - v2 ) + ( u2 - u1 ) * ( v0 - v2 ); 
		if ( det == 0 ) 
		{
			continue;
		}
		// Calculate first bar. coordinate
		Real b0  = ( u - u2 ) * ( v1 - v2 ) + ( u2 - u1 ) * ( v - v2 ); 
		if ( b0 * det >= 0 ) // Inside triangle ?
		{
			// Calculate second bar. coordinate
			Real b1  = ( u0 - u2 ) * ( v - v2 ) + ( u2 - u ) * ( v0 - v2 ); 
			if ( b1 * det >= 0 ) // Inside triangle ?
			{
				// Calculate third bar. coordinate
				Real b2  = det - b0 - b1; 
				if ( b2 * det >= 0 ) // Inside triangle ?
				{
					Real invdet = 1 / det;
					return UVPoint( b0 * invdet, b1 * invdet, static_cast< unsigned __int32 >( *trIt - mTriangles ) );
				}
			}
		}
	}
	// Nothing was found
	return UVPoint( 0, 0, UVPoint::NOT_TRIANGLE );
}

} // namespace HairShape

} // namespace Stubble