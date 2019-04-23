// This an abstract class meant to represent an event.
// The base class effectively does nothing, but does provide
// a mechansim to get a string event type.
// $Revision: 1.1 $
//   $Log: event.h,v $
//   Revision 1.1  2017/02/12 18:13:24  root
//   Initial revision
//
#ifndef EVENT_H
#define EVENT_H
#include<string>
class Event
{
public:
    virtual std::string type()=0;
};
#endif
