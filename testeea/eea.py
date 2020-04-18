#JMJ

# eea.py

import sys

def EEA(a, b, show_steps=False):
    if a<b:
        tmp=a
        a=b
        b=tmp
    if show_steps:
        print('i\tr\tq\tx\ty')
    rpp = a
    xpp = 1
    ypp = 0
    if show_steps:
        print(0, rpp, '', xpp, ypp, sep='\t')
    rp = b
    qp = a // b
    xp = 0
    yp = 1
    if show_steps:
        print(1, rp, qp, xp, yp, sep='\t')
    i = 2
    r = rpp % rp
    if r!=0:
        q = rp // r
    x = xpp - qp * xp
    y = ypp - qp * yp
    while r!=0:
        if show_steps:
            print(i, r, q, x, y, sep='\t')
        i += 1
        rpp = rp
        rp = r
        qp = q
        xpp = xp
        xp = x
        ypp = yp
        yp = y
        r = rpp % rp
        if r!=0:
            q = rp // r
        x = xpp - qp * xp
        y = ypp - qp * yp
    if show_steps :
        print(i, r, sep='\t')
    return (rp, xp, yp)

def main():
    if len(sys.argv) != 3:
        print("boo! I need 2 int args!")
    else:
        (a, b, c) = EEA(int(sys.argv[1]), int(sys.argv[2]), show_steps=True)
        print("results: gcd:", a,", x:", b, " y:", c,", and we didn't count.", sep='')
    print("Bye!")
main()

