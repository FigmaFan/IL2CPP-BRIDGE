#pragma once

#include <Windows.h>
#include <string>

#define ASSEMBLY_FILE "GameAssembly.dll"
#define ASSEMBLY_NAME "Assembly-CSharp"

#define ASSERT(x) { MessageBoxA(NULL, x, "il2cpp error", NULL); exit(1); }

namespace il2cpp
{
	namespace _internal
	{
		struct il2cppImage
		{
			const char* m_pName;
			const char* m_oNameNoExt;
		};

		struct il2cppAssemblyName
		{
			const char* m_pName;
			const char* m_pCulture;
			const char* m_pHash;
			const char* m_pPublicKey;
			unsigned int m_uHash;
			int m_iHashLength;
			unsigned int m_uFlags;
			int m_iMajor;
			int m_iMinor;
			int m_iBuild;
			int m_bRevision;
			unsigned char m_uPublicKeyToken[8];
		};

		struct il2cppAssembly
		{
			il2cppImage* m_pImage;
			unsigned int m_uToken;
			int m_ReferencedAssemblyStart;
			int m_ReferencedAssemblyCount;
			il2cppAssemblyName m_aName;
		};

		struct il2cppClass
		{
			void* m_pImage;
			void* m_pGC;
			const char* m_pName;
			const char* m_pNamespace;
			void* m_pValue;
			void* m_pArgs;
			il2cppClass* m_pElementClass;
			il2cppClass* m_pCastClass;
			il2cppClass* m_pDeclareClass;
			il2cppClass* m_pParentClass;
			void* m_pGenericClass;
			void* m_pTypeDefinition;
			void* m_pInteropData;
			void* m_pFields;
			void* m_pEvents;
			void* m_pProperties;
			void** m_pMethods;
			il2cppClass** m_pNestedTypes;
			il2cppClass** m_ImplementedInterfaces;
			void* m_pInterfaceOffsets;
			void* m_pStaticFields;
			void* m_pRGCTX;
		};

		struct il2cppObject
		{
			il2cppClass* m_pClass = nullptr;
			void* m_pMonitor = nullptr;
		};

		struct il2cppType
		{
			union
			{
				void* m_pDummy;
				unsigned int m_uClassIndex;
				il2cppType* m_pType;
				void* m_pArray;
				unsigned int m_uGenericParameterIndex;
				void* m_pGenericClass;
			};
			unsigned int m_uAttributes : 16;
			unsigned int m_uType : 8;
			unsigned int m_uMods : 6;
			unsigned int m_uByref : 1;
			unsigned int m_uPinned : 1;
		};

		struct il2cppFieldInfo
		{
			const char* m_pName;
			il2cppType* m_pType;
			il2cppClass* m_pParentClass;
			int m_iOffset;
			int m_iAttributeIndex;
			unsigned int m_uToken;
		};

		struct il2cppParameterInfo
		{
			const char* m_pName;
			int m_iPosition;
			unsigned int m_uToken;
			il2cppType* m_pParameterType;
		};

		struct il2cppMethodInfo
		{
			void* m_pMethodPointer;
			void* m_pInvokerMethod;
			const char* m_pName;
			il2cppClass* m_pClass;
			il2cppType* m_pReturnType;
			il2cppParameterInfo* m_pParameters;

			union
			{
				void* m_pRGCTX;
				void* m_pMethodDefinition;
			};

			union
			{
				void* m_pGenericMethod;
				void* m_pGenericContainer;
			};

			unsigned int m_uToken;
			unsigned short m_uFlags;
			unsigned short m_uFlags2;
			unsigned short m_uSlot;
			unsigned char m_uArgsCount;
			unsigned char m_uGeneric : 1;
			unsigned char m_uInflated : 1;
			unsigned char m_uWrapperType : 1;
			unsigned char m_uMarshaledFromNative : 1;
		};

		struct il2cppPropertyInfo
		{
			il2cppClass* m_pParentClass;
			const char* m_pName;
			il2cppMethodInfo* m_pGet;
			il2cppMethodInfo* m_pSet;
			unsigned int m_uAttributes;
			unsigned int m_uToken;
		};

		struct il2cppArrayBounds
		{
			unsigned long long m_uLength;
			int m_iLowerBound;
		};

		struct Il2CppRuntimeInterfaceOffsetPair
		{
			il2cppClass* interfaceType;
			int32_t offset;
		};

		struct Il2CppClass_1
		{
			void* image;
			void* gc_desc;
			const char* name;
			const char* namespaze;
			il2cppType byval_arg;
			il2cppType this_arg;
			il2cppClass* element_class;
			il2cppClass* castClass;
			il2cppClass* declaringType;
			il2cppClass* parent;
			void* generic_class;
			void* typeMetadataHandle;
			void* interopData;
			il2cppClass* klass;
			void* fields;
			void* events;
			void* properties;
			void* methods;
			il2cppClass** nestedTypes;
			il2cppClass** implementedInterfaces;
			Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
		};

