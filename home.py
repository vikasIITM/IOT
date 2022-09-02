


import random

while True:
    p=int(input("press 1 to check the condition of the room or 0 not to check  :"))
    if(p==1):
        dist=random.randint(0,15)
        if(dist<10):
            n=random.randint(0,50)
            L=random.randint(0,100)
            class AC:
                def __init__(self, temp):
                    self.temp= temp
    

                def myfunc(self):
                    print("Temperature of room is " ,int(+ self.temp))
    

            p1 = AC(n)
            p1.myfunc()

            if (n>27):
                print("AC is on")
            else:
                print("Ac is off")
    
# fan
            class fan:
                def __init__(self, temp):
                    self.temp= temp
    

                def myfunc(self):
                    print("and")

            p1 = fan(n)
            p1.myfunc()

            if (n<27)& (n>15):
                print("fan is on")
            else:
                print("fan is off")

#Light
            class LED:
                def __init__(self, Intensity):
                    self.Intensity= Intensity
    

                def myfunc(self):
                    print("Light intensity of room is " ,int(+ self.Intensity))

            p1 = LED(L)
            p1.myfunc()

            if (n<50):
                print("LED is on")
            else:
              print("LED is off")      
        
        else:
            print("No one in the room")
    elif(p==0):
        print("Do not want to check ")
        break

