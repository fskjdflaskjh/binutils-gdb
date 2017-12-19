--  Copyright 2017 Free Software Foundation, Inc.
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

with System;

package Pck is

   package Top is
      type Top_T is tagged private;
      type Top_A is access Top_T'Class;
      procedure Assign (Obj: in out Top_T; TV : Integer);
   private
      type Top_T is tagged record
         N : Integer := 1;
         A : Integer := 48;
      end record;
   end Top;

   package Middle is
      type Middle_T is new Top.Top_T with private;
      type Middle_A is access Middle_T'Class;
      procedure Assign (Obj: in out Middle_T; MV : Character);
   private
      type Middle_T is new Top.Top_T with record
         N : Character := 'a';
      end record;
   end Middle;

   type Bottom_T is new Middle.Middle_T with record
      N : Float := 4.0;
      X : Integer := 6;
      A : Character := 'J';
   end record;
   type Bottom_A is access Bottom_T'Class;
   procedure Assign (Obj: in out Bottom_T; BV : Float);

   procedure Do_Nothing (A : System.Address);

end Pck;
