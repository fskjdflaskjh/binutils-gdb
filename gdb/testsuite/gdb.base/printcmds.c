/* This table is used as a source for every ascii character.
   It is explicitly unsigned to avoid differences due to native characters
   being either signed or unsigned. */
#include <stdlib.h>
unsigned char ctable1[256] = {
  0000, 0001, 0002, 0003, 0004, 0005, 0006, 0007,
  0010, 0011, 0012, 0013, 0014, 0015, 0016, 0017,
  0020, 0021, 0022, 0023, 0024, 0025, 0026, 0027,
  0030, 0031, 0032, 0033, 0034, 0035, 0036, 0037,
  0040, 0041, 0042, 0043, 0044, 0045, 0046, 0047,
  0050, 0051, 0052, 0053, 0054, 0055, 0056, 0057,
  0060, 0061, 0062, 0063, 0064, 0065, 0066, 0067,
  0070, 0071, 0072, 0073, 0074, 0075, 0076, 0077,
  0100, 0101, 0102, 0103, 0104, 0105, 0106, 0107,
  0110, 0111, 0112, 0113, 0114, 0115, 0116, 0117,
  0120, 0121, 0122, 0123, 0124, 0125, 0126, 0127,
  0130, 0131, 0132, 0133, 0134, 0135, 0136, 0137,
  0140, 0141, 0142, 0143, 0144, 0145, 0146, 0147,
  0150, 0151, 0152, 0153, 0154, 0155, 0156, 0157,
  0160, 0161, 0162, 0163, 0164, 0165, 0166, 0167,
  0170, 0171, 0172, 0173, 0174, 0175, 0176, 0177,
  0200, 0201, 0202, 0203, 0204, 0205, 0206, 0207,
  0210, 0211, 0212, 0213, 0214, 0215, 0216, 0217,
  0220, 0221, 0222, 0223, 0224, 0225, 0226, 0227,
  0230, 0231, 0232, 0233, 0234, 0235, 0236, 0237,
  0240, 0241, 0242, 0243, 0244, 0245, 0246, 0247,
  0250, 0251, 0252, 0253, 0254, 0255, 0256, 0257,
  0260, 0261, 0262, 0263, 0264, 0265, 0266, 0267,
  0270, 0271, 0272, 0273, 0274, 0275, 0276, 0277,
  0300, 0301, 0302, 0303, 0304, 0305, 0306, 0307,
  0310, 0311, 0312, 0313, 0314, 0315, 0316, 0317,
  0320, 0321, 0322, 0323, 0324, 0325, 0326, 0327,
  0330, 0331, 0332, 0333, 0334, 0335, 0336, 0337,
  0340, 0341, 0342, 0343, 0344, 0345, 0346, 0347,
  0350, 0351, 0352, 0353, 0354, 0355, 0356, 0357,
  0360, 0361, 0362, 0363, 0364, 0365, 0366, 0367,
  0370, 0371, 0372, 0373, 0374, 0375, 0376, 0377
};

unsigned char ctable2[] = {
  'a','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
  'a','a','X','X','X','X','X','X','X','X','X','X','X','X','X','X',
  'a','a','a','X','X','X','X','X','X','X','X','X','X','X','X','X',
  'a','a','a','a','X','X','X','X','X','X','X','X','X','X','X','X',
  'a','a','a','a','a','X','X','X','X','X','X','X','X','X','X','X',
  'a','a','a','a','a','a','X','X','X','X','X','X','X','X','X','X',
  'a','a','a','a','a','a','a','X','X','X','X','X','X','X','X','X',
  'a','a','a','a','a','a','a','a','X','X','X','X','X','X','X','X',
  'a','a','a','a','a','a','a','a','a','X','X','X','X','X','X','X',
  'a','a','a','a','a','a','a','a','a','a','X','X','X','X','X','X',
  'a','a','a','a','a','a','a','a','a','a','a','X','X','X','X','X',
  'a','a','a','a','a','a','a','a','a','a','a','a','X','X','X','X',
  'a','a','a','a','a','a','a','a','a','a','a','a','a','X','X','X',
  'a','a','a','a','a','a','a','a','a','a','a','a','a','a','X','X',
  'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','X',
  'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a', 0
};

/* Single and multidimensional arrays to test access and printing of array
   members. */

typedef int ArrayInt [10];
ArrayInt a1 = {2,4,6,8,10,12,14,16,18,20};

typedef char ArrayChar [5];
ArrayChar a2 = {'a','b','c','d','\0'};

int int1dim[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
int int2dim[3][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11}};
int int3dim[2][3][2] = {{{0,1},{2,3},{4,5}},{{6,7},{8,9},{10,11}}};
int int4dim[1][2][3][2] = {{{{0,1},{2,3},{4,5}},{{6,7},{8,9},{10,11}}}};

char *teststring = (char*)"teststring contents";

/* Test printing of a struct containing character arrays. */

struct some_arrays {
    unsigned char array1[4];
    unsigned char array2[1];
    unsigned char array3[1];
    unsigned char array4[2];
    unsigned char array5[4];
} arrays = {
  {'a', 'b', 'c', '\0'},
  {'d'},
  {'e'},
  {'f', 'g' },
  {'h', 'i', 'j', '\0'}
};

struct some_arrays *parrays = &arrays;

enum some_volatile_enum { enumvolval1, enumvolval2 };

/* A volatile enum variable whose name is the same as the enumeration
   name.  See PR11827.  */
volatile enum some_volatile_enum some_volatile_enum = enumvolval1;

/* -- */

int main ()
{
#ifdef usestubs
  set_debug_traps();
  breakpoint();
#endif
  malloc(1);

  /* Prevent AIX linker from removing variables.  */
  return ctable1[0] + ctable2[0] + int1dim[0] + int2dim[0][0]
    + int3dim[0][0][0] + int4dim[0][0][0][0] + teststring[0] +
      *parrays -> array1 + a1[0] + a2[0];
}
