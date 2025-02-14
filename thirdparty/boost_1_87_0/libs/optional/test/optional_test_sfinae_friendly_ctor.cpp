// Copyright (C) 2014 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/lib/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#include "boost/optional/optional.hpp"

#ifdef BOOST_BORLANDC
#pragma hdrstop
#endif

using boost::optional;

#if (!defined BOOST_OPTIONAL_DETAIL_NO_IS_CONSTRUCTIBLE_TRAIT)

struct X {};
struct Y {};

struct Resource
{
  explicit Resource(const X&) {}
};

static_assert((  boost::is_constructible<Resource, const X&>::value ), "ERROR");
static_assert(( !boost::is_constructible<Resource, const Y&>::value ), "ERROR");

static_assert((  boost::is_constructible<optional<Resource>, const X&>::value ), "ERROR");
static_assert(( !boost::is_constructible<optional<Resource>, const Y&>::value ), "ERROR");

#ifndef BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
static_assert((  boost::is_constructible< optional< optional<int> >, optional<int> >::value ), "ERROR");
static_assert(( !boost::is_constructible< optional<int>, optional< optional<int> > >::value ), "ERROR");

static_assert((  boost::is_constructible< optional< optional<int> >, const optional<int>& >::value ), "ERROR");
static_assert(( !boost::is_constructible< optional<int>, const optional< optional<int> >& >::value ), "ERROR");

static_assert((  boost::is_constructible<optional<Resource>, const optional<X>&>::value ), "ERROR");
static_assert(( !boost::is_constructible<optional<Resource>, const optional<Y>&>::value ), "ERROR");
#endif

#endif

int main() { }
