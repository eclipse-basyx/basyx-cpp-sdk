/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SERVER_TCPSERVER_H
#define BASYX_SERVER_TCPSERVER_H

#include <atomic>
#include <iostream>
#include <vector>

#include <BaSyx/log/log.h>

#include <asio.hpp>
#include <asio/read.hpp>

#include <BaSyx/server/BaSyxNativeProvider.h>
#include <BaSyx/vab/provider/native/frame/BaSyxNativeFrameProcessor.h>

namespace basyx {
namespace server {

template<typename Backend>
class NativeConnection : public std::enable_shared_from_this<NativeConnection<Backend>>
{
public:
	using ptr_t = std::shared_ptr<NativeConnection>;
private:
	vab::provider::native::frame::BaSyxNativeFrameProcessor processor;
	asio::ip::tcp::socket socket_;

	static constexpr std::size_t default_buffer_size = 8192;
	std::array<char, default_buffer_size> recv_buffer;
	std::array<char, default_buffer_size> send_buffer;

	uint32_t received_frame_window_size;
	std::vector<uint8_t> data;
public:
	void process_frame()
	{
		using namespace basyx::vab::connector::native;

		auto frame = Frame::read_from_buffer(data);
		auto output_frame = processor.processInputFrame(frame);

		data.resize(output_frame.size() + BASYX_FRAMESIZE_SIZE);

		auto buffer_view = basyx::net::make_buffer(&data[BASYX_FRAMESIZE_SIZE], output_frame.size());
		Frame::write_to_buffer(
			buffer_view,
			output_frame
		);

		auto size_field = reinterpret_cast<uint32_t*>(&data[0]);
		*size_field = static_cast<uint32_t>(output_frame.size());

		auto transfer_size = data.size();
		auto shared_this = this->shared_from_this();
		asio::async_write(socket_, asio::buffer(data, transfer_size),
			[shared_this, transfer_size](asio::error_code error, std::size_t bytes_transferred) {
			if (error || bytes_transferred != transfer_size) {
				shared_this->close();
			}
			else {
				shared_this->run();
			}
		});
	};

	void close()
	{
		this->socket_.close();
	};

	void read_frame()
	{
		data.resize(received_frame_window_size);

		auto shared_this = this->shared_from_this();
		asio::async_read(socket_, asio::buffer(data),
			[shared_this](asio::error_code error, std::size_t bytes_read) {
			if (!error) {
				shared_this->process_frame();
			};
		});
	};
public:
	NativeConnection(asio::io_context & io_context, Backend * backend)
		: socket_(io_context)
		, processor(backend)
		, data(4, 0)
	{
	};

	asio::ip::tcp::socket & socket() { return this->socket_; }

	void run()
	{
		auto shared_this = this->shared_from_this();
		asio::async_read(socket_, asio::buffer((char*)&received_frame_window_size, sizeof(received_frame_window_size)), 
			[shared_this](asio::error_code error, std::size_t bytes_read) {
			if (!error) {
				shared_this->read_frame();
			};
		});
	};
};


template <typename Backend>
class TCPServer {
public:
    using socket_ptr_t = std::unique_ptr<asio::ip::tcp::socket>;
	using connection_t = NativeConnection<Backend>;
	using connection_ptr_t = typename connection_t::ptr_t;
private:
    Backend* backend;

    asio::io_context io_context;
	asio::executor_work_guard<asio::io_context::executor_type> work_guard;
	asio::ip::tcp::acceptor acceptor;

    basyx::log log;
public:
    TCPServer(Backend* backend, int port)
        : backend { backend }
        , io_context { 2 }
		, work_guard{ asio::make_work_guard(io_context) }
        , acceptor { io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port) }
        , log { "TCPServer" }
    {
        log.info("Creating server on port {}", port);
        acceptor.listen();
        log.trace("Acceptor open");
    }

    void run()
    {
		log.info("Starting server");

		asio::dispatch(this->acceptor.get_executor(), [this]() {
			this->start_accept();
		});

		this->io_context.run();
    };

    void stop()
    {
		this->acceptor.close();
		this->work_guard.reset();
		this->io_context.stop();
	};

    void start_accept()
    {
		log.info("Waiting for new connections...");
		asio::error_code ec;

		auto connection = std::make_shared<connection_t>(this->io_context, this->backend);

		acceptor.async_accept(connection->socket(), 
			[this, connection](const asio::error_code error) {
				this->handle_accept(error, std::move(connection));
		});
    };

    void handle_accept(const asio::error_code error, connection_ptr_t connection)
    {
		log.trace("Entering handle_accept()");

        if (!error) {
            log.info("Incoming new connection");

			asio::dispatch(this->io_context, [connection]() {
				connection->run();
			});
			start_accept();
        } else {
            //sockets.pop_back();
			log.warn("Client socket closed.");
        }
    };

    void Close()
    {
        log.trace("Closing...");

        if (!isRunning())
            return;

		this->stop();
    }

    ~TCPServer()
    {
        this->Close();
    }

    bool isRunning()
    {
        return !io_context.stopped();
    }
};
};
};

#endif /* BASYX_SERVER_TCPSERVER_H */