import selectors
sel = selectors.DefaultSelector()
import socket

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

host = '192.168.43.209'
port = 255
stringa=""
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    print("Partito")
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = str(conn.recv(1024))
            stringa = stringa + data
            found = Trova(stringa, "}")
            if (found > -1):
                split = stringa.split("}", 1)
                buona=split[0]
                stringa=split[1]

                x=Parse(buona, "X")
                if(x>"486"):
                    print("x avanti")
                elif(x<"486"):
                    print("x indietro")
                y=Parse(buona, "Y")
                if (y > "995"):
                    print("y avanti")
                elif (y < "993"):
                    print("y indietro")
                bottone=Parse(buona, "B")
                if(bottone=="true"):
                    print("tasto premuto")
            if not data:
                break
            #conn.sendall(data)
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.bind((host, port))
lsock.listen()
print('listening on', (host, port))
lsock.setblocking(False)
sel.register(lsock, selectors.EVENT_READ, data=None)