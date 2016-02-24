from pubnub import Pubnub 
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)  // Ardunio device

pubnub = Pubnub(publish_key='pub-c-77f8ee30-f9ba-4b09-815a-3ba6309ca3ed', 
subscribe_key='sub-c-059fe690-cf78-11e5-b764-02ee2ddab7fe')

channel = 'check'



def _callback(m, channel):
        if m == 1:
                def callback(message):
                        print(message)
                    

                message=(ser.readline())
                pubnub.publish(channel='new',message=message,callback=callback,error=callback)

def _error(m):
        print(m)
 
pubnub.subscribe(channels=channel, callback=_callback, error=_error)

channel = 'water'

def _callback(m, channel):
        print(m)
        if m == 2:
                for i in range(1):
                    ser.write('2')
                    

def _error(m):
        print(m)
 
pubnub.subscribe(channels=channel, callback=_callback, error=_error)

channel = 'cover'

def _callback(m, channel):
        print(m)
        if m == 3:
                for i in range(1):
                    ser.write('3')
                    

def _error(m):
        print(m)
 
pubnub.subscribe(channels=channel, callback=_callback, error=_error)
