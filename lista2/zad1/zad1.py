__author__ = 'michal'


class ModuloTwo:

    def xor(self, a, b):
        if a == b:
            return "0"

        else:
            return "1"

    def xorBait(self, a, b):

        s = str()
        for i in range(0, len(a)):
            s = s + self.xor(a[i], b[i])
        return s

    def intToBait(self, i):
        bait =  "{0:b}".format(int(i))
        for i in range(0,8-len(bait)):
            bait = "0"+bait
        return bait

    def baitToInt(self, bait):
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
        # print name
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
        #print self.entropy

    def decryptMessage(self,file, n, q):
        result = []
        p = {}
        for i in range(0,len(self.cryptograms.text)):
            result.append({"0":0})
        rold = []

        for i in range(0, n):
            #print self.cryptograms.cryptograms[k][n]
            r = []
            p = {}
            m = self.cryptograms.cryptograms[i]
            L = i%n
            rold = []
            for k in range(0,len(cryptograms.text)):
                rold.append(self.M2.xorBait(m[k],self.cryptograms.cryptograms[L][k] ))

            for j in range(0, len(self.cryptograms.text)):
                r.append(self.M2.xorBait(m[j],self.cryptograms.text[j] ))
            for j in range(0,q):
                s =   str(self.M2.intToBait(self.decodingTable[self.entropy[j]]))
                for k in range(0, len(self.cryptograms.text)):
                        tmp = self.M2.xorBait(r[k],s )
                        if str(self.M2.baitToInt(tmp)) in self.codingTable:
                            if self.M2.xorBait(rold[k],s) != tmp:
                                if tmp in result[k]:
                                    result[k][tmp] = result[k][tmp] + 1
                                else:
                                    result[k][tmp] = 1
                                #print p
                                '''if r[k] in p:
                                    if tmp in p[r[k]]:
                                        p[r[k]][tmp] = p[r[k]][tmp] +1
                                    else:
                                        p[r[k]][tmp] = 1
                                else:
                                    p[r[k]] = {}
                                    p[r[k]][tmp] = 1'''


        print result[5]
        Result = str()

        for r in result:
            try:
                Result = Result + self.codingTable[str(self.M2.baitToInt(sorted(r.iteritems(),key = lambda (k,v): v,reverse=True)[0][0]))]
            except:
                pass
                '''
        for t in self.cryptograms.text:
            try:
                Result = Result + self.codingTable[str(self.M2.baitToInt(sorted(p[t].iteritems(),key = lambda (k,v): v,reverse=True)[0][0]))]
            except:
                pass'''



        with open(file,"w") as file:
            file.write(Result)

if __name__ == "__main__":

    cryptograms = Cryptograms(20)
    decrypting = Decrypting(cryptograms, "kodowanie", "entropia")
    decrypting.decryptMessage("odczytany",19,7)


