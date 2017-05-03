#pragma once

#ifndef SPOT_LIGHT_SOURCE_H_INCLUDED
#define SPOT_LIGHT_SOURCE_H_INCLUDED

#include "LightSource.h"
#include "Direction.h"

/**
 * \file 
 * \brief SpotLightSource class header file.
 */

/**
 * \brief Light emitted from a Point in a limited range of Directions.
 *
 * A SpotLightSource represents light emitted from a point in the Scene,
 * but which only illuminates in a cone.
 * The amount of light that reaches any given part of the scene should follow
 * a \f$1/r^2\f$ law, so more distant Objects receive less illumination, much like PointLightSource.
 * However, a SpotLightSource also has a Direction, and an angle property. 
 * Only objects that are within the specified angle of the SpotLightSource's Direction should be illuminated.
 *
 * This creates the effect of a cone of light, as shown in the illustration below. A SpotLightSource
 * at some location, \b p, illuminates a cone around the direction, \b d. Only the parts of an object 
 * within some angle \f$\theta\f$ of that direction are illuminated. There is no illumination from
 * the SpotLightSource outside of the cone (black shading in the illustration). Note that within the
 * cone parts of an Object can still be shadowed (grey shading) like any other LightSource.
 *
 * \image html spotLight.png
 * \image latex spotLight.eps
 */
class SpotLightSource : public LightSource {

public:

	/** \brief SpotLightSource default constructor. 
	 *
	 * This creates a white light source at the origin that has intensity 1 at distance 1.
	 * The light source points along the Z-axis, and has an angle of 45 degrees.
	 **/
	SpotLightSource();

	/** \brief SpotLightSource constructor. 
	 *
	 * This creates a white light source at the origin that has intensity 1 at distance 1.
	 * The Direction and angle of the SpotLightSource are specified as parameters.
	 * 
	 * \param d The Direction of the SpotLightSource.
	 * \param a The angle of the SpotLightSource
	 **/
	SpotLightSource(Direction d, double a);

	/** \brief SpotLightSource copy constructor. 
	 *
	 * \param lightSource The SpotLightSource to copy to \c this.
	 **/
	SpotLightSource(const SpotLightSource& lightSource);
	
	/** \brief PointLightSource destructor */
	~SpotLightSource();
	
	/** \brief SpotLightSource assignment operator.
	 *
	 * \param lightSource The SpotLightSource to copy to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 **/
	const SpotLightSource& operator=(const SpotLightSource& lightSource);

	/** \brief Determine how much light reaches a Point.
	 *
	 * \todo The SpotLightSource intensity method needs to be implemented as part of the assignment.
	 *       The illumination from a SpotLightSource should be the same as that from a PointLightSource
	 *       within the angle of illumination, but zero outside of this cone.
	 *
	 * \param point The Point at which light is measured.
	 * \return The proportion of the base illumination that reaches the Point.
	 */
	double getIntensityAt(const Point& point) const;

	Direction direction; //!< The direction of the SpotLightSource.
	double angle; //!< The half-angle, in degrees, of illumination provided by the SpotLightSource.

};

#endif