		struct Il2CppClass_2
		{
			il2cppClass** typeHierarchy;
			void* unity_user_data;
			UINT32 initializationExceptionGCHandle;
			UINT32 cctor_started;
			UINT32 cctor_finished;
			size_t cctor_thread;
			void* genericContainerHandle;
			UINT32 instance_size;
			UINT32 actualSize;
			UINT32 element_size;
			INT32 native_size;
			UINT32 static_fields_size;
			UINT32 thread_static_fields_size;
			INT32 thread_static_fields_offset;
			UINT32 flags;
			UINT32 token;
			UINT16 method_count;
			UINT16 property_count;
			UINT16 field_count;
			UINT16 event_count;
			UINT16 nested_type_count;
			UINT16 vtable_count;
			UINT16 interfaces_count;
			UINT16 interface_offsets_count;
			UINT8 typeHierarchyDepth;
			UINT8 genericRecursionDepth;
			UINT8 rank;
			UINT8 minimumAlignment;
			UINT8 naturalAligment;
			UINT8 packingSize;
			UINT8 bitflags1;
			UINT8 bitflags2;
		};

		typedef void(*Il2CppMethodPointer)();
		struct VirtualInvokeData
		{
			Il2CppMethodPointer methodPtr;
			const il2cppMethodInfo* method;
		};

		struct System_String_VTable 
		{
			VirtualInvokeData _0_Equals;
			VirtualInvokeData _1_Finalize;
			VirtualInvokeData _2_GetHashCode;
			VirtualInvokeData _3_ToString;
			VirtualInvokeData _4_CompareTo;
			VirtualInvokeData _5_System_Collections_IEnumerable_GetEnumerator;
			VirtualInvokeData _6_System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
			VirtualInvokeData _7_CompareTo;
			VirtualInvokeData _8_Equals;
			VirtualInvokeData _9_GetTypeCode;
			VirtualInvokeData _10_System_IConvertible_ToBoolean;
			VirtualInvokeData _11_System_IConvertible_ToChar;
			VirtualInvokeData _12_System_IConvertible_ToSByte;
			VirtualInvokeData _13_System_IConvertible_ToByte;
			VirtualInvokeData _14_System_IConvertible_ToInt16;
			VirtualInvokeData _15_System_IConvertible_ToUInt16;
			VirtualInvokeData _16_System_IConvertible_ToInt32;
			VirtualInvokeData _17_System_IConvertible_ToUInt32;
			VirtualInvokeData _18_System_IConvertible_ToInt64;
			VirtualInvokeData _19_System_IConvertible_ToUInt64;
			VirtualInvokeData _20_System_IConvertible_ToSingle;
			VirtualInvokeData _21_System_IConvertible_ToDouble;
			VirtualInvokeData _22_System_IConvertible_ToDecimal;
			VirtualInvokeData _23_System_IConvertible_ToDateTime;
			VirtualInvokeData _24_ToString;
			VirtualInvokeData _25_System_IConvertible_ToType;
			VirtualInvokeData _26_Clone;
		};

		struct System_String_c 
		{
			Il2CppClass_1 _1;
			struct System_String_StaticFields* static_fields;
			void* rgctx_data;
			Il2CppClass_2 _2;
			System_String_VTable vtable;
		};

		struct __declspec(align(8)) System_String_Fields 
		{
			UINT32 _stringLength;
			UINT16 _firstChar;
		};

		struct System_String_o
		{
			System_String_c* klass;
			void* monitor;
			System_String_Fields fields;
		};
	}

	static HMODULE game_assembly = GetModuleHandleA(ASSEMBLY_FILE);
	_internal::il2cppAssembly* p_assembly = nullptr;

	template <class T>
	T resolve_export(const char* p_name)
	{
		return reinterpret_cast<T>(GetProcAddress((HMODULE)game_assembly, p_name));
	}

	auto resolve_call = resolve_export<void* (__fastcall*)(const char*)>("il2cpp_resolve_icall");
	auto get_domain = resolve_export<void* (__fastcall*)(void)>("il2cpp_domain_get");
	auto thread_attach = resolve_export<void* (__fastcall*)(void*)>("il2cpp_thread_attach");
	auto get_assemblies = resolve_export<_internal::il2cppAssembly** (__fastcall*)(void*, size_t*)>("il2cpp_domain_get_assemblies");
	auto class_from_name = resolve_export<_internal::il2cppClass* (__fastcall*)(_internal::il2cppImage*, const char*, const char*)>("il2cpp_class_from_name");
	auto method_from_name = resolve_export<_internal::il2cppMethodInfo* (__fastcall*)(_internal::il2cppClass*, const char*, int)>("il2cpp_class_get_method_from_name");
	auto field_from_name = resolve_export<_internal::il2cppFieldInfo* (__fastcall*)(_internal::il2cppClass*, const char*)>("il2cpp_class_get_field_from_name");
	auto static_field_get_value = resolve_export<void (__fastcall*)(_internal::il2cppFieldInfo*, void*)>("il2cpp_field_static_get_value");
	auto static_field_set_value = resolve_export<void (__fastcall*)(_internal::il2cppFieldInfo*, void*)>("il2cpp_field_static_set_value");
	auto create_new_string = resolve_export<_internal::System_String_o* (__fastcall*)(const char*)>("il2cpp_string_new");
	auto field_set_value = resolve_export<void (__fastcall*)(void*, _internal::il2cppFieldInfo*, void*)>("il2cpp_field_set_value");
	auto field_get_value = resolve_export<void (__fastcall*)(void*, _internal::il2cppFieldInfo*, void*)>("il2cpp_field_get_value");

