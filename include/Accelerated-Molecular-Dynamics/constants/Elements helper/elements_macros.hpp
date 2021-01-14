#ifndef TAHD_ELEMENT_ENUMERATION_MACROS
	#ifdef ENUM_CREATE
		#define ELEMENT_ENUMERATION(x) enum class x {
		#define CHEM_ELEMENT(x, y) x = y,
		#define ELEMENT_ENUMERATION_CLOSE };
	#else
		#ifdef CONVERT_TO_STRING
			#define ELEMENT_ENUMERATION(x)					std::string to_string(const element e)								\
															{																	\
																switch(e)														\
																{
			#define CHEM_ELEMENT(x, y)								case element::x:											\
																		return #x;
			#define ELEMENT_ENUMERATION_CLOSE					}																\
																throw ElementException("Failed convert element to string");		\
															}
		#else
			#ifdef PARSE_ELEMENT
				#define ELEMENT_ENUMERATION(x)				element parse(const std::string& s)									\
															{																			
				#define CHEM_ELEMENT(x, y)						if (s==#x)														\
																	return element::x;
				#define ELEMENT_ENUMERATION_CLOSE				throw ElementException("Failed parse " + s + " to element");	\
															}
				#else
					#ifdef ALL_ELEMENTS
						#define ELEMENT_ENUMERATION(x)		std::set<element> get_all()											\
															{																	\
																std::set<element> result;
						#define CHEM_ELEMENT(x, y)				result.insert(element::x);
						#define ELEMENT_ENUMERATION_CLOSE		return result;													\
															}
				#endif
			#endif
		#endif
	#endif
#endif	// TAHD_ELEMENT_ENUMERATION_MACROS
