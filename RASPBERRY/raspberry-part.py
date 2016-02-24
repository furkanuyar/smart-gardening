from pubnub import Pubnub 
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)  // Ardunio device

pubnub = Pubnub(publish_key='pub-c-***',        # you can get your unique pubnub key
subscribe_key='sub-c-***')                      # from pubnub official site as a free
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
