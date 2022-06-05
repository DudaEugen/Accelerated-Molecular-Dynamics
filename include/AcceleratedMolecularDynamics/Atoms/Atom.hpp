#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include "constants/Elements.hpp"
#include "Vector/Vector.hpp"

namespace md
{
	class Atom
	{
	private:
		char actualStepIndex;		/*indexing steps: a[actualStepIndex] containing actuality accelerations
									a[not actualStepIndex] containing accelerations corresponding previous step*/

	public:
		const element chemElement;
		const double mass;
	private:
		Vector r;
		Vector v;
		Vector a[2];

		double computeMass(element element);
		char getPreviousStepIndex() noexcept;
		void changeStepIndex() noexcept;
		void doStepVelocityVerlet(const double dt) noexcept;
	public:
		Atom(element element, Vector::ConstPass coordinates);
		Atom(char element, Vector::ConstPass coordinates);
		Atom(const char element[2], Vector::ConstPass coordinates);
		Atom(const std::string& element, Vector::ConstPass coordinates);
						
		void setCoordinates(Vector::ConstPass coordinates) noexcept;
		void setVelocity(Vector::ConstPass velocity) noexcept;
		void setAcceleration(Vector::ConstPass acceleration) noexcept;
		
		//addQuantity methods are adding argument to actuality value of quantity
		void addVelocity(Vector::ConstPass addingVelocity) noexcept;
		void addAcceleration(Vector::ConstPass addingAcceleratrion) noexcept;
		Vector::ConstPass getCoordinates() const noexcept;
		Vector::ConstPass getVelocity() const noexcept;
		Vector::ConstPass getAcceleration() const noexcept;
		
		//doStepAlhorithm are methods to moving atom corresponding algorithm
		void move(double dt) noexcept;
	};
}

#endif	//TAHD_ATOM_H
