# calcul $(|\Sigma|! \times N^{|\Sigma|})^{|N|}$

import math

def calcul(N, Sigma):
    return (math.factorial(Sigma) * N ** Sigma) ** N
    
    
Sigma = 26
for N in range(1, 6):
    result = calcul(N, Sigma)
    print(f"Result for N={N}, Sigma={Sigma}: {result:.2e}")
