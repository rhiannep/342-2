/* $Rev: 250 $ */
#pragma once

#ifndef CONE_H_INCLUDED
#define CONE_H_INCLUDED

#include "Object.h"

/** 
 * \file
 * \brief Cone class header file.
 */


/**
 * \brief Class for Cone objects.
 * 
 * This class provides an Object which is a cone that has its tip at
 * the origin, and its curved surface extends between this tip, to the
 * edge of a circle with unit radius, that is perpendicular to the
 * Z-axis, at Z=1.
 * 
 */
class Cone : public Object {

public:

	/** \brief Cone default constructor.
	 * 
	 * A newly constructed Cone that has its tip at the origin,
	 * and its curved surface extends between this tip, to the
	 * edge of a circle with unit radius, that is perpendicular to
	 * the Z-axis, at Z=1.
	 * It may be moved, rotated, and scaled through its transform member.
	 *
	 * \image html cone.png
	 * \image latex cone.eps
	 */
	Cone();

	/** \brief Cone copy constructor.      
	 * \param cone The Cone to copy.
	 */
	Cone(const Cone& cone);
	
	/** \brief Cone destructor. */
	~Cone();
	
	/** \brief Cone assignment operator.
	 *
	 * \param cone The Cone to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Cone& operator=(const Cone& cone);
	
	/** \brief Cone-Ray intersection computation.
	 *
	 * \todo Currently this method does no object intersections. This needs to be updated.
	 *
	 * As with the Cylinder, the Ray-Cone intersection can be divided into the curves surface
	 * and the cap at the end.
	 *
	 * The curved surface of a Cone has the formula \f$x^2 + y^2 - z^2 = 0\f$, and we are
	 * interested in cases where the \f$Z\f$ co-ordinate is in the range \f$[0,1]\f$.
	 *
	 * The cap at the end of the Cone is the same as that for the top of the Cylinder.
	 *
	 * \param ray The Ray to intersect with this Cone.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // CONE_H_INCLUDED
