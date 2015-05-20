/*
 * Generated by PWGenPrj
 * Generated at __PWTEMPLATE_DATE__
 */

/*!
 * \file servicechannel.h
 * \brief Service channel logic
 */

#ifndef SERVICECHANNEL_H
#define SERVICECHANNEL_H

class ServiceChannel final : public pw::MsgChannel
{
public:
	using pw::MsgChannel::MsgChannel;
	inline virtual ~ServiceChannel() {}

private:
	void eventReadPacket(const pw::PacketInterface& pk, const char*, size_t) override;

public:
	using proc_ptr_t = void (ServiceChannel::*)(const pw::MsgPacket& pk);
	
	void procTEST(const pw::MsgPacket& pk);
};

#endif // SERVICECHANNEL_H