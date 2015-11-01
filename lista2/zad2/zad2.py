from Crypto.Cipher import ARC4
import random

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
                self.text.append(int(tempString,2))
                tempString = str()
                i = 0
        #print self.text
        self.hexText = hex(self.text[0])
        for t in self.text[1:]:
            self.hexText = self.hexText+ hex(t)
            #print self.hexText

if __name__ == "__main__":
    entropy = []
    with open("znaki") as file:
        for line in file:
            if line != '\n':
                entropy.append(line[:-1])

    print entropy

    with open("klucz") as k:
        Key = k.read()[:-1]
    prep = []
    start = "00000000"
    key = start + Key
    key = hex(int(key,16))
    #k = hex(key)
    #print key
    var = True
    cryptogram = Cryptograms()
    while var:
        s = random.randint(0,pow(2,32))
        if s in prep:
            continue
        else:
            prep.append(s)
        start = hex(s)[2:]
        print start
        key = start + Key
        key = hex(int(key,16))

        Crypto = ARC4.ARC4Cipher(key)
        for c in Crypto.decrypt(cryptogram.hexText):
            print c
            if not(c in entropy):
                break
            else:
                continue
            var = False
    print Crypto.decrypt(cryptogram.hexText)


