/*
 * Copyright (c) 2014, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TEST_COMPONENTS_PROTOCOL_HANDLER_INCLUDE_PROTOCOL_HANDLER_PROTOCOL_HANDLER_TM_TEST_H_
#define TEST_COMPONENTS_PROTOCOL_HANDLER_INCLUDE_PROTOCOL_HANDLER_PROTOCOL_HANDLER_TM_TEST_H_
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "utils/shared_ptr.h"

#include "protocol_handler/protocol_handler_impl.h"
#include "protocol/common.h"

#include "protocol_handler/protocol_handler_mock.h"
#include "protocol_handler/protocol_observer_mock.h"
#include "protocol_handler/session_observer_mock.h"
#include "protocol_handler/control_message_matcher.h"
#include "security_manager/security_manager_mock.h"
#include "security_manager/ssl_context_mock.h"
#include "transport_manager/transport_manager_mock.h"
#include "protocol_handler/control_message_matcher.h"

namespace test {
namespace components {
namespace protocol_handler_test {

// id passed as NULL for new session establishing
#define NEW_SESSION_ID        0u
#define SESSION_START_REJECT  0u

using namespace ::protocol_handler;
using namespace ::transport_manager;  // For TM states
//using namespace ::security_manager;
using ::transport_manager::TransportManagerListener;
using protocol_handler_test::ControlMessage;
using ::testing::Return;
using ::testing::ReturnNull;
using ::testing::AnyOf;
using ::testing::Ge;
using ::testing::Le;
using ::testing::_;
using ::testing::Invoke;

class ProtocolHandlerImplTest : public ::testing::Test {
 protected:
  void IntitProtocolHandlerImpl(const size_t period_msec, const size_t max_messages) {
    protocol_handler_impl.reset(new ProtocolHandlerImpl(&transport_manager_mock,
                                                        period_msec, max_messages));
    protocol_handler_impl->set_session_observer(&session_observer_mock);
    tm_listener = protocol_handler_impl.get();
  }
  void SetUp() OVERRIDE {
    IntitProtocolHandlerImpl(0u, 0u);
    connection_id = 0xAu;
    session_id = 0xFFu;
    connection_key = 0xFF00AAu;
    message_id = 0xABCDEFu;
    some_date.resize(256, 0xAB);

    // expect ConnectionHandler support methods call (conversion, check heartbeat)
    EXPECT_CALL(session_observer_mock,
                KeyFromPair(connection_id, _)).
        //return some connection_key
        WillRepeatedly(Return(connection_key));
    EXPECT_CALL(session_observer_mock,
                IsHeartBeatSupported(connection_id, _)).
        //return false to avoid call KeepConnectionAlive
        WillRepeatedly(Return(false));
  }

  void TearDown() OVERRIDE {
    // Wait call methods in thread
    usleep(100000);
  }

  // Emulate connection establish
  void AddConnection() {
    tm_listener->OnConnectionEstablished(
          DeviceInfo(DeviceHandle(1u),
                     std::string("mac"),
                     std::string("name"),
                     std::string("BTMAC")),
          connection_id);
  }
  void AddSession() {
    AddConnection();
    const ServiceType start_service = kRpc;
  #ifdef ENABLE_SECURITY
    // For enabled protection callback shall use protection ON
    const bool callback_protection_flag = PROTECTION_ON;
  #else
    // For disabled protection callback shall ignore protection income flad and use protection OFF
    const bool callback_protection_flag  = PROTECTION_OFF;
  #endif  // ENABLE_SECURITY
    // expect ConnectionHandler check
    EXPECT_CALL(session_observer_mock,
                OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service,
                                         callback_protection_flag, _)).
        //return sessions start success
        WillOnce(Return(session_id));

    // expect send Ack with PROTECTION_OFF (on no Security Manager)
    EXPECT_CALL(transport_manager_mock,
                SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
        WillOnce(Return(E_SUCCESS));

    SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  }

#ifdef ENABLE_SECURITY
  // Emulate security manager initilization establish
  void AddSecurityManager() {
    protocol_handler_impl->set_security_manager(&security_manager_mock);
  }
#endif  // ENABLE_SECURITY
  void SendTMMessage(uint8_t connection_id,
                     uint8_t version, bool protection, uint8_t frameType,
                     uint8_t serviceType, uint8_t frameData,
                     uint8_t sessionId, uint32_t dataSize,
                     uint32_t messageID, const uint8_t *data = 0) {
    // Create packet
    const ProtocolPacket packet(
          connection_id, version, protection, frameType,
          serviceType, frameData, sessionId, dataSize,
          messageID, data);
    // Emulate resive packet from transoprt manager
    tm_listener->OnTMMessageReceived(packet.serializePacket());
  }
  void SendControlMessage(bool protection, uint8_t service_type,
                          uint8_t sessionId, uint32_t frame_data,
                          uint32_t dataSize = 0u, const uint8_t *data = NULL) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, protection, FRAME_TYPE_CONTROL,
                  service_type, frame_data, sessionId, dataSize, message_id, data);
  }

  ::utils::SharedPtr<ProtocolHandlerImpl> protocol_handler_impl;
  TransportManagerListener* tm_listener;
  // Uniq connection
  ::transport_manager::ConnectionUID connection_id;
  // id of established session
  uint8_t session_id;
  // uniq id as connection_id and session_id in one
  uint32_t connection_key;
  uint32_t message_id;
  std::vector<uint8_t> some_date;
  // Strict mocks (same as all methods EXPECT_CALL().Times(0))
  testing::StrictMock<transport_manager_test::TransportManagerMock> transport_manager_mock;
  testing::StrictMock<protocol_handler_test::SessionObserverMock>   session_observer_mock;
#ifdef ENABLE_SECURITY
  testing::NiceMock<security_manager_test::SecurityManagerMock>     security_manager_mock;
  testing::NiceMock<security_manager_test::SSLContextMock>          ssl_context_mock;
#endif  // ENABLE_SECURITY
};

#ifdef ENABLE_SECURITY
class OnHandshakeDoneFunctor {
public:
  OnHandshakeDoneFunctor(const uint32_t connection_key, const bool result)
    : connection_key(connection_key), result(result) {}
  void operator()(security_manager::SecurityManagerListener * listener) const {
    listener->OnHandshakeDone(connection_key, result);
  }
private:
  const uint32_t connection_key;
  const bool result;
};
#endif  // ENABLE_SECURITY

/*
 * ProtocolHandler shall skip empty message
 */
