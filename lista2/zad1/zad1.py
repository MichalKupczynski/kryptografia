__author__ = 'michal'


class ModuloTwo:

    def xor(self, a, b):
        if a == b:
            return 0

        else:
            return 1

    def xorBait(self, a, b):

        s = str()

        for i in range(0, len(a)):
            s = s + self.xor(a[i], b[i])

        return s

    def intToBait(self, i):
        bait =  "{0:b}".format(i)
        for i in range(0,8-len(bait)):
            bait = "0"+bait


    def baitToInt(self, bait):
        i = int(bait)



class Cryptograms:

    def __init__(self, numberOfCyptograms, text = "text", cryptogram = "cryptogram" ):

        self.NumberOfCryptograms = 0
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

        self.cryptograms = []
        for i in range(1, numberOfCyptograms):

            self.cryptograms.append(self.readCryptogram(i, baseName = "kryptogram"))

    def readCryptogram(self,n, baseName = "cryptogram"):

        cryptogram = []
        name = baseName + str(n)
        print name
        with open(name) as file:
            tmp = file.read()
        tempString = str()
        i = 0
        for char in tmp:
            if char == "0" or char == "1":
                tempString = tempString + char
                i +=1
            if i == 8:
                cryptogram.append(tempString)
                tempString = str()
                i = 0
        return cryptogram


class Decrypting:

    def __init__(self, cryptograms, coding = "coding", entropy = "entropy"):

        self.M2 = ModuloTwo()
        self.cryptograms = cryptograms
        self.codingTable = {}
        self.decodingTable = {}
        with open(coding) as file:
            for line in file.readline():
                i = line.find(";")
                self.codingTable[line[0:i]] = line[i+1:]
                self.decodingTable[line[i+1:]] = line[0:]

        self.enropy = []
        self.q = 0
        with open(entropy) as file:
            for line in file.readline():
                entropy.append[line]
                q = q +1

    def decryptOneSign(self, n, q = self.q):

        propositions = {}
        m = self.cryptograms.text[n]
        for i in range(0, self.cryptograms.numberOfCryptograms):
            try:
                m1 = self.cryptograms.cryptograms[n][j]
                result = self.M2.xorBait(m,m1)
                for j in range(0, q):
                    s = self.entropy[j]
                    if s in self.decodingTable:
                        c = self.M2.intToBait(s)
                        binaryR = self.M2.xorBait(result,c)
                        R = self.M2.baitToInt(binaryR)
                        if R in self.codingTable:
                            if R in propositions:
                                propositions[R] = propositions[R] +1
                            else:
                                propositions[R] = 1
            except:
                pass

        return sorted(propositions.iteritems(), key = lambda (k,v): v, reverse = True)[0][0]

    def decryptMessage(self, result):

        Result = str()
        i = 0
        for s in self.cryptograms.text:
            Result = Result + self.decryptOneSign(i)
            i = i+1
        with open(result) as file:
            file.write(Result)

if __name__ == "__main__":

    cryptograms = Cryptograms(20)
    print cryptograms.text
    for c in cryptograms.cryptograms:
        print c

