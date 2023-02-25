#include <gmpxx.h>

class EC_point {
public:
    mpz_class x;
    mpz_class y;
    bool isO;
    EC_point() {}
    EC_point(mpz_class x_, mpz_class y_, bool isO_): x(x_), y(y_), isO(isO_) {}
};

EC_point EC_DOUBLE(mpz_class p, mpz_class a, mpz_class b, EC_point P);
EC_point EC_ADD(mpz_class p, mpz_class a, mpz_class b, EC_point P1, EC_point P2);
EC_point EC_MUL(mpz_class p, mpz_class a, mpz_class b, EC_point P, mpz_class c);