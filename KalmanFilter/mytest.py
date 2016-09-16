
def inverse(x):
    import numpy as np
    tmp = np.matrix([x])
    inverse_val = np.linalg.inv(tmp)
    return inverse_val[0,0];


if __name__ == "__main__":
    import sys
    args = sys.argv[1]
    value = inverse(float(args))
    f = open("tmp.txt", "w")
    f.write(str(value))
    f.close()

