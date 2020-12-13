#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <stdlib.h>
#include <cassert>
#include <random>
#include <chrono>
#include <functional>
#include <utility>
#include "mpi.h"
#include "constants.hpp"
#include "Atom.hpp"
#include "Substances.hpp"
#include "Matrix/SquareMatrix.hpp"
#include "NeighboursList.hpp"
#include "ProcessesSet.hpp"
#include "Potential/MockPotential.hpp"
#include "utility/Zip.hpp"
#include "utility/IndexedZip.hpp"
#include "utility/functions_for_derivative.hpp"

using namespace std;

bool equal(double d1, double d2, const int symbolCountAfterPoint = 12)
{
	return static_cast<int>(abs(d1 - d2) * pow(10, symbolCountAfterPoint)) == 0;
}

bool equal(Vector::ConstPass v1, Vector::ConstPass v2, const int symbolCountAfterPoint = 12)
{	
	bool result = true;
	for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		result = result && equal(v1[i], v2[i], symbolCountAfterPoint);
	return result;
}

template<int MIN = -100, int MAX = 100>
double random()
{
	static auto r =  std::bind( 
				std :: uniform_real_distribution<double>(MIN, MAX), 
				std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
			);
	return r();
}

template<int MIN = -100, int MAX = 100>
Vector randomVector()
{
	Vector v;
	for (double& projection: v)
		projection = random<MIN, MAX>();
	return v;
}

void vectorDebug()
{
	if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		assert(equal(Vector({ 3, 4, 0 }).absoluteValue(), Vector({ -5, 0, 0 }).absoluteValue()));
		assert(not equal(Vector({ -3, 4.00000001, 0 }).sumSquares(), Vector({ 0, 0, -5 }).sumSquares()));
		assert(equal(Vector({ 9.8765, -6.789654, 4.324109 }), -Vector({ -9.8765, 6.789654, -4.324109 })));
		assert(equal(Vector({ 4.5, -3.8, 100.000501 }) / 2, Vector({ 2.25, -1.9, 50.0002505 })));
		assert(equal(Vector({ 4, 6, 7 })[0], Vector({ 1, 2, 4 })[2]));
		assert(not equal(Vector({ 4, 6, 7 })[1], Vector({ 1, -6, 4 })[1]));
	}

	Vector zero{};
	Vector v1 = randomVector();
	Vector v2 = v1;
	Vector v3 = randomVector();
	v3 = v2;

	assert(equal(v3, v1));
	assert(equal(2 * v1, v1 + v1));
	assert(equal(v1 - v1, zero));
	assert(equal(-v1, v1 - 2 * v1));
	assert(equal(v2 + v1 - 2 * v3, zero));

	v2 *= 2;
	v3 *= 3;
	assert(equal(v3 + v2, v1 * 5));

	v3 = v2 = v1;
	v2 /= 2;
	v3 /= 3;
	assert(equal(v2 - v3, v1 / 6));

	v3 = v2 = v1;
	v3 += v2;
	v2 -= v3;
	assert(equal(v2 + v1, zero / 6 - v3 * 0));

	Vector vect1 = randomVector();
	Vector::projection_index i = 0;
	for (double& value: vect1)
	{
		assert(value == vect1[i]);
		value = -vect1[i];
		assert(value = vect1[i]);
		vect1[i] *= -1;
		assert(value == vect1[i]);
		++i;
	}

	const Vector vect2;
	Vector::projection_index j = 0;
	for (const double& value: vect2)
	{
		assert(value == 0);
		++j;
	}

}

