#include "customeevent.h"

QEvent::Type CustomeEvent::type = Type::User;

CustomeEvent::CustomeEvent(CustomeEvent::ID id): QEvent (Type::User)
{
    this->id = id;
}

CustomeEvent::ID CustomeEvent::getId() const
{
    return id;
}
