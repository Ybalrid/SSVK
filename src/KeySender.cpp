#include "KeySender.hpp"

SSVK::KeySender::KeySender() : os(NOT_SET)
{
}

SSVK::KeySender::~KeySender()
{
}

SSVK::OS_type SSVK::KeySender::getOsType() const
{
	return os;
}