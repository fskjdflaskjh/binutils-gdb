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

with Pck;
use Pck;
use Pck.Middle;
use Pck.Top;

procedure Foo is
   B : Bottom_T;
   M : Middle_T;

begin
   Assign (Top_T (B), 12);
   Assign (B, 10.0);

   Assign (M, 'V');
   Assign (B, 5.0);
end Foo;
