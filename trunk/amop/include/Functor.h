#ifndef __AMOP_FUNCTOR__HH
#define __AMOP_FUNCTOR__HH

#include "Config.h"
#include "Tuple.h"
#include "MacroRepeat.h"
#include "FastDelegate.h"

namespace amop
{
namespace detail
{

template< typename T>
struct Functor;

#ifdef DETAIL_HAVE_THIS_CALL
template< typename R, typename C >
struct Functor< R (__thiscall C::*)()>
{
	typedef R ReturnType;
	typedef Tuple<> ParameterTypes;
	typedef fastdelegate::FastDelegate0<R> FunctorType;
};

template< typename R, typename C >
struct Functor< R (__thiscall C::*)() const>
{
	typedef R ReturnType;
	typedef Tuple<> ParameterTypes;
	typedef fastdelegate::FastDelegate0<R> FunctorType;
};
#endif 

template< typename R, typename C >
struct Functor< R (DETAIL_CDECL C::*)()>
{
	typedef R ReturnType;
	typedef Tuple<> ParameterTypes;
	typedef fastdelegate::FastDelegate0<R> FunctorType;
};

template< typename R, typename C >
struct Functor< R (DETAIL_CDECL C::*)() const>
{
	typedef R ReturnType;
	typedef Tuple<> ParameterTypes;
	typedef fastdelegate::FastDelegate0<R> FunctorType;
};


//now specialize
#define DETAIL_FUNCTION_BUILD(n)					\
template< typename R, typename C, DETAIL_TPARAMS(n) >		\
struct Functor< R (DETAIL_CALLING_CONVENTION C::*)(DETAIL_ARGS(n))>			\
{												\
	typedef R ReturnType;								\
	typedef Tuple<DETAIL_ARGS(n)> ParameterTypes;	\
	typedef fastdelegate::FastDelegate##n<DETAIL_ARGS(n), R> FunctorType; \
};			\
template< typename R, typename C, DETAIL_TPARAMS(n) >		\
struct Functor< R (DETAIL_CALLING_CONVENTION C::*)(DETAIL_ARGS(n)) const>			\
{												\
	typedef R ReturnType;								\
	typedef Tuple<DETAIL_ARGS(n)> ParameterTypes;	\
	typedef fastdelegate::FastDelegate##n<DETAIL_ARGS(n), R> FunctorType; \
};

#define DETAIL_CALLING_CONVENTION DETAIL_CDECL

DETAIL_FUNCTION_BUILD(1);
DETAIL_FUNCTION_BUILD(2);
DETAIL_FUNCTION_BUILD(3);
DETAIL_FUNCTION_BUILD(4);
DETAIL_FUNCTION_BUILD(5);
DETAIL_FUNCTION_BUILD(6);
DETAIL_FUNCTION_BUILD(7);
DETAIL_FUNCTION_BUILD(8);

#ifdef DETAIL_HAVE_THIS_CALL
#undef DETAIL_CALLING_CONVENTION 
#define DETAIL_CALLING_CONVENTION __thiscall 

DETAIL_FUNCTION_BUILD(1);
DETAIL_FUNCTION_BUILD(2);
DETAIL_FUNCTION_BUILD(3);
DETAIL_FUNCTION_BUILD(4);
DETAIL_FUNCTION_BUILD(5);
DETAIL_FUNCTION_BUILD(6);
DETAIL_FUNCTION_BUILD(7);
DETAIL_FUNCTION_BUILD(8);


#endif

#undef DETAIL_CALLING_CONVENTION 

// FastDelgate only support 8 params.
/*
DETAIL_FUNCTION_BUILD(9);
DETAIL_FUNCTION_BUILD(10);
DETAIL_FUNCTION_BUILD(11);
DETAIL_FUNCTION_BUILD(12);
DETAIL_FUNCTION_BUILD(13);
DETAIL_FUNCTION_BUILD(14);
DETAIL_FUNCTION_BUILD(15);
*/

}
}

#endif //__FUNCTOR__HH
