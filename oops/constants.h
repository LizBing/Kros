#ifndef OOPS_CONSTANTPOOL_
#define OOPS_CONSTANTPOOL_

enum {
    CONSTANT_Utf8 = 1,
    CONSTANT_Integer = 3,
    CONSTANT_Float,
    CONSTANT_Long,
    CONSTANT_Double,
    CONSTANT_Class,
    CONSTANT_String,
    CONSTANT_Fieldref,
    CONSTANT_Methodref,
    CONSTANT_InterfaceMethodref,
    CONSTANT_NameAndType,
    CONSTANT_MethodHandle = 15,
    CONSTANT_MethodType,
    CONSTANT_Dynamic,
    CONSTANT_InvokeDynamic,
    CONSTANT_Module,
    CONSTANT_Package
};


#endif
