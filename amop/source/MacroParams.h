#ifndef __MACROPARAMS_HH
#define __MACROPARAMS_HH

#include "MacroRepeat.h"

#define DETAIL_TPARAM(n,t) typename t##n, 
#define DETAIL_TPARAM_END(n,t) typename t##n

#define DETAIL_TPARAM_INC(n,t) DETAIL_APPEND(typename t, DETAIL_INC(n)), 
#define DETAIL_TPARAM_END_INC(n,t) DETAIL_APPEND(typename t, DETAIL_INC(n))

#define DETAIL_TPARAM_DEF(n, p) typename T##n = p, 
#define DETAIL_TPARAM_DEF_END(n, p) typename T##n = p

#define DETAIL_TPARAMS(n) DETAIL_REPEAT(n, DETAIL_TPARAM, DETAIL_TPARAM_END, T)
#define DETAIL_TPARAMS_INC(n) DETAIL_REPEAT(n, DETAIL_TPARAM_INC, DETAIL_TPARAM_END_INC, T) 
#define DETAIL_TPARAMS_DEF(n, def) DETAIL_REPEAT(n, DETAIL_TPARAM_DEF, DETAIL_TPARAM_DEF_END, def)

#define DETAIL_ARG(n,t) t##n, 
#define DETAIL_ARG_END(n,t) t##n
#define DETAIL_ARG_S(n,t) DETAIL_APPEND(t, DETAIL_CNTINC_##n),
#define DETAIL_ARG_S_END(n,t) DETAIL_APPEND(t, DETAIL_CNTINC_##n)

#define DETAIL_ARGS(n) DETAIL_REPEAT(n, DETAIL_ARG, DETAIL_ARG_END, T)
#define DETAIL_ARGS_S(n) DETAIL_REPEAT(n, DETAIL_ARG_S, DETAIL_ARG_S_END, T)

#define DETAIL_TYPEDEF(n, t) typedef t##n type##n;
#define DETAIL_TYPEDEF_END(n, t) typedef t##n type##n;
#define DETAIL_TYPEDEFS(n) DETAIL_REPEAT(n, DETAIL_TYPEDEF, DETAIL_TYPEDEF_END, T)

#define DETAIL_LIST_ITEM(n, t) t,
#define DETAIL_LIST_ITEM_END(n, t) t
#define DETAIL_LIST_ITEMS(n, t) DETAIL_REPEAT(n,DETAIL_LIST_ITEM,DETAIL_LIST_ITEM_END,t)

#define DETAIL_FUNC_PARAM(n,t) T##n t##n, 
#define DETAIL_FUNC_PARAM_END(n,t) T##n t##n
#define DETAIL_FUNC_PARAMS(n, p) DETAIL_REPEAT(n, DETAIL_FUNC_PARAM, DETAIL_FUNC_PARAM_END, p)

#define DETAIL_ENUM_ITEMS(n, t) DETAIL_REPEAT(n,DETAIL_ARG,DETAIL_ARG_END,t)

#endif //__MACROPARAMS_HH
