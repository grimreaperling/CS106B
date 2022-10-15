def divisor_sum(n):
    total = 0
    for divisor in range(1, n):
        if n % divisor == 0:
            total += divisor
    return total

def is_perfect(n):
    return n != 0 and n == divisor_sum(n)

def find_perfects(stop):
    for num in range(1, stop):
        if is_perfect(num):
            print("Found perfect number: ", num)
        if num % 10000 == 0: print('.', end='',flush=True) # progress bar
    print("Done searching up to ", stop)
