def primes(n):
    """ Returns  a list of primes < n """
    sieve = [True] * n
    for i in range(3,int(n**0.5)+1,2):
        if sieve[i]:
            sieve[i*i::2*i]=[False]*((n-i*i-1)//(2*i)+1)
    return [2] + [i for i in range(3,n,2) if sieve[i]]

f = open("primes.txt", 'w')
l = primes(10**6 + 5)
f.write('{' + ','.join(str(i) for i in l) + '};\n')
f.close()