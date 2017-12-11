// A more complex example using multiple recipients, binary messages and threads.

#include <stdint.h>
#include <stdio.h>

#include <boost/thread.hpp>
#include <websms/websms.h>

// Typedef for callback functions
typedef void (*Callback)(const websms::MessageResponse& response);

// Function to be called when the send reqeuest was processed
void BinaryMessageProcessed(const websms::MessageResponse& response) {
  printf("Binary message processed - %s (%d) \n",
         response.status_message(),
         response.status_code());
}

// Class for sending a binary message
class SendBinaryMessage {
 public:
  SendBinaryMessage(websms::SmsClient* client, websms::BinaryMessage* message,
                    Callback callback)
      : client_(client),
        message_(message),
        callback_(callback) {
  }

  void operator()() {
    try {
      printf("Sending binary message ...\n");
      websms::MessageResponse response = client_->Send(*message_, false);
      callback_(response);
    } catch (const websms::Exception& e) {
      fprintf(stderr, "Exception: %s \n", e.What());
    }
  }

 private:
  websms::SmsClient* client_;
  websms::BinaryMessage* message_;
  Callback callback_;
};

int main() {
  using namespace websms;

  // Create client
  SmsClient client("user", "password", "https://api.websms.com/json");

  // Create vector with multiple recipients.
  AddressList recipients(3);
  recipients[0] = 1000001;
  recipients[1] = 1000002;
  recipients[2] = 1000003;

  // Binary message - Create concatenated SMS using a user data header
  // (http://en.wikipedia.org/wiki/Concatenated_SMS)
  uint8_t data1[] = { 0x05, 0x00, 0x03, 0xCC, 0x02, 0x01, 'H', 'e', 'l', 'l',
      'o', ' ' };
  uint8_t data2[] = { 0x05, 0x00, 0x03, 0xCC, 0x02, 0x02, 'W', 'o', 'r', 'l',
      'd', '!' };
  BinaryData binary_content(2);
  binary_content.Set(0, data1, 12);
  binary_content.Set(1, data2, 12);

  BinaryMessage binary_message(recipients, binary_content);
  binary_message.set_user_data_header_present(true);

  // Starting send request in background
  boost::thread thread(
      SendBinaryMessage(&client, &binary_message, &BinaryMessageProcessed));

  // Do something else...

  thread.join();
  return 0;
}
