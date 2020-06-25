#ifndef TAHD_ELEMENT_ENUMERATION_MACROS
	#ifdef ENUM_CREATE
		#define ELEMENT_ENUMERATION(x) enum class x {
		#define CHEM_ELEMENT(x, y, z) x = y,
		#define ELEMENT_ENUMERATION_CLOSE };
	#else
		#ifdef GET_MASS
		#define ELEMENT_ENUMERATION(x)					int chem_element::get_atomic_mass(const element e)										\
														{																						\
															switch(e)																			\
															{
		#define CHEM_ELEMENT(x, y, z)							case element::x:																\
																	return z;
		#define ELEMENT_ENUMERATION_CLOSE					}																					\
															throw ElementException("Atomic mass of element not found");							\
														}
		#else
			#ifdef CONVERT_TO_STRING
			#define ELEMENT_ENUMERATION(x)				std::string chem_element::to_string(const element e)									\
														{																						\
															switch(e)																			\
															{
			#define CHEM_ELEMENT(x, y, z)						case element::x:																\
																	return #x;
			#define ELEMENT_ENUMERATION_CLOSE				}																					\
															throw ElementException("Failed convert element to string");							\
														}
			#else
				#ifdef PARSE_ELEMENT
				#define ELEMENT_ENUMERATION(x)			element chem_element::parse(const std::string& s)										\
														{																			
				#define CHEM_ELEMENT(x, y, z)				if (s==#x)																			\
																return element::x;
				#define ELEMENT_ENUMERATION_CLOSE			throw ElementException("Failed parse " + s + " to element");						\
														}
				#else
					#ifdef ALL_ELEMENTS
					#define ELEMENT_ENUMERATION(x)		std::vector<element> chem_element::get_all()											\
														{																						\
															std::vector<element> result;
					#define CHEM_ELEMENT(x, y, z)			result.push_back(element::x);
					#define ELEMENT_ENUMERATION_CLOSE		return result;																		\
														}
				#endif
			#endif
		#endif
		#endif
	#endif
#endif	// TAHD_ELEMENT_ENUMERATION_MACROS
