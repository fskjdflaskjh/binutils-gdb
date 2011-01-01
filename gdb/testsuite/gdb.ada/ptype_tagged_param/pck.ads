--  Copyright 2010, 2011 Free Software Foundation, Inc.
--
--  This program is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 3 of the License, or
--  (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with this program.  If not, see <http://www.gnu.org/licenses/>.

package Pck is

   type Shape is abstract tagged record
     X, Y: Integer;
   end record;
   function Position_X (S : in Shape) return Integer;

   type Circle is new Shape with record
     R : Integer;
   end record;
   function Area (C : in Circle) return Integer;

end Pck;

