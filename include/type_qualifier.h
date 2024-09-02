// C++20 type_qualifier.h
// Author: xupeigong@sjtu.edu.cn
// Last Updated: 2024-09-01

#ifndef _XH_TYPE_QUALIFIER_H_
#define _XH_TYPE_QUALIFIER_H_

#include <type_traits>

using std::bool_constant;
using std::integral_constant;
using std::type_identity;

namespace xh {

// std

template <class T>
using is_const = std::is_const<T>;
template <class T>
using is_volatile = std::is_volatile<T>;
template <class T>
using is_reference = std::is_reference<T>;
template <class T>
using is_lvalue_reference = std::is_lvalue_reference<T>;
template <class T>
using is_rvalue_reference = std::is_rvalue_reference<T>;
template <class T>
using is_ref = std::is_reference<T>;
template <class T>
using is_lref = std::is_lvalue_reference<T>;
template <class T>
using is_rref = std::is_rvalue_reference<T>;
template <class T>
using add_const = std::add_const<T>;
template <class T>
using add_volatile = std::add_volatile<T>;
template <class T>
using add_cv = std::add_cv<T>;
template <class T>
using add_lvalue_reference = std::add_lvalue_reference<T>;
template <class T>
using add_rvalue_reference = std::add_rvalue_reference<T>;
template <class T>
using add_lref = std::add_lvalue_reference<T>;
template <class T>
using add_rref = std::add_rvalue_reference<T>;
template <class T>
using remove_const = std::remove_const<T>;
template <class T>
using remove_volatile = std::remove_volatile<T>;
template <class T>
using remove_cv = std::remove_cv<T>;
template <class T>
using remove_reference = std::remove_reference<T>;
template <class T>
using remove_cvref = std::remove_cvref<T>;
template <class T>
using remove_ref = std::remove_reference<T>;
template <class T>
inline constexpr bool is_const_v = std::is_const_v<T>;
template <class T>
inline constexpr bool is_volatile_v = std::is_volatile_v<T>;
template <class T>
inline constexpr bool is_reference_v = std::is_reference_v<T>;
template <class T>
inline constexpr bool is_lvalue_reference_v = std::is_lvalue_reference_v<T>;
template <class T>
inline constexpr bool is_rvalue_reference_v = std::is_rvalue_reference_v<T>;
template <class T>
inline constexpr bool is_ref_v = std::is_reference_v<T>;
template <class T>
inline constexpr bool is_lref_v = std::is_lvalue_reference_v<T>;
template <class T>
inline constexpr bool is_rref_v = std::is_rvalue_reference_v<T>;
template <class T>
using add_const_t = std::add_const_t<T>;
template <class T>
using add_volatile_t = std::add_volatile_t<T>;
template <class T>
using add_cv_t = std::add_cv_t<T>;
template <class T>
using add_lvalue_reference_t = std::add_lvalue_reference_t<T>;
template <class T>
using add_rvalue_reference_t = std::add_rvalue_reference_t<T>;
template <class T>
using add_lref_t = std::add_lvalue_reference_t<T>;
template <class T>
using add_rref_t = std::add_rvalue_reference_t<T>;
template <class T>
using remove_const_t = std::remove_const_t<T>;
template <class T>
using remove_volatile_t = std::remove_volatile_t<T>;
template <class T>
using remove_cv_t = std::remove_cv_t<T>;
template <class T>
using remove_reference_t = std::remove_reference_t<T>;
template <class T>
using remove_cvref_t = std::remove_cvref_t<T>;
template <class T>
using remove_ref_t = std::remove_reference_t<T>;


// type qualifier

struct type_qualifier {
  static constexpr int          value = 0x0001;
  static constexpr int    const_value = 0x0002;
  static constexpr int volatile_value = 0x0004;
  static constexpr int       cv_value = 0x0008;
  static constexpr int           lref = 0x0010;
  static constexpr int     const_lref = 0x0020;
  static constexpr int  volatile_lref = 0x0040;
  static constexpr int        cv_lref = 0x0080;
  static constexpr int           rref = 0x0100;
  static constexpr int     const_rref = 0x0200;
  static constexpr int  volatile_rref = 0x0400;
  static constexpr int        cv_rref = 0x0800;

