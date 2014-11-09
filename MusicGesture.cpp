//
//  MusicGesture.cpp
//  hackSC
//
//  Created by Lawrence Yuan on 11/8/14.
//  Copyright (c) 2014 Lawrence Yuan. All rights reserved.
//

#include "MusicGesture.h"

MusicGesture::MusicGesture(Leap::Gesture &gesture)
{
    lefthand = false;
    righthand = false;
    handclose = false;
    handopen = false;
    _gesture = gesture;
    Leap::HandList allhands = _gesture.hands();
    for (int index = 0; index < allhands.count(); index++)
    {
        if ( allhands[index].isValid() )
        {
            if ( allhands[index].isLeft() )
            {
                lefthand = true;
            }
            else if ( allhands[index].isRight() )
            {
                righthand = true;
            }
            if ( allhands[index].pinchStrength() > 0.8)
            {
                handclose = true;
            }
            else if ( allhands[index].pinchStrength() < 0.2)
            {
                handopen = true;
            }
        }
    }
}

int MusicGesture::volumeUp1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && std::abs(swipedirection[0]) < 0.25 && swipedirection[1] > 0.6)
            return 1;
    }
    return 0;
}

int MusicGesture::volumeDown1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && std::abs(swipedirection[0]) < 0.25 && swipedirection[1] < -0.6)
            return 1;
    }
    return 0;
}

int MusicGesture::nextSong1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && handopen && swipedirection[0] > 0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::prevSong1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && handopen && swipedirection[0] < -0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::closeSwipeRight1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && handclose && swipedirection[0] > 0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::closeSwipeLeft1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (lefthand && handclose && swipedirection[0] < -0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}


int MusicGesture::pitchUp1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && circle.radius() < 35 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::pitchDown1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && circle.radius() < 35 && circle.durationSeconds() > 0.25 && ! (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::bigCounterclockwiseCircle1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && handopen && circle.radius() > 60 && circle.durationSeconds() > 0.25 && !(circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}


int MusicGesture::bigClockwiseCircle1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && handopen && circle.radius() > 60 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}


int MusicGesture::bigClosedCounterclockwiseCircle1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && handclose && circle.radius() > 60 && circle.durationSeconds() > 0.25 && !(circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}


int MusicGesture::bigClosedClockwiseCircle1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (lefthand && handclose && circle.radius() > 60 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::screentap1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP)
    {
        Leap::ScreenTapGesture screentap = _gesture;
        if (lefthand)
        {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::volumeUp2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && std::abs(swipedirection[0]) < 0.25 && swipedirection[1] > 0.6)
            return 1;
    }
    return 0;
}


int MusicGesture::volumeDown2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && std::abs(swipedirection[0]) < 0.25 && swipedirection[1] < -0.6)
            return 1;
    }
    return 0;
}

int MusicGesture::nextSong2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && handopen && swipedirection[0] > 0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::prevSong2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && handopen && swipedirection[0] < -0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::pitchUp2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && circle.radius() < 35 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::pitchDown2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && circle.radius() < 35 && circle.durationSeconds() > 0.25 && ! (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::bigCounterclockwiseCircle2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && handopen && circle.radius() > 60 && circle.durationSeconds() > 0.25 && !(circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}


int MusicGesture::bigClockwiseCircle2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && handopen && circle.radius() > 60 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::bigClosedCounterclockwiseCircle2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && handclose && circle.radius() > 60 && circle.durationSeconds() > 0.25 && !(circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)) {
            return 1;
        }
    }
    return 0;
}


int MusicGesture::bigClosedClockwiseCircle2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_CIRCLE)
    {
        Leap::CircleGesture circle = _gesture;
        if (righthand && handclose && circle.radius() > 60 && circle.durationSeconds() > 0.25 && circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2) {
            return 1;
        }
    }
    return 0;
}



int MusicGesture::closeSwipeRight2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && handclose && swipedirection[0] > 0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}

int MusicGesture::closeSwipeLeft2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SWIPE)
    {
        Leap::SwipeGesture swipe = _gesture;
        Leap::Vector swipedirection = swipe.direction();
        if (righthand && handclose && swipedirection[0] < -0.6 && std::abs(swipedirection[1]) < 0.25)
            return 1;
    }
    return 0;
}



int MusicGesture::screentap2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP)
    {
        Leap::ScreenTapGesture screentap = _gesture;
        if (righthand)
        {
            return 1;
        }
    }
    return 0;
}

int MusicGesture::keytappointer2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_KEY_TAP)
    {
        Leap::KeyTapGesture screentap = _gesture;
        Leap::PointableList pointables = screentap.pointables();
        for (int index = 0; index < pointables.count(); index++)
        {
            if (pointables[index].isFinger())
            {
                Leap::Finger finger = Leap::Finger(pointables[index]);
                if (righthand && finger.type() == Leap::Finger::TYPE_INDEX && finger.tipVelocity()[1] > 30)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int MusicGesture::keytapmiddle2()
{
    if (_gesture.type() == Leap::Gesture::TYPE_KEY_TAP)
    {
        Leap::KeyTapGesture screentap = _gesture;
        Leap::PointableList pointables = screentap.pointables();
        for (int index = 0; index < pointables.count(); index++)
        {
            if (pointables[index].isFinger())
            {
                Leap::Finger finger = Leap::Finger(pointables[index]);
                if (righthand && finger.type() == Leap::Finger::TYPE_MIDDLE && finger.tipVelocity()[1] > 30)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int MusicGesture::keytappointer1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_KEY_TAP)
    {
        Leap::KeyTapGesture screentap = _gesture;
        Leap::PointableList pointables = screentap.pointables();
        for (int index = 0; index < pointables.count(); index++)
        {
            if (pointables[index].isFinger())
            {
                Leap::Finger finger = Leap::Finger(pointables[index]);
                if (lefthand && finger.type() == Leap::Finger::TYPE_INDEX && finger.tipVelocity()[1] > 30)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int MusicGesture::keytapmiddle1()
{
    if (_gesture.type() == Leap::Gesture::TYPE_KEY_TAP)
    {
        Leap::KeyTapGesture screentap = _gesture;
        Leap::PointableList pointables = screentap.pointables();
        for (int index = 0; index < pointables.count(); index++)
        {
            if (pointables[index].isFinger())
            {
                Leap::Finger finger = Leap::Finger(pointables[index]);
                if (lefthand && finger.type() == Leap::Finger::TYPE_MIDDLE && finger.tipVelocity()[1] > 50)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}



