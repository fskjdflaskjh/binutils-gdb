#! /bin/sh

# Copyright (C) 2011-2012 Free Software Foundation, Inc.
#
# This file is part of GDB.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Usage: update-gnulib.sh <path-to-gnulib-repository>
# Update our import of gnulib in the GDB source tree.
#
# This script assumes that it is being called from the gdb/gnulib
# subdirectory, and will verify this before proceeding.
#
# This script will also make a number of other verifications:
#   . The gnulib version (it should match $GNULIB_COMMIT_SHA1).
#   . The correct versions of the auto-tools that are used to
#     regenerate the various scripts and Makefiles are on the PATH.

# The list of gnulib modules we are importing in GDB.
IMPORTED_GNULIB_MODULES="fnmatch-gnu frexpl inttypes memmem update-copyright"

# The gnulib commit ID to use for the update.
GNULIB_COMMIT_SHA1="8d5bd1402003bd0153984b138735adf537d960b0"

# The expected version number for the various auto tools we will
# use after the import.
AUTOCONF_VERSION="2.64"
AUTOMAKE_VERSION="1.11.1"
ACLOCAL_VERSION="$AUTOMAKE_VERSION"

if [ $# -ne 1 ]; then
   echo "Error: Path to gnulib repository missing. Aborting."
   echo "Usage: update-gnulib.sh <path-to-gnulib-repository>"
   exit 1
fi
gnulib_prefix=$1

gnulib_tool="$gnulib_prefix/gnulib-tool"

# Verify that the gnulib directory does exist...
if [ ! -f "$gnulib_tool" ]; then
   echo "Error: Invalid gnulib directory. Cannot find gnulib tool"
   echo "       ($gnulib_tool)."
   echo "Aborting."
   exit 1
fi

# Verify that we have the right version of gnulib...
gnulib_head_sha1=`cd $gnulib_prefix && git rev-parse HEAD`
if [ "$gnulib_head_sha1" != "$GNULIB_COMMIT_SHA1" ]; then
   echo "Error: Wrong version of gnulib: $gnulib_head_sha1"
   echo "       (we expected it to be $GNULIB_COMMIT_SHA1)"
   echo "Aborting."
   exit 1
fi

# Verify that we are in the gdb/ subdirectory.
if [ ! -f ../main.c -o ! -d import ]; then
   echo "Error: This script should be called from the gdb/gnulib subdirectory."
   echo "Aborting."
   exit 1
fi

# Verify that we have the correct version of autoconf.
ver=`autoconf --version 2>&1 | head -1 | sed 's/.*) //'`
if [ "$ver" != "$AUTOCONF_VERSION" ]; then
   echo "Error: Wrong autoconf version: $ver. Aborting."
   exit 1
fi

# Verify that we have the correct version of automake.
ver=`automake --version 2>&1 | head -1 | sed 's/.*) //'`
if [ "$ver" != "$AUTOMAKE_VERSION" ]; then
   echo "Error: Wrong automake version ($ver), we need $AUTOMAKE_VERSION."
   echo "Aborting."
   exit 1
fi

# Verify that we have the correct version of aclocal.
ver=`aclocal --version 2>&1 | head -1 | sed 's/.*) //'`
if [ "$ver" != "$ACLOCAL_VERSION" ]; then
   echo "Error: Wrong aclocal version: $ver. Aborting."
   exit 1
fi

# Update our gnulib import.
$gnulib_prefix/gnulib-tool --import --dir=. --lib=libgnu \
  --source-base=import --m4-base=import/m4 --doc-base=doc \
  --tests-base=tests --aux-dir=import/extra \
  --no-conditional-dependencies --no-libtool --macro-prefix=gl \
  --no-vc-files \
  $IMPORTED_GNULIB_MODULES
if [ $? -ne 0 ]; then
   echo "Error: gnulib import failed.  Aborting."
   exit 1
fi

# Regenerate all necessary files...
aclocal -Iimport/m4 &&
autoconf &&
autoheader &&
automake
if [ $? -ne 0 ]; then
   echo "Error: Failed to regenerate Makefiles and configure scripts."
   exit 1
fi

