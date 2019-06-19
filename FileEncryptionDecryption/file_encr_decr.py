import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QPushButton, QAction, QLineEdit, QMessageBox,QFileDialog
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
#from PySide import QtGui
import math

k=int(input('Enter: \n    1 to encrypt your file \n    2 to decrypt your file\n'))

if(k==1):   
    def modInverse(a, m):
        m0 = m
        y = 0
        x = 1
        if (m == 1):
            return 0
        while (a > 1):
            q = a // m
            t = m
            m = a % m
            a = t
            t = y
            y = x - q * y
            x = t
        if (x < 0):
            x = x + m0
        return x

    def nxtprimegen(n):
        m = n
        n = n + 100
        prime = [True for i in range(n + 1)]
        p = 2
        while (p * p <= n):

            if (prime[p] == True):
                for i in range(p * 2, n + 1, p):
                    prime[i] = False
            p += 1
        for p in range(2, n):
            if prime[p]:
                if p > m:
                    return p
                else:
                    val = p
        return val


    def rsa(p,q):
        p=nxtprimegen(p)
        q=nxtprimegen(q)
        print("prime: ", p, " ", q)
        n = p * q
        print("n: ", n)
        tor = (p - 1) * (q - 1)
        e = 2
        while (1):
            if math.gcd(e, tor) == 1:
                break
            else:
                e += 1
        print("public key: ", e)
        d = modInverse(e, tor)
        if d == 1:
            print("no multiplicative_inverse")
            return

        print("private key: ", d)
        return e, d, n
    
    class App(QMainWindow):
        n=0
        e=0
        d=0
        pp=0
        qq=0
        filename=""
        def __init__(self):
            super().__init__()
            self.title = 'Welcome to file encrypter!!!'
            self.left = 10
            self.top = 10
            self.width = 400
            self.height = 500
            self.initUI()


        def initUI(self):
            self.setWindowTitle(self.title)

            self.setGeometry(self.left, self.top, self.width, self.height)
            self.label = QLabel("ENTER FOR 1st PRIME NUMBER" , self)
            self.label.move(130, 40)
            self.label.resize(280, 40)


            # Create textbox
            self.textbox = QLineEdit(self)
            self.textbox.move(60, 70)
            self.textbox.resize(280, 40)

            self.label = QLabel("ENTER FOR 2nd PRIME NUMBER", self)
            self.label.move(130, 120)
            self.label.resize(280, 40)

            self.textbox2 = QLineEdit(self)
            self.textbox2.move(60, 150)
            self.textbox2.resize(280, 40)

            # Create a button in the window
            self.button = QPushButton('Generate Key', self)
            self.button.move(150, 200)
            # connect button to function on_click
            self.button.clicked.connect(self.on_click)



            self.button2 = QPushButton('Open File', self)
            self.button2.move(150, 270)
            self.button2.clicked.connect(self.openFileNameDialog)

            self.button3 = QPushButton('Encrypt', self)
            self.button3.move(150, 300)
            self.button3.clicked.connect(self.encrypt)
            self.show()


        def encrypt(self):
            with open(self.filename, "rb") as image:
                f = image.read()
                msg = bytearray(f)
            en = []
            de = []
            print("msg: ", msg)
            for x in msg:
                en.append(pow(x, self.e, self.n))
            print("\nencrypt msg: ", en)
            ss = ""
            f3 = open(r'C:\Users\User\Desktop\Encrypted\encfile', 'w')
            for x in en:
                ss += (str(x) + " ")
            f3.write(ss)

        @pyqtSlot()
        def on_click(self):
            p = self.textbox.text()
            self.pp=int(p)
            q = self.textbox2.text()
            self.qq = int(q)
            self.e, self.d, self.n = rsa(self.pp,self.qq)

        def openFileNameDialog(self):
            options = QFileDialog.Options()
            options |= QFileDialog.DontUseNativeDialog
            fileName, _ = QFileDialog.getOpenFileName(self, "QFileDialog.getOpenFileName()", "",
                                                  "All Files (*);;Python Files (*.py)", options=options)
            self.filename = fileName

    if __name__ == '__main__':
        app = QApplication(sys.argv)
        ex = App()
        sys.exit(app.exec_())
        
        
        
        
        
        
        
        
if(k==2):        
    class App(QMainWindow):
        de_key=0
        filename=""
        n=0
        file_type=""

        def __init__(self):
            super().__init__()
            self.title = 'Welcome to file decrypter!!!'
            self.left = 10
            self.top = 10
            self.width = 400
            self.height = 500
            self.initUI()


        def initUI(self):
            self.setWindowTitle(self.title)

            self.setGeometry(self.left, self.top, self.width, self.height)
            self.label = QLabel("ENTER PRIVATE KEY", self)
            self.label.move(152, 10)
            self.label.resize(280, 40)


            # Create textbox
            self.textbox = QLineEdit(self)
            self.textbox.move(60, 40)
            self.textbox.resize(280, 40)

            self.label = QLabel("ENTER VALUE OF N", self)
            self.label.move(152, 80)
            self.label.resize(280, 40)

            self.textbox2 = QLineEdit(self)
            self.textbox2.move(60, 110)
            self.textbox2.resize(280, 40)

            self.label = QLabel("ENTER FILE EXTENTION", self)
            self.label.move(144, 150)
            self.label.resize(280, 40)

            self.textbox3 = QLineEdit(self)
            self.textbox3.move(60, 180)
            self.textbox3.resize(280, 40)



            self.button2 = QPushButton('Open File', self)
            self.button2.move(150, 260)
            self.button2.clicked.connect(self.openFileNameDialog)
	    #self.button2.setStyleSheet("background-color: red")



#app = QtGui.QApplication([])

#button = QtGui.QPushButton()
#button.setStyleSheet('QPushButton {background-color: #A3C1DA; color: red;}')
#button.setText('Press Me')
#menu = QtGui.QMenu()
#menuItem1 = menu.addAction('Menu Item1')
#menuItem2 = menu.addAction('Menu Item2')

#button.setMenu(menu)
#button.show()

#app.exec_()








            self.button3 = QPushButton('Decrypt', self)
            self.button3.move(150, 300)
            self.button3.clicked.connect(self.decrypt)
            self.show()


        def decrypt(self):
            textboxValue = self.textbox.text()
            self.de_key = int(textboxValue)
            textboxValue3 = self.textbox2.text()
            self.n = int(textboxValue3)
            textboxValue2 = self.textbox3.text()
            self.file_type = textboxValue2
            en = []
            de = []
            f3 = open(self.filename, 'r')
            str2=f3.read()
            en2 = str2.split(" ")
            for x in en2:
                if len(x) > 0:
                    en.append(int(x))
            for x in en:
                de.append(pow(x, self.de_key, self.n))
            bytearray(de[:4])
            f2 = open(r'C:\Users\User\Desktop\Decrypted\decfile.'+self.file_type, 'wb')
            f2.write(bytearray(de))
            f2.close()
            print("decrypt msg: ", de)



        def openFileNameDialog(self):
            options = QFileDialog.Options()
            options |= QFileDialog.DontUseNativeDialog
            fileName, _ = QFileDialog.getOpenFileName(self, "QFileDialog.getOpenFileName()", "",
                                                  "All Files (*);;Python Files (*.py)", options=options)
            self.filename = fileName

    if __name__ == '__main__':
        app = QApplication(sys.argv)
        ex = App()
        sys.exit(app.exec_())
