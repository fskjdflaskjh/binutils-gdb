#as: -J
#objdump: -dw
#name: i386
.*: +file format .*

Disassembly of section .text:

0+ <.*>:
[ 	]*[a-f0-9]+:	0f be 10             	movsbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f be 10          	movsbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f be 10             	movsbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f be 10          	movsbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f be 10             	movsbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	0f bf 10             	movswl \(%eax\),%edx
[ 	]*[a-f0-9]+:	0f b6 10             	movzbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f b6 10          	movzbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f b6 10             	movzbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f b6 10          	movzbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f b6 10             	movzbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f b6 10          	movzbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f b7 10             	movzwl \(%eax\),%edx
[ 	]*[a-f0-9]+:	0f be 10             	movsbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f be 10          	movsbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f bf 10             	movswl \(%eax\),%edx
[ 	]*[a-f0-9]+:	0f b6 10             	movzbl \(%eax\),%edx
[ 	]*[a-f0-9]+:	66 0f b6 10          	movzbw \(%eax\),%dx
[ 	]*[a-f0-9]+:	0f b7 10             	movzwl \(%eax\),%edx
