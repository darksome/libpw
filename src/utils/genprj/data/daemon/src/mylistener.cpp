/*
 * Generated by PWGenPrj
 * Generated at __PWTEMPLATE_DATE__
 */

/*!
 * \file mylistener.cpp
 * \brief Listeners
 */

#include "./mycommon.h"
#include "./mylistener.h"
#include "./adminchannel.h"
#include "./servicechannel.h"

//------------------------------------------------------------------------
// Service Listener
bool ServiceListener::eventAccept(const accept_type& param)
{
	pw::chif_create_type cparam;
	cparam.fd = param.fd;
	cparam.poller = getIoPoller();
	cparam.ssl = param.ssl;
	ServiceChannel* ch(new ServiceChannel(cparam));
	return nullptr not_eq ch;
}

//------------------------------------------------------------------------
// Admin Listener
bool AdminListener::eventAccept(const accept_type& param)
{
	pw::chif_create_type cparam;
	cparam.fd = param.fd;
	cparam.poller = getIoPoller();
	cparam.ssl = param.ssl;
	AdminChannel* ch(new AdminChannel(cparam));
	return nullptr not_eq ch;
}

//------------------------------------------------------------------------
// Child Listener
bool ChildListener::eventAccept(const accept_type& param)
{
	pw::chif_create_type cparam;
	cparam.fd = param.fd;
	cparam.poller = getIoPoller();
	cparam.ssl = param.ssl;

	pw::ChannelInterface* ch(nullptr);

	if ( param.type == LT_SERVICE ) ch = new ServiceChannel(cparam);
	else if ( param.type == LT_ADMIN ) ch = new AdminChannel(cparam);

	return ch not_eq nullptr;
}