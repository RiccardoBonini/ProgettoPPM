import selectors
import test
sel = selectors.DefaultSelector()
import socket
import time

VK_TAB  = 0x09
VK_MENU = 0x12
VK_LBUTTON = 0x01
VK_RBUTTON = 0x02
W = 0x57
A = 0x41
S = 0x53
D = 0x44
VK_UP = 0x26
VK_LEFT = 0x25
VK_RIGHT = 0x27
VK_SPACE = 0x20

def Parse(Stringa, Carattere):
    s=""
    for i in range(len(Stringa)):
        if Stringa[i]==Carattere:
            i=i+3
            while((Stringa[i]=="'")or(Stringa[i]=="b")or(Stringa[i]==":")or(Stringa[i]=='"'))and i<=len(Stringa):
                i=(i+1)%len(Stringa)
            while (Stringa[i]!=",")and(Stringa[i]!="'")and(Stringa[i]!="b")and i<=len(Stringa)and(Stringa[i]!="{"):
                s=s+Stringa[i]
                i=(i+1)%len(Stringa)
            return s
    return -1
def Trova(Stringa, Carattere):
  Indice = 0
  while Indice < len(Stringa):
    if Stringa[Indice] == Carattere:
      return Indice
    Indice = Indice + 1
  return -1
def Check(modello):
    for i in range(len(lista)):
        if lista[i].model==modello:
            return i
    return -1
class connessioni:
    def __init__(self, addr, conn, mod):
        self.address=addr
        self.connection=conn
        self.model=mod
host = '192.168.43.209'
port = 255
stringa=""
lista=[]
connected = 3 #numero di connessioni accettate
s=socket.socket()
s.bind((host, port))
s.listen()

waiter=0
print("Partito")
while waiter<connected:
    conn, addr = s.accept()
    s.setblocking(1)

    if '192.168.43.162' in addr:
        modello="macchina"
    if '192.168.43.188' in addr:
        modello="controller"
    if '192.168.43.201' in addr:
        modello="interfaccia"
    if ((len(lista) == 0)or(Check(modello))==-1):
        a=connessioni(addr,conn,modello)
        lista.append(a)
        print('Connected by', a.address[0], 'Tipo', a.model )
        waiter = waiter + 1
    indice = Check("controller")
    controller = lista[indice].connection
    indice = Check("macchina")
    macchina = lista[indice].connection
    indice = Check("interfaccia")
    interfaccia = lista[indice].connection
waiter=0
# while True:
#     for i in range(len(lista)):
#         print(lista[i].connection)
#     data=str(interfaccia.recv(20480))
#     print(data)
while True:
    #da copiare in ogni funzione
    macchina.send(str.encode("a"))
    test.PressKey(VK_UP)
    time.sleep(1)
    test.ReleaseKey(VK_UP)
    ###

    data = str(controller.recv(20480))
    stringa = stringa + data
    found = Trova(stringa, "}")
    if (found > -1):
        split = stringa.split("}", 1)
        buona=split[0]
        stringa=split[1]
        x=Parse(buona, "X")
        print(x)
        # if(x>"486"):
        #     print("x avanti")
        #      macchina.send(str.encode("a"))
         # elif(x<"486"):
            #     print("x indietro")
            #     macchina.send(str.encode("i"))
            # y=Parse(buona, "Y")
            # if (y > "995"):
            #     print("y avanti")
            # elif (y < "993"):
            #     print("y indietro")
            # z=Parse(buona, "B")
            # if(z>"1"):
            #     print("z avanti")
# lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# lsock.bind((host, port))
# lsock.listen()
# print('listening on', (host, port))
# lsock.setblocking(False)
# sel.register(lsock, selectors.EVENT_READ, data=None)