void atomDebug()
{
	Atom aAl_1("Al", randomVector());
	Atom aAl_2("Al", randomVector());
	Atom aCu_1("Cu", randomVector());
	Atom aCu_2 = aCu_1;

	assert(aAl_1.chemElement == aAl_2.chemElement);
	assert(aCu_1.chemElement == aCu_2.chemElement);
	assert(not(aAl_1.chemElement == aCu_2.chemElement));
	assert(chem_element::get_atomic_mass(aAl_1.chemElement) == 27);
	assert(equal(aAl_1.mass, chem_element::get_atomic_mass(aAl_2.chemElement) / (N_AVOGADRO * 1000)));

	char c[2] = { 'A', 'u' };
	assert(chem_element::get_atomic_mass(Atom(c, randomVector()).chemElement) == 197);
	assert(chem_element::get_atomic_number(Atom(c, randomVector()).chemElement) == 79);

	Vector v = aAl_1.getCoordinates();
	Atom a(c, v);
	assert(equal(a.getCoordinates(), aAl_1.getCoordinates()));
	assert(equal(a.getAcceleration(), randomVector() * 0));

	if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		a.setVelocity(v);
		Vector v2 = { 4, -5.67, 9.23897 };
		a.addVelocity(v2);
		assert(equal(a.getVelocity(), v + v2));

		a.setAcceleration(v2);
		a.addAcceleration(v2 / 2);
		assert(equal(a.getAcceleration(), 1.5 * v2));
	}

	for (int p = 0; p < 3; ++p)
	{
		Vector rx = randomVector();
		Vector rv = randomVector();
		Vector ra = randomVector();
		Atom a1("Cu", Vector());
		Atom a2("Cu", Vector());
		a2.setVelocity(rv);
		Atom a3("Cu", Vector());	
		Atom a4("Al", rx);
		a4.setVelocity(rv);
		a4.addVelocity(rv);
		Atom a5("Au", Vector());
		double dt = 0.000'01;
		for(int i = 0; i < 100'000; ++i)
		{
			a1.move(dt);
			a2.move(dt);
			a3.setAcceleration(ra);
			a3.move(dt);
			a4.setAcceleration(Vector());
			a4.addAcceleration(ra);
			a4.move(dt);
			a5.setAcceleration(ra * (1 - i * dt));
			a5.move(dt);
		}
		assert(equal(a1.getCoordinates(), Vector(), 3));
		assert(equal(a2.getCoordinates(), rv, 3));
		assert(equal(a3.getCoordinates(), ra / 2, 3));
		assert(equal(a4.getCoordinates(), rx + 2*rv + ra / 2, 3));
		assert(equal(a5.getCoordinates(), ra / 2 - ra / 6, 3));
	}
}

void substanceDebug()
{
	assert(convert_to_substance("aluminum") == substance::Aluminum);
	assert(convert_to_substance("AluminUm") == substance::Aluminum);
	assert(convert_to_substance("Graphite") == substance::graphite);
	assert(convert_to_substance("CoPPeR") == substance::Copper);
	assert(equal(get_debye_temperature(convert_to_substance("Aluminum")), 390));
	assert(equal(get_debye_temperature(substance::Gold), 178.));
}

void matrixDebug()
{
	
	SquareMatrix<2> m1 = { {0, 1}, 
	                       {2, 3} };
	SquareMatrix<2> m2 = { {3, -4}, 
	                       {0.5, 6} };
	assert(equal(det(m1), -2));
	assert(equal(det(m2), 20));
	assert(equal(det(m1 + m2), 1. / det(invertible(m1+m2))));
	assert(equal((m1 * m2)[0][1], 6));
	m1[1][0] = 0;
	assert(equal(det(m1), 0));
	m2 /= 2;
	assert(equal(det(m2), 5));
	m2[0][0] *= 3;
	m2[1][0] *= 3;
	assert(equal(det(m2), 15));
	
	SquareMatrix<4> A = { {3.6, -7.8, 0, 2.5},
						   {7.6, -9, 11,  37},
						   {-2, 1.01, 0.345, -0.012504},
						   {34, 0, 3, 6} };
	ColumnMatrix<4> B = { 2, -7.4, 5, 7 };
	ColumnMatrix<4> X = invertible(A) * B;
	assert(equal(X[0], -5932236181. / 16361123414));
	assert(equal(X[1], -20634189316. / 8180561707));
	assert(equal(X[2], 159830004842. / 8180561707));
	assert(equal(X[3], -53563011250. / 8180561707));
	assert(equal(det(A), 1. / det(invertible(A))));
	assert(equal(A[2][3], transponse(A)[3][2]));
}

