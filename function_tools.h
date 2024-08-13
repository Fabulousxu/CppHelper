#ifndef _XH_FUNCTION_TOOLS_H_
#define _XH_FUNCTION_TOOLS_H_

#include <functional>
#include "function_traits.h"

namespace xh {
using
	std::function,
	std::invoke_result_t,
	std::forward;

// auto return

struct _auto_return_helper {
	template<class _T>
	operator _T() const { return _T{}; }
};

#define auto_return return _auto_return_helper{};


// getter and setter

template<typename _Ret>
class getter {
	function<_Ret()> _getter;
 public:
	template<typename _F>
	getter(_F &&f) noexcept : _getter(f) {}
	getter(const getter &) = delete;
	getter(getter &&) = delete;
	getter &operator=(const getter &) = delete;
	getter &operator=(getter &&) = delete;
	operator _Ret() const { return _getter(); }
};

template<typename _Arg>
class setter {
	function<void(_Arg)> _setter;
 public:
	template<typename _F>
	setter(_F &&f) noexcept : _setter(f) {}
	setter(const setter &) = delete;
	setter(setter &&) = delete;
	setter &operator=(const setter &) = delete;
	setter &operator=(setter &&) = delete;
	void operator=(_Arg arg) const { _setter(arg); }
};

template<typename _Ret, typename _Arg>
class getter_setter {
	function<_Ret()> _getter;
	function<void(_Arg)> _setter;
 public:
	template<typename _F1, typename _F2>
	getter_setter(_F1 &&f1, _F2 &&f2) noexcept : _getter(f1), _setter(f2) {}
	getter_setter(const getter_setter &) = delete;
	getter_setter(getter_setter &&) = delete;
	getter_setter &operator=(const getter_setter &) = delete;
	getter_setter &operator=(getter_setter &&) = delete;
	operator _Ret() const { return _getter(); }
	void operator=(_Arg arg) const { _setter(arg); }
};

#define get(name, return_type, ...) \
const getter<return_type> name      \
  = [&]() -> return_type __VA_ARGS__ ;

#define set(name, argument_type, argument_name, ...) \
const setter<argument_type> name                     \
  = [&](argument_type argument_name) -> void __VA_ARGS__ ;

#define REMOVE_PARENTHESES(...) __VA_ARGS__

#define getset(name, return_type, get, argument_type, argument_name, set) \
const getter_setter<return_type, argument_type> name                      \
  = { [&]() -> return_type REMOVE_PARENTHESES get,                        \
  		[&](argument_type argument_name) -> void REMOVE_PARENTHESES set };


// to std function

template<typename _T> requires is_callable_v<_T>
inline auto std_function(_T &&func)
{ return function_std_t<_T>(forward<_T>(func)); }


// member function

template<typename>
class member_function;

#define MEMBER_FUNCTION_QUALIFIERS(qualifiers)                           \
template <typename _Ret, typename _Cls, typename... _Args>               \
class member_function<_Ret(_Cls::*)(_Args...)qualifiers> {               \
  _Ret(_Cls::*_member_function)(_Args...)qualifiers;                     \
 public:                                                                 \
  template<typename _F>                                                  \
  member_function(_F &&f) noexcept : _member_function(forward<_F>(f)) {} \
	_Ret operator()(qualifiers _Cls &obj, _Args... args) const             \
	{ return (obj.*_member_function)(args...); }                           \
  _Ret operator()(qualifiers _Cls *obj, _Args... args) const             \
	{ return (obj->*_member_function)(args...); }                          \
};

MEMBER_FUNCTION_QUALIFIERS()
MEMBER_FUNCTION_QUALIFIERS(const)
MEMBER_FUNCTION_QUALIFIERS(volatile)
MEMBER_FUNCTION_QUALIFIERS(const volatile)

#undef MEMBER_FUNCTION_QUALIFIERS

template<typename _T>
member_function(_T) -> member_function<std::remove_cvref_t<_T>>;


// promise

template<typename>
class promise;

template<typename _Ret, typename... _Args>
class promise<_Ret(_Args...)> {
	function<_Ret(_Args...)> _promise;
 public:
	template<typename _T>
	promise(_T &&f) noexcept: _promise(f) {}
	_Ret operator()(_Args &&...args) const
	{ return _promise(forward<_Args>(args)...); }
	template<typename _F>
	promise<function_return_t<_F>(_Args...)> then(_F &&f)  {
		return {[f, this](_Args &&...args)
		{ return f(_promise(forward<_Args>(args)...)); }};
	}
};

template<typename _T>
promise(_T) -> promise<function_traits_t<_T>>;

}; // namespace xh

#endif //_XH_FUNCTION_TOOLS_H_
