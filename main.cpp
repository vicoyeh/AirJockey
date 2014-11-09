/******************************************************************************\
 * Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
 * Leap Motion proprietary and confidential. Not for distribution.              *
 * Use subject to the terms of the Leap Motion SDK Agreement available at       *
 * https://developer.leapmotion.com/sdk_agreement, or another agreement         *
 * between Leap Motion and you, your company or other organization.             *
 \******************************************************************************/

#include <iostream>
#include <string.h>
#include "Leap.h"
#include "MusicGesture.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace Leap;

enum ACTIONLIST { volumeUp1,
     volumeDown1,
     nextSong1,
     prevSong1,
     pitchUp1,
     pitchDown1,
     bigClockwiseCircle1,
     bigCounterclockwiseCircle1,
     bigClosedClockwiseCircle1,
     bigClosedCounterclockwiseCircle1,
     closeSwipeRight1,
     closeSwipeLeft1,
     screentap1,
     volumeUp2,
     volumeDown2,
     nextSong2,
     prevSong2,
     pitchUp2,
     pitchDown2,
     bigClockwiseCircle2,
     bigCounterclockwiseCircle2,
     bigClosedClockwiseCircle2,
     bigClosedCounterclockwiseCircle2,
     closeSwipeRight2,
     closeSwipeLeft2,
     screentap2};


class LeapListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    LeapListener(sf::Music* a, sf::Music* b, std::vector<sf::SoundBuffer*> c);
private:
    int lastAction;
	sf::Music* TrackL;
	sf::Music* TrackR;
    sf::Sound* effect1;
    sf::Sound* effect2;
    sf::Sound* effect3;
    sf::Sound* effect4;
    sf::Sound* effect5;
    sf::Sound* effect6;
    sf::Sound* effect7;
    sf::Sound* effect8;
	std::vector <std::string> testingFiles;
    std::vector <sf::SoundBuffer*> soundEffects;
	int LeftTrack;
	int RightTrack;
	int lastActionLeft;
    int lastActionRight;
	bool rightHandClear;
    bool leftHandClear;
};
LeapListener::LeapListener(sf::Music* a, sf::Music* b, std::vector<sf::SoundBuffer*> c){
    effect1 = new sf::Sound;
    effect2 = new sf::Sound;
    effect3 = new sf::Sound;
    effect4 = new sf::Sound;
    effect5 = new sf::Sound;
    effect6 = new sf::Sound;
    effect7 = new sf::Sound;
    effect8 = new sf::Sound;
	TrackL = a;
	TrackR = b;
	testingFiles.push_back("1.ogg");
	testingFiles.push_back("2.ogg");
	testingFiles.push_back("3.ogg");
    soundEffects = c;
    
    
	LeftTrack = 0;
	RightTrack = 0;
}
const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void LeapListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void LeapListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void LeapListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void LeapListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void LeapListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    
    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
		
        Gesture gesture = gestures[g];
        MusicGesture doSomething(gesture);
		//LEFT HAND VOL 
        if (doSomething.volumeUp1())
        {
			TrackL->setVolume(TrackL->getVolume()+1.5);
            std::cout << "VOLUME UP1" << std::endl;
			lastActionLeft = volumeUp1;
        }
        if (doSomething.volumeDown1())
        {
			TrackL->setVolume(TrackL->getVolume()-1.5);
            std::cout << "VOLUME DOWN1" << std::endl;
			lastActionLeft = volumeDown1;
        }
		//LEFT HAND PLAYLIST
        if (doSomething.nextSong1() && (lastActionLeft != nextSong1 || leftHandClear))
        {
			TrackL->stop();
			if (TrackL->getStatus() == sf::Music::Stopped)
			{
				if (LeftTrack >= 0 && LeftTrack < 2)
				{
					LeftTrack++;
				}
				else
				{
					LeftTrack = 0;
				}
				TrackL->openFromFile(testingFiles.at(LeftTrack));
				std::cout<<LeftTrack;
				TrackL->play();
			}
			TrackL->setPitch(1);
            std::cout << "NEXT SONGL" << std::endl;
            lastActionLeft = nextSong1;
            leftHandClear = false;
        }
        if (doSomething.prevSong1() && (lastActionLeft != prevSong1 || leftHandClear))
        {
			TrackL->stop();
			if (TrackL->getStatus() == sf::Music::Stopped)
			{
				if (LeftTrack > 0 && LeftTrack <= 2)
				{
					LeftTrack--;
				}
				else
				{
					LeftTrack = 2;
				}
				TrackL->openFromFile(testingFiles.at(LeftTrack));
				std::cout<<LeftTrack;
				TrackL->play();
			}
			TrackL->setPitch(1);
            std::cout << "PREV SONG1" << std::endl;
            lastActionLeft = prevSong1;
            leftHandClear = false;
        }
		//LEFT HAND PITCH
        if (doSomething.pitchUp1())
        {
			TrackL->setPitch(TrackL->getPitch()+.01);
            std::cout << "PITCH UP1" << std::endl;
			lastActionLeft = pitchUp1;
        }
        if (doSomething.pitchDown1())
        {
			TrackL->setPitch(TrackL->getPitch()-.01);
            std::cout << "PITCH DOWN1" << std::endl;
			lastActionLeft = pitchDown1;
        }
        //RIGHT HAND VOL
        if (doSomething.volumeUp2())
        {
			TrackR->setVolume(TrackR->getVolume()+1.5);
            std::cout << "VOLUME UP2" << std::endl;
			lastActionRight = volumeUp2;
        }
        if (doSomething.volumeDown2())
        {
			TrackR->setVolume(TrackR->getVolume()-1.5);
            std::cout << "VOLUME DOWN2" << std::endl;
			lastActionRight = volumeDown2;
        }
		//RIGHT HAND PLAYLIST
        if (doSomething.nextSong2() && (lastActionRight != nextSong2 || rightHandClear))
        {
			TrackR->stop();
			if (TrackR->getStatus() == sf::Music::Stopped)
			{
				if (RightTrack >= 0 && RightTrack < 2)
				{
					RightTrack++;
				}
				else
				{
					RightTrack = 0;
				}
				TrackR->openFromFile(testingFiles.at(RightTrack));
				std::cout<<RightTrack;
				TrackR->play();
			}
            std::cout << "NEXT SONG2" << std::endl;
			TrackR->setPitch(1);
			lastActionRight = nextSong2;
			rightHandClear = false;
        }
        if (doSomething.prevSong2() && (lastActionRight != prevSong2 || rightHandClear))
        {
			TrackR->stop();
			if (TrackR->getStatus() == sf::Music::Stopped)
			{
				if (RightTrack > 0 && RightTrack <= 2)
				{
					RightTrack--;
				}
				else
				{
					RightTrack = 2;
				}
				TrackR->openFromFile(testingFiles.at(RightTrack));
				std::cout<<RightTrack;
				TrackR->play();
			}
            std::cout << "NEXT SONG2" << std::endl;
			TrackR->setPitch(1);
            std::cout << "PREV SONG2" << std::endl;
			lastActionRight = prevSong2;
			rightHandClear = false;
        }
		//RIGHT HAND PITCH
        if (doSomething.pitchUp2())
        {
			TrackR->setPitch(TrackR->getPitch()+.01);
            std::cout << "PITCH UP2" << std::endl;
			lastActionRight = pitchUp2;
        }
        if (doSomething.pitchDown2())
        {
			TrackR->setPitch(TrackR->getPitch()-.01);
            std::cout << "PITCH DOWN2" << std::endl;
			lastActionRight = pitchDown2;
        }
        
		//LEFT HAND VOLUME RESET
        if (doSomething.bigClockwiseCircle1())
        {
			TrackL->setVolume(50);
            std::cout << "BIG CLOCKWISE CIRCLE1" << std::endl;
            lastActionLeft = bigClockwiseCircle1;
        }
		//RIGHT HAND PITCH RESET
        if (doSomething.bigClockwiseCircle2())
        {			
			TrackR->setPitch(1);
            std::cout << "BIG CLOCKWISE CIRCLE2" << std::endl;
            lastActionRight = bigClockwiseCircle2;
        }
		//LEFT HAND RESET PITCH
        if (doSomething.bigCounterclockwiseCircle1())
        {
			TrackL->setPitch(1);
            std::cout << "BIG COUNTERCLOCKWISE CIRCLE1" << std::endl;
            lastActionLeft = bigCounterclockwiseCircle1;
        }
		//RIGHT HAND RESET VOLUME
        if (doSomething.bigCounterclockwiseCircle2())
        {
			TrackR->setVolume(50);            
			std::cout << "BIG COUNTERCLOCKWISE CIRCLE2" << std::endl;
            lastActionRight = bigCounterclockwiseCircle2;
        }

		//UNUSED
        /*if (doSomething.bigClosedClockwiseCircle1())
        {
            std::cout << "BIG ClosedClockWISE CIRCLE1" << std::endl;
            lastActionLeft = bigClockwiseCircle1;
        }
        if (doSomething.bigClosedClockwiseCircle2())
        {
            std::cout << "BIG ClosedClockWISE CIRCLE2" << std::endl;
            lastActionRight = bigClosedClockwiseCircle2;
        }
        if (doSomething.bigClosedCounterclockwiseCircle1())
        {
            std::cout << "BIG ClosedCounterCLOCKWISE CIRCLE1" << std::endl;
            lastActionLeft = bigClosedCounterclockwiseCircle1;
        }
        if (doSomething.bigClosedCounterclockwiseCircle2())
        {
            std::cout << "BIG ClosedCounterCLOCKWISE CIRCLE2" << std::endl;
            lastActionLeft = bigClosedCounterclockwiseCircle2;
        }
        */

		//LEFT HAND PAUSE/PLAY
        if (doSomething.closeSwipeLeft1() && (lastActionLeft != closeSwipeLeft1 || leftHandClear))
        {
            if(TrackL->getStatus() == sf::Music::Playing)
                TrackL->pause();
            else
                TrackL->play();
            std::cout << "CLOSE SWIPE LEFT1" << std::endl;
            lastActionLeft = closeSwipeLeft1;
            leftHandClear = false;
        }
		//RIGHT HAND PLAY
        if (doSomething.closeSwipeLeft2() && (lastActionRight != closeSwipeLeft2 || rightHandClear))
        {
			
			TrackR->play();
            std::cout << "CLOSE SWIPE LEFT2" << std::endl;
            lastActionRight = closeSwipeLeft2;
            rightHandClear = false;
        }
		//LEFT HAND PAUSE
        if (doSomething.closeSwipeRight1() && (lastActionLeft != closeSwipeRight1 || leftHandClear))
        {
			
			TrackL->play();
            std::cout << "CLOSE SWIPE RIGHT1" << std::endl;
            lastActionLeft = closeSwipeRight1;
            leftHandClear = false;
        }
		//RIGHT HAND PLAY
        if (doSomething.closeSwipeRight2() && (lastActionRight != closeSwipeRight2 || rightHandClear))
        {
            if(TrackR->getStatus() == sf::Music::Playing)
                TrackR->pause();
            else
			TrackR->play();
            std::cout << "CLOSE SWIPE RIGHT2" << std::endl;
            lastActionRight = closeSwipeRight2;
            rightHandClear = false;
        }
        
		//LEFT HAND TAP
        if (doSomething.screentap1())
        {
            effect1->setBuffer(*(soundEffects[2]));
            effect1->play();
            std::cout << "HIT DA BASSS!!!!" << std::endl;
            lastActionLeft = screentap1;
            leftHandClear = false;
        }
		//RIGHT HAND TAP
        if (doSomething.screentap2())
        {
            effect2->setBuffer(*(soundEffects[3]));
            effect2->play();
            std::cout << "HIT DA BASSS!!!!" << std::endl;
            lastActionRight = screentap2;
            rightHandClear = false;
        }
        
        if (doSomething.keytappointer2())
        {
            effect3->setBuffer(*(soundEffects[4]));
            effect3->play();
            std::cout << "pointerR" << std::endl;
        }
        if (doSomething.keytapmiddle2())
        {
            effect4->setBuffer(*(soundEffects[5]));
            effect4->play();
            std::cout << "middleR" << std::endl;
        }
        if (doSomething.keytappointer1())
        {
            effect5->setBuffer(*(soundEffects[1]));
            effect5->play();
            std::cout << "pointerL" << std::endl;
        }
        if (doSomething.keytapmiddle1())
        {
            effect6->setBuffer(*(soundEffects[0]));
            effect6->play();
            std::cout << "middleL" << std::endl;
        }
        
        
		}
		HandList hands = frame.hands();
		bool hasleft = false;
		bool hasright = false;
		for (int handindex = 0; handindex < hands.count(); handindex++)
		{
			if (hands[handindex].isRight())
			{
				hasright = true;
			}
			else if (hands[handindex].isLeft())
			{
				hasleft = true;
			}
		}
		if (!hasright)
		{
			rightHandClear = true;
		}
		if (!hasleft)
		{
			leftHandClear = true;
		}
}

void LeapListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void LeapListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void LeapListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();
    
    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void LeapListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void LeapListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {

std::vector <std::string> testingFiles;
std::vector <sf::SoundBuffer*> soundEffects;
testingFiles.push_back("1.ogg");
testingFiles.push_back("2.ogg");
testingFiles.push_back("3.ogg");


    /*sf::SoundBuffer kickbuffer;
    sf::SoundBuffer clapbuffer;
    sf::SoundBuffer crashbuffer;

    kickbuffer.loadFromFile("KICK.wav");
    clapbuffer.loadFromFile("CLAP.wav");
    crashbuffer.loadFromFile("CRASH.wav");

    sf::Sound sound1;
    sound1.setBuffer(kickbuffer);

    sf::Sound sound2;
    sound2.setBuffer(clapbuffer);

    sf::Sound sound3;
    sound3.setBuffer(crashbuffer);*/

//Playlist track number

    sf::SoundBuffer Airhorn;
    Airhorn.loadFromFile("Airhorn.wav");
    soundEffects.push_back(&Airhorn);
    
    sf::SoundBuffer DrumFlam;
    DrumFlam.loadFromFile("DrumFlam.wav");
    soundEffects.push_back(&DrumFlam);
    
    sf::SoundBuffer Scratching;
    Scratching.loadFromFile("Scratching.wav");
    soundEffects.push_back(&Scratching);
    
    sf::SoundBuffer Bass;
    Bass.loadFromFile("Bass.wav");
    soundEffects.push_back(&Bass);
    
    sf::SoundBuffer Hihat;
    Hihat.loadFromFile("Hihat.wav");
    soundEffects.push_back(&Hihat);
    
    sf::SoundBuffer Bam;
    Bam.loadFromFile("Bam.wav");
    soundEffects.push_back(&Bam);
    /*
    sf::SoundBuffer Airhorn;
    Airhorn.loadFromFile("Airhorn.wav");
    soundEffects.push_back(&Airhorn);
    
    sf::SoundBuffer Airhorn;
    Airhorn.loadFromFile("Airhorn.wav");
    soundEffects.push_back(&Airhorn);*/
    
//Opening the music file
    sf::Music* FirstPlayer = new sf::Music();
    sf::Music* SecondPlayer = new sf::Music();
    FirstPlayer->openFromFile(testingFiles.at(0));
    SecondPlayer->openFromFile(testingFiles.at(0));
        //Playing Music
		FirstPlayer->setVolume(50);
		SecondPlayer->setVolume(50);
        //Making sure that the track moves on

    // Create a sample listener and controller
    LeapListener listener(FirstPlayer, SecondPlayer, soundEffects);
    Controller controller;
    
    // Have the sample listener receive events from the controller
    controller.addListener(listener);
    
    if (argc > 1 && strcmp(argv[1], "--bg") == 0)
        controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    
    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    
    // Remove the sample listener when done
    controller.removeListener(listener);
	

    return 0;
}