# IL2CPP-Resolver
unity il2cpp game hacking library

# how to use
include il2cpp_resolver.h in your project

# doc
before using il2cpp resolver, call il2cpp::init once!

## how to call a function
`auto result = il2cpp::call_function<[return type]>(il2cpp::get_method("[namespace]", "[class_name]", "[method_name]"), [class_instance], [argument(s)], [method]);`
example:
`yes`
