#include "library.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

void Library::Register(SOURCE id)
{
    this->source = id;
}
