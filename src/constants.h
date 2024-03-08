#ifndef CONSTANTS_H
#define CONSTANTS_H
// ****************************************************************************
//  constants.h                                                   DB48X project
// ****************************************************************************
//
//   File Description:
//
//     Constant values loaded from a constants file
//
//     Constants are loaded from a `config/constants.csv` file.
//     This makes it possible to define them with arbitrary precision
//
//
//
//
//
// ****************************************************************************
//   (C) 2024 Christophe de Dinechin <christophe@dinechin.org>
//   This software is licensed under the terms outlined in LICENSE.txt
// ****************************************************************************
//   This file is part of DB48X.
//
//   DB48X is free software: you can redistribute it and/or modify
//   it under the terms outlined in the LICENSE.txt file
//
//   DB48X is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// ****************************************************************************

#include "command.h"
#include "menu.h"
#include "algebraic.h"

GCP(constant);

struct constant : algebraic
// ----------------------------------------------------------------------------
//   A constant is a symbol where the value is looked up from a file
// ----------------------------------------------------------------------------
{
    constant(id type, uint index) : algebraic(type)
    {
        byte *p = (byte *) payload(this);
        leb128(p, index);
    }

    static size_t required_memory(id i, uint index)
    {
        return leb128size(i) + leb128size(index);
    }


    static constant_p make(uint index)
    {
        return rt.make<constant>(ID_constant, index);
    }

    static constant_p lookup(utf8 name, size_t len, bool error);
    static constant_p lookup(cstring name, bool error = true)
    {
        return lookup(utf8(name), strlen(name), error);
    }

    uint        index() const
    {
        byte_p p = payload();
        return leb128<uint>(p);
    }

    utf8        name(size_t *size = nullptr) const;
    algebraic_p value() const;
    bool        is_imaginary_unit() const       { return matches("ⅉ"); }
    bool        is_pi() const                   { return matches("π"); }
    bool        matches(cstring ref) const
    {
        size_t nlen = strlen(ref);
        size_t len = 0;
        utf8 txt = name(&len);
        return len == nlen && memcmp(ref, txt, len) == 0;
    }

public:
    OBJECT_DECL(constant);
    SIZE_DECL(constant);
    EVAL_DECL(constant);
    PARSE_DECL(constant);
    RENDER_DECL(constant);
    GRAPH_DECL(constant);
    HELP_DECL(constant);
};


struct constant_menu : menu
// ----------------------------------------------------------------------------
//   A constant menu is like a standard menu, but with constants
// ----------------------------------------------------------------------------
{
    constant_menu(id type) : menu(type) { }
    static utf8 name(id type, size_t &len);

public:
    MENU_DECL(constant_menu);
};


#define ID(i)
#define CONSTANT_MENU(ConstantMenu)     struct ConstantMenu : constant_menu {};
#include "ids.tbl"

COMMAND_DECLARE_INSERT(ConstantName);
COMMAND_DECLARE_INSERT(ConstantValue);

#endif // CONSTANT_H
