

def xor( a, b):
    if a == b:
        return "0"

    else:
        return "1"

def xorBait( a, b):

    s = str()
    for i in range(0, len(a)):
        s = s + xor(a[i], b[i])

    return s

def KSA(key):
    keylength = len(key)

    S = range(256)

    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % keylength]) % 256
        S[i], S[j] = S[j], S[i]  # swap

    return S


def PRGA(S):
    i = 0
    j = 0
    while True:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]  # swap

        K = S[(S[i] + S[j]) % 256]
        r = bin(K)[2:]
        while len(r) < 8:
            r = "0" + r
        yield r

def RC4(key):
    S = KSA(key)
    return PRGA(S)

class Cryptograms:

    def __init__(self, text = "wiadomosc" ):

        self.text = []
        with open(text) as file:
            tmp = file.read()
        tempString = str()
        i = 0
        for char in tmp:
            if char == "0" or char == "1":
                tempString = tempString + char
                i +=1
            if i == 8:
                self.text.append(tempString)
                tempString = str()
                i = 0

if __name__ == "__main__":

    with open("klucz") as k:
        key = k.read()[:-1]
    print key

    Key=[]
    t = 1
    tkey = 0
    for k in key:

        tkey = tkey + int(k,16)*pow(16,t)
        t = t -1
        if t == -1:
            Key.append(tkey)
            tkey = 0
            t = 1
    Key.append(0)
    Key.append(0)
    Key.append(0)
    Key.append(0)
    print Key

    KeyStr = RC4(Key)

    Result = []

    cryptogram = Cryptograms()
    print cryptogram.text
    for c in cryptogram.text:
        k = next(KeyStr)
        #print "klucz"
        Result.append(xorBait(k,c))
        #print k

    with open("result","w") as file:
        p = str()
        for r in Result:

            try:
                print chr( int(r,2))
            except:
                print "fafaf"
            file.write(chr( int(r,2)))