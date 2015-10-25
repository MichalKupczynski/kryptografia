__author__ = 'michal'


class ModuloTwo:

    def xor(self, a, b):
        if a == b:
            return "0"

        else:
            return "1"

    def xorBait(self, a, b):

        s = str()
        print "a" +a
        print "b" + b
        print len(a)
        for i in range(0, len(a)):
            s = s + self.xor(a[i], b[i])
        return s

    def intToBait(self, i):
        bait =  "{0:b}".format(int(i))
        for i in range(0,8-len(bait)):
            bait = "0"+bait
        return bait

    def baitToInt(self, bait):
        print bait
        i = int(bait,2)
        return i


class Cryptograms:

    def __init__(self, numberOfCryptograms, text = "text", cryptogram = "cryptogram" ):

        self.numberOfCryptograms = numberOfCryptograms
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
        for i in range(1, self.numberOfCryptograms):

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

    def __init__(self, cryptograms, coding = "coding", entropy_file = "entropy"):

        self.M2 = ModuloTwo()
        self.cryptograms = cryptograms
        self.codingTable = {}
        self.decodingTable = {}
        with open(coding) as file:
            for line in file:

                i = line.find(";")
                self.codingTable[line[0:i]] = line[i+1:-1]
                self.decodingTable[line[i+1:-1]] = line[0:i]

        self.entropy = []
        self.q = 0
        with open(entropy_file) as file:
            for line in file:
                if line != '\n':
                    self.entropy.append(line[:-1])
                    self.q = self.q +1
        print self.entropy

    def decryptOneSign(self, n, q ):

        propositions = {}
        m = self.cryptograms.text[n]
        for i in range(0, self.cryptograms.numberOfCryptograms):
            try:
                m1 = self.cryptograms.cryptograms[i][n]
                #print m1
                #print "czesc"
                result = self.M2.xorBait(m,m1)
                #print self.codingTable
                for j in range(0, q):
                    s = self.entropy[j]
                    if s in self.decodingTable:
                        #print s
                        c = self.M2.intToBait(self.decodingTable[s])
                        binaryR = self.M2.xorBait(result,c)
                        R = str(self.M2.baitToInt(binaryR))
                        if R in self.codingTable:
                            if R in propositions:
                                propositions[R] = propositions[R] +1
                            else:
                                propositions[R] = 1
            except:
                pass
        print propositions
        if propositions == {}:
            return self.decodingTable[self.entropy[0]]
        max = sorted(propositions.iteritems(), key = lambda (k,v): v, reverse = True)[0][0]
        print max
        return max

    def decryptMessage(self, result):

        Result = str()
        i = 0
        for s in self.cryptograms.text:
            Result = Result + self.codingTable[self.decryptOneSign(i, self.q)]
            i = i+1
        with open(result,"w") as file:
            file.write(Result)

if __name__ == "__main__":

    cryptograms = Cryptograms(20)
    decrypting = Decrypting(cryptograms, "kodowanie", "entropia")
    decrypting.decryptMessage("odczytany")

