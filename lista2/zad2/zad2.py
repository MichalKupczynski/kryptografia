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
                self.text.append(tempString)
                tempString = str()
                i = 0
        #print self.text
        #self.hexText = hex(self.text[0])
        #for t in self.text[1:]:
        #    self.hexText = self.hexText+ hex(t)
        #print self.hexText

if __name__ == "__main__":

    with open("klucz") as k:
        key = k.read()[:-1]

    #key = "00000000" + key
    #k = hex(key)
    #print key
    entropy = []
    with open("znaki") as file:
        for line in file:
            if line != '\n':
                entropy.append(line[:-1])
    print entropy
    t = 1
    '''Keys1 = []
    for i in range(0,256):
        Keys1.append(i)
        print i'''


    tkey = 0
    Key = [0,0,0,0]
    #print Key
    for k in key:

        tkey = tkey + int(k,16)*pow(16,t)
        t = t -1
        if t == -1:
            Key.append(tkey)
            tkey = 0
            t = 1
    print Key
    cryptogram = Cryptograms()
    '''
    print Key
    print Key
    Crypto = ARC4.ARC4Cipher(Key)
    print Crypto.decrypt(cryptogram.hexText)
    '''

    #for k in Key:

    KeyStr = RC4(Key)



    cryptogram = Cryptograms()
    #print cryptogram.text
    var = True
    while var:
        Key[0] = random.randint(0, 255)
        Key[1] = random.randint(0, 255)
        Key[2] = random.randint(0, 255)
        Key[3] = random.randint(0, 255)
        KeyStr = RC4(Key)
        Result = []
        for c in cryptogram.text:

            #print k
            #print c
            k = next(KeyStr)
            #print "klucz"
            tray = chr(int(xorBait(k,c),2))

            test = False
            for z in entropy:
                if z == tray:
                    test = True
                    break
            if not test:
                break

            Result.append(tray)
            #print k
        #print(Result)
        if len(Result) == len(cryptogram.text):
            break
            var =  False
    print Result

    '''
    with open("result","w") as file:
        p = str()
        for r in Result:

            try:
                print chr( int(r,2))
            except:
                print "fafaf"
            file.write(chr( int(r,2)))'''