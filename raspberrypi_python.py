#!/usr/bin/env python
# coding: utf-8

# In[1]:


import serial
import struct
import mysql.connector
import sys
from time import sleep
import time


# reading serial port for coordinator
ser = serial.Serial("/dev/ttyACM0",9600)

#reading serial port for sigfox module
ser1=serial.Serial("/dev/ttyAMA0",9600)

#SIGFOX Information and SEND defined functions
def SigfoxInfo():
    ser1.write(str.encode('AT\r\n'))
    data=ser1.read(2)
    ser1.write(str.encode('AT$I=10\r\n'))
    data=ser1.read(10)
    ser1.write(str.encode('AT$I=11\r\n'))
    data=ser1.read(18)

def SigfoxSend():
    #sleep(1)
    ser1.write(str.encode('AT$RC\r\n'))
    data=ser1.read(4)
    cmd = ('AT$SF=' + d + '\r\n').encode()
    #print(cmd)
    ser1.write(cmd)
    #ser1.write(str.encode('AT$SF=formatted\r\n'))
    #sleep(6)
    data=ser1.read(4)
   
while True:
    entry = []
    #payload=[]
    i = 1
    for i in range(1,6):
        string = ser.readline()
        line = string.decode('utf-8')
        if len(line)<8:
            continue
        padded = str.format('{:<08x}',int(line,16))
        a = struct.unpack('!f', bytes.fromhex(padded))[0]
        formated = "{:.2f}".format(a)
        i=i+1
        entry.append(formated)

    c=[abs(int(float(i)*100)) for i in entry]

    d= "".join(str(x) for x in c)

    if ser.isOpen:
        print("port is open")
        #SigfoxInfo()
        #SigfoxSend()
    else:
        print("could not open")

        ser.close()      
    conn = mysql.connector.connect(host="localhost",user="hello",passwd="hello",db = "sensordatadb")
    cursor = conn.cursor()
    #cursor.execute("DROP TABLE IF EXISTS DATA2")
    #sql = """CREATE TABLE DATA (
    #    TEMP float(10),
    #    HUM float(10),
    #    X float(10),
    #    Y float(10),
    #    Z float(10),
    #    DATETIME datetime NOT NULL
    #    )"""
    #cursor.execute(sql)
    now = time.strftime('%Y-%m-%d %H:%M:%S')
    entry.append(now)
    print(entry)
    query = """INSERT INTO DATA (TEMP,HUM,X,Y,Z,DATETIME)
             VALUES (%s,%s,%s,%s,%s,%s)"""
    records = entry
    cursor.execute(query,records)
    conn.commit()
    cursor.execute("SELECT * FROM DATA")
    rows = cursor.fetchall()
    for row in rows:
        print(row)
    #print(cursor.rowcount,"Record inserted successfully")
    conn.close()


# In[ ]:




