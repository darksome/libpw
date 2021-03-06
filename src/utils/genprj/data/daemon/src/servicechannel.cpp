/*
 * Generated by PWGenPrj
 * Generated at __PWTEMPLATE_DATE__
 */

/*!
 * \file servicechannel.cpp
 * \brief Service channel logic
 */

#include "./mycommon.h"
#include "./servicechannel.h"
#include "./myjob.h"

static const std::map<pw::KeyCode, ServiceChannel::proc_ptr_t> s_handler = {
	{"TEST", &ServiceChannel::procTEST},
	// Add new command here!
};

void ServiceChannel::eventReadPacket(const pw::PacketInterface& pk, const char*, size_t)
{
	auto& msgpk(dynamic_cast<const pw::MsgPacket&>(pk));
	auto ib(s_handler.find(msgpk.m_code));
	if ( ib not_eq s_handler.end() )
	{
		auto method(ib->second);
		(*this.*method)(msgpk);
	}
	else eventError(Error::INVALID_PACKET, 0);
}

void ServiceChannel::procTEST(const pw::MsgPacket& pk)
{
	auto job(HttpDemoJob::s_run(*this, nullptr));
}
