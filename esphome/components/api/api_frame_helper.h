#pragma once
#include <cstdint>
#include <deque>
#include <utility>
#include <vector>

#include "esphome/core/defines.h"
#ifdef USE_API
#ifdef USE_API_NOISE
#include "noise/protocol.h"
#endif

#include "api_noise_context.h"
#include "esphome/components/socket/socket.h"

namespace esphome {
namespace api {

struct ReadPacketBuffer {
  std::vector<uint8_t> container;
  uint16_t type;
  size_t data_offset;
  size_t data_len;
};

struct PacketBuffer {
  const std::vector<uint8_t> container;
  uint16_t type;
  uint8_t data_offset;
  uint8_t data_len;
};

enum class APIError : int {
  OK = 0,
  WOULD_BLOCK = 1001,
  BAD_HANDSHAKE_PACKET_LEN = 1002,
  BAD_INDICATOR = 1003,
  BAD_DATA_PACKET = 1004,
  TCP_NODELAY_FAILED = 1005,
  TCP_NONBLOCKING_FAILED = 1006,
  CLOSE_FAILED = 1007,
  SHUTDOWN_FAILED = 1008,
  BAD_STATE = 1009,
  BAD_ARG = 1010,
  SOCKET_READ_FAILED = 1011,
  SOCKET_WRITE_FAILED = 1012,
  HANDSHAKESTATE_READ_FAILED = 1013,
  HANDSHAKESTATE_WRITE_FAILED = 1014,
  HANDSHAKESTATE_BAD_STATE = 1015,
  CIPHERSTATE_DECRYPT_FAILED = 1016,
  CIPHERSTATE_ENCRYPT_FAILED = 1017,
  OUT_OF_MEMORY = 1018,
  HANDSHAKESTATE_SETUP_FAILED = 1019,
  HANDSHAKESTATE_SPLIT_FAILED = 1020,
  BAD_HANDSHAKE_ERROR_BYTE = 1021,
  CONNECTION_CLOSED = 1022,
};

const char *api_error_to_str(APIError err);

class APIFrameHelper {
 public:
  virtual ~APIFrameHelper() = default;
  virtual APIError init() = 0;
  virtual APIError loop() = 0;
  virtual APIError read_packet(ReadPacketBuffer *buffer) = 0;
  virtual bool can_write_without_blocking() = 0;
  virtual APIError write_packet(uint16_t type, const uint8_t *data, size_t len) = 0;
  virtual std::string getpeername() = 0;
  virtual int getpeername(struct sockaddr *addr, socklen_t *addrlen) = 0;
  virtual APIError close() = 0;
  virtual APIError shutdown(int how) = 0;
  // Give this helper a name for logging
  virtual void set_log_info(std::string info) = 0;

 protected:
  // Common implementation for writing raw data to socket
  template<typename StateEnum>
  APIError write_raw_(const struct iovec *iov, int iovcnt, socket::Socket *socket, std::vector<uint8_t> &tx_buf_,
                      const std::string &info, StateEnum &state, StateEnum failed_state) {
    // This method writes data to socket or buffers it
    // Returns APIError::OK if successful (or would block, but data has been buffered)
    // Returns APIError::SOCKET_WRITE_FAILED if socket write failed, and sets state to failed_state

    if (iovcnt == 0)
      return APIError::OK;  // Nothing to do, success

    size_t total_write_len = 0;
    for (int i = 0; i < iovcnt; i++) {
#ifdef HELPER_LOG_PACKETS
      ESP_LOGVV(TAG, "Sending raw: %s",
                format_hex_pretty(reinterpret_cast<uint8_t *>(iov[i].iov_base), iov[i].iov_len).c_str());
#endif
      total_write_len += iov[i].iov_len;
    }

    if (!tx_buf_.empty()) {
      // try to empty tx_buf_ first
      // Try send from tx_buf_
      while (!tx_buf_.empty()) {
        ssize_t sent = socket->write(tx_buf_.data(), tx_buf_.size());
        if (is_would_block(sent)) {
          break;
        } else if (sent == -1) {
          ESP_LOGVV(TAG, "%s: Socket write failed with errno %d", info.c_str(), errno);
          state = failed_state;
          return APIError::SOCKET_WRITE_FAILED;  // Socket write failed
        }
        // TODO: inefficient if multiple packets in txbuf
        // replace with deque of buffers
        tx_buf_.erase(tx_buf_.begin(), tx_buf_.begin() + sent);
      }
    }

    if (!tx_buf_.empty()) {
      // tx buf not empty, can't write now because then stream would be inconsistent
      // Reserve space upfront to avoid multiple reallocations
      tx_buf_.reserve(tx_buf_.size() + total_write_len);
      for (int i = 0; i < iovcnt; i++) {
        tx_buf_.insert(tx_buf_.end(), reinterpret_cast<uint8_t *>(iov[i].iov_base),
                       reinterpret_cast<uint8_t *>(iov[i].iov_base) + iov[i].iov_len);
      }
      return APIError::OK;  // Success, data buffered
    }

    ssize_t sent = socket->writev(iov, iovcnt);
    if (is_would_block(sent)) {
      // operation would block, add buffer to tx_buf_
      // Reserve space upfront to avoid multiple reallocations
      tx_buf_.reserve(tx_buf_.size() + total_write_len);
      for (int i = 0; i < iovcnt; i++) {
        tx_buf_.insert(tx_buf_.end(), reinterpret_cast<uint8_t *>(iov[i].iov_base),
                       reinterpret_cast<uint8_t *>(iov[i].iov_base) + iov[i].iov_len);
      }
      return APIError::OK;  // Success, data buffered
    } else if (sent == -1) {
      // an error occurred
      ESP_LOGVV(TAG, "%s: Socket write failed with errno %d", info.c_str(), errno);
      state = failed_state;
      return APIError::SOCKET_WRITE_FAILED;  // Socket write failed
    } else if ((size_t) sent != total_write_len) {
      // partially sent, add end to tx_buf_
      size_t remaining = total_write_len - sent;
      // Reserve space upfront to avoid multiple reallocations
      tx_buf_.reserve(tx_buf_.size() + remaining);

      size_t to_consume = sent;
      for (int i = 0; i < iovcnt; i++) {
        if (to_consume >= iov[i].iov_len) {
          to_consume -= iov[i].iov_len;
        } else {
          tx_buf_.insert(tx_buf_.end(), reinterpret_cast<uint8_t *>(iov[i].iov_base) + to_consume,
                         reinterpret_cast<uint8_t *>(iov[i].iov_base) + iov[i].iov_len);
          to_consume = 0;
        }
      }
      return APIError::OK;  // Success, data buffered
    }
    // fully sent
    return APIError::OK;  // Success, all data sent
  }
};

#ifdef USE_API_NOISE
class APINoiseFrameHelper : public APIFrameHelper {
 public:
  APINoiseFrameHelper(std::unique_ptr<socket::Socket> socket, std::shared_ptr<APINoiseContext> ctx)
      : socket_(std::move(socket)), ctx_(std::move(std::move(ctx))) {}
  ~APINoiseFrameHelper() override;
  APIError init() override;
  APIError loop() override;
  APIError read_packet(ReadPacketBuffer *buffer) override;
  bool can_write_without_blocking() override;
  APIError write_packet(uint16_t type, const uint8_t *payload, size_t len) override;
  std::string getpeername() override { return this->socket_->getpeername(); }
  int getpeername(struct sockaddr *addr, socklen_t *addrlen) override {
    return this->socket_->getpeername(addr, addrlen);
  }
  APIError close() override;
  APIError shutdown(int how) override;
  // Give this helper a name for logging
  void set_log_info(std::string info) override { info_ = std::move(info); }