void atomPairDebug()
{
	Atom a("Cu", randomVector());
	Atom b("Al", randomVector());
	AtomPair pair(a, b);

	assert(&pair.getAtomByIndex(AtomPair::index::first) == &pair.getFirst());
	assert(&pair.getAtomByIndex(AtomPair::index::second) == &pair.getSecond());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::second) == &pair.getFirst());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::first) == &pair.getSecond());
	assert(&a == &pair.getFirst());
	assert(&b == &pair.getSecond());
	Vector d = b.getCoordinates() - a.getCoordinates(); 
	assert(equal(d, pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setCoordinates(randomVector());
	pair.computeDistance();
	d = b.getCoordinates() - a.getCoordinates();
	assert(equal(b.getCoordinates() - a.getCoordinates(), pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setCoordinates(a.getCoordinates());
	pair.computeDistance();
	assert(equal(pair.getDistance(), 0));
}

void borderConditionsDebug()
{
	if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes = {
			BorderConditions::borderType::none,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond(Vector{0, 5, 11.2}, bTypes);
		Vector v; 
		Vector a;

		v = Vector{20, 20, 20};
		a = Vector{20, 0, -2.4};
		assert(not equal(bCond.computePosition(v), Vector{}));
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{-4.6, 0, 7.6}; 
		a = Vector{-4.6, 0, -3.6};	
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0.01, -6, -12.7};
		a = Vector{0.01, -1, -1.5};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{1082, -56.7, 132.4}; 
		a = Vector{1082, -1.7, -2};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0, -4.99, -11.2}; 
		a = Vector{0, 0.01, 0};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0, 2, -5.5}; 
		a = Vector{0, 2, -5.5};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes2 = {
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond2(Vector{3, 4, 5}, bTypes2, Vector{-2, 3, 0});

		v = Vector{-1.9, -0.9, 0.1};
		a = Vector{1.1, 7.1, 5.1};	
		assert(not equal(v, a));
		assert(equal(bCond2.computePosition(v), bCond2.computePosition(a)));

		v = Vector{8, -9.6, -3};
		a = Vector{2, 2.4, 2};
		assert(equal(bCond2.computePosition(v), bCond2.computePosition(a)));
		assert(not equal(v, a));


		assert(equal(bCond.computePosition(Vector{}), Vector{}));
		assert(not equal(bCond2.computePosition(Vector{}), Vector{}));
		assert(equal(bCond.computePosition(Vector{0.5, 3.5, 2}), bCond2.computePosition(Vector{0.5, 3.5, 2})));
		assert(not equal(bCond.computePosition(Vector{4, 4, 4}), bCond2.computePosition(Vector{4, 4, 4})));
	}
}

void neighboursListDebug()
{
	std::vector<Atom> l1;
	Vector v = randomVector();
	Vector d{};
	d[0] += 1;
	l1.push_back(Atom{"Cu", v - 2*d});
	l1.push_back(Atom{"Cu", v});
	l1.push_back(Atom{"Cu", v + 2*d});
	l1.push_back(Atom{"Cu", v + 4*d});

	std::vector<AtomPair> prs;
	prs.push_back(AtomPair(l1[0], l1[1]));
	prs.push_back(AtomPair(l1[0], l1[2]));
	prs.push_back(AtomPair(l1[0], l1[3]));
	prs.push_back(AtomPair(l1[1], l1[2]));
	prs.push_back(AtomPair(l1[1], l1[3]));
	prs.push_back(AtomPair(l1[0], l1[3]));

	NeighboursList nList{l1[1], 2};
	for (std::size_t i = 0; i < prs.size(); ++i)
		nList.addPair(prs[i]);

	assert(nList.getNeighboursOfAtom(l1[1]).size() == 3);
	assert(nList.getNeighboursOfAtom(l1[2]).size() == 2);
	assert(&nList.getNeighboursOfAtom(l1[2])[0].getNeighbourAtom() != &l1[2]);
	assert(&nList.getNeighboursOfAtom(l1[1])[2].getNeighbourAtom() != &l1[1]);
	assert(&nList.getNeighboursOfAtom(l1[1])[0].getPair() == &prs[0]);
	assert(&nList.getNeighboursOfAtom(l1[2])[1].getPair() == &prs[3]);
	assert(nList.getNeighboursOfAtom(l1[1])[1].getPair().getDistance() != 0);
	
	l1[1].setCoordinates(l1[2].getCoordinates());
	prs[3].computeDistance();
	assert(nList.getNeighboursOfAtom(l1[1])[1].getPair().getDistance() == 0);
}

void cellCollectionDebug()
{
	if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes = {
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond(Vector{8, 10, 47}, bTypes);
		APotential* potential = new MockPotential(4);
		std::vector<Atom> atoms = { Atom{"Cu", Vector{}}, Atom{"Cu", Vector{13, 12.1, 12}}};
		CellCollection cc{ atoms, potential, &bCond };
		assert(cc.getCells().size() == 44);

		CellCollection cellCollection{ atoms, potential};
		assert(cellCollection.getCells().size() >= 27);
		int* neighbourCellNumber = new int[30]();	// neighbourCellNumber[i] is number of cell that have i neighbours
		for(auto& cell: cellCollection.getCells())
			++neighbourCellNumber[cell.getNeighborCells().size()];
		for(int i = 0; i < 30; ++i)
		{
			if (i == 8)
				assert(neighbourCellNumber[i] == 8);
			else if ( i==12 || i==18 || i == 27)
				assert(neighbourCellNumber[i] > 0);
			else
				assert(neighbourCellNumber[i] == 0);	
		}
		delete[] neighbourCellNumber;
		int i = 0;
		try
		{
			cellCollection.findCellContainingVector(Vector{1000, -1000, 0});
		}
		catch(const std::range_error& e)
		{
			i = 1;
		}
		assert(i == 1);	
	}

	std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bordersType;
	for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		bordersType[i] = BorderConditions::borderType::periodic;
	Vector vect = randomVector<20, 50>();
	BorderConditions bConditions(vect, bordersType);
	APotential* pot = new MockPotential(6);
	std::vector<Atom> twoAtoms = { Atom{"Cu", Vector{}}, Atom{"Cu", vect}};

	CellCollection cColl{ twoAtoms, pot, &bConditions };
	for(auto& cell: cColl.getCells())
	{
		assert(cell.getNeighborCells().size() == static_cast<std::size_t>(round(pow(3, DIMENSIONAL_NUMBER))));
		bool isFindSelf = false;
		for(auto c: cell.getNeighborCells())
			if (c == &cell)
			{
				isFindSelf = true;
				break;
			}
		assert(isFindSelf);
	}
	Vector v = randomVector();
	assert(&cColl.findCellContainingVector(v) == &cColl.findCellContainingAtom(Atom{"Cu", v}));

	CellCollection cellColl{ twoAtoms, pot};
	for(auto& cell: cellColl.getCells())
	{
		bool isFindSelf = false;
		for(auto c: cell.getNeighborCells())
			if (c == &cell)
			{
				isFindSelf = true;
				break;
			}
		assert(isFindSelf);
	}
}

void zipDebug()
{
	Vector v1 = randomVector();
	Vector v2 = randomVector();
	std::array<int, DIMENSIONAL_NUMBER> arr;
	for(auto& v: arr)
		v = random();
	
	Vector::projection_index i = 0;
	for (auto [a, b, c]: Zip(v1, v2, std::as_const(arr)))
	{
		assert(equal(a, v1[i]));
		assert(equal(b, v2[i]));
		a = 1;
		assert(equal(v1[i], 1));
		a = -1;
		assert(equal(v1[i], -1));
		assert(c == arr[i]);
		++i;
	}
	assert(i == DIMENSIONAL_NUMBER);

	for (auto [index, a, b]: IndexedZip(v1, arr))
	{
		assert(equal(a, v1[index]));
		assert(b == arr[index]);
		assert(index >= 0 && index < DIMENSIONAL_NUMBER);
	}

	std::vector<int> v = {10, 20, 30 , 40, 50, 60, 70, 80, 90};
	i = 0;
	for (auto [index, p]: IndexedZip(v))
	{
		assert(p == 10*(index + 1));
		++i;
	}
	assert(i == v.size());

	for (auto [index, a, b, c]: IndexedZip(v1, arr, v2))
		assert(index < DIMENSIONAL_NUMBER);
	for (auto [index, a, b, c, p]: IndexedZip(v1, arr, v2, v))
		assert(index < DIMENSIONAL_NUMBER);
	std::array<int, 3> dd = {};
	for (auto [index, a, b, c, p, d]: IndexedZip(v1, arr, v2, v, dd))
		assert(index < DIMENSIONAL_NUMBER);
}

void derivativeDebug()
{
	double x = random<-3, 3>();

	Const c{2};
	assert(equal(compute_value(c, x), 2));
	assert(equal(compute_derivative(c, x), 0));

	Variable v;
	assert(equal(compute_value(v, x), x));
	assert(equal(compute_derivative(v, x), 1));

	auto e_c = f_exp(c);
	auto e_v = f_exp(v);
	assert(equal(compute_value(e_c, x), exp(c.compute_value(x))));
	assert(equal(compute_derivative(e_c, x), 0));
	assert(equal(compute_value(e_v, x), exp(v.compute_value(x))));
	assert(equal(compute_derivative(e_v, x), exp(v.compute_value(x))));

	auto ee = f_sum(f_exp(e_v), f_exp(c));
	assert(equal(compute_value(ee, x), exp(exp(x)) + exp(2)));
	assert(equal(compute_derivative(ee, x), exp(exp(x)) * exp(x)));

	auto p1 = f_sum(f_pow(v, 3), f_product(c, Const(3)));
	auto p2 = f_exp(f_pow(v, 0.5));
	assert(equal(compute_value(p1, x), pow(x, 3) + 6));
	assert(equal(compute_value(p2, abs(x)), exp(pow(abs(x), 0.5))));
	assert(equal(compute_derivative(p1, x), 3 * pow(x, 2)));
	assert(equal(compute_derivative(p2, abs(x)), exp(pow(abs(x), 0.5)) * 0.5 * pow(abs(x), -0.5)));

	auto func = f_sum(f_product(Variable(), f_exp(Variable())), f_product(Const(3), f_pow(Variable(), 5)));
	assert(equal(compute_value(func, x), x*exp(x) + 3 * pow(x, 5)));
	assert(equal(compute_derivative(func, x), x*exp(x) + exp(x) + 15 * pow(x, 4)));
}

void funcDebug(int ProcRank, int procNum)
{
	for (int i = 0; i < procNum; ++i)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		if (i == ProcRank)
		{
			vectorDebug();
			atomDebug();
			substanceDebug();
			matrixDebug();
			atomPairDebug();
			borderConditionsDebug();
			neighboursListDebug();
			cellCollectionDebug();
			zipDebug();
			derivativeDebug();

			std::cout << "tests completed\n";
		}
	}
}

int main(int argc, char* argv[])
{
	int ProcRank, ProcNum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
	funcDebug(ProcRank, ProcNum);

	MPI_Finalize();

	return 0;
}
