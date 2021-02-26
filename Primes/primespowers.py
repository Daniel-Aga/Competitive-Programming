def primes(n):
    l = [True for i in range(n + 1)]
    l[0] = False
    l[1] = False
    for i in range(2, n + 1):
         if l[i]:
             for j in range(i * i, n + 1, i):
                 l[j] = False
    return [i for i in range(n + 1) if l[i]]
             
def primes_powers(n):
    l = primes(n)
    k = []
    for i in l:
        m = []
        c = i
        while c <= n:
            m.append(c)
            c *= i
        k.append(m)
    return k

f = open("primespowers.txt", 'w')
l = primes_powers(10**6 + 5)
f.write('{' + ','.join(('{' + ','.join(str(j) for j in i) + '}') for i in l) + '};\n')
f.close()
