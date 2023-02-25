import elliptic_curve

# Define the parameters for the elliptic curve y^2 = x^3 + 7 (mod 23)
p = 23
a = 0
b = 7

# Define the base point on the curve
x = 5
y = 1
P = elliptic_curve.EC_point(x, y)

# Test point addition
Q = elliptic_curve.EC_point(18, 19)
R = elliptic_curve.add(p, a, b, P, Q)
print(f"P + Q = ({R.x}, {R.y})")

# Test point multiplication
c = 12
S = elliptic_curve.mul(p, a, b, P, c)
print(f"{c}P = ({S.x}, {S.y})")