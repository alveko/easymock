#ifndef EM_HEADER_1
#define EM_HEADER_1

//! simple declarations

void em_void_func_void(void);
void em_void_func_int(int a);
void em_void_func_int_int(int a, int b);
void em_void_func_voidptr(void* p);

int em_int_func_int(int a);
int em_int_func_int_int(int a, int b);
int em_int_func_voidptr(void* p);

//! function pointers

typedef void (*fn_ptr1)(void);
typedef void* (*fn_ptr2)(int, void*);

int em_func_funcptr1(fn_ptr1 fcb1, fn_ptr2 fcb2);
int em_func_funcptr2(fn_ptr1 fcb);
int em_func_funcptr3(void* (*fcb)(int, void*));

//! union

//union UnionX;
//int em_func_union_x(union UnionX u);

union Union1 { int x; char a[4]; };
int em_func_union_1(union Union1 u);
int em_func_union_1_ptr(union Union1* u);

union Union2 { int x; char a[4]; };
typedef union Union2 Union2T;
int em_func_union_2(Union2T u);
int em_func_union_2_ptr(Union2T* u);

//! enum

//enum EnumX;
//int em_func_enum_x(enum EnumX e);

enum Enum1 { Enum1_A, Enum1_B };
int em_func_enum_1(enum Enum1 e);
int em_func_enum_1_ptr(enum Enum1* e);

enum Enum2 { Enum2_A, Enum2_B };
typedef enum Enum2 Enum2T;
int em_func_enum_2(Enum2T e);
int em_func_enum_2_ptr(Enum2T* e);

//! struct parameters

//struct StructX;
//int em_func_struct_x(struct StructX s);

struct Struct1 { int x; };
int em_func_struct_1(struct Struct1* ptr);

struct Struct2 { int x; };
typedef struct Struct2 Struct2;
int em_func_struct_2(Struct2* ptr);

struct Struct3 { int x; };
typedef struct Struct3 Struct3T;
int em_func_struct_3_ptr(Struct3T* ptr);
int em_func_struct_3_ptr_const(const Struct3T* ptr);

struct Struct4 { int x; };
typedef struct Struct4* Struct4Ptr;
int em_func_struct_4_ptr(Struct4Ptr ptr);
int em_func_struct_4_ptr_const(const Struct4Ptr ptr);

struct HiddenStruct1;
int em_func_opaque_1(struct HiddenStruct1* ptr);

struct HiddenStruct2;
typedef struct HiddenStruct2 HiddenStruct2;
int em_func_opaque_2(HiddenStruct2* ptr);

struct HiddenStruct3;
typedef struct HiddenStruct3 HiddenStruct3T;
int em_func_opaque_3_ptr(HiddenStruct3T* ptr);
int em_func_opaque_3_ptr_const(const HiddenStruct3T* ptr);

struct HiddenStruct4;
typedef struct HiddenStruct4* HiddenStruct4Ptr;
int em_func_opaque_4_ptr(HiddenStruct4Ptr ptr);
int em_func_opaque_4_ptr_const(const HiddenStruct4Ptr ptr);

//! typedefed parameters

typedef unsigned char em_uint8_t;
int em_func_uint8(em_uint8_t n);
int em_func_uint8_const(const em_uint8_t n);
int em_func_uint8_ptr(em_uint8_t* n);

typedef em_uint8_t em_bool_t;
int em_func_bool(em_bool_t flag);
int em_func_bool_const(const em_bool_t flag);
int em_func_bool_ptr(em_bool_t* flag);

typedef char* em_string_t;
int em_func_string(em_string_t msg);
int em_func_string_const(const em_string_t msg);
int em_func_string_ptr(em_string_t* msg);

typedef const char* em_conststring_t;
int em_func_conststring(em_conststring_t msg);
int em_func_conststring_const(const em_conststring_t msg);
int em_func_conststring_ptr(em_conststring_t* msg);

typedef unsigned int em_size_t;
int em_func_size(em_size_t size);
int em_func_size_const(const em_size_t size);
int em_func_size_ptr(em_size_t* size);

typedef unsigned long int em_pthread_t;
int em_func_pthread(em_pthread_t tid);
int em_func_pthread_const(const em_pthread_t tid);
int em_func_pthread_ptr(em_pthread_t* tid);

//! extra

#define EMTYPER unsigned short
#define EMTYPE1 int
#define EMTYPE2 char*
#define EMTYPE3 const char*
#define EMTYPE4 char* const

EMTYPER em_typer_func_type1(
    EMTYPE1 param1);
EMTYPER em_typer_func_type12(
    EMTYPE1 param1, EMTYPE2 param2);
EMTYPER em_typer_func_type123(
    EMTYPE1 param1, EMTYPE2 param2, EMTYPE3 param3);
EMTYPER em_typer_func_type1234(
    EMTYPE1 param1, EMTYPE2 param2, EMTYPE3 param3, EMTYPE4 param4);

#endif
