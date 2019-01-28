#!/usr/bin/python
# -*- coding: utf-8 -*-
from pubnub import Pubnub
import serial

# Arduino device.

ser = serial.Serial('/dev/ttyACM0', 9600)

# Pub-sub operation credentials.

pubnub = Pubnub(publish_key='pub-c-***', subscribe_key='sub-c-***')

# Subscribes check, water and cover channels.

pubnub.subscribe(channels='check', callback=_callback, error=_error)
pubnub.subscribe(channels='water', callback=_callback, error=_error)
pubnub.subscribe(channels='cover', callback=_callback, error=_error)


# If there is an error, sends to web part.

def _error(m):
    pubnub.publish(channel='error', message=message,
                   callback=_callback, error=_error)


# Gets messages and commands from web part

def _callback(m, channel):

        # If message is 1, gets instant humidity value and sends to web part.

    if m == 1:
        message = ser.readline()
        pubnub.publish(channel='new', message=message,
                       callback=_callback, error=_error)
    elif m == 2:

        # If message is 2, sends message to arduino part to trigger watering.

        ser.write('2')
    elif m == 3:

        # If message is 3, sends message to arduino part to trigger close and open cover.

        ser.write('3')
