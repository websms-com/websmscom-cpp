// Simple example sending a text message via the websms.com services.

#include <stdio.h>
#include <iostream>

#include <websms/websms.h>

int main() {

  using namespace websms;
  printf("Sending text SMS using %s ...\n", Version());

  // Create the client.
  SmsClient client("user", "password", "https://api.websms.com/json");
  // Create new message with one recipient. You can also address multiple
  // recipients by passing in a vector.
  TextMessage message(1234567, UTF8("Hello World!"));

  try {
    // Send the message.
    MessageResponse response = client.Send(message,
                                           1,      // Max. sms per message
                                           false);  // Test message?
    // Print the response.
    printf("Status message: %s\nStatus code: %d\n",
           response.status_message(),
           response.status_code());

  } catch (const Exception& e) {
    // Handle exceptions.
    fprintf(stderr, "Exception: %s \n", e.What());
  }

  return 0;
}