	template <typename ret, typename... _args>
	ret call_function(_internal::il2cppMethodInfo* p_method, _args... args)
	{
		typedef ret(*func)(_args...);
		func fn = (func)((void*)p_method->m_pMethodPointer);
		return fn(args...);
	}

	_internal::il2cppClass* find_class(const char* p_namespace, const char* p_class_name)
	{
		if (!p_namespace || !p_class_name)
			return nullptr;
		return class_from_name(p_assembly->m_pImage, p_namespace, p_class_name);
	}

	_internal::il2cppMethodInfo* get_fn_ptr(_internal::il2cppClass* p_class, const char* p_method, int args_count = 0)
	{
		return method_from_name(p_class, p_method, args_count);
	}

	_internal::il2cppMethodInfo* get_method(const char* p_namespace, const char* p_class_name, const char* p_method)
	{
		if (!p_namespace || !p_class_name || !p_method) {
			return nullptr;
		}

		auto p_class = find_class(p_namespace, p_class_name);

		for (int i = 0; i < 16; i++)
		{
			auto p_info = method_from_name(p_class, p_method, i);

			if (!p_info)
				continue;

			return p_info;
		}

		return nullptr;
	}

	std::string to_string(_internal::System_String_o* p_sys_str)
	{
		if (!p_sys_str)
			return "NULL";
		else
		{
			auto w_str = std::wstring((wchar_t*)(&p_sys_str->fields._firstChar));
			return std::string(w_str.begin(), w_str.end());
		}
	}

	template <class type>
	type get_object_field_value(void* p_instance, const char* p_namespace, const char* p_class_name, const char* p_field_name)
	{
		if (!p_instance || !p_namespace || !p_class_name || !p_field_name)
			return NULL;

		const auto p_class = find_class(p_namespace, p_class_name);
		if (!p_class)
			return NULL;
		const auto p_field = field_from_name(p_class, p_field_name);
		if (!p_field)
			return NULL;

		type buffer;
		field_get_value(p_instance, p_field, &buffer);
		return buffer;
	}

	template <class type>
	bool set_object_field_value(void* p_instance, const char* p_namespace, const char* p_class_name, const char* p_field_name, type value)
	{
		if (!p_instance || !p_namespace || !p_class_name || !p_field_name)
			return false;

		const auto p_class = find_class(p_namespace, p_class_name);
		if (!p_class)
			return false;

		const auto p_field = field_from_name(p_class, p_field_name);
		if (!p_field)
			return false;

		field_set_value(p_instance, p_field, &value);
		return true;
	}

	template <class type>
	type get_static_field_value(_internal::il2cppClass* p_class, const char* p_field_name)
	{
		auto field = field_from_name(p_class, p_field_name);

		type buffer;
		static_field_get_value(field, &buffer);
		return buffer;
	}

	template <class type>
	void set_static_field_value(_internal::il2cppClass* p_class, const char* p_field_name, type val)
	{
		auto p_field = field_from_name(p_class, p_field_name);

		static_field_set_value(p_field, &val);
	}

	int get_field_offset(const char* p_namespace, const char* p_class_name, const char* p_field_name)
	{
		if (!p_namespace || !p_class_name || !p_field_name)
			return 0;

		auto p_class = find_class(p_namespace, p_class_name);
		if (p_class != NULL) {
			auto p_field = field_from_name(p_class, p_field_name);
			if (p_field != NULL)
				return p_field->m_iOffset;
		}
		return 0;
	}

	bool init()
	{
		if (!game_assembly)
		{
			ASSERT("failed to get GameAssembly.dll.")
		}
		if (!resolve_call)
		{
			ASSERT("failed to get resolve call.")
		}
		if (!get_domain)
		{
			ASSERT("failed to get get domain.")
		}
		if (!thread_attach)
		{
			ASSERT("failed to get thread attach")
		}

		size_t assembly_count = 0;
		auto pp_assemblies = get_assemblies(get_domain(), &assembly_count);
		for (int i = 0; i < assembly_count; i++)
		{
			if (std::string(pp_assemblies[i]->m_aName.m_pName) == ASSEMBLY_NAME)
				p_assembly = pp_assemblies[i];
		}

		if (!p_assembly)
		{
			ASSERT("failed to find assembly.")
		}

		return true;
	}
}
