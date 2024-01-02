#pragma once

/****************************************************
 * 功能：使用WebSocketpp控制联机，作为客户端
 * 作者：牟泳祯
 * 时间：2023年12月23日
 * 说明：以下代码中的websocketpp相关头文件来自WebSocketpp开源库，链接https://github.com/zaphoyd/websocketpp
  *       实现框架参考websocketpp说明文档，链接https://docs.websocketpp.org/
  *       根据项目需要进行改动，并添加了自己的方法
 * **************************************************
 * CopyRight 2023 by 牟泳祯
 * **************************************************/

 /*
  * Copyright (c) 2014, Peter Thorson. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *     * Redistributions of source code must retain the above copyright
  *       notice, this list of conditions and the following disclaimer.
  *     * Redistributions in binary form must reproduce the above copyright
  *       notice, this list of conditions and the following disclaimer in the
  *       documentation and/or other materials provided with the distribution.
  *     * Neither the name of the WebSocket++ Project nor the
  *       names of its contributors may be used to endorse or promote products
  *       derived from this software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

  // **NOTE:** This file is a snapshot of the WebSocket++ utility client tutorial.
  // Additional related material can be found in the tutorials/utility_client
  // directory of the WebSocket++ repository.

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <condition_variable>
#include <mutex>

typedef websocketpp::client<websocketpp::config::asio_client> client;

struct HeroInfo {
	int _id;
	int _level;
	int _x;
	int _y;
	HeroInfo(int id, int level, int x, int y) :_id(id), _level(level), _x(x), _y(y) {};
};
class connection_metadata {
public:
	typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

	connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
		: m_id(id)
		, m_hdl(hdl)
		, m_status("Connecting")
		, m_uri(uri)
		, m_server("N/A")
	{}

	void on_open(client* c, websocketpp::connection_hdl hdl) {
		m_status = "Open";

		client::connection_ptr con = c->get_con_from_hdl(hdl);
		m_server = con->get_response_header("Server");
	}

	void on_fail(client* c, websocketpp::connection_hdl hdl) {
		m_status = "Failed";

		client::connection_ptr con = c->get_con_from_hdl(hdl);
		m_server = con->get_response_header("Server");
		m_error_reason = con->get_ec().message();
	}

	void on_close(client* c, websocketpp::connection_hdl hdl) {
		m_status = "Closed";
		client::connection_ptr con = c->get_con_from_hdl(hdl);
		std::stringstream s;
		s << "close code: " << con->get_remote_close_code() << " ("
			<< websocketpp::close::status::get_string(con->get_remote_close_code())
			<< "), close reason: " << con->get_remote_close_reason();
		m_error_reason = s.str();
	}

	// 收到来自服务器的消息
	void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
		if (msg->get_opcode() == websocketpp::frame::opcode::text) {
			m_messages.push_back("<< " + msg->get_payload());
		}
		else {
			m_messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));
		}
		std::string current_message = m_messages.back();

	}

	websocketpp::connection_hdl get_hdl() const {
		return m_hdl;
	}

	int get_id() const {
		return m_id;
	}

	std::string get_status() const {
		return m_status;
	}

	void record_sent_message(std::string message) {
		m_messages.push_back(">> " + message);
	}

	//inline friend std::ostream& operator<< (std::ostream& out, connection_metadata const& data);
	std::vector<std::string> m_messages;
	std::list<int> hero_list;
	std::vector<HeroInfo> enemyHeroInfo;

private:
	int m_id;
	websocketpp::connection_hdl m_hdl;
	std::string m_status;
	std::string m_uri;
	std::string m_server;
	std::string m_error_reason;
	
};



//inline std::ostream& operator<< (std::ostream& out, connection_metadata& data);







class websocket_endpoint {
public:
	websocket_endpoint() : m_next_id(0) {
		m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
		m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

		m_endpoint.init_asio();
		m_endpoint.start_perpetual();

		m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);
	}

	~websocket_endpoint() {
		m_endpoint.stop_perpetual();

		for (con_list::const_iterator it = m_connection_list.begin(); it != m_connection_list.end(); ++it) {
			if (it->second->get_status() != "Open") {
				// Only close open connections
				continue;
			}

			std::cout << "> Closing connection " << it->second->get_id() << std::endl;

			websocketpp::lib::error_code ec;
			m_endpoint.close(it->second->get_hdl(), websocketpp::close::status::going_away, "", ec);
			if (ec) {
				std::cout << "> Error closing connection " << it->second->get_id() << ": "
					<< ec.message() << std::endl;
			}
		}

		m_thread->join();
	}

	int connect(std::string const& uri) {
		websocketpp::lib::error_code ec;
		client::connection_ptr con = m_endpoint.get_connection(uri, ec);

		if (ec) {
			std::cout << "> Connect initialization error: " << ec.message() << std::endl;
			return -1;
		}

		int new_id = m_next_id++;
		connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(new_id, con->get_handle(), uri);
		m_connection_list[new_id] = metadata_ptr;

		con->set_open_handler(websocketpp::lib::bind(
			&connection_metadata::on_open,
			metadata_ptr,
			&m_endpoint,
			websocketpp::lib::placeholders::_1
		));
		con->set_fail_handler(websocketpp::lib::bind(
			&connection_metadata::on_fail,
			metadata_ptr,
			&m_endpoint,
			websocketpp::lib::placeholders::_1
		));
		con->set_close_handler(websocketpp::lib::bind(
			&connection_metadata::on_close,
			metadata_ptr,
			&m_endpoint,
			websocketpp::lib::placeholders::_1
		));
		con->set_message_handler(websocketpp::lib::bind(
			&connection_metadata::on_message,
			metadata_ptr,
			websocketpp::lib::placeholders::_1,
			websocketpp::lib::placeholders::_2
		));

		m_endpoint.connect(con);

		return new_id;
	}

	void close(int id, websocketpp::close::status::value code, std::string reason) {
		websocketpp::lib::error_code ec;

		con_list::iterator metadata_it = m_connection_list.find(id);
		if (metadata_it == m_connection_list.end()) {
			std::cout << "> No connection found with id " << id << std::endl;
			return;
		}

		m_endpoint.close(metadata_it->second->get_hdl(), code, reason, ec);
		if (ec) {
			std::cout << "> Error initiating close: " << ec.message() << std::endl;
		}
	}

	// 向服务器发送消息
	void send(int id, std::string message) {
		websocketpp::lib::error_code ec;

		con_list::iterator metadata_it = m_connection_list.find(id);
		if (metadata_it == m_connection_list.end()) {
			std::cout << "> No connection found with id " << id << std::endl;
			return;
		}

		m_endpoint.send(metadata_it->second->get_hdl(), message, websocketpp::frame::opcode::text, ec);
		if (ec) {
			std::cout << "> Error sending message: " << ec.message() << std::endl;
			return;
		}

		metadata_it->second->record_sent_message(message);
	}



	connection_metadata::ptr get_metadata(int id) const {
		con_list::const_iterator metadata_it = m_connection_list.find(id);
		if (metadata_it == m_connection_list.end()) {
			return connection_metadata::ptr();
		}
		else {
			return metadata_it->second;
		}
	}

	void waitEnemyConnection(connection_metadata const& data) {
		while (!data.m_messages.empty() && data.m_messages.back() != "<< Connections All Done")
			;
	}
	void waitEnemySelectOver(connection_metadata const& data) {
		//std::unique_lock<std::mutex> lock(m_mutex);

		//m_cv.wait(lock, [&data] { return !data.m_messages.empty(); });

		while (!data.m_messages.empty() && data.m_messages.back() != "<< Select Over") {
			;
			//m_cv.wait(lock);
			//Sleep(100);
		}
		// 处理完消息后通知等待的线程
		//m_cv.notify_all();
	}

	void dealReceicedMessage(connection_metadata const & data, std::vector<HeroInfo>& info) {
		//waitEnemySelectOver(data);
		//m_cv.notify_all();
		std::vector<std::string>::const_iterator it;
		for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it) {
			const std::string myString = *it;
			//assert(false);
			const std::string dst = "up";
			const std::string tag = "<<";
			const std::string newGame = "new game";
			// 新回合
			//if (myString.find(newGame) != -1)
				//data.enemyHeroInfo.clear();
			// 敌方上场英雄
			if (myString.find(dst) != -1 && myString.find(tag) != -1) {
				//assert(false);
				std::istringstream iss(myString);

				std::string token;
				try {
					while (iss >> token) {
						if (token == "up") {
							int num1 = 0, num2 = 1;
							float num3 = 2, num4 = 3;

							// 依次读取三个数字
							if(iss >> num1 >> num2 >> num3 >> num4)
							{
								//data.enemyHeroInfo.emplace_back(HeroInfo(num1, num2, num3, num4));
								info.emplace_back(HeroInfo(num1, num2, num3, num4));
							}
							else{
								// 如果无法成功读取三个数字，则抛出异常
								throw std::runtime_error("Error: Unable to parse numbers after 'up'");
							}
						}
					}
				}
				catch (const std::exception& e) {
					// 捕获并处理异常
					std::cerr << e.what() << std::endl;
				}
			}
		}
		//return data.enemyHeroInfo;

	}



private:
	typedef std::map<int, connection_metadata::ptr> con_list;

	client m_endpoint;
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

	con_list m_connection_list;
	int m_next_id;
	std::condition_variable m_cv;
	std::mutex m_mutex;
};
/*
int main() {
	bool done = false;
	std::string input;
	websocket_endpoint endpoint;

	while (!done) {
		std::cout << "Enter Command: ";
		std::getline(std::cin, input);

		if (input == "quit") {
			done = true;
		}
		else if (input == "help") {
			std::cout
				<< "\nCommand List:\n"
				<< "connect <ws uri>\n"
				<< "send <connection id> <message>\n"
				<< "close <connection id> [<close code:default=1000>] [<close reason>]\n"
				<< "show <connection id>\n"
				<< "help: Display this help text\n"
				<< "quit: Exit the program\n"
				<< std::endl;
		}
		else if (input.substr(0, 7) == "connect") {
			int id = endpoint.connect(input.substr(8));
			if (id != -1) {
				std::cout << "> Created connection with id " << id << std::endl;
			}
		}
		else if (input.substr(0, 4) == "send") {
			std::stringstream ss(input);

			std::string cmd;
			int id;
			std::string message;

			ss >> cmd >> id;
			std::getline(ss, message);

			endpoint.send(id, message);
		}
		else if (input.substr(0, 5) == "close") {
			std::stringstream ss(input);

			std::string cmd;
			int id;
			int close_code = websocketpp::close::status::normal;
			std::string reason;

			ss >> cmd >> id >> close_code;
			std::getline(ss, reason);

			endpoint.close(id, close_code, reason);
		}
		else if (input.substr(0, 4) == "show") {
			int id = atoi(input.substr(5).c_str());

			connection_metadata::ptr metadata = endpoint.get_metadata(id);
			if (metadata) {
				//std::cout << *metadata << std::endl;
				endpoint.dealReceicedMessage(*metadata);
			}
			else {
				std::cout << "> Unknown connection id " << id << std::endl;
			}
		}
		else {
			std::cout << "> Unrecognized Command" << std::endl;
		}
	}

	return 0;
}
*/
/*

clang++ -std=c++11 -stdlib=libc++ -I/Users/zaphoyd/software/websocketpp/ -I/Users/zaphoyd/software/boost_1_55_0/ -D_WEBSOCKETPP_CPP11_STL_ step4.cpp /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_system.a

clang++ -I/Users/zaphoyd/software/websocketpp/ -I/Users/zaphoyd/software/boost_1_55_0/ step4.cpp /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_system.a /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_thread.a /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_random.a

clang++ -std=c++11 -stdlib=libc++ -I/Users/zaphoyd/Documents/websocketpp/ -I/Users/zaphoyd/Documents/boost_1_53_0_libcpp/ -D_WEBSOCKETPP_CPP11_STL_ step4.cpp /Users/zaphoyd/Documents/boost_1_53_0_libcpp/stage/lib/libboost_system.a

*/