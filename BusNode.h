#ifndef BUSNODE_H
#define BUSNODE_H

#include <memory>

#include "Message.h"

class BusNode
{
public:
	virtual void HandleMessage(std::shared_ptr<Message> msg) = 0;

protected:
	void SendMessage(std::shared_ptr<Message> msg);
	
};

#endif // BUSNODE_H
