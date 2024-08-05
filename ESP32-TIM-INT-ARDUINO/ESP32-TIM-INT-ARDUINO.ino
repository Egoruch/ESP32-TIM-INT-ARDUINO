/* Hardware Timer Interrupt ESP32 (No RTOS) */

bool timer_flag = false;

hw_timer_t *timer = NULL;

#define GPIO_PIN 48

void setup() {

  Serial.begin(115200);

  pinMode(GPIO_PIN, OUTPUT);

  Timer_Init();

  Serial.println("Start");
}

void loop() {

if(timer_flag == true)
{
  static uint8_t toggle = 0;

  if(toggle)
  {
    digitalWrite(GPIO_PIN, HIGH);

  }else
  {
    digitalWrite(GPIO_PIN, LOW);

  }

  toggle = ~toggle;

  timer_flag = false;
}

/*---- loop end ----*/
}

/* Timer Interrupt Handler */
void ARDUINO_ISR_ATTR onTimer() {

  if(timer_flag == false)
  {
    timer_flag = true;
  }

}

void Timer_Init(void)
{
  // Set timer frequency
  timer = timerBegin(1000000);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
  timerAlarm(timer, 200, true, 0);

}
