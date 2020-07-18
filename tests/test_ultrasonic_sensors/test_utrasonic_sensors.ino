const int trig_pin[] = {22, 24, 26, 28};
const int echo_pin[] = {23, 25, 27, 29};

long duration[4];
int distance[4];

unsigned long time;

void setup() {
    for (int i=0; i<4; i++) {
        pinMode(trig_pin[i], OUTPUT);
        pinMode(echo_pin[i], INPUT);
    }

    Serial.begin(115200);

    time = millis();
}

void loop() {
    for (int i=0; i<4; i++) {
        // Send a 10ms pulse
        digitalWrite(trig_pin[i], HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_pin[i], LOW);

        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration[i] = pulseIn(echo_pin[i], HIGH);
        // Calculating the distance
        distance[i] = duration[i]*0.034/2;

        // Prints the distance on the Serial Monitor
        Serial.print("Distance ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(distance[i]);
    }
    Serial.print("Elapsed time: ");
    Serial.println(millis() - time);
    time = millis();
}