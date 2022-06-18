#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include "constants/Elements.hpp"
#include "Vector/Vector.hpp"
#include "MoveAlgorithm/IMoveAlgorithm.hpp"

namespace md
{
	class Atom
	{
	public:
		const element chemElement;
		const double mass;
	private:
		IMoveAlgorithm* moveAlgorithm;
		Vector coordinates;
		Vector velocity;
		Vector acceleration;

		double computeMass(element element);
	public:
		Atom(element element, Vector::ConstPass coordinates, bool isFrozen = false);
		Atom(const std::string_view element, Vector::ConstPass coordinates, bool isFrozen = false);
		Atom(
			element element,
			Vector::ConstPass coordinates,
			Vector::ConstPass velocity,
			bool isFrozen = false
		);
		Atom(
			const std::string_view element,
			Vector::ConstPass coordinates,
			Vector::ConstPass velocity,
			bool isFrozen = false
		);

		Atom(const Atom& other);
		Atom& operator = (const Atom& other) = delete;
		Atom& operator = (Atom&& other) = delete;

		~Atom();
						
		Vector::ConstPass getCoordinates() const noexcept;
		Vector::ConstPass getVelocity() const noexcept;
		Vector::ConstPass getAcceleration() const noexcept;

		void setCoordinates(Vector::ConstPass newCoordinates) noexcept;
		void setVelocity(Vector::ConstPass newVelocity) noexcept;
		void setAcceleration(Vector::ConstPass nawAcceleration) noexcept;

		void addAcceleration(Vector::ConstPass addingAcceleratrion) noexcept;
		void applyForce(Vector::ConstPass force);
		
		void move(double deltaTime) noexcept;
		bool isFrozen() const;
	};
}

#endif	//TAHD_ATOM_H
