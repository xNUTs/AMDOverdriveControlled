
#include <math.h>
#include "BezierMath.h"
/*
 * Bezier Code based on work of Tolga Birdal. Have a look at Codeproject.com
 */

double Ni(int n, int i)
{
    const double factorial[] =
    {
	1.0,
	1.0,
	2.0,
	6.0,
	24.0,
	120.0,
	720.0,
	5040.0,
	40320.0,
	362880.0,
	3628800.0,
	39916800.0,
	479001600.0,
	6227020800.0,
	87178291200.0,
	1307674368000.0,
	20922789888000.0,
	355687428096000.0,
	6402373705728000.0,
	121645100408832000.0,
	2432902008176640000.0,
	51090942171709440000.0,
	1124000727777607680000.0,
	25852016738884976640000.0,
	620448401733239439360000.0,
	15511210043330985984000000.0,
	403291461126605635584000000.0,
	10888869450418352160768000000.0,
	304888344611713860501504000000.0,
	8841761993739701954543616000000.0,
	265252859812191058636308480000000.0,
	8222838654177922817725562880000000.0,
	263130836933693530167218012160000000.0
    };

    double ni;
    double a1 = factorial[n];
    double a2 = factorial[i];
    double a3 = factorial[n-i];
    ni =  a1/(a2*a3);
    return ni;
}

// Calculate Bernstein basis
double Bernstein(int n, int i, double t)
{
    double basis;
    double ti; /* t^i */
    double tni; /* (1 - t)^i */
    if (t == 0.0 && i == 0) ti = 1.0; else ti = pow(t, i);
    if (n == i && t == 1.0) tni = 1.0; else tni = pow((1 - t), (n - i));
    basis = Ni(n, i) * ti * tni;
    return basis;
}
