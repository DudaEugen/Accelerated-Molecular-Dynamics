#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include "CustomEnum/CustomEnum.hpp"
#include <vector>
#include <utility>

namespace md
{
	namespace element_impl
	{
		class AtomicMass
		{
			const std::vector<std::pair<double, unsigned>> massDistribution;
		public:
			AtomicMass(const std::initializer_list<std::pair<double, unsigned>>& massDistribution);
			unsigned average();
			unsigned random();
		};
	}

	CREATE_ENUM_F2(
		element,
		FUNCTION_HEADERS(std::uint8_t atomicNumber, element_impl::AtomicMass atomicMass),
		VALUE_TUPLE(H, 1, element_impl::AtomicMass({ {0.9998, 1}, {0.0002, 2} })),
		VALUE_TUPLE(He, 2, element_impl::AtomicMass({ {0.0000001, 3}, {0.9999999, 4} })),
		VALUE_TUPLE(Li, 3, element_impl::AtomicMass({ {0.079, 6}, {0.921, 7} })),
		VALUE_TUPLE(Be, 4, element_impl::AtomicMass({ {1, 9} })),
		VALUE_TUPLE(B, 5, element_impl::AtomicMass({ {0.188, 10}, {0.812, 11} })),
		VALUE_TUPLE(C, 6, element_impl::AtomicMass({ {0.989, 12}, {0.011, 13} })),
		VALUE_TUPLE(N, 7, element_impl::AtomicMass({ {0.9962, 14}, {0.0038, 15} })),
		VALUE_TUPLE(O, 8, element_impl::AtomicMass({ {0.9976, 16}, {0.0004, 17}, {0.002, 18} })),
		VALUE_TUPLE(F, 9, element_impl::AtomicMass({ {1, 19} })),
		VALUE_TUPLE(Ne, 10, element_impl::AtomicMass({ {0.9048, 20}, {0.0027, 21}, {0.0925, 22} })),
		VALUE_TUPLE(Na, 11, element_impl::AtomicMass({ {1, 23} })),
		VALUE_TUPLE(Mg, 12, element_impl::AtomicMass({ {0.786, 24}, {0.101, 25}, {0.113, 26} })),
		VALUE_TUPLE(Al, 13, element_impl::AtomicMass({ {1, 27} })),
		VALUE_TUPLE(Si, 14, element_impl::AtomicMass({ {0.9223, 28}, {0.0467, 29}, {0.031, 30} })),
		VALUE_TUPLE(P, 15, element_impl::AtomicMass({ {1, 31} })),
		VALUE_TUPLE(S, 16, element_impl::AtomicMass({ {0.9502, 32}, {0.0075, 33}, {0.0421, 34}, {0.0002, 36} })),
		VALUE_TUPLE(Cl, 17, element_impl::AtomicMass({ {0.7578, 35}, {0.2422, 37} })),
		VALUE_TUPLE(Ar, 18, element_impl::AtomicMass({ {0.00337, 36}, {0.00063, 38}, {0.996, 40} })),
		VALUE_TUPLE(K, 19, element_impl::AtomicMass({ {0.93258, 39}, {0.0673, 41} })),
		VALUE_TUPLE(Ca, 20, element_impl::AtomicMass({ {0.96941, 40}, {0.00647, 42}, {0.00135, 43}, {0.02086, 44}, {0.00004, 46} })),
		VALUE_TUPLE(Sc, 21, element_impl::AtomicMass({ {1, 45} })),
		VALUE_TUPLE(Ti, 22, element_impl::AtomicMass({ {0.0795, 46}, {0.0775, 47}, {0.7345, 48}, {0.0551, 49}, {0.0534, 50} })),
		VALUE_TUPLE(V, 23, element_impl::AtomicMass({ {0.9975, 51} })),
		VALUE_TUPLE(Cr, 24, element_impl::AtomicMass({ {0.04345, 50}, {0.83789, 52}, {0.09501, 53}, {0.02365, 54} })),
		VALUE_TUPLE(Mn, 25, element_impl::AtomicMass({ {1, 55} })),
		VALUE_TUPLE(Fe, 26, element_impl::AtomicMass({ {0.05845, 54}, {0.91754, 56}, {0.02119, 57}, {0.00282, 58} })),
		VALUE_TUPLE(Co, 27, element_impl::AtomicMass({ {1, 59} })),
		VALUE_TUPLE(Ni, 28, element_impl::AtomicMass({ {0.6827, 58}, {0.261, 60}, {0.0113, 61}, {0.0359, 62}, {0.0091, 64} })),
		VALUE_TUPLE(Cu, 29, element_impl::AtomicMass({ {0.691, 63}, {0.309, 65} })),
		VALUE_TUPLE(Zn, 30, element_impl::AtomicMass({ {0.492, 64}, {0.277, 66}, {0.04, 67}, {0.185, 68}, {0.006, 70} })),
		VALUE_TUPLE(Ga, 31, element_impl::AtomicMass({ {0.6011, 69}, {0.3989, 71} })),
		VALUE_TUPLE(Ge, 32, element_impl::AtomicMass({ {0.2055, 70}, {0.2737, 72}, {0.0767, 73}, {0.3674, 74} })),
		VALUE_TUPLE(As, 33, element_impl::AtomicMass({ {1, 75} })),
		VALUE_TUPLE(Se, 34, element_impl::AtomicMass({ {0.0087, 74}, {0.0902, 76}, {0.0758, 77}, {0.2352, 78}, {0.4982, 80} })),
		VALUE_TUPLE(Br, 35, element_impl::AtomicMass({ {0.5056, 79}, {0.4944, 81} })),
		VALUE_TUPLE(Kr, 36, element_impl::AtomicMass({ {0.0228, 80}, {0.1158, 82}, {0.1149, 83}, {0.57, 84}, {0.173, 86} })),
		VALUE_TUPLE(Rb, 37, element_impl::AtomicMass({ {0.722, 85} })),
		VALUE_TUPLE(Sr, 38, element_impl::AtomicMass({ {0.0056, 84}, {0.0986, 86}, {0.07, 87}, {0.8258, 88} })),
		VALUE_TUPLE(Y, 39, element_impl::AtomicMass({ {1, 89} })),
		VALUE_TUPLE(Zr, 40, element_impl::AtomicMass({ {0.5146, 90}, {0.1123, 91}, {0.1711, 92}, {0.174, 94} })),
		VALUE_TUPLE(Nb, 41, element_impl::AtomicMass({ {1, 93} })),
		VALUE_TUPLE(Mo, 42, element_impl::AtomicMass({ {0.1586, 92}, {0.0912, 94}, {0.157, 95}, {0.165, 96}, {0.0945, 97}, {0.2375, 98} })),
		VALUE_TUPLE(Ru, 44, element_impl::AtomicMass({ {0.057, 96}, {0.022, 98}, {0.128, 99}, {0.127, 100}, {0.13, 101}, {0.313, 102}, {0.183, 104} })),
		VALUE_TUPLE(Rh, 45, element_impl::AtomicMass({ {1, 103} })),
		VALUE_TUPLE(Pd, 46, element_impl::AtomicMass({ {0.01, 102}, {0.1114, 104}, {0.2233, 105}, {0.2733, 106}, {0.2646, 108}, {0.1172, 110} })),
		VALUE_TUPLE(Ag, 47, element_impl::AtomicMass({ {0.51839, 107}, {0.48161, 109} })),
		VALUE_TUPLE(Cd, 48, element_impl::AtomicMass({ {0.0125, 106}, {0.0089, 108}, {0.1247, 110}, {0.128, 111}, {0.2411, 112}, {0.2875, 114} })),
		VALUE_TUPLE(In, 49, element_impl::AtomicMass({ {0.0429, 113} })),
		VALUE_TUPLE(Sn, 50, element_impl::AtomicMass({ {0.0096, 112}, {0.0066, 114}, {0.0035, 115}, {0.143, 116}, {0.0761, 117}, {0.2403, 118}, {0.0858, 119}, {0.3285, 120}, {0.0472, 122}, {0.0594, 124} })),
		VALUE_TUPLE(Sb, 51, element_impl::AtomicMass({ {0.5736, 121}, {0.4264, 123} })),
		VALUE_TUPLE(Te, 52, element_impl::AtomicMass({ {0.0009, 120}, {0.0255, 122}, {0.0089, 123}, {0.0474, 124}, {0.0707, 125}, {0.1884, 126} })),
		VALUE_TUPLE(I, 53, element_impl::AtomicMass({ {1, 127} })),
		VALUE_TUPLE(Xe, 54, element_impl::AtomicMass({ {0.00089, 126}, {0.0191, 128}, {0.26401, 129}, {0.04071, 130}, {0.21232, 131}, {0.26909, 132}, {0.10436, 134} })),
		VALUE_TUPLE(Cs, 55, element_impl::AtomicMass({ {1, 133} })),
		VALUE_TUPLE(Ba, 56, element_impl::AtomicMass({ {0.001, 132}, {0.0242, 134}, {0.0659, 135}, {0.0785, 136}, {0.1123, 137}, {0.717, 138} })),
		VALUE_TUPLE(La, 57, element_impl::AtomicMass({ {0.99911, 139} })),
		VALUE_TUPLE(Ce, 58, element_impl::AtomicMass({ {0.00185, 136}, {0.00251, 138}, {0.8845, 140}, {0.11114, 142} })),
		VALUE_TUPLE(Pr, 59, element_impl::AtomicMass({ {1, 141} })),
		VALUE_TUPLE(Nd, 60, element_impl::AtomicMass({ {0.272, 142}, {0.122, 143}, {0.083, 145}, {0.172, 146}, {0.057, 148} })),
		VALUE_TUPLE(Sm, 62, element_impl::AtomicMass({ {0.0307, 144}, {0.0738, 150}, {0.2675, 152}, {0.2275, 154} })),
		VALUE_TUPLE(Eu, 63, element_impl::AtomicMass({ {0.522, 151}, {0.478, 153} })),
		VALUE_TUPLE(Gd, 64, element_impl::AtomicMass({ {0.0218, 154}, {0.148, 155}, {0.2047, 156}, {0.1565, 157}, {0.2484, 158}, {0.2186, 160} })),
		VALUE_TUPLE(Tb, 65, element_impl::AtomicMass({ {1, 159} })),
		VALUE_TUPLE(Dy, 66, element_impl::AtomicMass({ {0.00056, 156}, {0.00095, 158}, {0.02329, 160}, {0.18889, 161}, {0.25475, 162}, {0.24896, 163}, {0.2826, 164} })),
		VALUE_TUPLE(Ho, 67, element_impl::AtomicMass({ {1, 165} })),
		VALUE_TUPLE(Er, 68, element_impl::AtomicMass({ {0.00139, 162}, {0.01601, 164}, {0.33503, 166}, {0.22869, 167}, {0.26978, 168}, {0.1491, 170} })),
		VALUE_TUPLE(Tm, 69, element_impl::AtomicMass({ {1, 169} })),
		VALUE_TUPLE(Yb, 70, element_impl::AtomicMass({ {0.00126, 168}, {0.03023, 170}, {0.14216, 171}, {0.21754, 172}, {0.16098, 173}, {0.31896, 174}, {0.12887, 176} })),
		VALUE_TUPLE(Lu, 71, element_impl::AtomicMass({ {0.9741, 175} })),
		VALUE_TUPLE(Hf, 72, element_impl::AtomicMass({ {0.0526, 176}, {0.186, 177}, {0.2728, 178}, {0.1362, 179}, {0.3508, 180} })),
		VALUE_TUPLE(Ta, 73, element_impl::AtomicMass({ {0.999877, 181} })),
		VALUE_TUPLE(W, 74, element_impl::AtomicMass({ {0.265, 182}, {0.3064, 184}, {0.2843, 186} })),
		VALUE_TUPLE(Re, 75, element_impl::AtomicMass({ {0.3707, 185} })),
		VALUE_TUPLE(Os, 76, element_impl::AtomicMass({ {0.0002, 184}, {0.0196, 187}, {0.1324, 188}, {0.1615, 189}, {0.2626, 190}, {0.4078, 192} })),
		VALUE_TUPLE(Ir, 77, element_impl::AtomicMass({ {0.373, 191}, {0.627, 193} })),
		VALUE_TUPLE(Pt, 78, element_impl::AtomicMass({ {0.00782, 192}, {0.32967, 194}, {0.33832, 195}, {0.25242, 196}, {0.07163, 198} })),
		VALUE_TUPLE(Au, 79, element_impl::AtomicMass({ {1, 197} })),
		VALUE_TUPLE(Hg, 80, element_impl::AtomicMass({ {0.00155, 196}, {0.1004, 198}, {0.1694, 199}, {0.2314, 200}, {0.1317, 201}, {0.2974, 202}, {0.0682, 204} })),
		VALUE_TUPLE(Tl, 81, element_impl::AtomicMass({ {0.2952, 203}, {0.7048, 205} })),
		VALUE_TUPLE(Pb, 82, element_impl::AtomicMass({ {0.014, 204}, {0.241, 206}, {0.221, 207}, {0.524, 208} }))
	)

	class ElementException : public std::runtime_error {
	public:
		ElementException(const std::string& message);
	};

	//functions throw ElementException if dont know values for this element
	// or element of enum does not have enumerator, that corresponding to title
	element parseElement(char title);
	element parseElement(const char title[2]);
	element parseElement(const std::string& title);
	element_impl::AtomicMass atomicMass(char title);
	element_impl::AtomicMass atomicMass(const char title[2]);
	element_impl::AtomicMass atomicMass(const std::string& title);
	std::uint8_t atomicNumber(char title);
	std::uint8_t atomicNumber(const char title[2]);
	std::uint8_t atomicNumber(const std::string& title);
}

#endif	// TAHD_ELEMENTS_H
