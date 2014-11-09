//
//  MusicGesture.h
//  hackSC
//
//  Created by Lawrence Yuan on 11/8/14.
//  Copyright (c) 2014 Lawrence Yuan. All rights reserved.
//

#ifndef __hackSC__MusicGesture__
#define __hackSC__MusicGesture__

#include <stdio.h>
#include "Leap.h"

class MusicGesture
{
public:
    MusicGesture(Leap::Gesture &gesture);
    int volumeUp1();
    int volumeDown1();
    int nextSong1();
    int prevSong1();
    int pitchUp1();
    int pitchDown1();
    int bigClockwiseCircle1();
    int bigCounterclockwiseCircle1();
    int bigClosedClockwiseCircle1();
    int bigClosedCounterclockwiseCircle1();
    int closeSwipeRight1();
    int closeSwipeLeft1();
    int screentap1();
    int keytappointer1();
    int keytapmiddle1();
    
    int volumeUp2();
    int volumeDown2();
    int nextSong2();
    int prevSong2();
    int pitchUp2();
    int pitchDown2();
    int bigClockwiseCircle2();
    int bigCounterclockwiseCircle2();
    int bigClosedClockwiseCircle2();
    int bigClosedCounterclockwiseCircle2();
    int closeSwipeRight2();
    int closeSwipeLeft2();
    int screentap2();
    int keytappointer2();
    int keytapmiddle2();
    
private:
    bool lefthand;
    bool righthand;
    bool handopen;
    bool handclose;
    Leap::Gesture _gesture;
};

#endif /* defined(__hackSC__MusicGesture__) */
