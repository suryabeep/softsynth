#include "midiInput.h"

#include <iostream>

void callback(double deltatime, std::vector< unsigned char> *message, void *userData)
{
    unsigned int nBytes = message->size();
    if (nBytes < 3)
    {
        return;
    }

    unsigned char statusByte = message->at(0);
    unsigned char byte1 = message->at(1);
    unsigned char byte2 = message->at(2);
    if (statusByte = 0b10010000)
    {
        // note on message
        notes[(int)byte1] = 1.0f;
    }
    else if (statusByte = 0b10000000)
    {
        // note off message
        notes[(int)byte1] = 0.0f;
    }

    for ( unsigned int i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if ( nBytes > 0 )
        std::cout << "stamp = " << deltatime << std::endl;
}

MidiInput::MidiInput()
{
    midiin = 0;

    try {
        // RtMidiIn constructor
        midiin = new RtMidiIn();

        // Call function to select port.
        if ( chooseMidiPort( midiin ) == false )
        {
            if (midiin)
            {
                delete midiin;
            }
            return;
        };

        // Set our callback function.  This should be done immediately after
        // opening the port to avoid having incoming messages written to the
        // queue instead of sent to the callback function.
        midiin->setCallback( callback, this );

        // Don't ignore sysex, timing, or active sensing messages.
        midiin->ignoreTypes( false, false, false );
        
    } catch ( RtMidiError &error ) {
        error.printMessage();
    }
}

MidiInput::~MidiInput()
{
    delete midiin;
}

bool MidiInput::chooseMidiPort( RtMidiIn *rtmidi )
{
  std::string keyHit;
  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No input ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    // for ( i=0; i<nPorts; i++ ) {
    //   portName = rtmidi->getPortName(i);
    //   std::cout << "  Input port #" << i << ": " << portName << '\n';
    // }

    // do {
    //   std::cout << "\nChoose a port number: ";
    //   std::cin >> i;
    // } while ( i >= nPorts );
    // std::getline( std::cin, keyHit );  // used to clear out stdin
    
    // On my machine, the Behringer DeepMind 12 connects to port 1.
    // Just default to that.
    i = 1;
  }

  rtmidi->openPort( i );

  return true;
}