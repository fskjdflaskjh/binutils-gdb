#!/bin/sh

# debug_msg.sh -- a test case for printing debug info for missing symbols.

# Copyright 2006, 2007 Free Software Foundation, Inc.
# Written by Ian Lance Taylor <iant@google.com>.

# This file is part of gold.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
# MA 02110-1301, USA.

# This file goes with debug_msg.cc, a C++ source file constructed to
# have undefined references.  We compile that file with debug
# information and then try to link it, and make sure the proper errors
# are displayed.  The errors will be found in debug_msg.err.

check()
{
    if ! grep -q "$1" debug_msg.err
    then
	echo "Did not find expected error:"
	echo "   $1"
	echo ""
	echo "Actual error output below:"
	cat debug_msg.err
	exit 1
    fi
}

# We don't know how the compiler might order these variables, so we
# can't test for the actual offset from .data, hence the regexp.
check "debug_msg.o: in function fn_array:debug_msg.cc(.data+0x[0-9a-fA-F]*): undefined reference to 'undef_fn1()'"
check "debug_msg.o: in function fn_array:debug_msg.cc(.data+0x[0-9a-fA-F]*): undefined reference to 'undef_fn2()'"
check "debug_msg.o: in function badref1:debug_msg.cc(.data+0x[0-9a-fA-F]*): undefined reference to 'undef_int'"

check "debug_msg.o: in function Base::virtfn():${srcdir}/debug_msg.cc:50: undefined reference to 'undef_fn1()'"
check "debug_msg.o: in function Derived::virtfn():${srcdir}/debug_msg.cc:55: undefined reference to 'undef_fn2()'"
check "debug_msg.o: in function int testfn<int>(int):${srcdir}/debug_msg.cc:43: undefined reference to 'undef_fn1()'"
check "debug_msg.o: in function int testfn<int>(int):${srcdir}/debug_msg.cc:44: undefined reference to 'undef_fn2()'"
check "debug_msg.o: in function int testfn<int>(int):${srcdir}/debug_msg.cc:45: undefined reference to 'undef_int'"
check "debug_msg.o: in function int testfn<double>(double):${srcdir}/debug_msg.cc:43: undefined reference to 'undef_fn1()'"
check "debug_msg.o: in function int testfn<double>(double):${srcdir}/debug_msg.cc:44: undefined reference to 'undef_fn2()'"
check "debug_msg.o: in function int testfn<double>(double):${srcdir}/debug_msg.cc:45: undefined reference to 'undef_int'"

exit 0
