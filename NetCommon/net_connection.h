#pragma once
#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace net
{
	namespace conn
	{
		template<typename T>
		class Connection : public std::enable_shared_from_this<Connection<T>>
		{
		public:
			Connection()
			{
			}

			virtual ~Connection()
			{
			}
		
		public:
			bool ConnectToServer();
			bool Disconnect();
			bool IsConnected() const;

		public:
			bool Send(const msg::message<T>& msg);

		protected:
			// Each connection has a unique socket to a remote
			asio::ip::tcp::socket m_socket;

			// This context is shared with the whole asio instance
			asio::io_context& m_asioContext;

			// This queue holds all messages to be sent to the remote side
			// of this connection
			ts::tsqueue<msg::message<T>> m_qMessageOut;

			// This queue holds all messages that have been recieved from
			// the remote side of this connection. Note it is a reference
			// as the "owner" of this connection is expected to provide a queue
			ts::tsqueue<msg::owned_message>& m_qMesssagesIn;
		};
	}
}