 protected:
  struct ParsedFrame {
    std::vector<uint8_t> msg;
  };

  APIError state_action_();
  APIError try_read_frame_(ParsedFrame *frame);
  APIError try_send_tx_buf_();
  APIError write_frame_(const uint8_t *data, size_t len);
  inline APIError write_raw_(const struct iovec *iov, int iovcnt) {
    return APIFrameHelper::write_raw_(iov, iovcnt, socket_.get(), tx_buf_, info_, state_, State::FAILED);
  }
  APIError init_handshake_();
  APIError check_handshake_finished_();
  void send_explicit_handshake_reject_(const std::string &reason);

  std::unique_ptr<socket::Socket> socket_;

  std::string info_;
  uint8_t rx_header_buf_[3];
  size_t rx_header_buf_len_ = 0;
  std::vector<uint8_t> rx_buf_;
  size_t rx_buf_len_ = 0;

  std::vector<uint8_t> tx_buf_;
  std::vector<uint8_t> prologue_;

  std::shared_ptr<APINoiseContext> ctx_;
  NoiseHandshakeState *handshake_{nullptr};
  NoiseCipherState *send_cipher_{nullptr};
  NoiseCipherState *recv_cipher_{nullptr};
  NoiseProtocolId nid_;

  enum class State {
    INITIALIZE = 1,
    CLIENT_HELLO = 2,
    SERVER_HELLO = 3,
    HANDSHAKE = 4,
    DATA = 5,
    CLOSED = 6,
    FAILED = 7,
    EXPLICIT_REJECT = 8,
  } state_ = State::INITIALIZE;
};
#endif  // USE_API_NOISE

#ifdef USE_API_PLAINTEXT
class APIPlaintextFrameHelper : public APIFrameHelper {
 public:
  APIPlaintextFrameHelper(std::unique_ptr<socket::Socket> socket) : socket_(std::move(socket)) {}
  ~APIPlaintextFrameHelper() override = default;
  APIError init() override;
  APIError loop() override;
  APIError read_packet(ReadPacketBuffer *buffer) override;
  bool can_write_without_blocking() override;
  APIError write_packet(uint16_t type, const uint8_t *payload, size_t len) override;
  std::string getpeername() override { return this->socket_->getpeername(); }
  int getpeername(struct sockaddr *addr, socklen_t *addrlen) override {
    return this->socket_->getpeername(addr, addrlen);
  }
  APIError close() override;
  APIError shutdown(int how) override;
  // Give this helper a name for logging
  void set_log_info(std::string info) override { info_ = std::move(info); }

 protected:
  struct ParsedFrame {
    std::vector<uint8_t> msg;
  };

  APIError try_read_frame_(ParsedFrame *frame);
  APIError try_send_tx_buf_();
  inline APIError write_raw_(const struct iovec *iov, int iovcnt) {
    return APIFrameHelper::write_raw_(iov, iovcnt, socket_.get(), tx_buf_, info_, state_, State::FAILED);
  }

  std::unique_ptr<socket::Socket> socket_;

  std::string info_;
  std::vector<uint8_t> rx_header_buf_;
  bool rx_header_parsed_ = false;
  uint32_t rx_header_parsed_type_ = 0;
  uint32_t rx_header_parsed_len_ = 0;

  std::vector<uint8_t> rx_buf_;
  size_t rx_buf_len_ = 0;

  std::vector<uint8_t> tx_buf_;

  enum class State {
    INITIALIZE = 1,
    DATA = 2,
    CLOSED = 3,
    FAILED = 4,
  } state_ = State::INITIALIZE;
};
#endif

}  // namespace api
}  // namespace esphome
#endif
