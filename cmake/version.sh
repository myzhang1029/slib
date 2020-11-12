#!/bin/sh

srcdir="$(dirname "$0")/.."
ver_major="$(grep SBLLIB_VERSION "${srcdir}/include/slib/general.h" | cut -f3 -d\ )"
ver_minor="$(grep SBLLIB_MINOR "${srcdir}/include/slib/general.h" | cut -f3 -d\ )"
ver_pl="$(grep SBLLIB_PATCHLEVEL "${srcdir}/include/slib/general.h" | cut -f3 -d\ )"
version="${ver_major}.${ver_minor}.${ver_pl}"
echo -n "$version"
