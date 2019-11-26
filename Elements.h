#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

enum class element {
	C,
	Al,
	Ar,
	Ti,
	Fe,
	Ni,
	Cu,
	Ag,
	Au
};

element convert_to_element(char title)
{
	if (title == 'C') { return element::C; }
}

element convert_to_element(char title[2])
{
		 if (title[0] == 'A' && title[1] == 'l') { return element::Al; }
	else if (title[0] == 'A' && title[1] == 'r') { return element::Ar; }
	else if (title[0] == 'T' && title[1] == 'i') { return element::Ti; }
	else if (title[0] == 'F' && title[1] == 'e') { return element::Fe; }
	else if (title[0] == 'N' && title[1] == 'i') { return element::Ni; }
	else if (title[0] == 'C' && title[1] == 'u') { return element::Cu; }
	else if (title[0] == 'A' && title[1] == 'g') { return element::Ag; }
	else if (title[0] == 'A' && title[1] == 'u') { return element::Au; }
}

int get_atom_weight(element el)
{
		 if (el == element::C)  { return 12; }
	else if (el == element::Al)	{ return 27; }
	else if (el == element::Al) { return 40; }
	else if (el == element::Ti) { return 48; }
	else if (el == element::Fe) { return 56; }
	else if (el == element::Ni) { return 59; }
	else if (el == element::Cu) { return 64; }
	else if (el == element::Ag) { return 108;}
	else if (el == element::Au) { return 197;}
}

int get_atom_weight(char title)
{
	return get_atom_weight(convert_to_element(title));
}

int get_atom_weight(char title[2])
{
	return get_atom_weight(convert_to_element(title));
}

#endif	//TAHD_ELEMENTS_H
