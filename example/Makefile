##
# Copyright (C) 2016 Hansruedi Patzen
#
# This file is part of SHCL.
#
# SHCL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SHCL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SHCL. If not, see <http://www.gnu.org/licenses/>.
##

LIBRARY = -lSHCL
OPTIMIZE_FLAG = -O3
WARNING_FLAGS = -Wall -Wextra -Wconversion -Werror
PEDANTIC_FLAGS = -pedantic -pedantic-errors
CPP_FLAGS = -std=c++1y $(OPTIMIZE_FLAG) $(WARNING_FLAGS) $(PEDANTIC_FLAGS)
C_FLAGS = $(OPTIMIZE_FLAG) $(WARNING_FLAGS) $(PEDANTIC_FLAGS)

.PHONY:	all clean

all:	cppexample cexample

cppexample:	example.cpp
	g++ $(CPPFLAGS) $^ -o $@ $(LIBRARY)

cexample:	example.c
	gcc $(CFLAGS) $^ -o $@ $(LIBRARY)

clean:
	rm -f cppexample cexample

