#ifndef STUBBLE_SELECTED_GUIDES_HPP
#define STUBBLE_SELECTED_GUIDES_HPP

#include "Common\CommonTypes.hpp"
#include "HairShape\HairComponents\GuidePosition.hpp"
#include "HairShape\HairComponents\Segments.hpp"
#include "HairShape\Mesh\MeshPoint.hpp"
#include "Toolbox\ToolShapes\ToolShape.hpp"

namespace Stubble
{

namespace HairShape
{

namespace HairComponents
{

typedef Toolbox::ToolShape * SelectionMask;

///-------------------------------------------------------------------------------------------------
/// Additional information about the segment for tools (brush tool, cut tool etc.) 
///-------------------------------------------------------------------------------------------------
struct OneSegmentAdditionalInfo
{
	bool mActive;	///< true to active

	Real mFallOff;	///< The fall off
};

///-------------------------------------------------------------------------------------------------
/// Defines an alias representing the segments additional info .
///-------------------------------------------------------------------------------------------------
typedef std::vector< OneSegmentAdditionalInfo > SegmentsAdditionalInfo;

///-------------------------------------------------------------------------------------------------
/// Selected guide. 
///-------------------------------------------------------------------------------------------------
struct SelectedGuide
{
	GuideCurrentPosition mPosition; ///< The guide current position

	GuideId mGuideId; ///< The guide segments id

	OneGuideSegments mSegments; ///< Pointer to segments of selected guide ( represented as vertices )

	SegmentsAdditionalInfo mSegmentsAdditionalInfo; ///< Information describing the segments additional params

	bool mDirtyRedrawFlag; ///< True if segments has been changed and needs to be redrawn

	bool mDirtyFlag;	///< True if selected guide has been changed in any way and must be stored..
};

///-------------------------------------------------------------------------------------------------
/// Defines an alias representing the selected guides .
///-------------------------------------------------------------------------------------------------
typedef std::vector< SelectedGuide > SelectedGuides;

} // namespace HairComponents

} // namespace HairShape

} // namespace Stubble

#endif // STUBBLE_SELECTED_GUIDES_HPP