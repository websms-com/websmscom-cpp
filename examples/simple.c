/* Simple example sending a text message via the websms.com services. */

#include <stdio.h>
#include <string.h>

#include <websms/websms.h>

int main() {
  SmsClientContext* context;
  Int64Array* addresses;
  TextSmsSendRequest* request;
  int error_code;
  SmsSendResponse* response;

  printf("Sending text SMS using %s ...\n", Version());

  /* Create the context. */
  context = CreateSmsClientContext("user", "pass",
      "https://api.websms.com/json");

  /* Create new message with one recipient */
  addresses = CreateInt64Array(1);
  addresses->array[0] = 1234567;
  request = CreateTextSmsSendRequest();
  request->message_content = Strdup(UTF8("Hello World!"));
  request->recipient_address_list = addresses;
  request->test = 0;

  /* Send the message. */
  response = SendTextMessage(context, request, &error_code);

  if (error_code == 0) {
    /* Print the response. */
    printf("Status message: %s\nStatus code: %d\n",
           response->status_message,
           response->status_code);
  } else {
    /* Handle error */
    if (response != NULL) {
      fprintf(stderr, "Error: %s\n", response->status_message);
    } else {
      fprintf(stderr, "Error: %d\n", error_code);
    }
  }

  /* Free resources */
  FreeSmsSendResponse(response);
  FreeTextSmsSendRequest(request);
  FreeSmsClientContext(context);
  return 0;
}
