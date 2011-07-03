#ifndef STUBBLE_GUIDE_HAIR_HPP
#define STUBBLE_GUIDE_HAIR_HPP

#include "Primitives\Vector3D.hpp"

namespace Stubble
{

namespace HairShape
{

class GuideHair
{
public:
	///----------------------------------------------------------------------------------------------------
	/// Defines an alias representing the segments .
	///----------------------------------------------------------------------------------------------------
	typedef Vector3D< double > * Segments;

	///----------------------------------------------------------------------------------------------------
	/// Default constructor. 
	///----------------------------------------------------------------------------------------------------
	inline GuideHair();

	///----------------------------------------------------------------------------------------------------
	/// Copy constructor. 
	///----------------------------------------------------------------------------------------------------
	inline GuideHair( const GuideHair & aCopy );

	///----------------------------------------------------------------------------------------------------
	/// Copy operator. 
	///
	/// \param	aCopy	a copy. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline const GuideHair & operator==( const GuideHair & aCopy );

	///----------------------------------------------------------------------------------------------------
	///  Resets the segments in normal direction. 
	///
	/// \param	aSegmentsCount	Number of the segments. 
	/// \param	aSegmentSize	Size of a segment. 
	///----------------------------------------------------------------------------------------------------
	inline void resetSegments( unsigned int aSegmentsCount, double aSegmentSize );

	///----------------------------------------------------------------------------------------------------
	///  Resets the segments in normal direction without changes to segments count
	///
	/// \param	aSegmentSize	Size of a segment. 
	///----------------------------------------------------------------------------------------------------
	inline void resetSegments( double aSegmentSize );

	///----------------------------------------------------------------------------------------------------
	/// Gets the segments ( stored as end positions of segments )
	///
	/// \return	The segments ( stored as end positions of segments ). 
	///----------------------------------------------------------------------------------------------------
	inline const Segments getSegments() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets the segments count. 
	///
	/// \return	The segments count. 
	///----------------------------------------------------------------------------------------------------
	inline unsigned int getSegmentsCount() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets the world transform matrix. Can be used as model-view OpenGL matrix (glMultMatrix( * ) ).
	///
	/// \return	The world transform matrix. 
	///----------------------------------------------------------------------------------------------------
	inline const double * getWorldTransformMatrix() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets a segment end in world coordinates. 
	///
	/// \param	aIndex	Zero-based index of segments. 
	///
	/// \return	The segment end in world coordinates. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D< double > getSegmentEndInWorldCoordinates( unsigned int aIndex ) const;
	
	///----------------------------------------------------------------------------------------------------
	/// Finaliser. 
	///----------------------------------------------------------------------------------------------------
	inline ~GuideHair();

private:
	Segments mSegments; ///< The segments of guide hair ( stored as end positions of segments )

	unsigned int mSegmentsCount; ///< Number of segments

	double mWorldTransformMatrix[ 16 ]; ///< The world transformation matrix
};

} // namespace HairShape

} // namespace Stubble

#endif // STUBBLE_GUIDE_HAIR_HPP