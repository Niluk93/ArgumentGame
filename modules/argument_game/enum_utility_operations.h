#pragma once
#include "core/typedefs.h"

#define ENUM_STRUCT(Enum)																																					\
struct EnumOps##Enum																																						\
{																																											\
private:																																									\
	Enum underlyingVal;																																						\
public:																																										\
	EnumOps##Enum (Enum E) : underlyingVal(E) { }																															\
	EnumOps##Enum (int I) : underlyingVal(static_cast<Enum>(I)) { }																											\
	_ALWAYS_INLINE_ constexpr operator bool() { return (__underlying_type(Enum))underlyingVal; }																			\
	_ALWAYS_INLINE_ constexpr operator Enum() { return (Enum)(__underlying_type(Enum))underlyingVal;}																		\
	_ALWAYS_INLINE_ constexpr operator int() { return static_cast<int>(underlyingVal); }																					\
	_ALWAYS_INLINE_ EnumOps##Enum& operator=(int val) { underlyingVal = static_cast<Enum>(val); return *this; }																\
	_ALWAYS_INLINE_ friend bool operator ==(const EnumOps##Enum& Lhs, const EnumOps##Enum& Rhs)	{ return Lhs.underlyingVal == Rhs.underlyingVal; }							\
};

#define ENUM_FLAGS_true(Enum)																																				\
_ALWAYS_INLINE_ EnumOps##Enum operator|=(Enum &Lhs, Enum Rhs) { return EnumOps##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator&=(Enum &Lhs, Enum Rhs) { return EnumOps##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator^=(Enum &Lhs, Enum Rhs) { return EnumOps##Enum(Lhs = (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator|(Enum Lhs, Enum Rhs) { return EnumOps##Enum((Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs)); }					\
_ALWAYS_INLINE_ EnumOps##Enum operator&(Enum Lhs, Enum Rhs) { return EnumOps##Enum((Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs)); }					\
_ALWAYS_INLINE_ EnumOps##Enum operator^(Enum Lhs, Enum Rhs) { return EnumOps##Enum((Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs)); }					\
_ALWAYS_INLINE_ EnumOps##Enum operator~(Enum E) { return EnumOps##Enum((Enum) ~(__underlying_type(Enum))E); }

#define ENUM_FLAGS_false(Enum)

#define ENUM_UTILITY_OPERATIONS(Enum, IsFlag) \
	ENUM_STRUCT(Enum)                         \
	ENUM_FLAGS_##IsFlag(Enum)

#define SCOPED_ENUM_STRUCT(Scope, Enum)																																										\
struct EnumOps##Enum																																													\
{																																																		\
private:																																																\
	Scope::Enum underlyingVal;																																											\
public:																																																	\
	EnumOps##Enum (Scope::Enum E) : underlyingVal(E) { }																																				\
	EnumOps##Enum (int I) : underlyingVal(static_cast<Scope::Enum>(I)) { }																																\
	_ALWAYS_INLINE_ constexpr operator bool() { return (__underlying_type(Scope::Enum))underlyingVal; }																									\
	_ALWAYS_INLINE_ constexpr operator Scope::Enum() { return (Scope::Enum)(__underlying_type(Scope::Enum))underlyingVal;}																				\
	_ALWAYS_INLINE_ constexpr operator int() { return static_cast<int>(underlyingVal); }																												\
	_ALWAYS_INLINE_ EnumOps##Enum& operator=(int val) { underlyingVal = static_cast<Scope::Enum>(val); return *this; }																					\
	_ALWAYS_INLINE_ friend bool operator ==(const EnumOps##Enum& Lhs, const EnumOps##Enum& Rhs)	{ return Lhs.underlyingVal == Rhs.underlyingVal; }														\
};

#define SCOPED_ENUM_FLAGS_true(Scope,Enum)																																										\
_ALWAYS_INLINE_ EnumOps##Enum operator|=(Scope::Enum &Lhs, Scope::Enum Rhs) { return EnumOps##Enum(Lhs = (Scope::Enum)((__underlying_type(Scope::Enum))Lhs | (__underlying_type(Scope::Enum))Rhs)); }	\
_ALWAYS_INLINE_ EnumOps##Enum operator&=(Scope::Enum &Lhs, Scope::Enum Rhs) { return EnumOps##Enum(Lhs = (Scope::Enum)((__underlying_type(Scope::Enum))Lhs & (__underlying_type(Scope::Enum))Rhs)); }	\
_ALWAYS_INLINE_ EnumOps##Enum operator^=(Scope::Enum &Lhs, Scope::Enum Rhs) { return EnumOps##Enum(Lhs = (Scope::Enum)((__underlying_type(Scope::Enum))Lhs ^ (__underlying_type(Scope::Enum))Rhs)); }	\
_ALWAYS_INLINE_ EnumOps##Enum operator|(Scope::Enum Lhs, Scope::Enum Rhs) { return EnumOps##Enum((Scope::Enum)((__underlying_type(Scope::Enum))Lhs | (__underlying_type(Scope::Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator&(Scope::Enum Lhs, Scope::Enum Rhs) { return EnumOps##Enum((Scope::Enum)((__underlying_type(Scope::Enum))Lhs & (__underlying_type(Scope::Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator^(Scope::Enum Lhs, Scope::Enum Rhs) { return EnumOps##Enum((Scope::Enum)((__underlying_type(Scope::Enum))Lhs ^ (__underlying_type(Scope::Enum))Rhs)); }			\
_ALWAYS_INLINE_ EnumOps##Enum operator~(Scope::Enum E) { return EnumOps##Enum((Scope::Enum) ~(__underlying_type(Scope::Enum))E); }																		\

#define SCOPED_ENUM_FLAGS_false(Scope, Enum)

#define SCOPED_ENUM_UTILITY_OPERATIONS(Scope, Enum, IsFlag) \
SCOPED_ENUM_STRUCT(Scope, Enum) \
SCOPED_ENUM_FLAGS_##IsFlag(Scope, Enum)