TEST_F(ProtocolHandlerImplTest, RecieveEmptyRawMessage) {
  tm_listener->OnTMMessageReceived(RawMessagePtr());
}
/*
 * ProtocolHandler shall disconnect on no connection
 */
TEST_F(ProtocolHandlerImplTest, RecieveOnUnknownConenction) {
  // expect force dicsonnect on no connection for received data
  EXPECT_CALL(transport_manager_mock,
              DisconnectForce(connection_id)).
      WillOnce(Return(E_SUCCESS));

  SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_CONTROL,
                kRpc, FRAME_DATA_START_SERVICE, NEW_SESSION_ID, 0, message_id);
}
/*
 * ProtocolHandler shall send NAck on session_observer rejection
 * Check protection flag OFF for all services from kControl to kBulk
 */
TEST_F(ProtocolHandlerImplTest, StartSession_Unprotected_SessionObserverReject) {
  const int call_times = 5;
  AddConnection();
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(
                connection_id, NEW_SESSION_ID, AnyOf(kControl, kRpc, kAudio,
                                                     kMobileNav, kBulk), PROTECTION_OFF, _)).
      Times(call_times).
      //return sessions start rejection
      WillRepeatedly(Return(SESSION_START_REJECT));

  // expect send NAck
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_NACK, PROTECTION_OFF))).
      Times(call_times).
      WillRepeatedly(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_OFF, kControl,  NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_OFF, kRpc,      NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_OFF, kAudio,    NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_OFF, kMobileNav,NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_OFF, kBulk,     NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send NAck on session_observer rejection
 * Emulate getting PROTECTION_ON and check protection flag OFF in NAck
 * For ENABLE_SECURITY=OFF session_observer shall be called with protection flag OFF
 */
TEST_F(ProtocolHandlerImplTest, StartSession_Protected_SessionObserverReject) {
  const int call_times = 5;
  AddConnection();
#ifdef ENABLE_SECURITY
  // For enabled protection callback shall use protection ON
  const bool callback_protection_flag  = PROTECTION_ON;
#else
  // For disabled protection callback shall ignore protection income flad and use protection OFF
  const bool callback_protection_flag  = PROTECTION_OFF;
#endif  // ENABLE_SECURITY
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(
                connection_id, NEW_SESSION_ID, AnyOf(kControl, kRpc, kAudio,
                                                     kMobileNav, kBulk),  callback_protection_flag, _)).
      Times(call_times).
      //return sessions start rejection
      WillRepeatedly(Return(SESSION_START_REJECT));

  // expect send NAck with encryption OFF
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_NACK, PROTECTION_OFF))).
      Times(call_times).
      WillRepeatedly(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, kControl,  NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_ON, kRpc,      NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_ON, kAudio,    NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_ON, kMobileNav,NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
  SendControlMessage(PROTECTION_ON, kBulk,     NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack on session_observer accept
 * Check protection flag OFF
 */
TEST_F(ProtocolHandlerImplTest, StartSession_Unprotected_SessionObserverAccept) {
  AddConnection();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_OFF, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // expect send Ack
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_OFF, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack on session_observer accept
 * Emulate getting PROTECTION_ON and check protection flag OFF in Ack
 * For ENABLE_SECURITY=OFF session_observer shall be called with protection flag OFF
 */
TEST_F(ProtocolHandlerImplTest, StartSession_Protected_SessionObserverAccept) {
  AddSession();
}
// TODO(EZamakhov): add test for get_hash_id/set_hash_id from protocol_handler_impl.cc
/*
 * ProtocolHandler shall send NAck on session_observer rejection
 */
TEST_F(ProtocolHandlerImplTest, EndSession_SessionObserverReject) {
  AddSession();
  const ServiceType service = kRpc;

  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionEndedCallback(connection_id, session_id, _, service)).
      // reject session start
      WillOnce(Return(SESSION_START_REJECT));

  // expect send NAck
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_END_SERVICE_NACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_OFF, service, session_id, FRAME_DATA_END_SERVICE);
}
/*
 * ProtocolHandler shall send NAck on wrong hash code
 */
TEST_F(ProtocolHandlerImplTest, EndSession_Success) {
  AddSession();
  const ServiceType service = kRpc;

  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionEndedCallback(connection_id, session_id, _, service)).
      // return sessions start success
      WillOnce(Return(connection_key));

  // expect send Ack
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_END_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_OFF, service, session_id, FRAME_DATA_END_SERVICE);
}