  static constexpr int    const_type = const_value | cv_value;
  static constexpr int volatile_type = volatile_value | cv_value;
  static constexpr int       cv_type = const_type | volatile_type;
  static constexpr int value_type = value | cv_type;
  static constexpr int  lref_type = lref | const_lref | volatile_lref | cv_lref;
  static constexpr int  rref_type = rref | const_rref | volatile_rref | cv_rref;
  static constexpr int   ref_type = lref_type | rref_type;
  static constexpr int cvref_type = cv_type | ref_type;
};

using type_qualifier_t = int;


// type qualifier traits

template <type_qualifier_t value>
using type_qualifier_constant = integral_constant<type_qualifier_t, value>;

template <class T>
struct type_qualifier_traits
  : type_qualifier_constant<type_qualifier::value> {};
template <class T>
struct type_qualifier_traits<const T>
  : type_qualifier_constant<type_qualifier::const_value> {};
template <class T>
struct type_qualifier_traits<volatile T>
  : type_qualifier_constant<type_qualifier::volatile_value> {};
template <class T>
struct type_qualifier_traits<const volatile T>
  : type_qualifier_constant<type_qualifier::cv_value> {};
template <class T>
struct type_qualifier_traits<T &>
  : type_qualifier_constant<type_qualifier::lref> {};
template <class T>
struct type_qualifier_traits<const T &>
  : type_qualifier_constant<type_qualifier::const_lref> {};
template <class T>
struct type_qualifier_traits<volatile T &>
  : type_qualifier_constant<type_qualifier::volatile_lref> {};
template <class T>
struct type_qualifier_traits<const volatile T &>
  : type_qualifier_constant<type_qualifier::cv_lref> {};
template <class T>
struct type_qualifier_traits<T &&>
  : type_qualifier_constant<type_qualifier::rref> {};
template <class T>
struct type_qualifier_traits<const T &&>
  : type_qualifier_constant<type_qualifier::const_rref> {};
template <class T>
struct type_qualifier_traits<volatile T &&>
  : type_qualifier_constant<type_qualifier::volatile_rref> {};
template <class T>
struct type_qualifier_traits<const volatile T &&>
  : type_qualifier_constant<type_qualifier::cv_rref> {};

template <class T>
inline constexpr type_qualifier_t type_qualifier_traits_v =
  type_qualifier_traits<T>::value;


// type qualifier check

template <class T, type_qualifier_t Set>
using is_type_qualifier = bool_constant<type_qualifier_traits_v<T> & Set>;

template <class T, type_qualifier_t Set>
inline constexpr bool is_type_qualifier_v = is_type_qualifier<T, Set>::value;


// add type qualifier

template <class T, type_qualifier_t Q>
struct add_type_qualifier {};
template <class T>
struct add_type_qualifier<T, type_qualifier::value>
  : type_identity<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::const_value>
  : add_const<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::volatile_value>
  : add_volatile<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::cv_value>
  : add_cv<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::lref>
  : add_lref<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::const_lref>
  : add_lref<add_const_t<T>> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::volatile_lref>
  : add_lref<add_volatile_t<T>> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::cv_lref>
  : add_lref<add_cv_t<T>> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::rref>
  : add_rref<T> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::const_rref>
  : add_rref<add_const_t<T>> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::volatile_rref>
  : add_rref<add_volatile_t<T>> {};
template <class T>
struct add_type_qualifier<T, type_qualifier::cv_rref>
  : add_rref<add_cv_t<T>> {};

template <class T, type_qualifier_t Q>
using add_type_qualifier_t = add_type_qualifier<T, Q>::type;


// reset type qualifier

template <class T, type_qualifier_t Q>
using reset_type_qualifier = add_type_qualifier<remove_cvref_t<T>, Q>;

template <class T, type_qualifier_t Q>
using reset_type_qualifier_t = reset_type_qualifier<T, Q>::type;

// remove type qualifier

template <class T, type_qualifier_t Q>
struct remove_type_qualifier {};
template <class T>
struct remove_type_qualifier<T, type_qualifier::const_type>
  : remove_const<T> {};
template <class T>
struct remove_type_qualifier<T, type_qualifier::volatile_type>
  : remove_volatile<T> {};
template <class T>
struct remove_type_qualifier<T, type_qualifier::cv_type>
  : remove_cv<T> {};
template <class T>
struct remove_type_qualifier<T, type_qualifier::ref_type>
  : remove_ref<T> {};
template <class T>
struct remove_type_qualifier<T, type_qualifier::cvref_type>
  : remove_cvref<T> {};

template <class T, type_qualifier_t Q>
using remove_type_qualifier_t = remove_type_qualifier<T, Q>::type;

// copy type qualifier

template <class From, class To,
  type_qualifier_t Set = type_qualifier::cvref_type>
using copy_add_type_qualifier =
  add_type_qualifier<To, type_qualifier_traits_v<From> & Set>;

template <class From, class To,
  type_qualifier_t Set = type_qualifier::cvref_type>
using copy_reset_type_qualifier =
  reset_type_qualifier<To, type_qualifier_traits_v<From> & Set>;

template <class From, class To,
  type_qualifier_t Set = type_qualifier::cvref_type>
using copy_add_type_qualifier_t =
  copy_add_type_qualifier<From, To, Set>::type;

template <class From, class To,
  type_qualifier_t Set = type_qualifier::cvref_type>
using copy_reset_type_qualifier_t =
  copy_reset_type_qualifier<From, To, Set>::type;

}  // namespace xh

#endif  // !_XH_TYPE_QUALIFIER_H_
