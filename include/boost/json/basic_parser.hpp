//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/json
//

#ifndef BOOST_JSON_BASIC_PARSER_HPP
#define BOOST_JSON_BASIC_PARSER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/error.hpp>
#include <boost/json/detail/basic_parser.hpp>
#include <boost/json/detail/number.hpp>
#include <boost/json/detail/string.hpp>
#include <string>
#include <vector>
#include <stdint.h>

namespace boost {
namespace json {

/** A parser for serialized JSON
*/
class basic_parser
#ifndef GENERATING_DOCUMENTATION
    : private detail::parser_base
#endif
{
    enum class state : char;

    detail::number_parser iep_;
    unsigned top_ = 0;
    long u0_;
    unsigned short u_;
    bool is_key_;

public:
    virtual
    ~basic_parser()
    {
    }

    /// Returns `true` if the parser has completed without error
    BOOST_JSON_DECL
    bool
    is_done() const noexcept;

    /** Reset the state, to parse a new document.
    */
    BOOST_JSON_DECL
    void
    reset();

    BOOST_JSON_DECL
    std::size_t
    write_some(
        char const* data,
        std::size_t size,
        error_code& ec);

    BOOST_JSON_DECL
    std::size_t
    write(
        char const* data,
        std::size_t size,
        error_code& ec);

    BOOST_JSON_DECL
    void
    write_eof(error_code& ec);

protected:
    struct stack
    {
        void* base;
        unsigned capacity;
    };

    class stack_impl;

    /// Constructor (default)
    BOOST_JSON_DECL
    basic_parser();

    virtual
    void
    on_stack_info(
        stack& s) noexcept = 0;

    virtual
    void
    on_stack_grow(
        stack& s,
        unsigned capacity,
        error_code& ec) = 0;

    virtual
    void
    on_document_begin(
        error_code& ec) = 0;

    virtual
    void
    on_object_begin(
        error_code& ec) = 0;

    virtual
    void
    on_object_end(
        error_code& ec) = 0;

    virtual
    void
    on_array_begin(
        error_code& ec) = 0;

    virtual
    void
    on_array_end(
        error_code& ec) = 0;

    virtual
    void
    on_key_data(
        string_view s,
        error_code& ec) = 0;

    virtual
    void
    on_key_end(
        string_view s,
        error_code& ec) = 0;

    virtual
    void
    on_string_data(
        string_view s,
        error_code& ec) = 0;

    virtual
    void
    on_string_end(
        string_view,
        error_code& ec) = 0;

    virtual
    void
    on_int64(
        int64_t i,
        error_code& ec) = 0;

    virtual
    void
    on_uint64(
        uint64_t u,
        error_code& ec) = 0;

    virtual
    void
    on_double(
        double d,
        error_code& ec) = 0;

    virtual
    void
    on_bool(bool b, error_code& ec) = 0;

    virtual
    void
    on_null(error_code& ec) = 0;
};

} // json
} // boost

#ifdef BOOST_JSON_HEADER_ONLY
#include <boost/json/impl/basic_parser.ipp>
#endif

#endif
