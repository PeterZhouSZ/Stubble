#ifndef STUBBLE_UV_POINT_HPP
#define STUBBLE_UV_POINT_HPP

namespace Stubble
{

namespace HairShape
{

///----------------------------------------------------------------------------------------------------
/// Class that holds UV coordinates.
///----------------------------------------------------------------------------------------------------
class UVPoint
{
public:

	///----------------------------------------------------------------------------------------------------
	/// Constructor
	///----------------------------------------------------------------------------------------------------
	inline UVPoint(float aU, float AV, int aTriangleID);

	///----------------------------------------------------------------------------------------------------
	/// Gets the U part.
	///----------------------------------------------------------------------------------------------------
	inline float getU() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets the V part.
	///----------------------------------------------------------------------------------------------------
	inline float getV() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets ID of the triangle.
	///----------------------------------------------------------------------------------------------------
	inline int getTriangleID() const;

private:
	float mU; ///< The U coordinate.

	float mV; ///< The V coordinate.

	int mTriangleID; ///< ID of triangle.
};

///----------------------------------------------------------------------------------------------------
/// Constructor
///----------------------------------------------------------------------------------------------------
inline UVPoint::UVPoint(float aU, float AV, int aTriangleID):
	mU(aU),
	mV(mV),
	mTriangleID(aTriangleID)
{
}

///----------------------------------------------------------------------------------------------------
/// Gets the U part.
///----------------------------------------------------------------------------------------------------
inline float UVPoint::getU() const
{
	return mU;
}

///----------------------------------------------------------------------------------------------------
/// Gets the V part.
///----------------------------------------------------------------------------------------------------
inline float UVPoint::getV() const
{
	return mV;
}

///----------------------------------------------------------------------------------------------------
/// Gets ID of the triangle.
///----------------------------------------------------------------------------------------------------
inline int UVPoint::getTriangleID() const
{
	return mTriangleID;
}

} // namespace HairShape

} // namespace Stubble

#endif // STUBBLE_UV_POINT_HPP