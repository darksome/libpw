/*
 * Generated by PWGenPrj
 * Generated at __PWTEMPLATE_DATE__
 */

/*!
 * \file myinstance.cpp
 * \brief Instance.
 */

#include "./mycommon.h"
#include "./mylistener.h"
#include "./centralchannel.h"
#include "./myinstance.h"

MyInstance& INST(MyInstance::s_getInstance());
pw::JobManager& JOBMAN(INST.m_job.man);
pw::Ini& CONF(INST.m_config.conf);
pw::Log& CMDLOG(INST.m_log.cmd);
pw::Log& ERRLOG(INST.m_log.err);


MyInstance::MyInstance(const char* appname) : InstanceInterface(appname)
{
	this->m_test_integer = 0;
	this->m_test_string = "Hello, world!";
}

MyInstance::~MyInstance()
{

}

void MyInstance::eventTimer(int id, void* param)
{
	switch(id)
	{
	case TIMER::ONE_MIN:
	{
		setFlagReload(true);
		break;
	}
	case TIMER::FIVE_MIN:
	{
		break;
	}
	case TIMER::TEN_MIN:
	{
		break;
	}
	case TIMER::ONE_HOUR:
	{
		break;
	}
	case TIMER::ONE_DAY:
	{
		break;
	}
	default:;
	}//switch(id)
}

bool MyInstance::eventConfig(bool isDefault, bool isReload)
{
	//! \todo Load configuration...

	std::string sec = "main";

	do {
	if ( not isReload ) // First call!
	{
		m_test_integer = CONF.getInteger("test.integer", sec, this->m_test_integer);

		/* Add new service here */
		if ( not loadPort(TAG_ADMIN_SSL, sec) ) logError(__FILE__, __LINE__, "failed to load %s.port", TAG_ADMIN_SSL);
	}

	CONF.getString2(m_test_string, "test.string", sec, m_test_string);
	} while (false);

	// Load certs...
	// pw::ssl::context_type::read(CONF, "prefix", "section")
	if ( not m_tls_server.read(CONF, "server", "tls") )
	{
		logError(__FILE__, __LINE__, "failed to load tls settings...");
		return false;
	}

	// Load additional log...
	// this->reloadLog(pw::Log, CONF, PREFIX, TAG, SECTION)
	//if ( not reloadLog(m_log_XXX, CONF, "XXX", "log.XXX", "main") ) { ... }

	return true;
}

bool MyInstance::eventInitLog(void)
{
	//! \todo Initialize log objects...

	return true;
}

bool MyInstance::eventInitChannel(void)
{
	//! \todo Initialize channels...

	do {
	if ( isWorkProcess() ) // Is working process?
	{
		if ( not CentralChannel::s_initialize() )
		{
			PWTRACE("failed to initialize central channel");
			return false;
		}
	}
	} while (false);

	return true;
}

bool MyInstance::eventInitListenerSingle(void)
{
	//! \todo Initialize listener for single...

	PWTRACE("%s %d", __func__, int(::getpid()));
	if ( not openListenerSingle<ServiceListener>("svc") ) return false;
	if ( not openListenerSingle<AdminListener>("admin") ) return false;
	if ( not openListenerSingle<AdminListener>(TAG_ADMIN_SSL) ) return false;
	/* Add new service here */

	return true;
}

bool MyInstance::eventInitListenerParent(void)
{
	//! \todo Initialize listener for parent...

	PWTRACE("%s %d", __func__, int(::getpid()));
	if ( not this->openListenerParent<pw::ListenerInterface::LT_SERVICE>("svc") ) return false;
	if ( not this->openListenerParent<pw::ListenerInterface::LT_ADMIN>("admin") ) return false;
	if ( not this->openListenerParent<pw::ListenerInterface::LT_ADMIN_SSL>(TAG_ADMIN_SSL) ) return false;
	/* Add new service here */

	return true;
}

bool MyInstance::eventInitListenerChild(void)
{
	//! \brief Initialize listener for children...

	PWTRACE("%s %d", __func__, int(::getpid()));
	return this->openListenerChild<ChildListener>(lsnr_names{
			"svc",
			"admin",
			TAG_ADMIN_SSL,
			/* Add new service here */
			});
}

bool MyInstance::eventInitTimer(void)
{
	//! \todo Initialize timer events...

	pw::TimerAdd(this, TIMER::ONE_MIN, 60LL*1000LL);
	pw::TimerAdd(this, TIMER::FIVE_MIN, 5LL*60LL*1000LL);
	pw::TimerAdd(this, TIMER::TEN_MIN, 10LL*60LL*1000LL);
	pw::TimerAdd(this, TIMER::ONE_HOUR, 60LL*60LL*1000LL);
	pw::TimerAdd(this, TIMER::ONE_DAY, 24LL*60LL*60LL*1000LL);
	/* Add new timer events here */

	return true;
}

void MyInstance::eventForkCleanUpChannel(size_t index, void* param)
{
	//! \todo Cleanup channels for fork...

	do {
	CentralChannel::s_destroy();
	} while (false);
}
