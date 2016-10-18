#include <Bridge.h>
#include <Mailbox.h>

unsigned long previousMillis = 0;
const long interval = 10000;
int previousLikesCount = 0;
Process twitter;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Bridge.begin();
  Bridge.put("1", "CultureID");
  Bridge.put("2", "cultureID");
  Serial.begin(9600);
  delay(1000);
  Mailbox.begin();
  // twitter.runShellCommandAsynchronously(F("python /socialEngine/motoreSociale.py"));
  twitter.runShellCommandAsynchronously(F("/socialEngine/startSocialEngine.sh"));
}

void loop() {
  if (Mailbox.messageAvailable())
  {
    // read all the messages present in the queue
    while (Mailbox.messageAvailable())
    {
      String message;
      Mailbox.readMessage(message);  // consume the Mailbox
      Serial.println(message);
    }
    giraRuote();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    Process fb;
    fb.runShellCommand(F("curl http://graph.facebook.com/toolboxcoworking?fields=likes"));
    int likesCount = fb.parseInt();

    if (previousLikesCount == 0)
      previousLikesCount = likesCount;

    int newLikes = likesCount - previousLikesCount;
    int likeSign = sign(newLikes);

    if (newLikes > 0)
      giraRuote();
    /*
    while (newLikes) {
      if (likeSign > 0) {
        Serial.println("Got new Like!");
        giraRuote();
      }
      else
        Serial.println("Someone left! :(");

      newLikes -= likeSign;

    }
    */
    Serial.print("likes count: ");
    Serial.println(likesCount);

    previousLikesCount = likesCount;
  }
}




int sign (int x) {
  return (x > 0) - (x < 0);
}

void giraRuote() {
  int delaylength = 40;
  for (int i = 0; i < 100; i++)
  {
    if ( i % 5 == 0)
    {
      delaylength -= 1;
    }

    digitalWrite(3, HIGH);
    digitalWrite(11, HIGH);

    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(12, HIGH);
    delay(delaylength);

    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(13, LOW);
    delay(delaylength);

    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(12, LOW);
    delay(delaylength);

    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(13, HIGH);
    delay(delaylength);
  }
  stop();
}

void stop() {
  digitalWrite(3, LOW);
  digitalWrite(11, LOW);

  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
}
