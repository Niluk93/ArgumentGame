#pragma once
#include "core/typedefs.h"

#define ENUM_FLAG_OPERATIONS(Enum)\
struct BoolFrom##Enum\
{\
private:\
	Enum underlyingVal;\
public:\
	BoolFrom##Enum (Enum E) : underlyingVal(E) { }\
	_ALWAYS_INLINE_ constexpr operator bool() { return (__underlying_type(Enum))underlyingVal; }\
	_ALWAYS_INLINE_ operator Enum() { return (Enum)(__underlying_type(Enum))underlyingVal;}\
};\
_ALWAYS_INLINE_ BoolFrom##Enum operator|=(Enum &Lhs, Enum Rhs) { return BoolFrom##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs)); }	\
_ALWAYS_INLINE_ BoolFrom##Enum operator&=(Enum &Lhs, Enum Rhs) { return BoolFrom##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs)); }	\
_ALWAYS_INLINE_ BoolFrom##Enum operator^=(Enum &Lhs, Enum Rhs) { return BoolFrom##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs)); }	\
_ALWAYS_INLINE_ BoolFrom##Enum operator|(Enum Lhs, Enum Rhs) { return BoolFrom##Enum((Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ BoolFrom##Enum operator&(Enum Lhs, Enum Rhs) { return BoolFrom##Enum((Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ BoolFrom##Enum operator^(Enum Lhs, Enum Rhs) { return BoolFrom##Enum((Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ BoolFrom##Enum operator~(Enum E) { return BoolFrom##Enum((Enum) ~(__underlying_type(Enum))E); }
