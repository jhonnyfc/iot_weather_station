int previousSeconds = 0;
unsigned long currentSeconds;
unsigned long diffTime;

void saveTick() {
  previousSeconds = currentSeconds;
}

bool isTick() {
  currentSeconds = millis() / 1000;

  if (ZERO_SECONDS <= currentSeconds && currentSeconds < UL_MAX_VALUE) {
    diffTime = currentSeconds - previousSeconds;
  } else {
    diffTime = 0;
  }

  if (diffTime < ZERO_SECONDS) {
    diffTime = UL_MAX_VALUE + diffTime + 1;
  }

  return diffTime >= ONE_SECOND;
}

int getDiff() {
  return diffTime;
}