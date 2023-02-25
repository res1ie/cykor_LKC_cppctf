#include "elliptic_curve.h"

EC_point EC_DOUBLE(mpz_class p, mpz_class a, mpz_class b, EC_point P) {
    if (P.isO)
        return P;

    mpz_class x1 = P.x, y1 = P.y;
    mpz_class y1_inv=2*y1;
    mpz_invert(y1_inv.get_mpz_t(),y1_inv.get_mpz_t(),p.get_mpz_t());
    mpz_class m = (3 * x1 * x1 + a) * y1_inv;
    mpz_class x3 = (m * m - 2 * x1) % p;
    mpz_class y3 = (m * (x1 - x3) - y1) % p;

    return EC_point(x3, y3, false);
}

EC_point EC_ADD(mpz_class p, mpz_class a, mpz_class b, EC_point P1, EC_point P2) {
    if (P1.isO)
        return P2;
    if (P2.isO)
        return P1;
    if (P1.x == P2.x && P1.y != P2.y)
        return EC_point(0, 0, true);

    mpz_class x1 = P1.x, y1 = P1.y, x2 = P2.x, y2 = P2.y;
    mpz_class sub_inv=x2-x1;
    mpz_invert(sub_inv.get_mpz_t(),sub_inv.get_mpz_t(),p.get_mpz_t());
    mpz_class m = (y2 - y1) * sub_inv;
    mpz_class x3 = (m * m - x1 - x2) % p;
    mpz_class y3 = (m * (x1 - x3) - y1) % p;

    return EC_point(x3, y3, false);
}

EC_point EC_MUL(mpz_class p, mpz_class a, mpz_class b, EC_point P, mpz_class c) {
    EC_point Q(0, 0, true);
    EC_point R = P;

    while (c > 0) {
        if (c % 2 == 1)
            Q = EC_ADD(p, a, b, Q, R);
        R = EC_DOUBLE(p, a, b, R);
        c /= 2;
    }

    return Q;
}