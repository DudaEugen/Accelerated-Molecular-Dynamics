#ifndef TAHD_ELEMENT_ENUMERATION_MACROS
#include "elements_macros.h"

/*Everyone element is corresponding to number (first number) that equal to atomic number of this element. 
Second number is atomic mass of element*/
ELEMENT_ENUMERATION(element)
CHEM_ELEMENT(C, 6, 12)
CHEM_ELEMENT(N, 7, 14)
CHEM_ELEMENT(O, 8, 16)
CHEM_ELEMENT(F, 9, 19)
CHEM_ELEMENT(Na, 11, 23)
CHEM_ELEMENT(Mg, 12, 24)
CHEM_ELEMENT(Al, 13, 27)
CHEM_ELEMENT(Si, 14, 28)
CHEM_ELEMENT(Ar, 18, 40)
CHEM_ELEMENT(Ti, 22, 48)
CHEM_ELEMENT(Fe, 26, 56)
CHEM_ELEMENT(Ni, 28, 59)
CHEM_ELEMENT(Cu, 29, 64)
CHEM_ELEMENT(Ag, 47, 108)
CHEM_ELEMENT(Au, 79, 197)
ELEMENT_ENUMERATION_CLOSE

#undef SMART_ENUMERATION
#undef ADD_ELEMENT
#undef SMART_ENUMERATION_CLOSE
#endif	// TAHD_ELEMENTS_H
