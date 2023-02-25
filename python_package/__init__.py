from .python_extension import *

class EC_point:
    def __init__(self, x, y, isO):
        self.x = x
        self.y = y
        self.isO = isO

def add(p, a, b, x1, y1, x2, y2):
    x1_str, y1_str, x2_str, y2_str = str(x1), str(y1), str(x2), str(y2)
    res = EC_ADD(str(p), str(a), str(b), x1_str, y1_str, x2_str, y2_str)
    if res == "O":
        return EC_point(0, 0, True)
    x3, y3 = int(res[0]), int(res[1])
    return EC_point(x3, y3, False)

def mul(p, a, b, x1, y1, c):
    x_str, y_str, c_str = str(x1), str(y1), str(c)
    res = EC_MUL(str(p), str(a), str(b), x_str, y_str, c_str)
    if res == "O":
        return EC_point(0, 0, True)
    x3, y3 = int(res[0]), int(res[1])
    return EC_point(x3, y3, False)