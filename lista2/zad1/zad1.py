__author__ = 'michal'


class ModuloTwo:

    def xor(self, a, b):
        if a == b:
            return 0

        else:
            return 1

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

if __name__ == "__main__":

    cryptograms = Cryptograms(20)
    print cryptograms.text
    for c in cryptograms.cryptograms:
        print c

