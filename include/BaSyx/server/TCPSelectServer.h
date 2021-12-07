/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * TCPSelectServer.h
 *
 *      Author: wendel
 */

#ifndef BASYX_SERVER_TCPSELECTSERVER_H
#define BASYX_SERVER_TCPSELECTSERVER_H

#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/vab/provider/native/frame/BaSyxNativeFrameProcessor.h>
#include <BaSyx/log/log.h>

#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

namespace basyx {
namespace vab {
namespace provider {
namespace native {

using socket_t = int;

/**********************************************************************************************/
/* A non-blocking server that is capable to observe real-time properties.                     */
/* To obtain this property the server loops over the ingoing connections,                     */
/* instead of waiting actively.                                                               */
/* This implementation is based on an example given on:                                       */
/* https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzab6/xnonblock.htm               */
/**********************************************************************************************/
class TCPSelectServer
{
public:
  /**********************************************************************************************/
  /* Server Constructor                                                                         */
  /*                                                                                            */
  /* @param backend the backen (normally a model provider)                                      */
  /* @param port the tcp port which should be used for connections                              */
  /* @param timeout_ms Time until the server is closed if no connection comes in.               */
  /* @param listen_backlog defines the number of pending connections until server rejects       */
  /*             incoming connections.                                                          */ 
  /**********************************************************************************************/
  TCPSelectServer(core::IModelProvider * backend, int port,
                  int timeout_ms, int listen_backlog = 32);

  /**********************************************************************************************/
  /* Destructor. Closes all connections.                                                        */
  /**********************************************************************************************/
  ~TCPSelectServer();

  /**********************************************************************************************/
  /* Initializes the server.                                                                    */
  /**********************************************************************************************/
  void Init();

  /**********************************************************************************************/
  /* Needs to be called periodically.                                                           */
  /* Waiting for incoming connections or data of connected sockets.                             */
  /**********************************************************************************************/
  int Update();

  /**********************************************************************************************/
  /* Closes all connections.                                                                    */
  /**********************************************************************************************/
  void Close();

  /**********************************************************************************************/
  /* Currenct server running state.                                                             */
  /**********************************************************************************************/
  bool isRunning();

private:
  void clean_up();

  /*************************************************/
  /* Accept all incoming connections that are      */
  /* queued up on the listening socket before we   */
  /* loop back and call select again.              */
  /*************************************************/
  void accept_incoming_connections();

  /*************************************************/
  /* Receive all incoming data on this socket      */
  /* before we loop back and call select again.    */
  /*************************************************/
  void receive_incoming_data(int fd);

private:
  bool initialized;

  vab::core::IModelProvider* backend;
  std::unique_ptr<vab::provider::native::frame::BaSyxNativeFrameProcessor> frame_processor;
  basyx::log log;

  // Buffers
  static constexpr std::size_t default_buffer_size = 4096;
  std::array<char, default_buffer_size> recv_buffer;
  std::array<char, default_buffer_size> send_buffer;

  //tcp
  int port;
  struct timeval timeout;
  socket_t listen_sd, max_socket;
  int listen_backlog;
  int desc_ready, end_server = 0;
  struct sockaddr_in addr;
  fd_set master_set;
  bool close_connection;
};

}
}
}
}

#endif /* BASYX_SERVER_TCPSELECTSERVER_H */