#ifdef ENABLE_SECURITY
/*
 * ProtocolHandler shall not call Security logics with Protocol version 1
 * Check session_observer with PROTECTION_OFF and Ack with PROTECTION_OFF
 */
TEST_F(ProtocolHandlerImplTest, SecurityEnable_StartSessionProtocoloV1) {
  AddConnection();
  // Add security manager
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_OFF, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // expect send Ack with PROTECTION_OFF (on no Security Manager)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendTMMessage(connection_id, PROTOCOL_VERSION_1, PROTECTION_ON, FRAME_TYPE_CONTROL,
                start_service, FRAME_DATA_START_SERVICE, NEW_SESSION_ID, 0, message_id);
}
/*
 * ProtocolHandler shall not call Security logics on start session with PROTECTION_OFF
 */
TEST_F(ProtocolHandlerImplTest, SecurityEnable_StartSessionUnprotected) {
  AddConnection();
  // Add security manager
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_OFF, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // expect send Ack with PROTECTION_OFF (on no Security Manager)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_OFF, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_OFF on fail SLL creation
 */
TEST_F(ProtocolHandlerImplTest, SecurityEnable_StartSessionProtected_Fail) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // expect start protection for unprotected session
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return fail protection
      WillOnce(ReturnNull());

  // expect send Ack with PROTECTION_OFF (on fail SLL creation)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_ON on already established and initialized SLLContext
 */
TEST_F(ProtocolHandlerImplTest,SecurityEnable_StartSessionProtected_SSLInitialized) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // call new SSLContext creation
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return new SSLContext
      WillOnce(Return(&ssl_context_mock));

  // initilization check
  EXPECT_CALL(ssl_context_mock,
              IsInitCompleted()).
      //emulate SSL is initilized
      WillOnce(Return(true));

  // Expect service protection enable
  EXPECT_CALL(session_observer_mock,
              SetProtectionFlag(connection_key, start_service));

  // expect send Ack with PROTECTION_ON (on SSL is initilized)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_ON))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_OFF on session handshhake fail
 */
TEST_F(ProtocolHandlerImplTest, SecurityEnable_StartSessionProtected_HandshakeFail) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // call new SSLContext creation
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return new SSLContext
      WillOnce(Return(&ssl_context_mock));

  // initilization check
  EXPECT_CALL(ssl_context_mock,
              IsInitCompleted()).
      //emulate SSL is not initilized
      WillOnce(Return(false));

  // Pending handshake check
  EXPECT_CALL(ssl_context_mock,
              IsHandshakePending()).
      //emulate is pending
      WillOnce(Return(true));

  // expect add listener for handshake result
  EXPECT_CALL(security_manager_mock,
              AddListener(_))
      // emulate handshake fail
      .WillOnce(Invoke(OnHandshakeDoneFunctor(connection_key, PROTECTION_OFF)));

  // Listener check SSLContext
  EXPECT_CALL(session_observer_mock,
              GetSSLContext(connection_key, start_service)).
      // emulate protection for service is not enabled
      WillOnce(ReturnNull());

  // expect send Ack with PROTECTION_OFF (on fail handshake)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_OFF))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_ON on session handshhake success
 */
TEST_F(ProtocolHandlerImplTest, SecurityEnable_StartSessionProtected_HandshakeSuccess) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // call new SSLContext creation
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return new SSLContext
      WillOnce(Return(&ssl_context_mock));

  // initilization check
  EXPECT_CALL(ssl_context_mock,
              IsInitCompleted()).
      //emulate SSL is not initilized
      WillOnce(Return(false));

  // Pending handshake check
  EXPECT_CALL(ssl_context_mock,
              IsHandshakePending()).
      //emulate is pending
      WillOnce(Return(true));

  // expect add listener for handshake result
  EXPECT_CALL(security_manager_mock,
              AddListener(_))
      // emulate handshake fail
      .WillOnce(Invoke(OnHandshakeDoneFunctor(connection_key, PROTECTION_ON)));

  // Listener check SSLContext
  EXPECT_CALL(session_observer_mock,
              GetSSLContext(connection_key, start_service)).
      // emulate protection for service is not enabled
      WillOnce(ReturnNull());

  // Expect service protection enable
  EXPECT_CALL(session_observer_mock,
              SetProtectionFlag(connection_key, start_service));

  // expect send Ack with PROTECTION_OFF (on fail handshake)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_ON))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_ON on session handshhake success
 */
TEST_F(ProtocolHandlerImplTest,
       SecurityEnable_StartSessionProtected_HandshakeSuccess_ServiceProtectedBefore) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // call new SSLContext creation
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return new SSLContext
      WillOnce(Return(&ssl_context_mock));

  // initilization check
  EXPECT_CALL(ssl_context_mock,
              IsInitCompleted()).
      //emulate SSL is not initilized
      WillOnce(Return(false));

  // Pending handshake check
  EXPECT_CALL(ssl_context_mock,
              IsHandshakePending()).
      //emulate is pending
      WillOnce(Return(true));

  // expect add listener for handshake result
  EXPECT_CALL(security_manager_mock,
              AddListener(_))
      // emulate handshake fail
      .WillOnce(Invoke(OnHandshakeDoneFunctor(connection_key, PROTECTION_ON)));

  // Listener check SSLContext
  EXPECT_CALL(session_observer_mock,
              GetSSLContext(connection_key, start_service)).
      // emulate protection for service is not enabled
      WillOnce(ReturnNull());

  // Expect service protection enable
  EXPECT_CALL(session_observer_mock,
              SetProtectionFlag(connection_key, start_service));

  // expect send Ack with PROTECTION_OFF (on fail handshake)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_ON))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
/*
 * ProtocolHandler shall send Ack with PROTECTION_ON on session handshhake success
 */
TEST_F(ProtocolHandlerImplTest,
       SecurityEnable_StartSessionProtected_HandshakeSuccess_SSLIsNotPending) {
  AddConnection();
  AddSecurityManager();
  const ServiceType start_service = kRpc;
  // expect ConnectionHandler check
  EXPECT_CALL(session_observer_mock,
              OnSessionStartedCallback(connection_id, NEW_SESSION_ID, start_service, PROTECTION_ON, _)).
      //return sessions start success
      WillOnce(Return(session_id));

  // call new SSLContext creation
  EXPECT_CALL(security_manager_mock,
              CreateSSLContext(connection_key)).
      //return new SSLContext
      WillOnce(Return(&ssl_context_mock));

  // initilization check
  EXPECT_CALL(ssl_context_mock,
              IsInitCompleted()).
      //emulate SSL is not initilized
      WillOnce(Return(false));

  // Pending handshake check
  EXPECT_CALL(ssl_context_mock,
              IsHandshakePending()).
      //emulate is pending
      WillOnce(Return(false));

  // Wait restart handshake operation
  EXPECT_CALL(security_manager_mock,
              StartHandshake(connection_key));

  // expect add listener for handshake result
  EXPECT_CALL(security_manager_mock,
              AddListener(_))
      // emulate handshake fail
      .WillOnce(Invoke(OnHandshakeDoneFunctor(connection_key, PROTECTION_ON)));

  // Listener check SSLContext
  EXPECT_CALL(session_observer_mock,
              GetSSLContext(connection_key, start_service)).
      // emulate protection for service is not enabled
      WillOnce(ReturnNull());

  // Expect service protection enable
  EXPECT_CALL(session_observer_mock,
              SetProtectionFlag(connection_key, start_service));

  // expect send Ack with PROTECTION_OFF (on fail handshake)
  EXPECT_CALL(transport_manager_mock,
              SendMessageToDevice(ControlMessage(FRAME_DATA_START_SERVICE_ACK, PROTECTION_ON))).
      WillOnce(Return(E_SUCCESS));

  SendControlMessage(PROTECTION_ON, start_service, NEW_SESSION_ID, FRAME_DATA_START_SERVICE);
}
TEST_F(ProtocolHandlerImplTest,
       FloodVerification) {
  const size_t period_msec = 1000;
  const size_t max_messages = 1000;
  IntitProtocolHandlerImpl(period_msec, max_messages);
  AddConnection();
  AddSession();

  // expect flood notification to CH
  EXPECT_CALL(session_observer_mock,
              OnApplicationFloodCallBack(connection_key)).
      Times(1);

  for (size_t i = 0; i < max_messages + 1; ++i) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_SINGLE,
                  kControl, FRAME_DATA_SINGLE, session_id,
                  some_date.size(), message_id, &some_date[0]);
  }
}
TEST_F(ProtocolHandlerImplTest,
       FloodVerification_ThresholdValue) {
  const size_t period_msec = 1000;
  const size_t max_messages = 1000;
  IntitProtocolHandlerImpl(period_msec, max_messages);
  AddConnection();
  AddSession();

  // expect NO flood notification to CH
  for (size_t i = 0; i < max_messages - 1; ++i) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_SINGLE,
                  kControl, FRAME_DATA_SINGLE, session_id,
                  some_date.size(), message_id, &some_date[0]);
  }
}
TEST_F(ProtocolHandlerImplTest,
       FloodVerification_VideoFrameSkip) {
  const size_t period_msec = 1000;
  const size_t max_messages = 1000;
  IntitProtocolHandlerImpl(period_msec, max_messages);
  AddConnection();
  AddSession();

  // expect NO flood notification to CH on video data streaming
  for (size_t i = 0; i < max_messages + 1; ++i) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_SINGLE,
                  kMobileNav, FRAME_DATA_SINGLE, session_id,
                  some_date.size(), message_id, &some_date[0]);
  }
}
TEST_F(ProtocolHandlerImplTest,
       FloodVerification_AudioFrameSkip) {
  const size_t period_msec = 1000;
  const size_t max_messages = 1000;
  IntitProtocolHandlerImpl(period_msec, max_messages);
  AddConnection();
  AddSession();

  // expect NO flood notification to CH on video data streaming
  for (size_t i = 0; i < max_messages + 1; ++i) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_SINGLE,
                  kAudio, FRAME_DATA_SINGLE, session_id,
                  some_date.size(), message_id, &some_date[0]);
  }
}
TEST_F(ProtocolHandlerImplTest,
       FloodVerificationDisable) {
  const size_t period_msec = 0;
  const size_t max_messages = 0;
  IntitProtocolHandlerImpl(period_msec, max_messages);
  AddConnection();
  AddSession();

  // expect NO flood notification to session observer
  for (size_t i = 0; i < max_messages + 1; ++i) {
    SendTMMessage(connection_id, PROTOCOL_VERSION_3, PROTECTION_OFF, FRAME_TYPE_SINGLE,
                  kControl, FRAME_DATA_SINGLE, session_id,
                  some_date.size(), message_id, &some_date[0]);
  }
}
#endif  // ENABLE_SECURITY
}  // namespace test
}  // namespace components
}  // namespace protocol_handler_test
#endif  //TEST_COMPONENTS_PROTOCOL_HANDLER_INCLUDE_PROTOCOL_HANDLER_PROTOCOL_HANDLER_TM_TEST_H_
